#include <string>
#include "fileParser.cpp"

int main()
{
    vector <string> myvec (10);
   // string arr;
    string file = "test_networking_doc.txt";

    fileParser a;
    /*
    for(int i=0; i<2000; i++)
    {
            myvec=a.read();
            for(int i=0; i<myvec.size();i++){
                    cout<< myvec[i]<<endl;
            }

    }
    */
    cout<<" r1 "<<a.readString()<<endl;
    cout<<" r2 "<<a.readString()<<endl;
    cout<<" r3 "<<a.readString()<<endl;
    cout<<" r4 "<<a.readString()<<endl;
    cout<<" r5 "<<a.readString()<<endl;



    //cout<<"array: "<<a.getFrame(1)<<endl;




    //cout<<a.lineCount();
    return 0;
}
