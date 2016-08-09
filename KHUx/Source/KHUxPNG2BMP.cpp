#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int main()
{
    ifstream fin,pngList,DATSfin;
    ofstream fout;
    string infile,outfile,openFile;
    unsigned char c,R,B,size[2]; //Color Swap

    pngList.open("pngList.txt");

    while(getline(pngList,infile))
    {
        cout<<"Converting "<<infile<<"..."<<endl;
        openFile = "Input\\\\" + infile;
        fin.open(openFile.c_str(),ios::binary);
        fin>>noskipws;


        openFile = "DATS\\\\" + infile + ".dat";
        DATSfin.open(openFile.c_str(),ios::binary);
        if (!DATSfin.good())
        {
            DATSfin.close();
            fin.close();
            continue;
        }
        DATSfin.close();


        outfile = "pngImages\\\\" + infile;
        outfile[outfile.length()-1] = 'P';
        outfile[outfile.length()-2] = 'M';
        outfile[outfile.length()-3] = 'B';
        outfile[outfile.length()-4] = '.';

        fout.open(outfile.c_str(),ios::binary);

        //BMP Header
        fout<<char(0x42)<<char(0x4D);
        for (int i = 0; i < 8; i++)
            fout<<char(0x00);
        fout<<char(0x36)<<char(0x00)<<char(0x00)<<char(0x00)<<char(0x28)<<char(0x00)<<char(0x00)<<char(0x00);



        for(int i = 0; i < 0x1E; i++)
            fin>>c;
        fin>>c;
        fout<<c;
        fin>>c;
        fout<<c<<char(0x00)<<char(0x00);

        fin>>size[1]>>size[0]; //Height
        //Reverse Height
        if (size[1] == char(00))
            size[0] -= 01;
        fout<<char(-size[1])<<char(-size[0]-1)<<char(0xFF)<<char(0xFF);

        fout<<char(0x01)<<char(0x00)<<char(0x20);
        for (int i = 0; i < 0x19; i++)
            fout<<char(0x00);

        fin.close();
        //infile += ".dat";
        openFile = "DATS\\\\" + infile + ".dat";
        fin.open(openFile.c_str(),ios::binary);
        //cout<<"INFILE: "<<infile; //DEBUG
        fin>>noskipws;

        while(fin>>R)
        {
            fin>>c;
            fin>>B;
            fout<<B<<c<<R;
            fin>>c;
            fout<<c;
        }
        fin.close();
        fout.close();

    }
    pngList.close();
}
