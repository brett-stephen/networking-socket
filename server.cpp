#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include<iostream>
 
int main(int argc, int argv[])
{
   std::cout << "runningData....\n";
   try{
      // Create the socket
      ServerSocket server(30000);
      ServerSocket Ack(30001);

      while (true){
	 ServerSocket new_sock;
	 server.accept(new_sock);

	 ServerSocket new_sock2;
	 Ack.accept(new_sock2);

	 // For multiple threading, you need to create
	 // a new thread here and pass new_sock to it.
	 // The thread will use new_sock to communicate
	 // with the client.
	 try{
	    while (true){
	       std::string data = "Lethbridge";
	       std::string ack;
	       new_sock << data;
	       new_sock2 >> ack;
	       if (ack == "ACK") {
		  std::cout << "Good" << std::endl;
		   std::cout<<ack<<std::endl;
	       } else{
		  std::cout << "Bad" << std::endl;
		  std::cout<<ack<<std::endl;
	       }
	       
	    }
	 }
	 catch(SocketException&){
	 }
      }
   }
   catch (SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
   }

      
  return 0;
}
