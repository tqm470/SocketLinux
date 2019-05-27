#pragma once
#include <string>
#include "../shared/Connection.hpp"

class ClientSocket
{
  public:
    ClientSocket() = delete;
    ClientSocket( const ClientSocket& ) = delete;
    ClientSocket& operator=( const ClientSocket& ) = delete;
  public:
    static Connection Connect( const std::string hostname, const int porta );
  private:
    int sockfd;
};