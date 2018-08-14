#ifndef HEXA_DEC_H_INCLUDED
#define HEXA_DEC_H_INCLUDED
#include<string>
using namespace std ;
int toDec(string val);
string toHex(int a);
char toHexDig(int a);
int toDecDig(char a);
string extend(string s);
string extendtosix(string s);
string extendtofiv(string s);
string extendtothree(string s);
string extendtotwo(string s );
const char* hex_char_to_bin(char c);
string hex_str_to_bin_str(const string& hex);
string binstringtohexstring(string& binary_str);
void twos_comp(string &s);

#endif // HEXA_DEC_H_INCLUDED
