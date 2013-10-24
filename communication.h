#ifndef communication_h
#define communication_h

#include <string>



using namespace std;



class Communication {
  public:
    Communication();
    void Listen();
    void Send(string *);
};


#endif
