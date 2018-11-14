#include "ServerSocket.h"
#include "SocketException.h"
#include <stdlib.h> 
#include <string>
#include<iostream>
#include "generator.cpp"
 
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
	    // Every five frames, one should have a
	    // reversed parity bit. The frame with
	    // the reversed parity should receive a NACK
	    // and have to be resent.
	    int frame_counter = 0;
	    int failed_frame = rand() % 5;
	    string test[4]= {"Lethbridge", "Alberta","Canada","Earth"};
	    int data_counter=0;

	    std::string prev_ack;
	    int sequence_counter = 0;
	    
	       
	    while (true){
	       sleep(3);
	    
	    
	       //data_counter=(data_counter +1)%4;
	       std::string ack;
               std::string parity_bit;

	       if (prev_ack == "ACK")
	       {
		  sequence_counter = (sequence_counter + 1) % 4;
	        }

	       std::string data = test[sequence_counter];
	       
	       parity_bit = getParity(data);
	       if (frame_counter > 4) {
		  // Five frames have passed, so we
		  // need to recalculate the frame number
		  // that will have a flipped parity bit.
		  frame_counter = 0;
		  failed_frame = rand() % 5;
	       }

	       std::cout << failed_frame << " " << frame_counter << std::endl;
	       
	       if (failed_frame == frame_counter) {
		  // The current frame is the frame to
		  // fail, so flip to parity bit.
		  parity_bit = (parity_bit == "1") ? "0" : "1";
	       }
	       
	       data = parity_bit + data;

	       //std::cout<<data;
	       new_sock << data;
	       new_sock2 >> ack;
	       if (ack == "ACK") {
		  std::cout << "Good" << std::endl;
		  prev_ack = "ACK";
		  // std::cout<<ack<<std::endl;
	       }
	       else{
		  std::cout << "Bad" << std::endl;
		  prev_ack = "NAK";
		  // std::cout<<ack<<std::endl;
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
