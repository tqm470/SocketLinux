#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include "ServerSocket.hpp"

extern "C" {
  unsigned char* md5check( const char* filename);
  void print_md5_sum(unsigned char* md);
}


int main( int argc, char* argv[] )
{
  try
  {
    if( argc < 2 )
    {
      throw( "informe a porta!" );
    }
    ServerSocket server( atoi( argv[1] ) );
    while( true )
    {
      server.Listen( 1 );
      Connection client = server.Accept();
      auto start = std::chrono::steady_clock::now();
      auto msg = client.Get();
      std::string filename( msg.data.get() );
      std::fstream file( filename, std::fstream::out | std::fstream::trunc );
      client.Send("ok");
      msg = client.Get();
      file.seekp(0);
      while( strcmp( msg.data.get(), "done_sending_file" ) != 0 )
      {
        file.write( msg.data.get(), msg.size );
        client.Send( "ok" );
        msg = client.Get();
      }

      file.close();
      std::chrono::duration<float> dur = std::chrono::steady_clock::now() - start;
      std::cout << "Done receiving file '" << filename << "' in " << static_cast<int>( dur.count() ) << "s!\n";

      auto result = md5check( filename.c_str() );
      msg = client.Get();
      unsigned char* clientResult = (unsigned char*) msg.data.get();
      std::cout << "Client md5: ";
      print_md5_sum( (unsigned char*)msg.data.get() );
      std::cout << "\nServer md5: ";
      print_md5_sum( result );
      if( strcmp( (char*)result, (char*)clientResult ) == 0)
      {
        std::cout << "\nmd5 match!\n";
      }
      else
      {
        std::cout << "\nmd5 dismatch!\n";
      }
    }
  }
  catch( const char* e )
  {
    std::cout << e << std::endl;
    exit( -1 );
  }
  
}