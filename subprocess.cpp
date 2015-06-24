#include "subprocess.hpp"

#include <unistd.h>
#include <iostream>

using namespace std;
using namespace cppshell;

subprocess::subprocess(vector<std::string> args){
        
  // Create pipe - a read and a write end
  if (pipe(pipes)==-1)
    throw runtime_error("stdout-pipe");

  if (pipe(pipes+2)==-1)
    throw runtime_error("stdin-pipe");
  
  // Create the argument list to exec
  // Note: This only have to live until piced up by exec, so stack OK
  char* arr[args.size()+1];
  int i=0;
  for(auto str : args)
    arr[i++]=(char*)str.c_str();
  // Last element is a null-pointer
  arr[args.size()]=0;
    
  // FORK!
  if ((pid_ = fork()) < 0)
    throw runtime_error("fork");

  // Child
  if(pid_ == 0) {

    // Redirect stdout to the "write" side of the pipe
    dup2 (pipes[OUT_WRITE], STDOUT_FILENO);
    dup2 (pipes[IN_READ],STDIN_FILENO);
    
    // Close the read side (Parent uses it)
    close(pipes[OUT_READ]);
      
    //Execute
    execvp(arr[0], (char* const*)arr);
    throw runtime_error("execl returned. It means it failed.");
      
    // Parent
  } else {

    // Close the write side (Child uses it)
    close(pipes[OUT_WRITE]);
    
    // We have to keep the future - if it goes out of scope it blocks
    exit_status_=std::async(std::launch::async,[&]{
	
        // Wait for the child, save the exit status
        int ret; 
        int res;
        if((res=waitpid(pid_, &ret, 0)) < 0)
          throw runtime_error("Error waiting for child: "+to_string(res));
        return ret;
      });
  }
}


string subprocess::read(int n){
  string in;
  char c{};
  int res{},i{0};
  do {    
    res=::read(stdout(),&c,1);
    if (res < 1)
      throw SubprocessException("No output from process, while read");    
    in += c;
  }while(++i < n && res);
  return in;
}

void subprocess::write(string str){  
  ::write(stdin(), (void*)str.c_str(), str.size());  
}


string subprocess::getline(){
  string in{};
  char c{};
  int res{};
  do{
    res=::read(stdout(),&c,1);
    if (res < 1)
      throw SubprocessException("No output from process");
    in += c;
  }while(c!='\n' && res);
  
  return in;
}


void subprocess::kill(){
  ::kill(pid_,SIGKILL);
}


subprocess::~subprocess(){
  close(pipes[OUT_READ]);
  close(pipes[OUT_WRITE]);
  close(pipes[IN_READ]);
  close(pipes[IN_WRITE]);
  this->kill();
}



ostream& cppshell::operator<<(ostream& str,subprocess& proc){
  char buf[4096]{0};
  
  while(read(proc.stdout(),buf,4096))
    str << buf;
  return str;
}

