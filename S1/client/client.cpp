#include "ClientSocket.h"
#include "../SocketException.h"
#include <iostream>
#include <string>
#include <queue>
#include "./../server/generator.cpp"

queue <string> receivedLine;

// Takes a string, pushes it into queue, searches for \n,
// writes out line if it finds \n
void stackCheck(string str)
{
	//cout<<"pushing string to stack"<<endl;
    receivedLine.push(str);

    string currentStr = receivedLine.back();

    size_t found = currentStr.find("\n"); // returns position at found character

    if (found!=string::npos)
    {
        //cout << "\\n found at: " << found << '\n';
        int sz = receivedLine.size();

        for(int i = 0; i<sz; i++)
        {
            cout<<receivedLine.front();
            receivedLine.pop();
        }
        //cout<<"removing queue "<<receivedLine.size()<<endl;
    }
}

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
	    response = (expected_parbit == received_parbit) ? ACK : NAK;
 
	    if (response != NAK) {
	      stackCheck(frame);
	    }
	    
            if (frame == END_TRANSMISSION) {
              std::cout << "Reached the end of the file, exiting." << std::endl;
              return 0;
	    }
	
	    client_socket2 << response;
	 }
	 catch(SocketException&){
	 }

	 //std::cout << "We received this frame from the server:\n\"" << frame << "\"\n";
	 std::cout<<"Client is sending a "<<response<<std::endl<<std::endl;
      }
   }
   catch(SocketException& e){
      std::cout << "Exception was caught:" << e.description() << "\n";
   }

   return 0;
}
