#include <communication.h>


int main()
{
  Communication *comm = new Communication(3310);
  char *msg;
  while(1)
  {
    msg = comm->Listen();
    printf("MSG = %s\n", msg);
  }
  return 0;
}

