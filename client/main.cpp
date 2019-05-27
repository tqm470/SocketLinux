#include <fstream>
#include <chrono>
#include <iostream>
#include <string.h>
#include "ClientSocket.hpp"

extern "C" {
unsigned char* md5check( const char* filename);
}

int main( int argc, char* argv[] )
{
  try
  {
    if( argc < 3 )
    {
      throw( "Invalido! Por favor forneça um hostname, porta e filename!" );
    }
    std::fstream file( argv[3], std::fstream::in );
    if(!file.is_open())
    {
      throw( "Arquivo não encontrado!" );
    }
    Connection server = ClientSocket::Connect( argv[1], atoi( argv[2] ) );
    auto start = std::chrono::steady_clock::now();
    server.Send( argv[3] );
    auto msg = server.Get();
    if( strcmp(msg.data.get(), "ok") != 0 )
    {
      throw( "Server não 'ok'!" );
    }
    file.seekg(0);
    while( file.good() )
    {
      std::shared_ptr<char> buffer( new char[ message_max ] );
      file.read( buffer.get(), message_max );
      server.Send( { static_cast<int>( file.gcount() ), buffer } );
      server.Get();
    }
    server.Send( "done_sending_file" );
    file.close();
    std::chrono::duration<float> dur = std::chrono::steady_clock::now() - start;
    std::cout << "Done sending file in " << static_cast<int>( dur.count() ) << "s!\n";
    
    auto md5result = md5check( argv[3] );
    server.Send( (char*) md5result );
  }
  catch( const char* e )
  {
    std::cout << e << std::endl;
    exit( -1 );
  }
}