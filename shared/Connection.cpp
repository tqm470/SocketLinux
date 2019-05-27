#include "Connection.hpp"
#include <string.h>
#include <unistd.h>
#include <memory>

Connection::Connection( int sockfd, sockaddr_in* addr, socklen_t* addrlen )
  :
  sockfd( sockfd ), addr( addr ), addrlen( addrlen )
{
  if( sockfd < 0 )
  {
    throw( "Erro ao criar Connection, sockfd inválido!" );
  }
}

//retorna quantos bytes foram enviados
int Connection::Send( const Message& msg ) const
{
  return write( sockfd, msg.data.get(), msg.size );
}

//retorna quantos bytes foram enviados
int Connection::Send( const std::string msg ) const
{
  return write( sockfd, msg.c_str(), msg.length() + 1 );
}

Connection::Message Connection::Get() const
{
  std::shared_ptr<char> buffer( new char[message_max] );
  bzero( buffer.get(), message_max );
  int size = read( sockfd, buffer.get(), message_max );
  return Message( size, buffer );
}

Connection::~Connection()
{
  close( sockfd );
  delete addr;
  delete addrlen;
}