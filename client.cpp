#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main(int argc, int argv[])
{
   try{
      // Replace "localhost" with the hostname
      // that you're running your server.
      ClientSocket client_socket("localhost", 30000);
      ClientSocket client_socket2("localhost", 30001);
      
      while(true){ 
	 std::string reply;
	 // Usually in real applications, the following
	 // will be put into a loop. 
	 try {
	    client_socket << "Test message.";
	    client_socket >> reply;
	    client_socket2 << "ACK";
	 }
	 catch(SocketException&){
	 }
	 std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
      
      }


      
      
   }
   catch(SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\n";
   }

   return 0;
}
