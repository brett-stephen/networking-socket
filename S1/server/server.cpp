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
  
	while (true){
	
	
	fileParser FileParser;
	std::cout<< "client is requesting a connection"<< std::endl;

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
	      
	      //sleep(2); // TODO: Remove when we wanna go full speed

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

	     // std::cout << "Failed frame: " << failed_frame << " Frame counter: " << frame_counter << std::endl;

	      // Send that gucci data
	      new_sock << parity_bit + data;

	      if (FileParser.eof) {
		// After we've sent END_TRANSMISSION we
		// don't need to receive anything else.
		std::cout<<"Finished streaming data to client"<<std::endl;
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
	
  return true;
}

int main(int argc, char **argv)
{

    if (argc != 2) {
      // The script name is always passed as argv[0] 
      std::cout << "Please enter 1 argument!\n"
        "1) port #\n"
        "\n";
      return 0;
    }

    // Convert char array to strings
    std::vector<std::string> all_args(argv, argv + argc);

    int port = std::stoi(all_args[1]); // string -> int
    int ack_port = port + 1;

  std::cout << "runningData....\n";
  
  try{
    // Create the socket
    ServerSocket server_socket(port);
    ServerSocket ack_socket(ack_port);
    
	ServerSocket client_socket;
	ServerSocket client_ack_socket;
    
    while (true){
		// Wait for the client to send a request 
		server_socket.accept(client_socket);
		// Wait for ack socket connection
		ack_socket.accept(client_ack_socket);
		// Send the data
		transferData(client_socket, client_ack_socket);
      }
    }
  catch (SocketException& e){
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }


  return 0;
}
