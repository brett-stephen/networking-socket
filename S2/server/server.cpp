#include "ServerSocket.h"
#include "./../SocketException.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include "generator.cpp"
#include "fileParser.cpp"
#include <queue>


bool transferData(ServerSocket new_sock, ServerSocket new_sock2)
{
  fileParser FileParser;
  std::cout<< "client is requesting a connection"<< std::endl;
  
  // For multiple threading, you need to create
  // a new thread here and pass new_sock to it.
  // The thread will use new_sock to communicate
  // with the client.
  
  try
  {
    int frame_counter = 0;
    int failed_frame = rand() % 5;
    int sequence_counter = 0;
    
    std::string previous_client_response;
    std::string client_response;
    std::string parity_bit;
    
    // Read 64 characters from the file parser
    std::string data  = FileParser.readString();
    bool continueTrasfer = true;
    
    bool eof;
    
    while (continueTrasfer){ //continuely sends out data while not eof
      //sleep(2); // TODO: Remove when we wanna go full speed
      
      if (previous_client_response == ACK) {
	// Get the next string to send
	std::cout<<"Moving onto next line"<<std::endl;
	data = FileParser.readString();
	
	
	if (FileParser.eof){
	  data = END_TRANSMISSION;
	  eof = true;
	}
      } 
      else 
      {
	// Send the same string over again
	
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
      
      // std::cout << "Failed frame: " << failed_frame << " Frame counter: " << frame_counter << std::endl;
      
      
      // Send the data
      std::cout<<"Outgoing data is : "<< data <<std::endl;
      new_sock << parity_bit + data;
      
      // Receive ACK/NAK response 
      new_sock2 >> client_response;
      
      if (client_response == ACK) {
	previous_client_response = ACK;
	
	if (eof == true) 
	  continueTrasfer = false; std::cout<<"Client received END transmission, stop disconnect from socket."<< data <<std::endl;
	  //return true;
      }
      else{
	previous_client_response = NAK;
      }
      
      frame_counter++;
    }
  }
  catch(SocketException& e)
  {
     std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    return false;
  } 
  
  return true;
}



  int main(int argc, int argv[])
  {
    std::cout << "runningData....\n"<<endl;
    
    try{
      // Create the socket
      ServerSocket Server(30000);
      ServerSocket Ack(30001);
      
      
      while (true){
	// the Server object will stop and wait until it gets a request from a client
	ServerSocket new_sock;
	Server.accept(new_sock);
	
	ServerSocket new_sock2;
	Ack.accept(new_sock2);
	
	transferData(new_sock,new_sock2);
	
	return 0;
      }
    }
    catch (SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    
    
    return 0;
  }
  