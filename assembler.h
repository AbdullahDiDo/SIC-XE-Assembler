#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#include<string>
#include<map>
#include<vector>
using namespace std ;
struct op{
string opcode ;
int format ;
int operands;
};
struct reg {
int num;
};
struct lab{
int address;
int value ;
};
struct obj{
string objcode;
int address;
int bytes;
int data_flag=0;
};
typedef map<string,op>   map1;
typedef map<string,reg>  map2;
typedef map<string,lab>   map3;
typedef vector<string> v ;
typedef vector<obj> o ;
class assembler {
private :
map1 OPTAB ;
map2 REGISTER;
map3 SYMTAB;
int LOCCTR;
int base_reg;
v SourceLine ;
o objvec;
int error_flag ;
int ENDval;
int Scnt ;
bool pass1_fail;
int errors [100];
int modification_flag;
vector<int> mod ;
string s ;
string flagbits;
int immediate_flag;
public :
assembler ();
void pass1();
void read_input();
bool is_comment(string &s);
bool is_opcode(string &s);
bool is_label(string &s);
void divide(string &s1,string &s2,string &s3);
bool has_correct_operands(string , string);
int getbyte(const string &s);
void typetext(ostream &o);
void pass2();
bool getpass1(){return pass1_fail;}

void printsym();
};


#endif // ASSEMBLER_H_INCLUDED
