#include "ServerSocket.hpp"
#include <string.h>
#include <unistd.h>

ServerSocket::ServerSocket( int porta )
  :
  porta( porta )
{
  sockfd = socket( AF_INET, SOCK_STREAM, 0 );
  if( sockfd < 0 )
  {
    throw( "Erro ao abrir o socket" );
  }
  bzero( (char *) &serv_addr, sizeof( serv_addr ) );
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons( porta );
  if( bind( sockfd, (const sockaddr*) &serv_addr, sizeof( serv_addr )) < 0 )
  {
    throw( "Erro ao vincular o socket!" );
  }
}

void ServerSocket::Listen( int n )
{
  listen( sockfd, n );
}

Connection ServerSocket::Accept()
{
  struct sockaddr_in* client_addr = new sockaddr_in;
  socklen_t* clilen = new socklen_t;
  *clilen = sizeof(*client_addr);
  int newsockfd = accept( sockfd, (struct sockaddr*) client_addr, clilen );
  return Connection( newsockfd, client_addr, clilen );
}

ServerSocket::~ServerSocket()
{
  close( sockfd );
}