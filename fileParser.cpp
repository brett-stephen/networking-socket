#include <fstream>
#include "fileParser.h"
#include <cmath>


fileParser::fileParser()
{
    file.open("test_networking_doc.txt");
    if (file.is_open()){
        cout<<"The file has been found"<<endl;
    }
    charCount= 0;
    lineCount = 0;
    index = 0;

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



