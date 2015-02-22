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

#ifndef CPPSHELL_HPP
#define CPPSHELL_HPP

#include <string>
#include <stdexcept>

namespace cppshell {
  
  class cmd{  
    int exit_code_;
    std::string command_;
    std::string output_;
    FILE* pipe_{nullptr};
    
  public:
    cmd(std::string command, bool throws = true);
    ~cmd();
    
    bool ok();
    std::string str();
    friend std::ostream& operator<<(std::ostream&,cmd);
    
  };
  
  std::ostream& operator<<(std::ostream&,cmd);
  
  class cmdException : public std::runtime_error {
    int exit_code_;
  public:
    cmdException(std::string command, std::string output, int exit);
    cmdException(std::string output, int exit);
    
    int exit_code();
  };
}
  
#endif


