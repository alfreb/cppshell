#include "cppshell.hpp"
#include <iostream>

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
}
