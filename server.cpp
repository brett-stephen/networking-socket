#include "ServerSocket.h"
#include "SocketException.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include "generator.cpp"
#include "fileParser.cpp"
#include <queue>
 
int main(int argc, int argv[])
{
   std::cout << "runningData....\n";
   
   fileParser FileParser;
   
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
	    int frame_counter = 0;
	    int failed_frame = rand() % 5;
	    int sequence_counter = 0;

	    std::string previous_client_response;
	    std::string client_response;
	    std::string parity_bit;

	    // Read 64 characters from the file parser
	    std::string data  = FileParser.readString();
	       
	    while (true){
	       sleep(2); // TODO: Remove when we wanna go full speed

	       if (previous_client_response == ACK) {
		 // Get the next string to send
		  data = FileParser.readString();
	       } else {
		 // Send the same string over again
	       }
	       
	       if (FileParser.eof) {
		 // Nothing more to send 
		 // signal the client to close.
		 data = END_TRANSMISSION;
	       }

	       // Every five frames, one should have a
	       // reversed parity bit that should illicit 
	       // a NAK from the client to resend the data.
	       parity_bit = getParity(data);
	       if (frame_counter > 4) {
		  // Five frames have passed, so we
		  // need to recalculate the frame number
		  // that will have a flipped parity bit.
		  frame_counter = 0;
		  failed_frame = rand() % 5;
	       }
	       
	       if (failed_frame == frame_counter) {
		  // The current frame is the frame to
		  // fail, so flip to parity bit.
		  parity_bit = (parity_bit == "1") ? "0" : "1";
	       }

	       std::cout << "Failed frame: " << failed_frame << " Frame counter: " << frame_counter << std::endl;

	       // Send that gucci data
	       new_sock << parity_bit + data;

	       if (FileParser.eof) {
		 // After we've sent END_TRANSMISSION we
	         // don't need to receive anything else.
		 return 0;
	       }

	       // Receive ACK/NAK response 
	       new_sock2 >> client_response;
	       
	       if (client_response == ACK) {
		  previous_client_response = ACK;
	       }
	       else{
		  previous_client_response = NAK;
	       }
	       
	       frame_counter++;
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
