#include<iostream>
#include<fstream>
using namespace std;

void inverse_gematria(int, int[]);
void inverse_gematria(int, int[], int[]);
void rotation(int, int[], int);
void normal(int, int[]);
void vignere(int, int[]);
const string GEMATRIA[29] = {"F","U","TH","O","R","K","G","W","H","N","I","J","EO","P","X","Z","T","B","E","M","L","ING","OE","D","A","AE","Y","IO","EA"};

int main()
{

    int x, value[80], inv[80], ctr = 0; //Maximum 80 characters

    cout<<"Enter the ID, invalid to stop: ";

    while (cin>>x)
    {
        if (x < 0 || x > 28)
            break;
        ctr++; //Track the indices in an array
        value[ctr-1] = x;
    }

    cout<<"Vigenere:\n";
    vignere(ctr, value);

    cout<<"Press Any Number then Enter to exit...\n";
    cin>>x;



}

void vignere(int ctr, int value[80])
{

    ofstream fout("BruteVig_Out.txt");
    int key[80], ctr2 = 3, decrypted[80];
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
        {
            cout<<i<<j<<k<<endl;

            key[0] = i;
            key[1] = j;
            key[2] = k;

            if (ctr2 < ctr)
            {
                int x = ctr - ctr2;
                for (int z = 0; z < x; z++)
                {
                    key[ctr2+z] = key[z];
                }

            }

                fout<<"Key: ";
                for (int z = 0; z < 3; z++)
                    fout<<GEMATRIA[key[z]]<<" ";
                fout<<endl;
                for (int z = 0; z < ctr; z++)
                {
                    decrypted[z] = value[z] - key[z];
                    if (decrypted[z] < 0)
                        decrypted[z] += 29;

                    fout<<GEMATRIA[decrypted[z]]<<" ";
                }
                fout<<endl;


        }

    }





}

void normal(int ctr, int value[80])
{
    for (int i = 0; i < ctr; i++)
        cout<<GEMATRIA[value[i]]<<" ";
    cout<<endl;
}

void rotation(int ctr, int value[80], int index)
{
    for (int i = 0; i < ctr; i++)
    {
        cout<<GEMATRIA[(value[i]+index)%29]<<" ";
    }
    cout<<endl;
}

void inverse_gematria(int ctr, int value[80])
{
    for (int i = 0; i < ctr; i++)
    {
        cout<<GEMATRIA[29-value[i]-1]<<" ";
    }
    cout<<endl;
}

void inverse_gematria(int ctr, int value[80], int inv[80])
{
    for (int i = 0; i < ctr; i++)
    {
        inv[i] = 29-value[i]-1;
    }
}
