#include <iostream>
#include"assembler.h"
using namespace std;

int main()
{assembler a ;
a.pass1();
if( a.getpass1())
{

cout<<"ERRORS IN PASS 1 "<<endl<<"GENERATING OBJECT CODE TERMINATED "<<endl<<"CHECK LIST FILE FOR MORE DETAILS"<<endl;}
else {
a.printsym();
cout<<"PASS 1 DONE !"<<endl;
a.pass2();
    return 0;}
}
