#include"F:\Games\Mortal Kombat X\Hacks\C++Library\MKX4B.cpp"

int main()
{
    ifstream fin;
    ofstream fout;
    int size,ctr=0,ctr2=0,DATA[4],x;
    unsigned char H[4],X,*D,create[2048];

    try{
    fin.open("Input/CombinedReferencer.ObjectReferencer",ios::ate);
    if (!fin.good())
        throw 0;
    size = fin.tellg();
    fin.close();
    fin.open("Input/CombinedReferencer.ObjectReferencer",ios::binary);
    fin>>noskipws;
    fout.open("CombinedReferencer.ObjectReferencer.Out",ios::binary);
    read(fin,H);
    DATA[0] = H2I(H); //NameTable
    discard(fin,4);
    read(fin,H);
    DATA[1] = H2I(H); //Export?
    discard(fin,4);
    read(fin,H);
    DATA[2] = H2I(H); //Previous Size of File - 20
    discard(fin,8);

    D = new unsigned char[8200]; //create size *4 + 8

    /*for (int i = 0; i < (DATA[2] -4)/4; i++)
    {
        read(fin,H);
        D[i*4] = H[3];
        D[i*4+1] = H[2];
        D[i*4+2] = H[1];
        D[i*4+3] = H[0];
        ctr++;
        cout<<hex<<int(D[i*4])<<" ";
    }*/
    while (fin>>X)
    {
        D[ctr] = X;
        ctr++;
    }
    //cout<<dec<<"Objects: "<<ctr/4 -2;

    x = 0;
    while(x!= -1)
    {
        cout<<"Enter Export Table Number (type -1 to stop): ";
        cin>>x;
        if (x == -1)
            break;
        I2H(x,H);
        create[ctr2++] = H[3];
        create[ctr2++] = H[2];
        create[ctr2++] = H[1];
        create[ctr2++] = H[0];
    }


    I2H(DATA[0],H);
    writeLE(H,fout);
    writeNull(fout);
    I2H(DATA[1],H);
    writeLE(H,fout);
    writeNull(fout);
    I2H(ctr2+ ctr -4,H);
    writeLE(H,fout);
    writeNull(fout);
    I2H((ctr2+ctr)/4 -2,H);
    writeLE(H,fout);

    for (int i = 0; i < ctr -8 ; i++)
    {
        fout<<char(D[i]);
    }

    for (int i = 0; i < ctr2; i++)
    {
        fout<<char(create[i]);
    }

    fout<<char(D[ctr-8]);
    fout<<char(D[ctr-7]);
    fout<<char(D[ctr-6]);
    fout<<char(D[ctr-5]);
    writeNull(fout);

}catch(int x)
{
    if (x == 0)
        cout<<"MAKE SURE THE OBJECT FILE IS THERE!";
}
}

