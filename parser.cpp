#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string file;
string str;

string reassembly(string frame, string file){
   file.append(frame);

    cout<<file<<endl;
    return file;
}

void stringTotal(string a)
{
    str=str+a;
}

void deassembly(){
    ifstream testFile("test_networking_doc.txt");
    string line;
    int charCount;
    int frameSz = 64;
    string newString;
    //string *frame = new string[frameSz];

    if (testFile.is_open()){

            while (!testFile.eof()){
                    getline (testFile, line);
                    int len = line.length();
                    int a = len/64;
                    int b = len % 64;
                    int j = 0;
                    for (int i=0; i<= a; i++)
                    {
                        string sub = line.substr(j,j+63);
                        stringTotal(sub);

                        //cout<<sub<<endl;
                        j=j+ 63;
                    }

            }
            testFile.close();

    }

}


int main(){

deassembly();
string file2 = reassembly(str,file);

 return 0;
}
