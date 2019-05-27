#pragma once
#include "../shared/Connection.hpp"
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

class ServerSocket
{
  public:
    ServerSocket( int porta );
  public:
    void Listen( int n );
    Connection Accept();
    ~ServerSocket();
  private:
    int porta;
    int sockfd;
    struct sockaddr_in serv_addr;
};