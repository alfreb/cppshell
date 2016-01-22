/**
    This file is part of cppshell.
    Copyright (C) 2015 Alfred Bratterud

    cppshell is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cppshell is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cppshell.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <unistd.h>
#include <iostream>

#include "subprocess.hpp"

namespace cppshell {

using namespace std;

subprocess::subprocess(const vector<string>& args) {
  // Create pipe - a read and a write end
  if (pipe(pipes_) == -1)   throw runtime_error{"stdout-pipe"};

  if (pipe(pipes_ + 2) == -1) throw runtime_error{"stdin-pipe"};
  
  // Create the argument list to exec
  // Note: This only have to live until picked up by exec, so stack OK
  char* arr[args.size() + 1];
  int i=0;
  for(const auto& arg : args) arr[i++] = const_cast<char*>(arg.c_str());

  // Last element is a null-pointer
  arr[args.size()] = nullptr;
    
  // FORK!
  if ((pid_ = fork()) < 0) throw runtime_error{"fork"};
  
  if(pid_ == 0) { // Child
    // Redirect stdout to the "write" side of the pipe
    dup2 (pipes_[OUT_WRITE], STDOUT_FILENO);
    dup2 (pipes_[IN_READ], STDIN_FILENO);
    
    // Close the read side (Parent uses it)
    close(pipes_[OUT_READ]);
      
    //Execute
    execvp(arr[0], static_cast<char* const*>(arr));
    throw runtime_error{"execl returned. It means it failed."};
  } else { // Parent
    // Close the write side (Child uses it)
    close(pipes_[OUT_WRITE]);
    
    // We have to keep the future - if it goes out of scope it blocks
    exit_status_ = std::async(std::launch::async, [this] {
        // Wait for the child, save the exit status
        int ret; 
        int res;
        if((res = waitpid(pid_, &ret, 0)) < 0)
          throw runtime_error{"Error waiting for child: " + to_string(res)};
        return ret;
      });
  }
}

subprocess::~subprocess() {
  close(pipes_[OUT_READ]);
  close(pipes_[OUT_WRITE]);
  close(pipes_[IN_READ]);
  close(pipes_[IN_WRITE]);
  kill();
}

string subprocess::read(int n) {
  string   in;
  char c   {};
  int  i   {};
  int  res {};
  do {    
    res = ::read(stdout(), &c, 1);
    if (res < 1)
      throw subprocess_exception{"No output from process, while read"};    
    in += c;
  } while(++i < n && res);
  return in;
}

subprocess& subprocess::write(const string& str) {  
  ::write(stdin(), static_cast<const void*>(str.c_str()), str.size());
  return *this;
}

string subprocess::getline() {
  char   c   {};
  int    res {};
  string in  {};
  do {
    res = ::read(stdout(), &c, 1);
    if (res < 1)
      throw subprocess_exception{"No output from process"};
    in += c;
  }while(c != '\n' && res);
  return in;
}

void subprocess::kill() {
  ::kill(pid_, SIGKILL);
}

ostream& operator<<(ostream& str, subprocess& proc) {
  char buf[4096] {0};
  while(read(proc.stdout(), buf, 4096)) str << buf;
  return str;
}

} //< namespace cppshell
