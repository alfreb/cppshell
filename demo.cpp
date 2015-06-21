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

#include "cppshell.hpp"
#include "subprocess.hpp"


using namespace std;


int main(){
  try{
           
    cout << endl << "Running : ls -l" << endl;
    
    // Simplest possible
    cout << cppshell::cmd{"ls -l"} << endl;
    
    
    string command = "whoami";
    cout << endl << "Running : " << command << endl;    
    // Store output in a string
    string user = cppshell::cmd{command}.str();
    cout << "Returned: " << user << endl;

    // Call - and don't throw if command failed, to inspect return value
    command = "pwdz";
    cout << endl << "Running : " << command << endl;
    cppshell::cmd res{command,0};
    cout << (res.ok() ? "Output: "+res.str() : "Command failed!" )<< endl;
    
    // Run a malformed command - which throws    
    command = "wtf";
    cout << endl << "Running : " << command << endl;
    cout << cppshell::cmd{command} << endl;

    
  }catch(cppshell::cmdException e){
    cout << "cmdException thrown: " << e.what() << endl << endl;
  }

  // Running a subprocess
  cppshell::subprocess proc{"ls","-l"};
  cout << "The subprocess runs in a separate thread. output:" << endl;
  for(int i=0;i<3; i++)
    cout << "Line " << i << ": " << proc.getline();
  cout << "The rest: " << endl;
  cout << proc << endl;

  
  cout << "Starting a two-way dialogue" << endl;
  cppshell::subprocess proc2{"./two_way_test_program"};
  for(int i=0;i<4; i++)
    cout << "Line " << i << ": " << proc2.getline();

  // Read "Now give me some data"  
  cout << proc2.read(30) << endl;
  
  proc2.write("Hello\n");
  cout << proc2.getline() << endl;
  proc2.write("data\n");
  cout << proc2.getline() << endl;
  
  
  
}
