#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<windows.h>
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
    fOpen = "Cocos2dxPrefsFile.xml";
    fin.open(fOpen.c_str());

    getline(fin,discard);
    getline(fin,discard);
    fin>>discard;
    for (int i = 0; i < 13; i++)
        fin.get(c);
    fin>>data;
    data.resize(data.length()-9);

    data = base64_decode(data); //Data is decoded
    fOpen = fOpen+".BGAD";
    fout.open(fOpen.c_str(), ios::binary);
    fout<<data;





}
