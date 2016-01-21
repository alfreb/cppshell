/**
    This file is part of cppshell.
    Copyright (C) 2016 Rico Antonio Felix

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

#ifndef PIPE_HPP
#define PIPE_HPP

#include <array>
#include <string>
#include <stdexcept>

namespace cppshell {

class pipe {
public:
  explicit pipe(const std::string& command);
  ~pipe() noexcept;

  bool read();
  std::string str() const;
  int close();
private:
  FILE*                 pipe_;
  std::array<char, 512> buffer_;
  bool                  closed_;
}; // class pipe

class pipe_exception : public std::runtime_error {
public:
  explicit pipe_exception(const std::string& what);
}; // class pipe_exception

} //< namespace cppshell

#endif //< PIPE_HPP
