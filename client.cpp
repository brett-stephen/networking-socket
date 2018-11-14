#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include"generator.cpp"

int main(int argc, int argv[])
{
   try{
      // Replace "localhost" with the hostname
      // that you're running your server.
      ClientSocket client_socket("localhost", 30000);
      ClientSocket client_socket2("localhost", 30001);
      
      while(true){ 
	 std::string frame, received_parbit, expected_parbit;
	 
	 // Usually in real applications, the following
	 // will be put into a loop. 
	 try {
	    client_socket >> frame;
	    received_parbit=frame[0];
	    frame=frame.substr(1);
	    // std::cout<<frame<<parbit<<std::endl;
	    expected_parbit=getParity(frame);

	    if(expected_parbit==received_parbit)
	       client_socket2 << "ACK";
	    else
	       client_socket2 << "NACK";
	    
	 }
	 catch(SocketException&){
	 }
	 std::cout << "We received this response from the server:\n\"" << frame << "\"\n";
      
      }


      
      
   }
   catch(SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\n";
   }

   return 0;
}
