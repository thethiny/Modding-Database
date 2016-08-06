#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream Ifin,Efin,Xfin; //ini & ENG & X64TOC
    ofstream Ifout,Efout,Xfout,f3;
    char I,E,X;
    string Cname,Ename,exit="0";
    bool find1[21],find2[22];
    int ctr=0;

    for (int i = 0; i < 21; i++)
        find1[i]=0;
    for (int i = 0; i < 22; i++)
        find2[i]=0;

    Ifin.open("Extract/$StartupCacheDir$/Config/X64-MK10Game.ini");
    Ifin>>noskipws;
    Ifout.open("ExtedIni.ini");
    Efin.open("LANGFILE.txt");
    Efin>>noskipws;
    Efout.open("ExtedLang.txt");
    Xfin.open("X64_Dec.txt");
    Xfin>>noskipws;
    Xfout.open("ExtedX64.txt");
    f3.open("names");

    cout<<"Enter 0 and press Enter at any time to stop."<<endl;
    while(Ifin>>I)
    {
        Ifout<<I; //[Unlocked.Characters]
        switch(I){
        case '[': find1[ctr]=1; ctr++; break;
        case 'U': find1[ctr]=1; ctr++; break;
        case 'n': find1[ctr]=1; ctr++; break;
        case 'l': find1[ctr]=1; ctr++; break;
        case 'o': find1[ctr]=1; ctr++; break;
        case 'c': find1[ctr]=1; ctr++; break;
        case 'k': find1[ctr]=1; ctr++; break;
        case 'e': find1[ctr]=1; ctr++; break;
        case 'd': find1[ctr]=1; ctr++; break;
        case '.': find1[ctr]=1; ctr++; break;
        case 'C': find1[ctr]=1; ctr++; break;
        case 'h': find1[ctr]=1; ctr++; break;
        case 'a': find1[ctr]=1; ctr++; break;
        case 'r': find1[ctr]=1; ctr++; break;
        case 't': find1[ctr]=1; ctr++; break;
        case 's': find1[ctr]=1; ctr++; break;
        case ']': find1[ctr]=1; ctr++; break;
        default : for (int i = 0; i < 21; i++) find1[i]=0; ctr = 0;
        }
        if (find1[20] == 1)
            break;

    }

    while(Efin>>E)
    {
        Efout<<E; //CHAR_Mileena_M=KLASSIC
        switch(E){
        case 'C': find2[ctr]=1; ctr++; break;
        case 'H': find2[ctr]=1; ctr++; break;
        case 'A': find2[ctr]=1; ctr++; break;
        case 'R': find2[ctr]=1; ctr++; break;
        case '_': find2[ctr]=1; ctr++; break;
        case 'M': find2[ctr]=1; ctr++; break;
        case 'i': find2[ctr]=1; ctr++; break;
        case 'l': find2[ctr]=1; ctr++; break;
        case 'e': find2[ctr]=1; ctr++; break;
        case 'n': find2[ctr]=1; ctr++; break;
        case 'a': find2[ctr]=1; ctr++; break;
        case '=': find2[ctr]=1; ctr++; break;
        case 'K': find2[ctr]=1; ctr++; break;
        case 'L': find2[ctr]=1; ctr++; break;
        case 'S': find2[ctr]=1; ctr++; break;
        case 'I': find2[ctr]=1; ctr++; break;
        default : for (int i = 0; i < 22; i++) find2[i]=0; ctr = 0;
        }
        if (find2[21] == 1)
            break;

    }

    while (Xfin>>X)
    Xfout<<X;


    //Write at End of ini
    while (Ifin>>I)
    {
        if (I == '[')
            break;
        Ifout<<I;
    }

    // Loop Write
    cout<<"Enter a Character_Costume (Ex: Subzero_A): ";
    cin>>Cname;
        if (Cname != "0")
        {
    cout<<"Enter the name of the costume to appear in game: ";
    cin.ignore();
    getline(cin,Ename);
        }
    while(Cname != "0" && Ename != "0")
    {
    Ifout<<"Unlocked=CHAR_"<<Cname<<endl; //Write the characters here
    Efout<<endl<<"CHAR_"<<Cname<<"="<<Ename;
    Xfout<<"0 0 0 0 11 ..\\Asset\\CHAR_"<<Cname<<".xxx 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\Asset\\CHAR_"<<Cname<<"_SCRIPTASSETS.xxx 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\Asset\\DISM_"<<Cname<<".xxx 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\Asset\\DISM_"<<Cname<<"_DLC.xxx 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\MKScript\\CHAR_"<<Cname<<".mko 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\MKScript\\CHAR_"<<Cname<<".module 11"<<endl;
    Xfout<<"0 0 0 0 11 ..\\MKScript\\CHAR_"<<Cname<<".tweak 11"<<endl;
    f3<<Cname<<endl;

    cout<<"Enter a Character_Costume (Ex: Subzero_A): ";
    cin>>Cname;
    cin.ignore();
        if (Cname != "0")
        {
    cout<<"Enter the name of the costume to appear in game: ";
    getline(cin,Ename);
        }
    }



    //Write Remaining Files
    Ifout<<I;
    while (Ifin>>I)
        Ifout<<I;

    while (Efin>>E)
        Efout<<E;


    //Close Files
    Ifin.close();
    Efin.close();
    Xfin.close();
    Ifout.close();
    Efout.close();
    Xfout.close();
    f3.close();



}
