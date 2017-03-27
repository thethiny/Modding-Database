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

    cout<<"Normal: ";
    normal(ctr, value);

    cout<<"Inverse Gematria: ";
    inverse_gematria(ctr, value);

    for (int i = 1; i < 29; i++)
    {
        cout<<"Rotate by "<<i<<": ";
        rotation(ctr, value, i);
    }

    for (int i = 28; i >= 1; i--)
    {
        cout<<"Rotate Inverse (Inverse with key) by "<<29 - i<<": ";
        inverse_gematria(ctr,value,inv);
        rotation(ctr, inv, 29 - i);
    }

    cout<<"Vigenere:\n";
    vignere(ctr, value);

    cout<<"Press Any Number then Enter to exit...\n";
    cin>>x;



}

void vignere(int ctr, int value[80])
{
    int key[80], ctr2 = 0, decrypted[80];
    cout<<"Enter the key: ";
    while(cin>>key[ctr2])
    {
        if (key[ctr2]< 0 || key[ctr2] > 28)
            break;
        ctr2++;
    }
    if (ctr2 < ctr)
    {
        int x = ctr - ctr2;
        for (int i = 0; i < x; i++)
        {
            key[ctr2+i] = key[i];
        }

    }

    /*
    cout<<"Key is: ";

    for(int i = 0; i < ctr; i++)
        cout<<key[i]<<" ";
    cout<<endl;*/

    for (int i = 0; i < ctr; i++)
    {
        decrypted[i] = value[i] - key[i];
        if (decrypted[i] < 0)
            decrypted[i] += 29;

        cout<<GEMATRIA[decrypted[i]]<<" ";
    }
    cout<<endl;


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
