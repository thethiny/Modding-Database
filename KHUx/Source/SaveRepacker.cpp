#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<windows.h>
#include"base64.cpp"
using namespace std;


int main()
{
    unsigned int size;//NumberOfXMLs, FileCounter
    ifstream fin;
    ofstream fout;
    string fOpen, dataEnc = "";
    unsigned char *data;
    unsigned char Long[4], Short[2];

    cout<<"Enter your save name: ";
    cin>>fOpen;

    fin.open(fOpen.c_str(), ios::ate);
    size = fin.tellg();
    fin.close();

    fin.open(fOpen.c_str(),ios::binary);
    fin>>noskipws;

    data = new unsigned char [size];

    for (int i = 0; i < size; i++)
    {
        fin>>data[i];
    }

    /*cout<<"Test out: ";
    for (int i = 0; i < size; i++)
        cout<<hex<<(unsigned short)(data[i])<<" ";
    cout<<endl<<endl;*/


    dataEnc = base64_encode(data, size); //Data is decoded
    fOpen = "Cocos2dxPrefsFile_out.xml";
    fout.open(fOpen.c_str(), ios::binary);
    fout<<"<?xml version=\'1.0\' encoding=\'utf-8\' standalone=\'yes\' ?>"<<endl<<"<map>"<<endl<<"    <string name=\"data\">";
    fout<<dataEnc;
    fout<<"</string>"<<endl<<"</map>";





}
