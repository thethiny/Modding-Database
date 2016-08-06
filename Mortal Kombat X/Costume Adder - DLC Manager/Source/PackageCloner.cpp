#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
using namespace std;

int main()
{
    ifstream fin,namein,namein2,itfc;
    ofstream fout,nameout,otfc;
    char costumeLetter;
    string origPackage,CHARName,SAName,DISMName,DISMDLCName,MKOName,costumeName,currentfile,saveto,searchfor,name2;
    unsigned char c;
    unsigned char* DATA;
    int FileSize,S,subbed,runs,pos;
    //int debug; //To Pause

    nameout.open("name2.txt"); //Output modded costumes
    namein.open("name.txt");
    namein2.open("names");
    while(getline(namein,origPackage))
    {
    CHARName = "CHAR_" + origPackage + ".xxx";
    SAName = "CHAR_" + origPackage + "_SCRIPTASSETS.xxx";
    DISMName = "DISM_" + origPackage + ".xxx";
    DISMDLCName = "DISM_" + origPackage + "_DLC.xxx";
    MKOName = "CHAR_" + origPackage + ".mko";

    cout<<"MAKE SURE TO HAVE THESE FILES IN \"Files\\Content\" Folder: "<<endl<<endl;
    cout<<"CHAR Package: "<<CHARName<<endl;
    cout<<"SCRIPTASSETS Package: "<<SAName<<endl;
    cout<<"DISM Package: "<<DISMName<<endl;
    cout<<"*DISM_DLC Package: "<<DISMDLCName<<endl;
    cout<<"MKO Package: "<<MKOName<<endl;
    cout<<"*CHAR tfc Package: "<<"CHAR_"+origPackage+".tfc"<<endl;
    cout<<"*CHAR tfc Package: "<<"CHAR_"+origPackage+"_SCRIPTASSETS.tfc"<<endl;
    cout<<"*CHAR tfc Package: "<<"DISM_"+origPackage+".tfc"<<endl;
    cout<<"*CHAR tfc Package: "<<"DISM_"+origPackage+"_DLC.tfc"<<endl;
    cout<<endl<<endl<<"*Only for some characters"<<endl;
    cout<<"================"<<endl;
    getline(namein2,name2);

    cout<<"New Costume Letter of "+origPackage+" is "<<name2[name2.length()-1];
    cout<<"."<<endl<<"Replacing strings...";
    //cin>>costumeLetter; //OLD
    costumeLetter = name2[name2.length()-1];
    cout<<endl<<endl;
    costumeName = origPackage;
    costumeName[costumeName.length()-1] = costumeLetter;
    //cin>>debug; //Debug

    nameout<<costumeName<<endl; //Print into output this costume
    //cout<<costumeName<<endl; //DEBUG ONLY


    //OPENING FILE CHAR_NAME_COSTUME.xxx
    currentfile = "PackageFiles/" + CHARName;
    saveto = CHARName;
    saveto[CHARName.length()-5] = costumeLetter;

    fin.open(currentfile.c_str(),ios::ate);
    FileSize = fin.tellg();
    fin.close();

    fin.open(currentfile.c_str(),ios::binary);
    fin>>noskipws;

    if (fin.good())
    {
    fout.open(saveto.c_str(),ios::binary);

    DATA = new unsigned char[FileSize];
    pos = 0;

    while (fin>>c)
    {
        DATA[pos] = c;
        pos++;
    }


    //SEARCHING FOR CHAR_NAME_COSTUME
    searchfor = "CHAR_" + origPackage;
    S = searchfor.length();
    subbed=0;

    for (int i = 0; i < FileSize; i++)
    {
        bool flag;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+5+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //SEARCHING FOR DISM_NAME_COSTUME
    subbed = 0;
    searchfor = "DISM_" + origPackage;

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+5+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;




    //SEARCHING FOR NAME_COSTUME_DLC
    subbed = 0;
    searchfor = origPackage+"_DLC";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //SEARCHING FOR NAME_COSTUME_DISM
    subbed = 0;
    searchfor = origPackage+"_DISM";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;

    //SEARCHING FOR NAME_COSTUME (mesh)
    subbed = 0;
    searchfor = origPackage;

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1] = costumeLetter;
            subbed++;
            break; //Only One Change
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;



    //MUST ONLY SAVE THE FILE ONCE
    //SAVING CHAR_NAME_COSTUME.xxx
    for (int i = 0; i < FileSize; i++)
        fout<<DATA[i];
    fout.close();
    } else cout<<endl<<"\tCHAR File Not Found."<<endl;

    fin.close();



    //OPENING FILE CHAR_NAME_COSTUME_SCRIPTASSETS.xxx
    currentfile = "PackageFiles/" + SAName;
    saveto = SAName;
    saveto[SAName.length()-18] = costumeLetter;

    fin.open(currentfile.c_str(),ios::ate);
    FileSize = fin.tellg();
    fin.close();

    fin.open(currentfile.c_str(),ios::binary);
    fin>>noskipws;

    if (fin.good())
    {
    fout.open(saveto.c_str(),ios::binary);

    delete [] DATA;

    DATA = new unsigned char[FileSize];
    pos = 0;

    while (fin>>c)
    {
        DATA[pos] = c;
        pos++;
    }

    //SEARCHING FOR NAME_COSTUME
    subbed = 0;
    searchfor = "CHAR_"+origPackage;

    //Implement an if statement for _A scriptassets, not all strings must be changed.
    //THIS IS A NEW VERSION TO TEST IF _A PACKS WORK
    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1+5] = costumeLetter;
            subbed++;
            if (subbed == 3)
                break;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //SEARCHING FOR .MKO
    subbed = 0;
    searchfor = ".mko";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i-1] = costumeLetter;
            subbed++;
            break;
        }


    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;




    //MUST ONLY SAVE THE FILE ONCE
    //SAVING CHAR_NAME_COSTUME_SCRIPTASSETS.xxx
    for (int i = 0; i < FileSize; i++)
        fout<<DATA[i];
    fout.close();
    } else cout<<endl<<"\tSCRIPTASSETS does not exist."<<endl;

    fin.close();




    //OPENING FILE DISM_CHAR_COSTUME.xxx
    currentfile = "PackageFiles/" + DISMName;
    saveto = DISMName;
    saveto[DISMName.length()-5] = costumeLetter;

    fin.open(currentfile.c_str(),ios::ate);
    FileSize = fin.tellg();
    fin.close();

    fin.open(currentfile.c_str(),ios::binary);
    fin>>noskipws;

    if (fin.good())
    {
    fout.open(saveto.c_str(),ios::binary);

    delete [] DATA;
    DATA = new unsigned char[FileSize];
    pos = 0;

    while (fin>>c)
    {
        DATA[pos] = c;
        pos++;
    }

    //SEARCHING FOR DISM_NAME_COSTUME
    subbed = 0;
    searchfor = "DISM_"+origPackage;

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1+5] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //SEARCHING FOR NAME_COSTUME_DISM
    subbed = 0;
    searchfor = origPackage+"_DISM";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //MUST ONLY SAVE THE FILE ONCE
    //SAVING DISM_CHAR_COSTUME.xxx
    for (int i = 0; i < FileSize; i++)
        fout<<DATA[i];

    fout.close();

    } else cout<<endl<<"\tDISM does not exist."<<endl;

    fin.close();



    //OPENING FILE DISM_CHAR_COSTUME_DLC.xxx
    currentfile = "PackageFiles/" + DISMDLCName;
    saveto = DISMDLCName;
    saveto[DISMDLCName.length()-9] = costumeLetter;

    fin.open(currentfile.c_str(),ios::ate);
    FileSize = fin.tellg();
    fin.close();

    fin.open(currentfile.c_str(),ios::binary);
    fin>>noskipws;

    if (fin.good())
    {
    fout.open(saveto.c_str(),ios::binary);

    delete [] DATA;
    DATA = new unsigned char[FileSize];
    pos = 0;

    while (fin>>c)
    {
        DATA[pos] = c;
        pos++;
    }



    //SEARCHING FOR DISM_CHAR_COSTUME_DLC
    subbed = 0;
    searchfor = "DISM_" + origPackage+"_DLC";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1+5] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //SEARCHING FOR DCHAR_COSTUME_DLC_DISM
    subbed = 0;
    searchfor = origPackage+"_DLC_DISM";

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;



    //MUST ONLY SAVE THE FILE ONCE
    //SAVING DISM_CHAR_COSTUME_DLC.xxx
    for (int i = 0; i < FileSize; i++)
        fout<<DATA[i];
    fin.close();
    fout.close();

    } else
        {
        cout<<endl<<"\t_DLC File Not Found."<<endl;
        fin.close();
        }




    //OPENING FILE CHAR_CHAR_COSTUME.mko
    currentfile = "PackageFiles/" + MKOName;
    saveto = MKOName;
    saveto[MKOName.length()-5] = costumeLetter;

    fin.open(currentfile.c_str(),ios::ate);
    FileSize = fin.tellg();
    fin.close();

    fin.open(currentfile.c_str(),ios::binary);
    fin>>noskipws;


    if (fin.good())
    {
    fout.open(saveto.c_str(),ios::binary);

    delete [] DATA;
    DATA = new unsigned char[FileSize];
    pos = 0;

    while (fin>>c)
    {
        DATA[pos] = c;
        pos++;
    }


    //SEARCHING FOR CHAR_CHAR_COSTUME
    subbed = 0;
    searchfor = "CHAR_"+origPackage;

    for (int i = 0; i < FileSize; i++)
    {
        bool flag = 0;
        for (int j = 0; j < searchfor.length(); j++)
        {
            if (tolower(DATA[j+i]) == tolower(searchfor[j]) )
                flag = 1;
            else {flag = 0; break;}
        }
        if (flag == 1)
        {
            DATA[i+origPackage.length()-1+5] = costumeLetter;
            subbed++;
        }
    }
    cout<<"REPLACED "<<subbed<<" Instances of "<<searchfor<<" in "<<currentfile<<endl;


    //MUST ONLY SAVE THE FILE ONCE
    //SAVING DISM_CHAR_COSTUME_DLC.xxx
    for (int i = 0; i < FileSize; i++)
        fout<<DATA[i];
    fin.close();
    fout.close();

    } else
    {
        fin.close();
        cout<<endl<<"\t.mko File Not Found"<<endl;
    }



       //COPY .TFC Files
        cout<<endl<<"Cloning _.tfc files..."<<endl<<endl;
        currentfile = "Files/Content/CHAR_"+origPackage+".tfc";
        saveto = "CHAR_"+costumeName+".tfc";
        itfc.open(currentfile.c_str(),ios::binary);
        itfc>>noskipws;
        if (itfc.good())
        {
            otfc.open(saveto.c_str(),ios::binary);
            while(itfc>>c)
                otfc<<c;
            otfc.close();
        } else cout<<"CHAR tfc File Not Found"<<endl;
        itfc.close();


        currentfile = "Files/Content/CHAR_"+origPackage+"_SCRIPTASSETS.tfc";
        saveto = "CHAR_"+costumeName+"_SCRIPTASSETS.tfc";
        itfc.open(currentfile.c_str(),ios::binary);
        itfc>>noskipws;
        if (itfc.good())
        {
            otfc.open(saveto.c_str(),ios::binary);
            while(itfc>>c)
                otfc<<c;
            otfc.close();
        } else cout<<"SCRIPTASSETS tfc File Not Found"<<endl;
        itfc.close();


        currentfile = "Files/Content/DISM_"+origPackage+".tfc";
        saveto = "DISM_"+costumeName+".tfc";
        itfc.open(currentfile.c_str(),ios::binary);
        itfc>>noskipws;
        if (itfc.good())
        {
            otfc.open(saveto.c_str(),ios::binary);
            while(itfc>>c)
                otfc<<c;
            otfc.close();
        } else cout<<"DISM tfc File Not Found"<<endl;
        itfc.close();


        currentfile = "Files/Content/DISM_"+origPackage+"_DLC.tfc";
        saveto = "DISM_"+costumeName+"_DLC.tfc";
        itfc.open(currentfile.c_str(),ios::binary);
        itfc>>noskipws;
        if (itfc.good())
        {
            otfc.open(saveto.c_str(),ios::binary);
            while(itfc>>c)
                otfc<<c;
            otfc.close();
        } else cout<<"_DLC tfc File Not Found"<<endl;
        itfc.close();

        system("cls");
    }
    namein.close();
    nameout.close();
    delete [] DATA;
}
