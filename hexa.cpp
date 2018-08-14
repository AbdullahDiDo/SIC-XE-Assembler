#include"hexa.h"
#include<string>
#include <bitset>
#include <sstream>
using namespace std ;
int toDecDig(char a)
{
    if(a=='0') return 0;
    if(a=='1') return 1;
    if(a=='2') return 2;
    if(a=='3') return 3;
    if(a=='4') return 4;
    if(a=='5') return 5;
    if(a=='6') return 6;
    if(a=='7') return 7;
    if(a=='8') return 8;
    if(a=='9') return 9;
    if(a=='A') return 10;
    if(a=='B') return 11;
    if(a=='C') return 12;
    if(a=='D') return 13;
    if(a=='E') return 14;
    if(a=='F') return 15;
}
char toHexDig(int a)
{
    if(a==0) return '0';
    if(a==1) return '1';
    if(a==2) return '2';
    if(a==3) return '3';
    if(a==4) return '4';
    if(a==5) return '5';
    if(a==6) return '6';
    if(a==7) return '7';
    if(a==8) return '8';
    if(a==9) return '9';
    if(a==10) return 'A';
    if(a==11) return 'B';
    if(a==12) return 'C';
    if(a==13) return 'D';
    if(a==14) return 'E';
    if(a==15) return 'F';
}
string toHex(int a)
{
    string res="";
    if(a==0)
        res="0";
    while(a>0)
    {
        res=toHexDig(a%16)+res;
        a/=16;
    }
    return res;
}
int toDec(string val)
{
    int l=val.length()-1,curr=1,res=0;
    while(l>=0)
    {
        res+=(toDecDig(val[l])*curr);
        curr*=16;
        --l;
    }
    return res;
}
string extend(string s)
{
    int number=s.size();
    string s2 (4-number,'0');
    for(int i=0;i<s.size();i++)
    {
        s2+=s[i];
    }
    return s2;
}
string  extendtosix(string s)
{
        int number=s.size();
    string s2 (6-number,'0');
    for(int i=0;i<s.size();i++)
    {
        s2+=s[i];
    }
    return s2;

}
string extendtofiv(string s){

   int number=s.size();
    string s2 (5-number,'0');
    for(int i=0;i<s.size();i++)
    {
        s2+=s[i];
    }
    return s2;

}
string extendtothree(string s)

 {int number=s.size();
    string s2 (3-number,'0');
    for(int i=0;i<s.size();i++)
    {
        s2+=s[i];
    }
    return s2;
 }
const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}
string hex_str_to_bin_str(const string& hex)
{
    // TODO use a loop from <algorithm> or smth
    string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}
string binstringtohexstring(string& binary_str)
{
    string temp=binary_str.substr(0,4);
    bitset<100> set(binary_str);
    stringstream ss;
    ss << hex << set.to_ulong() << endl;
    ss >> binary_str;
    if(temp=="0000")
        binary_str="0"+binary_str;
    return binary_str;
}
void twos_comp(string &s)
{int flag=0;

    for(int i=s.size();i>=0;i--)
    {
        if(s[i]=='1'&&flag==0)
        {

flag++;            continue;
        }
        if(flag==1)
            if(s[i]=='1')
            s[i]='0';
        else if(s[i]=='0')
            s[i]='1';
    }
}

string extendtotwo(string s )
{ int number=s.size();
    string s2 (2-number,'0');
    for(int i=0;i<s.size();i++)
    {
        s2+=s[i];
    }
    return s2;

}


