#ifndef SUBPROCESS_HPP
#define SUBPROCESS_HPP

#include <string>
#include <future>
#include <vector>

// For fork and wait
#include <sys/types.h>
#include <sys/wait.h>



namespace cppshell{

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
}

#endif
