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
	 std::string response;
	 // Usually in real applications, the following
	 // will be put into a loop. 
	 try {
	    // Receive the frame from server
	    client_socket >> frame;

	    // Split the parity bit from the rest of the frame
	    received_parbit=frame[0];
	    frame=frame.substr(1);
	    
	    expected_parbit=getParity(frame);

	    // Select the response and send it to the server
	    response = (expected_parbit == received_parbit) ? "ACK" : "NACK";
	
	    client_socket2 << response;
	 }
	 catch(SocketException&){
	 }
	 std::cout << "We received this frame from the server:\n\"" << frame << "\"\n";
	 std::cout<<"Client is sending a "<<response<<std::endl;
      }
   }
   catch(SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\n";
   }

   return 0;
}
