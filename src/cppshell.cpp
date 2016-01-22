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

namespace cppshell {

using namespace std;

cmd::cmd(const std::string& command, bool throws) try:
  output_{},
  exit_code_{},
  pipe_{command}
{
  while(pipe_.read()) output_ += pipe_.str();
  auto status = pipe_.close();
  exit_code_ = WEXITSTATUS(status);
  if(exit_code_ != 0 && throws) throw cmd_exception(command, output_, exit_code_);
} catch(const pipe_exception& e) {
  if (throws) throw cmd_exception(command, output_, exit_code_);
  std::cerr << e.what() << '\n';
}

const string& cmd::str() const noexcept {
  return output_;
}

bool cmd::ok() const noexcept { 
  return !exit_code_;
}

ostream& operator<<(ostream& str, const cmd& sh) {
  return str << sh.output_;
};

cmd_exception::cmd_exception(const string& command, const string& output, int code) :
  runtime_error{"Command '" + command + "' returned error: " + to_string(code) + " " + output},
  exit_code_   {code}
{}

cmd_exception::cmd_exception(const string& what, int code) :
  runtime_error{what},
  exit_code_   {code}
{}

int cmd_exception::exit_code() const noexcept {
  return exit_code_;
}

} //< namespace cppshell
