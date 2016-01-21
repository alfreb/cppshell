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

#ifndef SUBPROCESS_HPP
#define SUBPROCESS_HPP

#include <string>
#include <future>
#include <vector>

// For fork and wait
#include <sys/types.h>
#include <sys/wait.h>

namespace cppshell{
  
/** 
    A simple class to start and read from a subprocess 
 */
class subprocess {
public:
  // Construct with a list of parameters, the program being the first
  // @note: uses execvp and passes arg[0] as first and second arg)
  subprocess(const std::vector<std::string>& args);

  subprocess(std::initializer_list<std::string> args) :
    subprocess(std::vector<std::string>{args})
  {}

  ~subprocess();

  int stdout() const noexcept
  { return pipes_[OUT_READ]; }

  int stdin() const noexcept
  { return pipes_[IN_WRITE]; }

  int pid() const noexcept
  { return pid_; }

  std::string getline();
  std::string read(int n);
  
  subprocess& write(const std::string&);
  
  // i.e. Kill -9
  void kill();
private:
  int              pipes_[4];
  pid_t            pid_;
  std::string      output_;
  std::future<int> exit_status_;

  enum {OUT_READ, OUT_WRITE, IN_READ, IN_WRITE};
}; //< class subprocess

/** 
    Read from stdout of the process, until EOF. 
    NOTE: If you want partial output, read from 
          subprocess::stdout().
 */
std::ostream& operator<<(std::ostream&, subprocess&);

class subprocess_exception : public std::runtime_error {
  using runtime_error::runtime_error;
}; //< class subprocess_exception
  
} //< namespace cppshell

#endif //< SUBPROCESS_HPP
