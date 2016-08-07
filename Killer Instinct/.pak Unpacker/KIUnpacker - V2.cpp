#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<windows.h>
#include<sstream>
#include"MKX4B.cpp"
using namespace std;

void setExt(int, string*, int);

int main()
{
    int fnum, *fsize, *floc, extVar = 0;
    unsigned char H[4], fdata[262], c;
    string file_open,file_det_out, *fname, *fext;
    stringstream ss1;
    ifstream fin;
    ofstream fout,outDetails,test;
    fin>>noskipws;

    cout<<"Enter a file to open: ";
    cin>>file_open;
    fin.open(file_open.c_str(), ios::binary);
    cout<<endl;
    if (fin.good())
        cout<<"Opened "+file_open+" successfully...\n";
    else cout<<file_open + " Not Found!";

    read(fin,H);
    if (H[0] == 0x5F && H[1] == 0x4B && H[2] == 0x41 && H[3] == 0x50)
    {
        read(fin,H);
        if (H[3] == 04)
            cout<<"Killer Instinct Game File Detected...";
        else cout<<"Not a valid Killer Instinct File!";
    }   else cout<<"Not a valid Killer Instinct File!";

    //Open the Details File
    file_det_out = file_open;
    file_det_out[file_det_out.length()-3] = 't';
    file_det_out[file_det_out.length()-2] = 'x';
    file_det_out[file_det_out.length()-1] = 't';
    outDetails.open(file_det_out.c_str());

    discard(fin,8);

    //Check how many files
    read(fin,H);
    fnum = H2I(H);
    cout<<"\n\nFound "<<fnum<<" Game Files...\n";
    fsize = new int[fnum]; //Store the size of each file
    floc = new int[fnum]; //Store the location of each file
    fname = new string[fnum]; //Store the name of each file
    fext = new string[fnum]; //Store the extension of each file

    discard(fin,8);

    //Print Details
    //This area is only to display Working Directory, optional
    outDetails<<"Detected game root ";
    outDetails.close();
    string syntax = "echo %cd% >>"+file_det_out;
    system(syntax.c_str());
    outDetails.open(file_det_out.c_str(), ios::app);
    //End of this area
    outDetails<<"Killer Instinct\nFound "<<fnum<<" game files\nLoading package: "<<file_open<<endl;

    //Read File Names, Sizes, and Locations.
    for (int i = 0; i < fnum; i++)
    {
        cout<<"\nFile ";
        fname[i] = "";
        fin>>c;
        while(c != 0x00)
        {
            fname[i] += c;
            fin>>c;
        }
        cout<<fname[i]<<": ";

        discard(fin,243-fname[i].length()); //Each File has 0x106 slots exactly.
        read(fin,H);
        floc[i] = H2I(H);
        cout<<"\n    Location: "<<uppercase<<hex<<"0x"<<floc[i];
        discard(fin,4);
        read(fin,H);
        fsize[i] = H2I(H);
        cout<<"\n    Size: "<<hex<<"0x"<<fsize[i];

        //Print Details
        outDetails<<uppercase<<setw(4)<<i<<" "<<setw(8)<<hex<<floc[i]<<" "<<setw(8)<<hex<<fsize[i]<<" "<<fname[i]<<endl;

        //Extension Handling
        read(fin,H); //Get Extension
        H[0] = 0;
        H[1] = 0;
        extVar = H2I(H); //Extension Variable
        //cout<<"The test is here now: "<<hex<<int(H[0])<<" "<<int(H[1])<<" "<<int(H[2])<<" "<<int(H[3])<<" "<<extVar<<endl; //DEBUG
        //cin>>c; //DEBUG

        setExt(extVar, fext, i);
        //cout<<"THE TEST IS NOW HERE: "<<fext[i]<<endl;//DEBUG
        //cin>>c; //DEBUG
        if (fext[i] == "Unknown")
        {
            ss1.str("");
            ss1<<extVar;
            fext[i] = ss1.str();
        }

        discard(fin,2);

    }
    cout<<"\nLoading Data done...\nExtracting, Please Wait...\n";

    string Dir,Name,Syntax;
    int ctr;

    fin.close();
    fin.open(file_open.c_str(), ios::binary);
    fin>>noskipws;
    discard(fin,floc[0]);
    for(int i = 0; i < fnum; i++)
    {
        cout<<"Extracting "<<fname[i]+"."+fext[i]<<"...";
        Dir = "";
        Name = "";
        ctr = 0; //In Case there isn't a directory
        for (int j = 0; j < fname[i].length(); j++) //Convert each '\' into '\\'
        {
            Dir+=fname[i][j];
            if (fname[i][j] == '\\')
                Dir+='\\';
        }
        //Name = Dir;
        for (int j = 0; j < Dir.length(); j++) //Split File name
        {
            if (Dir[Dir.length()-1-j] == '\\')
            {
                ctr = j;
                break;
            }
        }
        if (ctr != 0)
            Dir.resize(Dir.length()-ctr-2);
        Syntax = file_open; //Reusing Syntax to save memory
        for (int j = 0; j < Syntax.length(); j++)
            if (Syntax[Syntax.length()-1-j] == '.')
        {
            Syntax[Syntax.length()-1-j] = '_';
            break;
        }
        ctr = 0;
        for (int j = 0; j < fname[i].length(); j++) //Adjust the Name
        {
            if (fname[i][fname[i].length()-1-j] == '\\')
            {
                ctr = j;
                break;
            }
        }
        for(int j = 0; j < ctr; j++)
        {
            Name += fname[i][fname[i].length()-ctr+j];
        }
        Name = Syntax + "\\\\"+Dir+"\\\\"+Name+"."+fext[i]; //EDITED HERE
        //cout<<"Here's a test: "<<Name<<endl<<endl;
        Syntax = "md "+Syntax + "\\\\"+Dir+" 2>nul";
        system(Syntax.c_str());
        //if (fsize[i] != 0) //Enable this to not create empty files
            fout.open(Name.c_str(), ios::binary);
        for(int j = 0; j < fsize[i]; j++)
        {
            fin>>c;
            fout<<c;
        }
        fout.close();
        cout<<"Done!\n";

    }

    cout<<"All Tasks have been performed!";
    system("pause>nul");

}

void setExt(int x, string* s, int i)
{
    switch(x)
    {
        case 2: s[i] = "kimesh"; break;
        case 3: s[i] = "kimat"; break;
        case 4: s[i] = "kitex"; break;
        case 13: s[i] = "CinematicShot.xml"; break;
        case 21: s[i] = "EventList.xml"; break;
        case 22: s[i] = "MeshAttachmentInfo.xml"; break;
        case 28: s[i] = "kihkx"; break;
        case 29: s[i] = "hkAnim"; break;
        case 53: s[i] = "ProceduralAnimationData.xml";
        default: s[i] = "Unknown"; break;
    }
}
