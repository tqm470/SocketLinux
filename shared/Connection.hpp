#pragma once
#define message_max 1024
#include <memory>
#include <string>
#include <netinet/in.h>

class Connection
{
  public:
    class Message
    {
      public:
        Message( int size, std::shared_ptr<char> data )
          : size( size ), data( data )
          {}
        int size;
        std::shared_ptr<char> data;
    };
  public:
    Connection() = delete;
    Connection( int sockfd, sockaddr_in* client_addr, socklen_t* clilen );
    int Send( const Message& msg ) const;
    int Send( const std::string msg ) const;
    Message Get() const;
    ~Connection();
  private:
    int sockfd;
    socklen_t* addrlen;
    sockaddr_in* addr;
};