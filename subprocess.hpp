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
  class subprocess{
    enum{READ,WRITE};
    int link[2];
    pid_t pid_;
    std::string output;
    std::future<int> exit_status_;
  public:
    
    subprocess(std::vector<std::string> args);
    inline subprocess(std::initializer_list<std::string> args) 
      : subprocess(std::vector<std::string>(args)) {}
    inline int stdout(){return link[READ] ;}
    inline int pid(){ return pid_; }
    
  };
  
  /** 
      Read from stdout of the process, until EOF. 
      NOTE: If you want partial output, read from 
            subprocess::stdout().
   */
  std::ostream& operator<<(std::ostream&,subprocess&);
}

#endif
