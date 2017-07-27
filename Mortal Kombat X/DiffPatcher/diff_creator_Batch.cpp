#include<iostream>
#include<fstream>
using namespace std;

int BATCH_SIZE = 4;

int main(int argv, const char* argc[])
{
    ifstream fin, fin2;
    ofstream fout, foutlog;
    string base, diff;
    long long ctr = 0, len = 0;
    unsigned char c1, c2, H[4];
    bool f1=1, f2=1, in = 0, bt = 0;
    int batch = 0;

    if (argv > 1)
    {
        if (argc[1][0] == '-' && argc[1][1] == 'b')
            bt = 1;
        else base = argc[1];
    }
    if (argv > 2)
    {
        diff = argc[2];
    }
    if (argv > 3 || bt)
    {
        cout<<"For Mesh Swaps: Recommended Batch Size is Character Name Length+1\n";
        cout<<"For Texture Change: Recommended Batch Size is 64\n";
        cout<<"For slight change such as material swap: Recommended size is 3\n";
        cout<<"You might choose whatever number you like, I personally use 15\n";
        cout<<"Enter your Batch Size: ";
        cin>>::BATCH_SIZE;
    }

    if (argv == 1 || bt)
    {
        cout<<"Enter Base File Name: ";
        cin>>base;
        cout<<"Enter Modified File Name: ";
        cin>>diff;
    }
    else if (argv == 2)
    {
        cout<<"Enter Modified File Name: ";
        cin>>diff;
    }

    fin.open(base.c_str(), ios::binary);
    if (!fin.good())
    {
        cerr<<"Cannot open Base File "<<base<<".";
        return 1;
    }

    fin2.open(diff.c_str(), ios::binary);
    if (!fin2.good())
    {
        cerr<<"Cannot open Modified File "<<diff<<".";
        return 2;
    }

    cout<<"Creating..."<<endl;

    fout.open((diff+".diff").c_str(), ios::binary);
    foutlog.open((diff+".difflog").c_str(), ios::binary);
    fin>>noskipws;
    fin2>>noskipws;

    while(f1 && f2)
    {
        if (!(fin>>c1))
        {
            f1 = 0;
        }
        if (!(fin2>>c2))
        {
            f2 = 0;
        }
        if (!(f1 && f2))
            break;

        if (c1 != c2)
        {
            batch = 0;
            if (!in)
            {
                foutlog<<(unsigned char)(ctr>>24)<<(unsigned char)(ctr>>16)<<(unsigned char)(ctr>>8)<<(unsigned char)(ctr);
                len = 0;
            }
            in = 1;
            fout<<c2;
            len++;
        }
        else
        {
                if (in)
                {
                    if (batch >= BATCH_SIZE)
                    {
                        foutlog<<(unsigned char)(len>>24)<<(unsigned char)(len>>16)<<(unsigned char)(len>>8)<<(unsigned char)(len);
                        len = 0;
                        foutlog<<char(0); //So that the program knows the type is '0', which means replace. if type is '1' then that means delete or diff is shorter.
                        batch = -1;
                    }
                    else
                    {
                        batch++;
                        len++;
                        fout<<c2;
                        in = 1;
                    }

                }
                if (batch == -1)
                    in = 0;

        }

        ctr++;

    }

    if (in) //if it broke while still in
    {
        foutlog<<(unsigned char)(len>>24)<<(unsigned char)(len>>16)<<(unsigned char)(len>>8)<<(unsigned char)(len);
        foutlog<<char(0);
        len = 0;
        in = 0;
    }

    if (f1) //If base still has some stuff inside
    {
        foutlog<<(unsigned char)(ctr>>24)<<(unsigned char)(ctr>>16)<<(unsigned char)(ctr>>8)<<(unsigned char)(ctr);
        len = 1;

        while(fin>>c1)
        {
            len++;
        }
        foutlog<<(unsigned char)(len>>24)<<(unsigned char)(len>>16)<<(unsigned char)(len>>8)<<(unsigned char)(len);
        foutlog<<char(1);

    }
    else if (f2) //if difference file is longer
    {
        foutlog<<(unsigned char)(ctr>>24)<<(unsigned char)(ctr>>16)<<(unsigned char)(ctr>>8)<<(unsigned char)(ctr);
        //cout<<hex<<ctr;
        len++;
        fout<<c2;

        while(fin2>>c2)
        {
            fout<<c2;
            len++;
        }

        foutlog<<(unsigned char)(len>>24)<<(unsigned char)(len>>16)<<(unsigned char)(len>>8)<<(unsigned char)(len);
        foutlog<<char(2); //'2' means "add"

    }


    cout<<"Done!";
    cout<<endl<<"Output files "<<diff<<".diff and "<<diff<<".difflog have been created.";
    cout<<endl<<"Share the two files along with this tool ;)";
    fin.close();
    fin2.close();
    fout.close();
    foutlog.close();

}
