#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

int khux_random(int seed)
{
    return 0x19660D * seed + 0x3C6EF35F;
}

unsigned int chartoint4(unsigned char* c)
{
    return c[0]+ c[1] * 0x100 + c[2] * 0x10000 + c[3] * 0x1000000;
}

unsigned int chartoint2(unsigned char* c)
{
    return c[0]+ c[1] * 0x100;
}

int main(int argc, const char* args[])
{
    int fcount = 0, cdLen;
    string cd, *names;
    ifstream fin("Dir_Out.txt");
    while (getline(fin, cd))
        fcount++;
    fin.close();
    fin.open("Dir_Out.txt");
    fcount--;
    names = new string [fcount];

    getline(fin,cd);
    cdLen = cd.length();

    for (int i = 0; i < fcount; i++)
    {
        getline(fin,names[i]);
        names[i].erase(0,cdLen+1);
        for (int j = 0; j < names[i].length(); j++)
        if (names[i][j] == '\\')
            names[i][j] = '/';
    }


    string openName="", openName2="";
    ifstream finBGAD;
    string OPENNow = args[2];
    ofstream fout(OPENNow.c_str(),ios::binary);

    for (int i = 0; i < fcount; i++)
    {
        openName2 = names[i];
        openName = args[1];
        openName += "/";
        openName += openName2;// bla.mp4_folder/File

        unsigned char *name;
        unsigned char *data,*data2;


        cout<<"Reading "<<openName2<<"...\n";
        finBGAD.open(openName.c_str(), ios::binary | ios::ate);
        if (!finBGAD.good())
        {
            cout<<"Couldn't find " + openName + " to open! Exiting!";
            return 1;
        }

        cout<<"Size: "<<finBGAD.tellg()<<" bytes."<<endl;
        cout<<"Name Length: "<<openName2.length()<<" characters."<<endl;

        name = new unsigned char [openName2.length()];
        data = new unsigned char [finBGAD.tellg()];

        for (int i = 0; i < openName2.length(); i++)
            name[i] = (unsigned char)(openName2[i]);

        int key = finBGAD.tellg();
        int count = (openName2.length()+3) >> 2;
        int temp = key;

        for (int i = 0; i < count; i++)
        {
            temp = chartoint4(name +i*4);
            key = khux_random(key);
            temp ^= key;

            for (int j = 0; j < 4; j++)
            {
                name[j + i*4] = char(temp);
                temp >>= 8;
            }
        }

        //Write the part of the header:
        {
        unsigned char header[10] = {0x42, 0x47, 0x41, 0x44, 0x02, 0x00, 0x00, 0x00, 0x18, 0x00};
        for (int i = 0; i < 10; i++)
        {
            fout<<header[i];
        }
        //Write the name length
        unsigned short name_length = openName2.length();
        fout<<(unsigned char)(name_length);
        name_length >>= 8;
        fout<<(unsigned char)(name_length);
        //Write rest of header
        fout<<(unsigned char)(0x02)<<(unsigned char)(0x00)<<(unsigned char)(0x00)<<(unsigned char)(0x00);
        //Write Data Size
        unsigned int data_size = finBGAD.tellg();
        fout<<(unsigned char)(data_size);
        data_size >>= 8;
        fout<<(unsigned char)(data_size);
        data_size >>= 8;
        fout<<(unsigned char)(data_size);
        data_size >>= 8;
        fout<<(unsigned char)(data_size);
        //Write uncompressed size
        unsigned int data_size2 = finBGAD.tellg();
        fout<<(unsigned char)(data_size2);
        data_size2 >>= 8;
        fout<<(unsigned char)(data_size2);
        data_size2 >>= 8;
        fout<<(unsigned char)(data_size2);
        data_size2 >>= 8;
        fout<<(unsigned char)(data_size2);
        }

        //Write Name encoded
        for (int i = 0; i < openName2.length(); i++)
        {
            fout<<name[i];
        }


        //fin.tellg() will stop working after this line, so I will back it up.
        unsigned int fsize = finBGAD.tellg();

        //For some reason I can't read data in ate mode
        finBGAD.close();
        finBGAD.open(openName.c_str(), ios::binary);
        finBGAD>>noskipws;

        for (int i = 0; i < fsize; i++) //For now, the entire file will be written into memory, need better optimization
        {
            finBGAD>>data[i];

        }

        key = openName2.length();
        count = (fsize +3) >> 2; //I want Data Size to be same as Decompressed because I won't decompress.
        temp = key;

        for (int i = 0; i < count; i++)
        {
            temp = chartoint4(data + i*4);
            key = khux_random(key);
            temp ^= key;

            for (int j = 0; j < 4; j++)
            {
                data[j + i*4] = temp;
                temp >>= 8;
            }
        }
        //Data Encoded


        for (int i = 0; i < fsize; i++)
            fout<<data[i];

        finBGAD.close();
        cout<<"Done!\n";
    }

    fin.close();
    fout.close();
    cout<<"MP4 file written successfully!";
}
