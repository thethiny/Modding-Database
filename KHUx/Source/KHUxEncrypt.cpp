#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
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
    if (argc <2)
    {
        cout<<"Usage: "<<args[0]<<" FileName InternalName(Optional)"<<endl<<"Internal name is when you want to rename the extracted file but leave it intact internally\nExample: Khux_Encrypt image.png data\nwill encode the file image.png as if it was called \"data\"";
        return 1;
    }
    ifstream fin(args[1], ios::binary | ios::ate);
    fin>>noskipws;
    if (fin.good())
        cout<<"Opened "<<args[1]<<" Succesfully!"<<endl;
    else
    {
        cout<<"Error 404 "<<args[1]<<" not found!"<<endl;
        return 404;
    }

    string openName;
    if (argc == 2)
        openName = args[1];
    else if (argc >2)
        openName = args[2];

    stringstream fopen("");
    fopen<<args[1]<<".BGAD";
    ofstream fout(fopen.str(),ios::binary);

    unsigned char *name;
    unsigned char *data,*data2;

    cout<<"Size: "<<fin.tellg()<<" bytes."<<endl;
    cout<<"Name Length: "<<openName.length()<<" characters."<<endl;

    name = new unsigned char [openName.length()];
    data = new unsigned char [fin.tellg()];
    //data2 = new unsigned char [fin.tellg()];

    for (int i = 0; i < openName.length(); i++)
        name[i] = (unsigned char)(openName[i]);

    int key = fin.tellg();
    int count = (openName.length()+3) >> 2;
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
    unsigned short name_length = openName.length();
    fout<<(unsigned char)(name_length);
    name_length >>= 8;
    fout<<(unsigned char)(name_length);
    //Write rest of header
    fout<<(unsigned char)(0x02)<<(unsigned char)(0x00)<<(unsigned char)(0x00)<<(unsigned char)(0x00);
    //Write Data Size
    unsigned int data_size = fin.tellg();
    fout<<(unsigned char)(data_size);
    data_size >>= 8;
    fout<<(unsigned char)(data_size);
    data_size >>= 8;
    fout<<(unsigned char)(data_size);
    data_size >>= 8;
    fout<<(unsigned char)(data_size);
    //Write uncompressed size
    unsigned int data_size2 = fin.tellg();
    fout<<(unsigned char)(data_size2);
    data_size2 >>= 8;
    fout<<(unsigned char)(data_size2);
    data_size2 >>= 8;
    fout<<(unsigned char)(data_size2);
    data_size2 >>= 8;
    fout<<(unsigned char)(data_size2);
    }

    //Write Name encoded
    for (int i = 0; i < openName.length(); i++)
    {
        fout<<name[i];
    }


    //fin.tellg() will stop working after this line, so I will back it up.
    unsigned int fsize = fin.tellg();

    //For some reason I can't read data in ate mode
    fin.close();
    fin.open(args[1], ios::binary);
    fin>>noskipws;

    for (int i = 0; i < fsize; i++) //For now, the entire file will be written into memory, need better optimization
    {
        fin>>data[i];

    }

    key = openName.length();
    count = (fsize +3) >> 2; //I want Data Size to be same as Decompressed because I won't decompress.
    temp = key;

    for (int i = 0; i < count; i++)
    {
        temp = chartoint4(data + i*4);
        key = khux_random(key);
        temp ^= key;

        for (int j = 0; j < 4; j++)
        {
            //data2[j + i*4] = temp;
            data[j + i*4] = temp;
            temp >>= 8;
        }
    }
    //Data Encoded


    for (int i = 0; i < fsize; i++)
        fout<<data[i];

    fin.close();
    fout.close();
    cout<<"BGAD file written succesfully into "<<fopen.str();
}
