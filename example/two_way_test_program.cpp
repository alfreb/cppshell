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

using namespace std;

int main() {
  cout << "Two way test " << endl;
  cout << "Line 1 to ignore" << endl;
  cout << "Line 2 to ignore" << endl;
  cout << "Line 3 to ignore" << endl;

  string s;
  
  do {
    cout << "Now please give me some data: ";
    if (!cin) break;
    cin >> s;
    cout << (s != "data" ? "UNKNOWN" : "OK") << endl;
  } while (s != "data");
  
  cout << "Exit" << endl;
}
