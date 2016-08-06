#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

int main()
{
    char* x;
    char c;
    unsigned char dbg;
    string searchFor,got;
    ifstream coalIn,langIn,coalIn2;
    ofstream coalOut,langOut,coalOut2;
    bool B1;
    int Size,Size2,Size3;

    try{
    coalIn.open("Extract/$StartupCacheDir$/Config/X64-MK10Game.ini",ifstream::binary);
    if (!coalIn.good())
        throw(1);
    langIn.open("LANGFILE.txt",ifstream::binary);
    if (!langIn.good())
        throw(2);
    coalIn.seekg (0, coalIn.end);
    Size = coalIn.tellg();
    coalIn.seekg (0, coalIn.beg);

    langIn.seekg (0, langIn.end);
    Size3 = langIn.tellg();
    langIn.seekg (0, langIn.beg);


    //coalIn>>noskipws;

    coalOut.open("UnIndMK10.ini",ifstream::binary);
    langOut.open("UnIndLANG.txt",ifstream::binary);

    if (Size <=0)
        throw(10);
    x = new char [Size];
    //Store all chars in x
    coalIn.read(x,Size);

    cout<<"Enter Name_Costume to Uninstall: ";
    cin>>got;
    searchFor = "Unlocked=CHAR_" + got;

    cout<<"Uninstalling CHAR_"<<got<<"...\n";

    //Unintall from ini - UNLOCKED
    for (int i = 0; i < Size; i++)
    {
        B1 = false;

        if (tolower(x[i]) != tolower(searchFor[0]) )
            coalOut<<x[i];

        else {
            for (int j = 0; j < searchFor.length(); j++)
            {
                if (tolower(x[i+j]) == tolower(searchFor[j]) )
                    B1 = true;
                else {B1 = false; break;}
            }
        if (!B1)
            {
                coalOut<<x[i];
            }
        else
        {       //Skip Writing searchFor and the line.
                i+= searchFor.length()+1;
                //dbg = x[i];
                //cout<<"DBG: "<<int(dbg);
        }
        }

    }
    coalOut.close();

    delete [] x;

    searchFor = "[CharacterSettings.CHAR_" + got + "]";
    coalIn2.open("UnIndMK10.ini",ios::binary | ios::ate);
    if (!coalIn2.good())
        throw(3);
    //coalIn2.seekg (0, coalIn2.end);
    Size2 = coalIn2.tellg();
    //cout<<coalIn2.tellg(); //DEBUG
    coalIn2.seekg (0, coalIn2.beg);
    if (Size2 <=0)
        throw(10);
    x = new char [Size2];
    coalIn2.read(x,Size2);
    coalOut2.open("UnSetMK10.ini",ios::binary);

        //Uninstall from ini - Settings

    for (int i = 0; i < Size2; i++)
    {
        B1 = false;

        if (tolower(x[i]) != tolower(searchFor[0]) )
            coalOut2<<x[i];

        else {
            for (int j = 0; j < searchFor.length(); j++)
            {
                if (tolower(x[i+j]) == tolower(searchFor[j]) )
                    B1 = true;
                else {B1 = false; break;}
            }
        if (!B1)
            {
                coalOut2<<x[i];
            }
        else
        {       //Skip Writing searchFor and the line.
                i+= searchFor.length()+1;
                while(x[i] != '[' && i != Size2)
                    i++;
        }
        }

    }

    delete [] x;

    if (Size3 <=0)
        throw(10);
    x = new char [Size3];
    langIn.read(x,Size3);
    searchFor = "CHAR_" + got + "=";
        //Unintall from ENG
    for (int i = 0; i < Size3; i++)
    {
        B1 = false;

        if (tolower(x[i]) != tolower(searchFor[0]) )
            langOut<<x[i];

        else {
            for (int j = 0; j < searchFor.length(); j++)
            {
                if (tolower(x[i+j]) == tolower(searchFor[j]) )
                    B1 = true;
                else {B1 = false; break;}
            }
        if (!B1)
            {
                langOut<<x[i];
            }
        else
        {       //Skip Writing searchFor
                i+= searchFor.length()+1;
                //Search for End line
                while(x[i] != 10 && i !=Size3)
                    i++;

        }
        }

    }
    delete [] x;

    coalIn.close();
    coalOut.close();
    langIn.close();
    langOut.close();

    } catch (int Err)
    {
        cout<<"Error "<<Err<<": ";
        switch(Err)
        {
            case  1:  cout<<"Extract\\$StartupCacheDir$\\Config\\X64-MK10Game.ini Not Found\n";exit(404);
            case  2:  cout<<"Extract2\\$GameDir$\\Localization\\eng\\MK10Game.ENG Not Found\nor\nConverting MK10Game.ENG to UTF-8 Failed."; exit(404);
            case  3:  cout<<"COULDN'T LOAD MODDED FILE. CHECK YOUR WRITING PRIVILEDGES.\n";exit(0);
            case 10:  cout<<"MEMORY ALLOCATION FAILED. CHECK YOUR FILES\n";exit(1);
            default: cout<<"Unknown Error\n"; exit(2);
        }

    }

}
