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

#include "pipe.hpp"

namespace cppshell {
  
class cmd {  
public:
  cmd(const std::string& command, bool throws = true);
  ~cmd() noexcept = default;
  
  bool ok() const noexcept;
  const std::string& str() const noexcept;

private:
  std::string command_;
  std::string output_;
  int         exit_code_;
  pipe        pipe_;

  friend std::ostream& operator<<(std::ostream&, const cmd&);
}; //< class cmd

class cmd_exception : public std::runtime_error {
public:
  cmd_exception(const std::string& command, const std::string& output, int exit);
  cmd_exception(const std::string& output, int exit);
  
  int exit_code() const noexcept;

private:
  int exit_code_;
}; //< class cmd_exception

} //< namespace cppshell
  
#endif //< CPPSHELL_HPP
