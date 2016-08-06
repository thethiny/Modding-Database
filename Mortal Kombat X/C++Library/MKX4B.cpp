#include"MKX4B.h"

int H2I(unsigned char Array[4])
{
    int x = 0;
    x += (Array[3]) * pow(256,0);
    x += (Array[2]) * pow(256,1);
    x += (Array[1]) * pow(256,2);
    x += (Array[0]) * pow(256,3);
    return x;
}

void I2H(int x, unsigned char H[4])
{
    H[0] = x/0x1000000;
    x %= 0x1000000;
    H[1] = x/0x10000 ;
    x %= 0x10000;
    H[2] = x/0x100;
    H[3] = x % 0x100;

}

void uI2H(unsigned int x, unsigned char H[4])
{
    H[0] = x/0x1000000;
    x %= 0x1000000;
    H[1] = x/0x10000 ;
    x %= 0x10000;
    H[2] = x/0x100;
    H[3] = x % 0x100;

}

void writeLE(unsigned char H[4],ofstream& fout)
{
    for (int i = 0; i < 4; i++)
        fout<<H[3-i];
}

void discard(ifstream& fin, int x)
{
    unsigned char H;
    for (int i = 0; i < x; i++)
        fin>>H;
}

void write(ifstream& fin, ofstream& fout, int amnt)
{
    unsigned char H;
    for (int i = 0; i < amnt; i++)
    {
        fin>>H;
        fout<<H;
    }
}

void writeNull(ofstream& fout)
{
    fout<<char(0)<<char(0)<<char(0)<<char(0);
}

void writeRand(ofstream& fout,int x)
{
    srand(time(0));
    for (int i = 0; i < x; i++)
        fout<<char(rand());
}

void read(ifstream& fin, unsigned char H[4])
{
    fin>>H[3];
    fin>>H[2];
    fin>>H[1];
    fin>>H[0];
}
