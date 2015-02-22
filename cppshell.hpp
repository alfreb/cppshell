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


