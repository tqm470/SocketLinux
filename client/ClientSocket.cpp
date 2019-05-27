#include "ClientSocket.hpp"
#include <string.h>
#include <netdb.h>

Connection ClientSocket::Connect( const std::string hostname, const int porta )
{
  int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
  struct hostent *server;
  struct sockaddr_in* server_addr = new sockaddr_in;
  socklen_t* serverlen = new socklen_t;
  server = gethostbyname( hostname.c_str() );
  if( server == NULL )
  {
    throw( "Erro, host não existe." );
  }
  bzero( (char*) server_addr, sizeof( *server_addr ) );
  server_addr->sin_family = AF_INET;
  bcopy( (char*) server->h_addr, (char*) &server_addr->sin_addr.s_addr, server->h_length );
  server_addr->sin_port = htons( porta );
  *serverlen = sizeof( *server_addr );
  if( connect(sockfd, (struct sockaddr*) server_addr, *serverlen ) < 0 )
  {
    throw( "Erro ao conectar ao host!" );
  }
  return Connection( sockfd, server_addr, serverlen );
}