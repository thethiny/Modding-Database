#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<windows.h>
#include"MKX4B.cpp"
#include"base64.cpp"
using namespace std;


int main()
{
    int noXML, headSize, extSize, dataSize, fCtr=0;//NumberOfXMLs, FileCounter
    ifstream fin;
    ofstream fout;
    string fOpen, discard, data;
    stringstream ss1;
    char c;
    unsigned char Long[4], Short[2];
    cout<<"Enter file to open: ";
    cin>>fOpen;
    fin.open(fOpen.c_str());

    getline(fin,discard);
    getline(fin,discard);
    fin>>discard;
    for (int i = 0; i < 13; i++)
        fin.get(c);
    fin>>data;
    data.resize(data.length()-9);
    //cout<<data;

    data = base64_decode(data); //Data is decoded
    fOpen[fOpen.length()-4] = '_';
    discard = fOpen;

    for (int i = 0; i < data.length(); i = i)
    {
       if (data[i] == 'B' && data[i+1] == 'G' && data[i+2] == 'A' && data[i+3] == 'D') //Must be BGAD file
       {
            Long[0] = 0; Long[1] = 0; //Initialize to 2Bytes
            Long[3] = data[i+8]; Long[2] = data[i+9];
            headSize = H2I(Long);
            cout<<"\nBGAD File "<<fCtr+1<<"\n    Header Size: "<<headSize;

            Long[3] = data[i+10]; Long[2] = data[i+11];
            extSize = H2I(Long);
            cout<<"\n    Extension Size: "<<extSize;

            Long[3] = data[i+16]; Long[2] = data[i+17]; Long[1] = data[i+18]; Long[0] = data[i+19];
            dataSize = H2I(Long);
            cout<<"\n    Data Size: "<<dataSize;

            //Extract BGADs
            ss1.str(""); //Clear SS1
            fOpen = discard;
            fOpen = "md "+fOpen+" 2>nul";
            system(fOpen.c_str());
            ss1<<discard<<"\\\\"<<fCtr+1<<".BGAD";
            fOpen = ss1.str();
            fout.open(fOpen.c_str());
            for (int j = 0; j < dataSize + extSize; j++)
            {
                fout<<data[i+headSize+j];
            }
            fout.close();
            i = i+headSize+dataSize+extSize;
            fCtr++;
            //break; //DEBUG
       } else break;
    }

    cout<<"\nDone!";





}
