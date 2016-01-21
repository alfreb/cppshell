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

#include <cstdio>

#include "pipe.hpp"

namespace cppshell {

pipe::pipe(const std::string& command) :
  pipe_{popen(command.c_str(), "r")},
  closed_{false}
{
  if (!pipe_) throw pipe_exception{"Couldn't open pipe."};
}

pipe::~pipe() noexcept {
  if (!closed_)
    if (pclose(pipe_) == -1) {
      perror("pclose");
      exit(EXIT_FAILURE);
    }
}

bool pipe::read() {
  return fgets(buffer_.data(), buffer_.size(), pipe_) != nullptr;
}

std::string pipe::str() const {
  return std::string{buffer_.data()};
}

int pipe::close() {
  auto pclose_status = pclose(pipe_);
  return pclose_status == -1 ? pclose_status : closed_ = true, pclose_status;
}

pipe_exception::pipe_exception(const std::string& what) :
  std::runtime_error{what}
{}

} //< namespace cppshell
