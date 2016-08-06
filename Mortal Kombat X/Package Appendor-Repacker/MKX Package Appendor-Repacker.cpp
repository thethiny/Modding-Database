#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

int H2I(unsigned char []);
void I2H(int, unsigned char []);
void uI2H(unsigned int, unsigned char []);
void writeLE(unsigned char[],ofstream&);
void writeNull(ofstream&);
void writeRand(ofstream&,int size);
void write(ifstream&, ofstream&, int amnt);
void discard(ifstream&, int amnt);



int main()
{
    srand(time(0));
    int names=0,imports=0,exports=0,namesize=0,ctr=0,levels=0;
    int start,impstart,expstart,expend,filestart,origexps,start2,origimpstart,origexpstart,size,psize,fsize;
    string inName,open,ignore;
    string *NAMES,*IMPORTS,*EXPORTS,*type1,*type2,*type3,*exp1,*exp2,exp3; //Type, Class, Name. Import,NameTable,Temp.
    ifstream fin,fin2;
    ofstream fout,fout2;
    unsigned char H,_4byte[4] = {char(0),char(0),char(0),char(0)};
    char *X;
    bool _bool;

    try{
    cout<<"Enter folder name to repack: ";
    cin>>inName;
    open = inName + "/NameTable.txt";
    fin.open(open.c_str());
    cout<<"\nOpening " + open + " ";
    if (!fin.good())
    {
        throw(0);
    }
    cout<<"Successful";

    while(getline(fin,ignore))
    {
        if (ignore.length() >0)
        names++;
    }
    cout<<"\nNumber of Names is: "<<names<<endl;
    //Array of Names
    NAMES = new string [names];
    fin.close();
    fin.open(open.c_str());

    cout<<"Reading Names...\n";
    for (int i = 0; i < names; i++)
    {
        fin>>ignore;
        fin>>ignore;
        getline(fin,NAMES[i]);
        for (int j = 0; j < NAMES[i].length(); j++)
        {
            NAMES[i][j] = NAMES[i][j+2];
        }
        NAMES[i].resize(NAMES[i].length()-3);
    }
    /*
    for (int i = 0; i < names; i++)
        cout<<i<<" = "+NAMES[i]<<endl; */ //DEBUG CHECK STRINGS

    //IMPORT TABLE
    fin.close();
    open = inName + "/ImportTable.txt";
    fin.open(open.c_str());

    cout<<"\nOpening " + open + " ";
    if (!fin.good())
    {
        throw(1);
    }
    cout<<"Successful";

    while(getline(fin,ignore))
    {
        if (ignore.length() >0)
        imports++;
    }
    cout<<"\nNumber of Imports is: "<<imports<<endl;

    IMPORTS = new string [imports];
    type1 = new string [imports];
    type2 = new string [imports];
    type3 = new string [imports];
    fin.close();
    fin.open(open.c_str());

    cout<<"Reading Imports...\n";
    for (int i = 0; i < imports; i++)
    {
        fin>>ignore;
        fin>>ignore;
        getline(fin,IMPORTS[i]);
        for (int j = 0; j < IMPORTS[i].length(); j++)
        {
            IMPORTS[i][j] = IMPORTS[i][j+1];
        }
    }
    /*
    for (int i = 0; i < imports; i++)
        cout<<i<<" = "+IMPORTS[i]<<endl; */ //DEBUG CHECK STRINGS


    //EXPORT TABLE UNFINISHED
    fin.close();
    open = inName + "/ExportTable.txt";
    fin.open(open.c_str());
    cout<<"\nOpening " + open + " ";
    if (!fin.good())
    {
        throw(2);
    }
    cout<<"Successful";

    while(getline(fin,ignore))
    {
        if (ignore.length() >0)
        exports++;
    }
    cout<<"\nNumber of Exports is: "<<exports<<endl;
    //Array of Names
    EXPORTS = new string [exports];
    exp1 = new string [exports];
    exp2 = new string [exports];
    fin.close();
    fin.open(open.c_str());

    cout<<"Reading Exports...\n";
    for (int i = 0; i < exports; i++)
    {
        fin>>ignore;
        fin>>ignore;
        getline(fin,EXPORTS[i]);
        for (int j = 0; j < EXPORTS[i].length(); j++)
        {
            EXPORTS[i][j] = EXPORTS[i][j+1];
        }
    }
/*
    for (int i = 0; i < exports; i++)
        cout<<i<<" = "+EXPORTS[i]<<endl; */  //DEBUG CHECK STRINGS


    //START REBUILDING
    fin.close();
    open = inName + ".xxx";
    fin.open(open.c_str(),ios::binary);
    cout<<"\nOpening " + open + " ";
    if (!fin.good())
    {
        throw(3);
    }
    cout<<"Successful";
    fout.open((open + ".repack").c_str(),ios::binary);
    if (!fout.good())
        throw(4);
    fin>>noskipws; fout<<noskipws;
    for (int i = 0; i < 57; i++)
    {
        fin>>H;
    }
    fin>>_4byte[3];
    fin>>_4byte[2];
    fin>>_4byte[1];
    fin>>_4byte[0];
    //cout<<" "<<hex<<(int(_4byte[0]))<<(int(_4byte[1]))<<(int(_4byte[2]))<<(int(_4byte[3]))<<" _4byte"<<endl;

    start = H2I(_4byte);
    cout<<hex<<"\nName Table start: "<<start<<endl;
    for (int i = 0; i < names; i++)
    {
        namesize += NAMES[i].length() + 5; //Adding + n because there are 4 for Size and one null
    }
    //cout<<"NAMESIZE: "<<namesize;
    impstart = namesize + start;
    expstart = impstart + imports*0x2C; //0x2C is size of each import
    expend = expstart + exports*0x58; //0x58 is size of each export
    cout<<"Import Table Start: "<<impstart<<endl;
    cout<<"Export Table Start: "<<expstart<<endl;
    cout<<"Exports End Location: "<<expend<<endl;

    fin.close();
    fin.open(open.c_str(),ios::binary);

    discard(fin,0x41);
    fin>>_4byte[3];
    fin>>_4byte[2];
    fin>>_4byte[1];
    fin>>_4byte[0];
    origexps = H2I(_4byte);

    fin>>_4byte[3];
    fin>>_4byte[2];
    fin>>_4byte[1];
    fin>>_4byte[0];
    origexpstart = H2I(_4byte);

    fin.close();
    fin.open(open.c_str(),ios::binary);

    discard(fin, origexpstart + 0x58*origexps);
    //cout<<"ASDASD: "<<origexpstart + 0x58*origexps;

    filestart = expend;//origexpstart+ 0x58*exports;

    fin>>H;
    while(H == char(0))
    {
        filestart++;
        fin>>H;
    }
    cout<<"Files Start: "<<filestart<<endl;
    fin.close();
    fin.open(open.c_str(),ios::binary);

    cout<<"\nWriting Header..\n";
    write(fin,fout,8);
    I2H(filestart,_4byte);
    writeLE(_4byte,fout);

    discard(fin,4);

    write(fin,fout,0x29);

    I2H(names,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    I2H(start,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    write(fin,fout,4);

    I2H(exports,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    I2H(expstart,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    write(fin,fout,4);

    I2H(imports,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    I2H(impstart,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    write(fin,fout,8);

    I2H(expend,_4byte);
    //cout<<"HHHH: "<<expend;
    writeLE(_4byte,fout);
    discard(fin,4);

    write(fin,fout,12);

    I2H(filestart-4,_4byte);
    writeLE(_4byte,fout);
    discard(fin,4);

    write(fin,fout,start-0x71);
    fin.close();

    cout<<"\nCreating the NameTable...\n";
    for (int i = 0; i < names; i++)
    {
        I2H(NAMES[i].length()+1,_4byte);
        writeLE(_4byte,fout);
        for (int j = 0; j < NAMES[i].length(); j++)
        {
            fout<<NAMES[i][j];
        }
        fout<<char(0);
    }
    cout<<"Creating the ImportTable...\n";
    //cout<<IMPORTS[0]<<endl; //DEBUG
    _bool = false;
    for(int i = 0; i < imports; i++)
    {
        ctr = 0;
        type1[i]=IMPORTS[i];
        type2[i]=IMPORTS[i];
        type3[i]=IMPORTS[i];
        while(IMPORTS[i][ctr] != '\'')
        {
            ctr++;
        }
        type1[i].resize(ctr);
        ctr = 0;

        for (int j = 0; j < type2[i].length(); j++)
        {
            type2[i][j] = type2[i][j+type1[i].length()+1];
        }
        while(type2[i][ctr] != '.' && type2[i][ctr] != '\'')
        {
            ctr++;
        }
        if (type2[i][ctr] == '\'')
            _bool = true;
        type2[i].resize(ctr);
        ctr = 0;
        if (!_bool)
            {
        for (int j = 0; j < type3[i].length(); j++)
        {
            type3[i][j] = type3[i][j+type1[i].length()+1+type2[i].length()+1];
        }

        while(type3[i][ctr] != '\'')
        {
            ctr++;
        }
            }
        type3[i].resize(ctr);

    }
    //cout<<type1[43]+'\''+type2[43] + '.' + type3[43] + '\'' + "<- ReCreated\n";
     //FOR NOW, IMPORT TABLE IS BEING IMPORTED (NO PUN INTENDED), NOT RECREATED BECAUSE I DIDN'T UNDERSTAND HOW IT WORKS YET
    /*
    //Search for the 3 types in the name table
    for (int i = 0; i < imports; i++)
    {
        _bool = false;
        for (int j = 0; j < names; j++)
            if (NAMES[j] == type2[i])
            {
                I2H(j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }

        writeNull(fout);

        _bool = false;
        for (int j = 0; j < names; j++)
            if (NAMES[j] == type1[i])
            {
                I2H(j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }

        writeNull(fout);

        _bool = false;
         for (int j = 0; j < imports; j++)
        {
            if (type2[j] == type2[i] && type3[j] == "") //Searching for Core be equal to Core and there's no Type3
            {
                uI2H(0xFFFFFFFF-j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }
        }

        _bool = false;
        for (int j = 0; j < names; j++)
            if (NAMES[j] == type3[i])
            {
                I2H(j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }

        writeNull(fout);
        writeRand(fout,0x10);


    }
    */

    //HERE IS WHERE I IMPORT THE IMPORT TABLE
    fin.open(open.c_str(),ios::binary);
    fin>>noskipws;


    discard(fin,0x51);
    fin>>_4byte[3];
    fin>>_4byte[2];
    fin>>_4byte[1];
    fin>>_4byte[0];
    origimpstart = H2I(_4byte);

    discard(fin,origimpstart - 0x55);
    write(fin,fout,imports*0x2C);
    fin.close();


    //Building Export Table
    cout<<"Creating ExportTable...\n";

    for (int i = 0; i < exports; i++)
    {
        exp1[i] = EXPORTS[i];
        exp2[i] = EXPORTS[i];

        ctr = 0;
        while(exp1[i][ctr] != '\'')
            ctr++;
        exp1[i].resize(ctr);

        ctr = 0;
        for (int j = 0; j < exp2[i].length(); j++)
        {
            exp2[i][j] = exp2[i][j+exp1[i].length()+1];
        }
        while(exp2[i][ctr] != '\'')
        {
            ctr++;
        }
        exp2[i].resize(ctr);


    }

    //DEBUG
    //cout<<exp1[696]+"'"+exp2[696]+"'<- Rebuilt\n";

//REMOVED BECUASE HARD TO IMPLEMENT, WILL IMPORT EXPORTS AND JUST ADD NEW ONES.
/*
    //Search to write
    for (int i = 0; i < exports; i++)
    {
        for (int j = 0; i < imports; j++)
        {
            if (exp1[i] == type3[j])
            {
                uI2H(0xFFFFFFFF-j,_4byte);
                writeLE(_4byte,fout);
                break;
            }
        }

        writeNull(fout);
        //Check if inside a package
        ctr = 0;
        levels = 0;
        for (int j = 0; j < exp2[i].length(); j++)
        {
            if (exp2[i][ctr] != '.')
                ctr++;
            else
            {
                //exp3[levels] = exp2[i];
                //exp3[levels].resize(ctr);
                //levels++;
                exp3 = exp2[i];
                exp3.resize(ctr);
                ctr++;
            }
        }
        _bool = false;
        for (int j = 0; j < exports; j++)
        {
            if (exp3 == exp2[j])
            {
                I2H(j+1,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }
        }
        if (!_bool)
            writeNull(fout);

        _bool = false;
        for (int j = 0; j < names; j++)
        {
            if (exp2[i] == NAMES[j])
            {
                I2H(j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }
        }
        if (!_bool) //Maybe it has a suffix
        {
            //if (exp2[exp2.length()-4 ==]
                  cout<<endl<<exp2[i];//[exp2[i].length()-1]; //INCOMPLETE
        }
        if (!_bool) //Check, maybe this files is inside a package
        {
            ctr = 0;
            exp3 = exp2[i];
            for (int j = exp3.length(); j>0; j--)
            {
                if (exp3[j] != '.')
                    ctr++;
                else
                {
                    for (int k = 0; k < exp3.length(); k++)
                    {
                        exp3[k] = exp3[exp3.length()-ctr+k];
                    }
                    exp3.resize(ctr);
                    cout<<exp3;
                }
            }
        }

    }
    */

    //IMPORT EXPORTS
    fin.open(open.c_str(),ios::binary);
    fin>>noskipws;

    discard(fin,0x41);
    fin>>_4byte[3];
    fin>>_4byte[2];
    fin>>_4byte[1];
    fin>>_4byte[0];

    origexps = H2I(_4byte);

    //cout<<"Orig Exps: "<<dec<<int(origexps)<<endl;
    discard(fin,origexpstart-0x45);

    //FIX OFFSETS OF EXPORT TABLE
    size = filestart;
    for (int i = 0; i < origexps; i++)
    {
        write(fin,fout,0x34);

        fin>>_4byte[3];
        fin>>_4byte[2];
        fin>>_4byte[1];
        fin>>_4byte[0];

        psize = H2I(_4byte);
        fout<<_4byte[3];
        fout<<_4byte[2];
        fout<<_4byte[1];
        fout<<_4byte[0];

        I2H(size,_4byte); //size actually means location
        writeLE(_4byte,fout);
        discard(fin,4);

        write(fin,fout,0x1C);
        size += psize;

    }

        fin.close();
//Adding Exports for added files
    for (int i = origexps; i < exports; i++)
    {
        cout<<"\nEnter the number of the export to use as template (start at 0): ";
        cin>>ctr;
        open = inName + ".xxx";
        fin.open(open.c_str(),ios::binary);
        fin>>noskipws;
        discard(fin,origexpstart);
        discard(fin,0x58*ctr);
        if (0x58*ctr > 0x58*origexps)
            throw(7);
        write(fin,fout,0xC);
        discard(fin,4);
        _bool = false;
        for(int j = 0; j < names; j++)
        {
            if (exp2[i] == NAMES[j])
            {
                I2H(j,_4byte);
                writeLE(_4byte,fout);
                _bool = true;
                break;
            }

        }
        if (!_bool)
        {
            throw(8);
        }
        write(fin,fout,0x24);
        fin.close();

        open = inName + "/" + exp2[i] + "." + exp1[i];
        cout<<"Open: "<<open;
        fin.open(open.c_str(),ios::ate);

        if (!fin.good())
            throw(6);

        fsize = fin.tellg(); //getFileSize
        I2H(fsize,_4byte);
        writeLE(_4byte,fout);
        discard(fin,4);
        I2H(size,_4byte);
        writeLE(_4byte,fout);
        discard(fin,4);

        for (int k = 0; k < 7; k++)
            writeNull(fout);

        size += fsize;
        fin.close();
        }

    cout<<"\n\nWriting Data..";
    //WRITE REMANING DATA
    fin.close();
    open = inName + ".xxx";
    fin.open(open.c_str(),ios::binary);
    fin>>noskipws;
    discard(fin,origexps*0x58 + origexpstart);
    //cout<<hex<<"TTTT: "<<origexps*0x58+origexpstart;
    while (fin>>_4byte[1])
    {
        fout<<_4byte[1];
    }


    cout<<"\nWriting Added Files..\n";
    //Writing Data of added files
    for (int i = origexps; i < exports; i++)
    {
        fin.close();
        open = inName + "/" + exp2[i] + "." + exp1[i];
        fin.open(open.c_str(),ios::ate);

        fsize = fin.tellg();
        fin.close();

        open = inName + "/" + exp2[i] + "." + exp1[i];
        fin.open(open.c_str(),ios::binary);

        write(fin,fout,fsize);

    }
    cout<<"\nDone... You may exit the tool now";
    fin.close();
    fout.close();

    delete [] NAMES;
    delete [] IMPORTS;
    delete [] EXPORTS;
    delete [] type1;
    delete [] type2;
    delete [] type3;
    delete [] exp1;
    delete [] exp2;

    cin>>ctr;

} catch(int n)
{
    switch(n)
    {
        case 0: cout<<"\nNameTable.txt does not exist!\n"; break;
        case 1: cout<<"\nImportTable.txt does not exist!\n"; break;
        case 2: cout<<"\nExportTable.txt does not exist!\n"; break;
        case 3: cout<<"\nCOULDN'T OPEN PACKAGE FILE!\n"; break;
        case 4: cout<<"\nCouldn't Create Output File!\n"; break;
        case 5: cout<<"\nImport Table Failure, name table entry not found, check your ImportTable.txt!\n"; break;
        case 6: cout<<"\nCouldn't Load " + open + " for appending\n"; break;
        case 7: cout<<"\nInvalid Export Number...\n"; break;
        case 8: cout<<"\nMake sure that you added the name to the nametable correctly! The export couldn't find it..\n"; break;
        default: cout<<"\nAn Unknown Error Occurred\n";
    }
}

}

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
    for (int i = 0; i < x; i++)
        fout<<char(rand());
}
