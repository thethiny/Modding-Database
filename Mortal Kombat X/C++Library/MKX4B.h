#ifndef MKX4B_H_INCLUDED
#define MKX4B_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int H2I(unsigned char []);
void I2H(int, unsigned char []);
void uI2H(unsigned int, unsigned char []);
void writeLE(unsigned char[],ofstream&);
void writeNull(ofstream&);
void writeRand(ofstream&,int );
void write(ifstream&, ofstream&, int );
void discard(ifstream&, int);
void read(ifstream&, unsigned char []);



#endif // MKX4B_H_INCLUDED
