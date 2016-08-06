#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <sstream>
using namespace std;
void GetFirstPTR(string );

    ifstream fin;
    ofstream fout;
    char h_offsetE[8], h_sizeE[8];

int main()
{
    unsigned char c;
    string File_user;
    cout<<"============================================================\n\n";
    cout<<setw(54)<<"MKX Package File Structure Adjuster by thethiny\n";
    cout<<setw(55)<<right<<"Special Thanks to UncleFestor and the MKKommunity\n"<<"\n============================================================\n\n";
    cout<<"Enter File Name without .xxx: ";
    getline(cin, File_user);
    GetFirstPTR(File_user);
    string File_out = File_user;
    File_user += ".xxx";
    File_out += "_out.xxx";


    // Get File Size to Open
    fin.open(File_user.c_str(),ios::ate);
    int FileSize = fin.tellg();
    fin.close();
    unsigned char* c_Hex = new unsigned char[FileSize];
//  unsigned char c_Hex[FileSize];

    //Open Input and Output Folders as Hex
    fin.open(File_user.c_str(), ios::binary);
    fout.open(File_out.c_str(), ios::binary);
    fin >> noskipws;
    int i = 0;
    while (fin >> c)
        {
            c_Hex[i] = c;
            i++;
        }
    //Debug Hex
   // if ((int)c_Hex[174587] == 15*1+8*16 )
   //     cout<<"yes";
   // cout<<hex<<(int)c_Hex[174587];

   //Convert to Hex
   for (int u = 0; u < 8; u++)
   {
    if (h_offsetE[u] == '0' )
        h_offsetE[u] = 0;
    if (h_offsetE[u] == '1' )
        h_offsetE[u] = 1;
    if (h_offsetE[u] == '2' )
        h_offsetE[u] = 2;
    if (h_offsetE[u] == '3' )
        h_offsetE[u] = 3;
    if (h_offsetE[u] == '4' )
        h_offsetE[u] = 4;
    if (h_offsetE[u] == '5' )
        h_offsetE[u] = 5;
    if (h_offsetE[u] == '6' )
        h_offsetE[u] = 6;
    if (h_offsetE[u] == '7' )
        h_offsetE[u] = 7;
    if (h_offsetE[u] == '8' )
        h_offsetE[u] = 8;
    if (h_offsetE[u] == '9' )
        h_offsetE[u] = 9;
    if (h_offsetE[u] == 'A' || h_offsetE[u] == 'a' )
        h_offsetE[u] = 10;
    if (h_offsetE[u] == 'B' || h_offsetE[u] == 'b' )
        h_offsetE[u] = 11;
    if (h_offsetE[u] == 'C' || h_offsetE[u] == 'c' )
        h_offsetE[u] = 12;
    if (h_offsetE[u] == 'D' || h_offsetE[u] == 'd' )
        h_offsetE[u] = 13;
    if (h_offsetE[u] == 'E' || h_offsetE[u] == 'e' )
        h_offsetE[u] = 14;
    if (h_offsetE[u] == 'F' || h_offsetE[u] == 'f' )
        h_offsetE[u] = 15;
    if (h_sizeE[u] == '0' )
        h_sizeE[u] = 0;
    if (h_sizeE[u] == '1' )
        h_sizeE[u] = 1;
    if (h_sizeE[u] == '2' )
        h_sizeE[u] = 2;
    if (h_sizeE[u] == '3' )
        h_sizeE[u] = 3;
    if (h_sizeE[u] == '4' )
        h_sizeE[u] = 4;
    if (h_sizeE[u] == '5' )
        h_sizeE[u] = 5;
    if (h_sizeE[u] == '6' )
        h_sizeE[u] = 6;
    if (h_sizeE[u] == '7' )
        h_sizeE[u] = 7;
    if (h_sizeE[u] == '8' )
        h_sizeE[u] = 8;
    if (h_sizeE[u] == '9' )
        h_sizeE[u] = 9;
    if (h_sizeE[u] == 'A' || h_sizeE[u] == 'a' )
        h_sizeE[u] = 10;
    if (h_sizeE[u] == 'B' || h_sizeE[u] == 'b' )
        h_sizeE[u] = 11;
    if (h_sizeE[u] == 'C' || h_sizeE[u] == 'c' )
        h_sizeE[u] = 12;
    if (h_sizeE[u] == 'D' || h_sizeE[u] == 'd' )
        h_sizeE[u] = 13;
    if (h_sizeE[u] == 'E' || h_sizeE[u] == 'e' )
        h_sizeE[u] = 14;
    if (h_sizeE[u] == 'F' || h_sizeE[u] == 'f' )
        h_sizeE[u] = 15;
   }


    unsigned char h_offsetH[4],h_sizeH[4];
    h_offsetH[0] = h_offsetE[1] + h_offsetE[0]*16;
    h_offsetH[1] = (int)h_offsetE[3] + (int)h_offsetE[2]*16;
    h_offsetH[2] = (int)h_offsetE[5] + (int)h_offsetE[4]*16;
    h_offsetH[3] = (int)h_offsetE[7] + (int)h_offsetE[6]*16;

    h_sizeH[0] = (int)h_sizeE[1] + (int)h_sizeE[0]*16;
    h_sizeH[1] = (int)h_sizeE[3] + (int)h_sizeE[2]*16;
    h_sizeH[2] = (int)h_sizeE[5] + (int)h_sizeE[4]*16;
    h_sizeH[3] = (int)h_sizeE[7] + (int)h_sizeE[6]*16;
    /* Debug
    cout<<(int)h_offsetE[0];
    cout<<(int)h_offsetE[1];
    cout<<endl;

    cout<<h_sizeH[0];
    cout<<h_sizeH[1];
    cout<<h_sizeH[2];
    cout<<h_sizeH[3];
    cout<<h_offsetH[0];
    cout<<h_offsetH[1];
    cout<<h_offsetH[2];
    cout<<h_offsetH[3];
    cout<<endl<<(int)c_Hex[174583];
    cout<<(int)c_Hex[174584];
    cout<<(int)c_Hex[174585];
    cout<<(int)c_Hex[174586];
    */
    int k = 0;
    while (k < FileSize)
    {
        if ( (int)c_Hex[k] == h_sizeH[0])
            {
                if ( (int)c_Hex[k+1] == h_sizeH[1] )
                {
                    if ( (int)c_Hex[k+2] == h_sizeH[2] )
                    {
                        if ( (int)c_Hex[k+3] == h_sizeH[3] )
                        {
                            if ( (int)c_Hex[k+4] == h_offsetH[0] )
                            {
                                if ( (int)c_Hex[k+5] == h_offsetH[1] )
                                {
                                    if ( (int)c_Hex[k+6] == h_offsetH[2] )
                                    {
                                        if ( (int)c_Hex[k+7] == h_offsetH[3] )
                                        {
                                            cout<<hex<<"0x"<<k<<" (Tool Start)"<<endl;
                                            int StartLoc = k;
                                            break;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
            k++;

    }


    unsigned char FoundO[4],FoundS[4],FoundOE[4],FoundSE[4];



    while (k < FileSize)
    {

    if (c_Hex[k+92] == 0 && c_Hex[k+93] == 0 && c_Hex[k+94] == 0 && c_Hex[k+95] == 0)
    {
        cout<<hex<<"0x"<<k<<" (Tool End)\n\nSaving File...\n\n";
        break;
    }

    for (int i = 0; i < 4; i++)
    {
        FoundS[i] = c_Hex[k+i];
        FoundO[i] = c_Hex[k+i+4];
    }

    FoundOE[0] = FoundO[3];
    FoundOE[1] = FoundO[2];
    FoundOE[2] = FoundO[1];
    FoundOE[3] = FoundO[0];

    FoundSE[0] = FoundS[3];
    FoundSE[1] = FoundS[2];
    FoundSE[2] = FoundS[1];
    FoundSE[3] = FoundS[0];

    stringstream buffer;
    stringstream buffer2;

    for (int i = 0; i < 4; i++)
    {
        buffer<<hex<<setw(2)<<setfill('0')<<(int)FoundOE[i];
        buffer2<<hex<<setw(2)<<setfill('0')<<(int)FoundSE[i];
    }



    string testnow = buffer.str();
    string testnow2 = buffer2.str();

       //Convert to Hex
   for (int u = 0; u < 8; u++)
   {
    if (testnow[u] == '0' )
        testnow[u] = 0;
    if (testnow[u] == '1' )
        testnow[u] = 1;
    if (testnow[u] == '2' )
        testnow[u] = 2;
    if (testnow[u] == '3' )
        testnow[u] = 3;
    if (testnow[u] == '4' )
        testnow[u] = 4;
    if (testnow[u] == '5' )
        testnow[u] = 5;
    if (testnow[u] == '6' )
        testnow[u] = 6;
    if (testnow[u] == '7' )
        testnow[u] = 7;
    if (testnow[u] == '8' )
        testnow[u] = 8;
    if (testnow[u] == '9' )
        testnow[u] = 9;
    if (testnow[u] == 'A' || testnow[u] == 'a' )
        testnow[u] = 10;
    if (testnow[u] == 'B' || testnow[u] == 'b' )
        testnow[u] = 11;
    if (testnow[u] == 'C' || testnow[u] == 'c' )
        testnow[u] = 12;
    if (testnow[u] == 'D' || testnow[u] == 'd' )
        testnow[u] = 13;
    if (testnow[u] == 'E' || testnow[u] == 'e' )
        testnow[u] = 14;
    if (testnow[u] == 'F' || testnow[u] == 'f' )
        testnow[u] = 15;
    if (testnow2[u] == '0' )
        testnow2[u] = 0;
    if (testnow2[u] == '1' )
        testnow2[u] = 1;
    if (testnow2[u] == '2' )
        testnow2[u] = 2;
    if (testnow2[u] == '3' )
        testnow2[u] = 3;
    if (testnow2[u] == '4' )
        testnow2[u] = 4;
    if (testnow2[u] == '5' )
        testnow2[u] = 5;
    if (testnow2[u] == '6' )
        testnow2[u] = 6;
    if (testnow2[u] == '7' )
        testnow2[u] = 7;
    if (testnow2[u] == '8' )
        testnow2[u] = 8;
    if (testnow2[u] == '9' )
        testnow2[u] = 9;
    if (testnow2[u] == 'A' || testnow2[u] == 'a' )
        testnow2[u] = 10;
    if (testnow2[u] == 'B' || testnow2[u] == 'b' )
        testnow2[u] = 11;
    if (testnow2[u] == 'C' || testnow2[u] == 'c' )
        testnow2[u] = 12;
    if (testnow2[u] == 'D' || testnow2[u] == 'd' )
        testnow2[u] = 13;
    if (testnow2[u] == 'E' || testnow2[u] == 'e' )
        testnow2[u] = 14;
    if (testnow2[u] == 'F' || testnow2[u] == 'f' )
        testnow2[u] = 15;
   }

   int FoundOI = testnow[7]*pow(16,0)+ testnow[6]*pow(16,1)+ testnow[5]*pow(16,2)+ testnow[4]*pow(16,3)+ testnow[3]*pow(16,4)+ testnow[2]*pow(16,5)+ testnow[1]*pow(16,6)+ testnow[0]*pow(16,7);
   int FoundSI = testnow2[7]*pow(16,0)+ testnow2[6]*pow(16,1)+ testnow2[5]*pow(16,2)+ testnow2[4]*pow(16,3)+ testnow2[3]*pow(16,4)+ testnow2[2]*pow(16,5)+ testnow2[1]*pow(16,6)+ testnow2[0]*pow(16,7);
   //cout<<endl<<FoundOI<<endl<<FoundSI;

    stringstream buffer3;
    int nextmustbe = FoundOI+FoundSI;
    buffer3<<hex<<setw(8)<<setfill('0')<<nextmustbe;

    testnow = buffer3.str();
    //cout<<endl<<testnow;

    unsigned char now[8];
//    01234567
//    67452301

    now[0] = testnow[6];
    now[1] = testnow[7];
    now[2] = testnow[4];
    now[3] = testnow[5];
    now[4] = testnow[2];
    now[5] = testnow[3];
    now[6] = testnow[0];
    now[7] = testnow[1];
    //cout<<endl<<"Projected: "<<now<<endl;

       for (int u = 0; u < 8; u++)
   {
    if (now[u] == '0' )
        now[u] = 0;
    if (now[u] == '1' )
        now[u] = 1;
    if (now[u] == '2' )
        now[u] = 2;
    if (now[u] == '3' )
        now[u] = 3;
    if (now[u] == '4' )
        now[u] = 4;
    if (now[u] == '5' )
        now[u] = 5;
    if (now[u] == '6' )
        now[u] = 6;
    if (now[u] == '7' )
        now[u] = 7;
    if (now[u] == '8' )
        now[u] = 8;
    if (now[u] == '9' )
        now[u] = 9;
    if (now[u] == 'A' || now[u] == 'a' )
        now[u] = 10;
    if (now[u] == 'B' || now[u] == 'b' )
        now[u] = 11;
    if (now[u] == 'C' || now[u] == 'c' )
        now[u] = 12;
    if (now[u] == 'D' || now[u] == 'd' )
        now[u] = 13;
    if (now[u] == 'E' || now[u] == 'e' )
        now[u] = 14;
    if (now[u] == 'F' || now[u] == 'f' )
        now[u] = 15;
   }

    unsigned char c_Hextemp[4];
    c_Hextemp[0] = now[1]+now[0]*16;
    c_Hextemp[1] = now[3]+now[2]*16;
    c_Hextemp[2] = now[5]+now[4]*16;
    c_Hextemp[3] = now[7]+now[6]*16;
    //cout<<endl<<hex<<setw(2)<<setfill('0')<<(int)c_Hextemp[3];


        if (c_Hextemp[0] != c_Hex[k+92] || c_Hextemp[1] != c_Hex[k+93] || c_Hextemp[2] != c_Hex[k+94] || c_Hextemp[3] != c_Hex[k+95] )
        {


            //else
            {
                for (int i = 0; i < 4; i++)
                c_Hex[k+92+i] = c_Hextemp[i];
                //cout<<endl<<"replaced"<<endl;
            }

        }
       // else cout<<endl<<"Didn't Replace ANySHISHE"<<endl;

            k += 88;
}





    //Write to File

    int j = 0;
    while (j < FileSize)
    {
        fout << c_Hex[j];
        j++;
    }


    return 0;
}

void GetFirstPTR(string TFile)
{
    string ignore;
    char h_offset[8], h_size[8];
    TFile += ".txt";
    fin.open(TFile.c_str());
    getline(fin, ignore);
    getline(fin, ignore);
    ignore = fin.get();
    ignore = fin.get();
    ignore = fin.get();
    ignore = fin.get();
    ignore = fin.get();
    for (int i = 0; i < 8; i++ )
    {
        h_offset[i] = fin.get();
        if (h_offset[i] == ' ')
            h_offset[i] = '0';
    }

    ignore = fin.get();

    for (int i = 0; i < 8; i++ )
    {
        h_size[i] = fin.get();
        if (h_size[i] == ' ')
            h_size[i] = '0';
    }


    //Write in Little Endian
    //01 23 45 67 = 67 45 23 01
    h_offsetE[7] = h_offset[1];
    h_offsetE[6] = h_offset[0];
    h_offsetE[5] = h_offset[3];
    h_offsetE[4] = h_offset[2];
    h_offsetE[3] = h_offset[5];
    h_offsetE[2] = h_offset[4];
    h_offsetE[1] = h_offset[7];
    h_offsetE[0] = h_offset[6];

    h_sizeE[7] = h_size[1];
    h_sizeE[6] = h_size[0];
    h_sizeE[5] = h_size[3];
    h_sizeE[4] = h_size[2];
    h_sizeE[3] = h_size[5];
    h_sizeE[2] = h_size[4];
    h_sizeE[1] = h_size[7];
    h_sizeE[0] = h_size[6];


    cout<<"\nLoading the Character's files...\nReading Text File...\n\n";
    cout<<"First File In Package's Offset: ";
    for (int i = 0; i < 8; i++)
    {
        cout<<h_offsetE[i];
    }
    cout<<"\n";



    cout<<"Its Size: ";
    for (int i = 0; i < 8; i++)
    {
        cout<<h_sizeE[i];
    }
    cout<<"\n\n";
    fin.close();

}
