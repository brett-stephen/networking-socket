#include <fstream>

#include <cmath>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class fileParser
{
    public:
    fileParser();
   ~fileParser();
    vector<string> read();
    string readString();
    string write(string);
    int getFrameCount();
    void setFrameCount(int);


    //data memebers
    int vectorIndex;
    int lineCount;
    int frameCount;
    int charCount;
    fstream file;
    int line_num;
    vector<string> fileLine;
    string textline;
    int index;
    bool eof;
};

fileParser::fileParser()
{
    file.open("test_networking_doc.txt");
    if (file.is_open()){
        cout<<"The file has been found"<<endl;
    }
    charCount= 0;
    lineCount = 0;
    index = 0;
    eof=0;
    vectorIndex = 0;

}

fileParser::~fileParser(){

    file.close();

}


//Function setFramecount(): This function returns the number of frames that will be sent out
//Input: The length of the line divided by 64
//Output: none
void fileParser::setFrameCount(int a){

frameCount=a;
}

//Function getFramecount(): This function returns the number of frames that will be sent out
//Input: none
//Output: the number of frames

int fileParser::getFrameCount(){

return frameCount;
}

//Function read(): This function should be called for each line in the text to break the
//text file into smaller frame sizes.
//Input: none
//Output: A vector which contains frames of a max size of 64 characters for
//one text line

vector<string> fileParser::read(){

    string line;
    getline (file, line);
    if (file.eof())
    {
        //cout<<"End of file."<<endl;
        eof =1;

    }
    double len = line.length();
    double b = len/64.00;

    setFrameCount(ceil(b));

    int j = 0;
    vector<string> temp;

    while(!fileLine.empty()){
        fileLine.pop_back();
    }

    for (int i=0; i<=b; i++){
        string sub = line.substr(j,j+64);
        fileLine.push_back(sub);
        j=j+ 64;
        temp=fileLine;
    }
        return temp;
        // charCount = len;
}

string fileParser::readString()
{
    cout<<"fileLine vector size = "<<fileLine.size()<<endl;
    
    if(fileLine.size() != 0)
    {
        string temp = fileLine[0]; //saves string in first index
        fileLine.erase(fileLine.begin()); //erases first index
	
	if(fileLine.size() == 0)
	{
	  cout<<"Appending \\n to "<<temp<<endl;
	  temp += "\n";
	}
        return temp; //returns string from first index
    }
    
    vector<string> vec = read();
    string temp = fileLine[0]; //saves string in first index
    fileLine.erase(fileLine.begin()); //erases first index
   
    //vectorIndex++;
    //if (vectorIndex>=vec.size())
    //    vectorIndex = 0;
    return temp;
}


