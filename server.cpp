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
	    // Every five frames, one should have a
	    // reversed parity bit. The frame with
	    // the reversed parity should receive a NACK
	    // and have to be resent.
	    int frame_counter = 0;
	    int failed_frame = rand() % 5;
	    //std::string test[4]= {"Lethbridge", "Alberta","Canada","Earth"}; // TODO: Remove this once we have the file input

	    std::string prev_ack;
	    int sequence_counter = 0;

	    std::string data  = FileParser.readString();
	    //Read the first 64 characters
	    //of the file before entering
	    //the loop
	       
	    while (true){
	       sleep(3); // TODO: Remove when we wanna go full speed

	       
	       std::string ack;
               std::string parity_bit;

	       if (prev_ack == "ACK") {
		  //sequence_counter = (sequence_counter + 1) % 4;

		  data = FileParser.readString();
	       }

	       //std::string data = test[sequence_counter];
	       
	       parity_bit = getParity(data);
	       if (frame_counter > 4) {
		  // Five frames have passed, so we
		  // need to recalculate the frame number
		  // that will have a flipped parity bit.
		  frame_counter = 0;
		  failed_frame = rand() % 5;
	       }

	       std::cout << "Failed frame: " << failed_frame << " Frame counter: " << frame_counter << std::endl;
	       
	       if (failed_frame == frame_counter) {
		  // The current frame is the frame to
		  // fail, so flip to parity bit.
		  parity_bit = (parity_bit == "1") ? "0" : "1";
	       }

	       // Prepend the parity bit to the data
	       data = parity_bit + data;

	       // Send the line 
	       new_sock << data;

	       // Receive the Ack/Nak
	       new_sock2 >> ack;
	       
	       if (ack == "ACK") {
		  //std::cout << "Good" << std::endl;
		  prev_ack = "ACK";
	       }
	       else{
		  //std::cout << "Bad" << std::endl;
		  prev_ack = "NAK";
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
