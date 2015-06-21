#include <iostream>

using namespace std;


int main(){
  
  
  cout << "Two way test " << endl;
  cout << "Line 1 to ignore" << endl;
  cout << "Line 2 to ignore" << endl;
  cout << "Line 3 to ignore" << endl;
  
  
  
  string s;
  
  do{
    
    cout << "Now please give me some data: ";
    
    if (!cin.good())
      break;
    
    cin >> s;
      	
    cout << (s!="data" ? "UNKNOWN" : "OK") << endl;
    
  }while (s != "data");
  
  cout << "Exit" << endl;
}
