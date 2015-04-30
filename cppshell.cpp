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

#include <iostream>
#include <unistd.h>
#include "cppshell.hpp"


using namespace std;
using namespace cppshell;

cmd::cmd(string command, bool throws) : command_(command){
  char line[500];
  if ( !(pipe_ = (FILE*)popen(command.c_str(),"r")) )
    throw cmdException("Couldn't open pipe.",(long)pipe_);
  
  while( fgets(line, sizeof line, pipe_))
    output_.append(line);   
  
  int status = pclose(pipe_);
  exit_code_ = WEXITSTATUS(status);
  if(exit_code_ != 0 && throws)
    throw cmdException(command_, output_, exit_code_);
}

cmd::~cmd(){
  // Closing is allready done in the constructor
  // pclose(pipe_); 
}


string cmd::str(){ return output_; }

bool cmd::ok(){ return exit_code_ == 0; }

ostream& cppshell::operator<<(ostream& str,cmd sh){
  return str << sh.output_;
};


/** CMD EXCEPTION */
cmdException::cmdException(string command, string output,int code)
  : runtime_error{"Command '"+command+"' returned error: "
    +to_string(code)+" "+output},
                exit_code_(code)
{}

cmdException::cmdException(string what,int code)
  : runtime_error{what},exit_code_(code)
{}


int cmdException::exit_code(){ return exit_code_; }
