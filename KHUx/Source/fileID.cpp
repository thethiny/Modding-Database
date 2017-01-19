#include<iostream>
#include<fstream>
#include<cstdlib>
#include<unistd.h>
using namespace std;

string compare (unsigned char []);

int main(int argc, const char * argv[])
{
    int ignore;
    unsigned char C[4];
    string cmd, fName, cd, file;
    ifstream fin, fin2;
    //ofstream fout("RenameLog");
    if (argc < 2)
    {
        cout<<"Folder name: ";
        cin>>fName;
    }
    else fName = argv[1];

    system("cd > AllFiles.txt");
    cmd = "DIR /S /B /A:-D " + fName + ">> AllFiles.txt";

    system(cmd.c_str());

    fin.open("AllFiles.txt");

    getline(fin, cd);

    while(getline(fin,file))
    {
        //Prevent Double Run
        if (file[file.length()-1] != 't' && file[file.length()-2] != 'u' && file[file.length()-3] != 'o')
            continue;



        file.erase(0,cd.length()+1);

        for (int i = 0; i < file.length(); i++)
            if (file[i] == '\\')
                file[i] = '/';

        fin2.open(file.c_str(), ios::binary);
        fin2>>C[0]>>C[1]>>C[2]>>C[3];
        fin2.close();

        file.erase(0,fName.length()+1);

        cout<<file<<" -> ";

        string ext = compare(C);

            chdir(fName.c_str());

            string prev = file;

            file.erase(file.length()-3,3);
            file +=ext;

            cmd = "ren " + prev + " " + file;

            cout<<file<<endl;

            system(cmd.c_str());



            chdir("..\\");
    }

    fin.close();

    system("DEL /S /Q AllFiles.txt > nul");


}

string compare (unsigned char H[4])
{
    long long int sum = 0;
    sum |= H[0];
    sum <<= 8;
    sum |= H[1];
    sum <<= 8;
    sum |= H[2];
    sum <<= 8;
    sum |= H[3];

    cout<<hex<<"Header: 0x"<<sum<<" -> ";
    switch(sum)
    {
        case 0x414b4220: return "akb"; break;
        case 0x89425446: return "png"; break;
        case 0xefbbbf3c: return "plist"; break;
        case 0x4c574600:
        case 0x5df90000: return "lwf"; break;
        case 0x4a4d5000:
        case 0x424d4900:
        case 0x434c5300:
        case 0x43485000:
        case 0x53544700:
        case 0x4d415000: return "bin"; break;
        default: return "";
    }

}
