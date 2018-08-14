#include"assembler.h"
#include"hexa.h"
#include<fstream>
#include<vector>
#include<map>
#include <cstddef>        // std::size_t
#include<iostream>
#include<algorithm>
#include<ctype.h>
#include<stdlib.h>
using namespace std;

assembler::assembler()
{
    Scnt = 0;
    error_flag = 0;
    LOCCTR = 0;
    base_reg = 0;
    modification_flag=0;
    immediate_flag=0;
     pass1_fail=false;

    flagbits="000000";
    OPTAB["ADD"].opcode = "18";
    OPTAB["ADD"].format = 3;
    OPTAB["ADD"].operands = 1;

    OPTAB["ADDF"].opcode = "58";
    OPTAB["ADDF"].format = 3;
    OPTAB["ADDF"].operands = 1;

    OPTAB["ADDR"].opcode = "90";
    OPTAB["ADDR"].format = 2;
    OPTAB["ADDR"].operands = 2;

    OPTAB["AND"].opcode = "40";
    OPTAB["AND"].format = 3;
    OPTAB["AND"].operands = 1;

    OPTAB["CLEAR"].opcode = "B4";
    OPTAB["CLEAR"].format = 2;
    OPTAB["CLEAR"].operands = 1;

    OPTAB["COMP"].opcode = "28";
    OPTAB["COMP"].format = 3;
    OPTAB["COMP"].operands = 1;

    OPTAB["COMPF"].opcode = "88";
    OPTAB["COMPF"].format = 3;
    OPTAB["COMPF"].operands = 1;

    OPTAB["COMPR"].opcode = "A0";
    OPTAB["COMPR"].format = 2;
    OPTAB["COMPR"].operands = 2;

    OPTAB["DIV"].opcode = "24";
    OPTAB["DIV"].format = 3;
    OPTAB["DIV"].operands = 1;

    OPTAB["DIVF"].opcode = "64";
    OPTAB["DIVF"].format = 3;
    OPTAB["DIVF"].operands = 1;

    OPTAB["DIVR"].opcode = "9C";
    OPTAB["DIVR"].format = 2;
    OPTAB["DIVR"].operands = 2;

    OPTAB["FIX"].opcode = "C4";
    OPTAB["FIX"].format = 1;
    OPTAB["FIX"].operands = 1;

    OPTAB["FLOAT"].opcode = "C0";
    OPTAB["FLOAT"].format = 1;
    OPTAB["FLOAT"].operands = 1;

    OPTAB["HIO"].opcode = "F4";
    OPTAB["HIO"].format = 1;
    OPTAB["HIO"].operands = 1;

    OPTAB["J"].opcode = "3C";
    OPTAB["J"].format = 3;
    OPTAB["J"].operands = 1;

    OPTAB["JEQ"].opcode = "30";
    OPTAB["JEQ"].format = 3;
    OPTAB["JEQ"].operands = 1;

    OPTAB["JGT"].opcode = "34";
    OPTAB["JGT"].format = 3;
    OPTAB["JGT"].operands = 1;

    OPTAB["JLT"].opcode = "38";
    OPTAB["JLT"].format = 3;
    OPTAB["JLT"].operands = 1;

    OPTAB["JSUB"].opcode = "48";
    OPTAB["JSUB"].format = 3;
    OPTAB["JSUB"].operands = 1;

    OPTAB["LDA"].opcode = "00";
    OPTAB["LDA"].format = 3;
    OPTAB["LDA"].operands = 1;

    OPTAB["LDB"].opcode = "68";
    OPTAB["LDB"].format = 3;
    OPTAB["LDB"].operands = 1;

    OPTAB["LDCH"].opcode = "50";
    OPTAB["LDCH"].format = 3;
    OPTAB["LDCH"].operands = 1;

    OPTAB["LDF"].opcode = "70";
    OPTAB["LDF"].format = 3;
    OPTAB["LDF"].operands = 1;

    OPTAB["LDL"].opcode = "08";
    OPTAB["LDL"].format = 3;
    OPTAB["LDL"].operands = 1;

    OPTAB["LDS"].opcode = "6C";
    OPTAB["LDS"].format = 3;
    OPTAB["LDS"].operands = 1;

    OPTAB["LDT"].opcode = "74";
    OPTAB["LDT"].format = 3;
    OPTAB["LDT"].operands = 1;

    OPTAB["LDX"].opcode = "04";
    OPTAB["LDX"].format = 3;
    OPTAB["LDX"].operands = 1;

    OPTAB["LPS"].opcode = "D0";
    OPTAB["LPS"].format = 3;
    OPTAB["LPS"].operands = 1;

    OPTAB["MUL"].opcode = "20";
    OPTAB["MUL"].format = 3;
    OPTAB["MUL"].operands = 1;

    OPTAB["MULF"].opcode = "60";
    OPTAB["MULF"].format = 3;
    OPTAB["MULF"].operands = 1;

    OPTAB["MULR"].opcode = "98";
    OPTAB["MULR"].format = 2;
    OPTAB["MULR"].operands = 2;

    OPTAB["NORM"].opcode = "C8";
    OPTAB["NORM"].format = 1;
    OPTAB["NORM"].operands = 0;

    OPTAB["OR"].opcode = "44";
    OPTAB["OR"].format = 3;
    OPTAB["OR"].operands = 1;

    OPTAB["RD"].opcode = "D8";
    OPTAB["RD"].format = 3;
    OPTAB["RD"].operands = 1;

    OPTAB["RMO"].opcode = "AC";
    OPTAB["RMO"].format = 2;
    OPTAB["RMO"].operands = 2;

    OPTAB["RSUB"].opcode = "4C";
    OPTAB["RSUB"].format = 3;
    OPTAB["RSUB"].operands = 0;

    OPTAB["SHIFTL"].opcode = "A4";
    OPTAB["SHIFTL"].format = 2;
    OPTAB["SHIFTL"].operands = 2;

    OPTAB["SHIFTR"].opcode = "A8";
    OPTAB["SHIFTR"].format = 2;
    OPTAB["SHIFTR"].operands = 2;

    OPTAB["SIO"].opcode = "F0";
    OPTAB["SIO"].format = 1;
    OPTAB["SIO"].operands = 0;

    OPTAB["SSK"].opcode = "EC";
    OPTAB["SSK"].format = 3;
    OPTAB["SSK"].operands = 1;

    OPTAB["STA"].opcode = "0C";
    OPTAB["STA"].format = 3;
    OPTAB["STA"].operands = 1;

    OPTAB["STB"].opcode = "78";
    OPTAB["STB"].format = 3;
    OPTAB["STB"].operands = 1;

    OPTAB["STCH"].opcode = "54";
    OPTAB["STCH"].format = 3;
    OPTAB["STCH"].operands = 1;

    OPTAB["STF"].opcode = "80";
    OPTAB["STF"].format = 3;
    OPTAB["STF"].operands = 1;

    OPTAB["STI"].opcode = "D4";
    OPTAB["STI"].format = 3;
    OPTAB["STI"].operands = 1;

    OPTAB["STL"].opcode = "14";
    OPTAB["STL"].format = 3;
    OPTAB["STL"].operands = 1;

    OPTAB["STS"].opcode = "7C";
    OPTAB["STS"].format = 3;
    OPTAB["STS"].operands = 1;

    OPTAB["STSW"].opcode = "E8";
    OPTAB["STSW"].format = 3;
    OPTAB["STSW"].operands = 1;

    OPTAB["STT"].opcode = "84";
    OPTAB["STT"].format = 3;
    OPTAB["STT"].operands = 1;

    OPTAB["STX"].opcode = "10";
    OPTAB["STX"].format = 3;
    OPTAB["STX"].operands = 1;

    OPTAB["SUB"].opcode = "1C";
    OPTAB["SUB"].format = 3;
    OPTAB["SUB"].operands = 1;

    OPTAB["SUBF"].opcode = "5C";
    OPTAB["SUBF"].format = 3;
    OPTAB["SUBF"].operands = 1;

    OPTAB["SUBR"].opcode = "94";
    OPTAB["SUBR"].format = 2;
    OPTAB["SUBR"].operands = 2;

    OPTAB["SVC"].opcode = "B0";
    OPTAB["SVC"].format = 2;
    OPTAB["SVC"].operands = 1;

    OPTAB["TD"].opcode = "E0";
    OPTAB["TD"].format = 3;
    OPTAB["TD"].operands = 1;

    OPTAB["TIO"].opcode = "F8";
    OPTAB["TIO"].format = 1;
    OPTAB["TIO"].operands = 0;

    OPTAB["TIX"].opcode = "2C";
    OPTAB["TIX"].format = 3;
    OPTAB["TIX"].operands = 1;

    OPTAB["TIXR"].opcode = "B8";
    OPTAB["TIXR"].format = 2;
    OPTAB["TIXR"].operands = 1;

    OPTAB["WD"].opcode = "DC";
    OPTAB["WD"].format = 3;
    OPTAB["WD"].operands = 1;
    /*---REGISTERS'-INFO-------*/

    REGISTER["A"].num = 0;

    REGISTER["X"].num = 1;

    REGISTER["L"].num = 2;

    REGISTER["B"].num = 3;

    REGISTER["S"].num = 4;

    REGISTER["T"].num = 5;

    REGISTER["F"].num = 6;

    REGISTER["PC"].num = 8;

    REGISTER["SW"].num = 9;
}

void assembler::pass1()
{
    ofstream list;
    list.open("listfile.txt");
    list <<"no\t"<< "LOCCTR\t" << "LABEL\t" << "OPCODE\t" << "OPEEAND\t" << "COMMENT\t" << endl;
    list << "==============================================================" << endl;
    string tlabel;
    string topcode;
    string toperand;
    read_input();
    //cout << "string assigned" << endl;
    s = SourceLine[Scnt];
    // cout << s << endl;
    int loc = s.find(".");
    if (loc != string::npos)
    {
        string s2(s, 0, loc);
        s = s2;
    }
    while (is_comment(s))
    {
        //  cout << "in loop1" << endl;
        list << Scnt << "\t" << SourceLine[Scnt] << endl;
        Scnt++;
        s = SourceLine[Scnt];
    }
    divide(tlabel, topcode, toperand);

    //cout << tlabel << "* " << topcode << " *" << toperand << endl;
    if (topcode == "START")
    {
        LOCCTR = ENDval = toDec(toperand);
        //  cout << "LOCCTR" <<toHex (LOCCTR) << endl;
        if (tlabel != "NULL")
        {
            SYMTAB[tlabel].address = LOCCTR;
        }
        list << Scnt << "\t" <<extend(toHex(LOCCTR))<<"\t"<< SourceLine[Scnt]<< endl;
        Scnt++;

    }

    //cout << "first line done" << endl;
    while (topcode != "END")
    {
        s=SourceLine[Scnt];

        error_flag = 0;
        list << Scnt << "\t";
        list << extend(toHex(LOCCTR)) << "\t";
        //cout << "LOCCTR" << toHex(LOCCTR) << endl;

        if (!is_comment(SourceLine[Scnt]))
        {
            loc = s.find(".");
            if (loc != string::npos)
            {

                string s3(s, 0, loc);
                s = s3;
            }
            divide(tlabel, topcode, toperand);
            //cout << "T LABEL" << tlabel << endl;
            if (tlabel != "NULL")
            {
                if (!is_label(tlabel))
                {
                    //      cout << "insertingg in symtaaaaaaaaaaaable" << endl;
                    SYMTAB[tlabel].address = LOCCTR;
                }
                else error_flag = 2;//duplicate symbol
            }
            //cout << "------------------TOPCODE----------<<" << topcode << endl;
            if (topcode == "RESW")
            {

                LOCCTR += atoi(toperand.c_str())*3;
                //      cout << "LOCCCCCCTTTTTRRRR" << LOCCTR << endl;
            }
            else if (topcode == "RESB")
            {

                LOCCTR += atoi(toperand.c_str());
            }
            else if (topcode == "WORD")
            {

                LOCCTR += 3;
            }
            else if (topcode == "BYTE")
            {

                LOCCTR+=getbyte(toperand);
            }
            else if (topcode[0] == '+')
            {

                LOCCTR += 4;
            }
            else if (is_opcode(topcode))
            {
                LOCCTR += OPTAB[topcode].format;
            }
            else if (!is_opcode(topcode))
                error_flag = 3;
        }
        list << SourceLine[Scnt] << endl;
        switch (error_flag)
        {
        case 2:
        {cout << '\a';
            list << "  error:Duplicate symbol" << endl;
                 pass1_fail=true;

            break;
        }
        case 3:
        {cout << '\a';
            list << "  error instruction not found" << endl;
                             pass1_fail=true;

            break;
        }
        case 4:
        {cout << '\a';
             list << "error: wrong number of operands" << endl;
                              pass1_fail=true;

            break;
        }
        default:
            break;
        }
        //cout << "ERROR FLAGGGG !!!!" << error_flag << endl;
        Scnt++;

    }

    if (toperand != "NULL")
        if (!is_label(toperand))
            SYMTAB[toperand].address = ENDval;
}

void assembler::read_input()
{
    ifstream input;
    string line;
    input.open("input.txt");    //input file
    if (input.fail())
    {
        //  cout << "input file not found " << endl;
        error_flag = 1;
        return;
    }         //error flag 1 ---> input file not found
    while (getline(input, line))
        SourceLine.push_back(line);
}

bool assembler::is_comment(string& s)
{
    if (s[0] == '.')
        return true;
    //cout << "notcomment" << endl;
    return false;
}

bool assembler::is_opcode(string& s)
{
    string si = s;
    map1::iterator it;
    if (si[0] == '+')
        si = s.substr(1);
    it = OPTAB.find(si);
    if (it == OPTAB.end())
        return false;
    return true;
}

void assembler::divide(string &label, string &opcode, string &operand)
{
    //cout << "in divide" << endl;
    label = "";
    opcode = "";
    operand = "";
    int  index;   // indexf
    string temp = "";
    string tempr = "";
    index = s.find_first_not_of(" ");
    //cout<<"HI "<<s<<endl;
    //cout << "index1" << index << endl;
    while (s[index] != ' ' && (isalpha(s[index]) || isdigit(s[index]) || s[index] == '+'))
    {
        temp += s[index];
        index++;
    }
    //cout << "index2" << index << endl;

    //cout << "temp" << temp << endl;
    /*if (temp == "RSUB")
    {
        label = "NULL";
        operand = "NULL";
        opcode = temp;
        return;
    }*/
    if (is_opcode(temp) || temp == "START" || temp == "END" ||temp == "BYTE"
            || temp == "WORD" || temp == "RESW" || temp == "RESB" || temp == "BASE")
    {
        //cout << "in" << opcode << endl;
        label = "NULL";
        opcode = temp;
        //cout<<opcode<<endl;

        //what i hanve done is here///////////////////////////////////////////////////////////////////////////
        /*if (OPTAB[opcode].format == 1)
        {
            operand = "NULL";
            return;
        }*///i think this will solve the problem/////////////////////////////////////////////////////////////////
        while (s[index] == ' ')
            index++;
        int i = s.find_last_not_of(" ");
        for (int y = index; y <= i; y++)
            operand += s[y];
        //cout << "2nd " << "label" << label << "opcode" << opcode << "operand" << operand << endl;
        if (!has_correct_operands(opcode, operand))
        {
            error_flag = 4;
            return;
        }
    }
    else
    {
        label = temp;
        //cout << "index" << index << endl;
        //cout << "label" << label << endl;

        while (s[index] == ' ')
            index++;
        //cout << index << endl;
        while (s[index] != ' ' && (isalpha(s[index]) || isdigit(s[index]) || s[index] == '+'))
        {
            opcode += SourceLine[Scnt][index];
            index++;
        }
        //cout << "opcode" << opcode << endl;
        //ASLO HERE THE ORING OF THE OPCODE OF FORMAT 1 //////////////////////////////////////////////////////
        if (!is_opcode(opcode)&&(opcode!="RSUB")&&(opcode!="BYTE")&&
            opcode!=("WORD")&&opcode!=("RESB")&&opcode!=("RESW")&&opcode!=("BASE"))
        {
            // cout<<"HHHHHHHHHHHHHHHHHHHHHHHEEEEEEEEEEEEEEEYYYYYYYYYYYYYYYYYYYYY"<<endl;
            error_flag=3;
            return;
        }
        /*if (opcode == "RSUB" || OPTAB[opcode].format == 1)
        {
            operand = "NULL";
            return;
        }*/////////////////////////////////////////////////////////////////////////////////////////////////////

        while (s[index] == ' ')
            index++;
        // cout << "index before " << index << endl;
        int i = s.find_last_not_of(" ");
        for (int y = index; y <= i; y++)
            operand += s[y];
        // cout << "operand" << operand << endl;
        if (!has_correct_operands(opcode, operand))
        {
            error_flag = 4;
            return;
        }
    }
}

bool assembler::has_correct_operands(string opcode,string operand)
{
    if (opcode[0] == '+')
        opcode = opcode.substr(1);
    if ( ((OPTAB[opcode].format == 1) && operand.empty() ) || ((opcode == "RSUB") && operand.empty()))
        return true;
    else if ((OPTAB[opcode].format == 1 && !operand.empty()))
        return false;
    else if ((OPTAB[opcode].format != 1) && operand.empty())
        return false;
    int count = 0;
    for (int i = 0; i < operand.size(); i++)
        if (operand[i] == ',')
        {
            count++;
            if (operand[i + 1] == 'X' || operand[i + 1] == 'x')
                return true;
        }
    if (opcode == "BYTE" || opcode == "WORD" || opcode == "RESB" ||
        opcode == "RESW" || opcode == "END" || opcode == "START" || opcode == "BASE")
        if (!count && !(operand.empty()))
            return true;
        else return false;
    else if (++count == OPTAB[opcode].operands)//++count; as if 1 ',' then 2 operands and if 0 ',' 1 operand
        return true;
    return false;
}

bool assembler::is_label(string& s)
{
    map3::iterator i;
    i = SYMTAB.find(s);
    if (i == SYMTAB.end())
        return false;
    return true;
}

int assembler::getbyte(const string& operand)
{
    if(operand[0]=='C')
    {

        return (operand.size()-3);
    }
    else if (operand[0]=='X')
    {
        return ((operand.size()-2)/2);
    }
    else return 1 ;
}

void assembler::printsym()
{

    ofstream p;
    p.open("sym2.txt");
    map3::const_iterator it;
    for (it = SYMTAB.begin(); it != SYMTAB.end(); ++it)
        p << it->first << "\t"  << extend(toHex(it->second.address)) << endl;
}

void assembler::pass2()
{
    Scnt=0;
    int obj_index=0;
    s = SourceLine[Scnt];
    string s2;
    ofstream objfile;
    ofstream list ;
    list.open("listfile.txt");
    objfile.open("objfile.txt");
    string tlabel,toperand,topcode;
    string prog_name;
    int prog_length=LOCCTR-ENDval;
    LOCCTR=error_flag=0;
    int loc = s.find(".");
    if (loc != string::npos)
    {
        string s2(s, 0, loc);
        s = s2;


    }
     list <<"no\t"<< "LOCCTR\t" << "LABEL\t" << "OPCODE\t" << "OPEEAND\t" << "COMMENT\t"<<endl;
    list << "===================================================" << endl;
    while (is_comment(s))
    {  list << Scnt << "\t" <<  extend(toHex(LOCCTR)) << "\t"<<SourceLine[Scnt] << endl;
        Scnt++;
        s = SourceLine[Scnt];
    }
    divide(tlabel, topcode, toperand);
    if(topcode=="START")
    {
        LOCCTR = toDec(toperand);

        if(tlabel!="NULL")
        {
            prog_name=tlabel;
            int i=prog_name.size();
            if(i!=6)
            {
                int f =6-i;
                while(f>0)
                {
                    prog_name+=" ";
                    f--;
                }
            }
        }
        else
            prog_name="      ";
        objfile<<"H^"<<prog_name<<"^"<<extendtosix(toHex(LOCCTR))<<"^"<<extendtosix(toHex(prog_length))<<endl;

        Scnt++;
    }
    while(topcode != "END")
    {list <<Scnt<<"\t";
        cout<<SourceLine[Scnt]<<endl;
        s=SourceLine[Scnt];
        flagbits="000000";
        error_flag=0;

        if (!(is_comment(SourceLine[Scnt])))
        {
            cout<<"NOT COMMENT "<<endl;
            loc = s.find(".");
            if (loc != string::npos)
            {

                string s3(s, 0, loc);
                s = s3;
            }

            divide(tlabel,topcode,toperand);
            cout<<tlabel <<topcode<<toperand<<endl;
            if(topcode=="RESB")
            {
                objvec.push_back(obj());
                objvec[obj_index].data_flag=1;
                objvec[obj_index].address=LOCCTR;
 list << extend(toHex(LOCCTR)) << "\t";
  LOCCTR += atoi(toperand.c_str());                obj_index++;
            }
            else if (topcode=="RESW")
            {
                cout<<"IN RESW"<<endl;
                objvec.push_back(obj());
                objvec[obj_index].data_flag=1;
                objvec[obj_index].address=LOCCTR;
 list << extend(toHex(LOCCTR)) << "\t";
                 LOCCTR += atoi(toperand.c_str())*3;

                obj_index++;
            }
            else if(topcode=="WORD")
            {
                loc=toperand.find("X");
                if(loc!=string::npos)
                {
                    objvec.push_back(obj());
                    objvec[obj_index].objcode=string(toperand,2,toperand.size()-3);
                    objvec[obj_index].bytes=3;
                    objvec[obj_index].address=LOCCTR;
                    list << extend(toHex(LOCCTR)) << "\t";
                    objvec[obj_index].data_flag=0;
                    LOCCTR+=3;
                    obj_index++;
                }
                else
                {
                    loc=toperand.find("C");
                    if(loc!=string::npos)
                    {
                        objvec.push_back(obj());
                        string s3=string(toperand,2,toperand.size()-3);//
                        int number =toperand.size()-3;
                        int i=0;
                        string s4;
                        while(number>0)
                        {
                            int ascii=int(s3[i++]);
                            s4=toHex(ascii);
                            objvec[obj_index].objcode+=s4;
                            number--;
                        }
                        objvec[obj_index].bytes=3;
                        objvec[obj_index].address=LOCCTR;
                        objvec[obj_index].data_flag=0;
                         list << extend(toHex(LOCCTR)) << "\t";
                        LOCCTR+=3;
                        obj_index++;
                    }
                    else
                    {
                        objvec.push_back(obj());

                        int number =atoi(toperand.c_str());
                        objvec[obj_index].objcode=toHex(number);
                        objvec[obj_index].bytes=3;
                        objvec[obj_index].address=LOCCTR;
                        list << extend(toHex(LOCCTR)) << "\t";
                        objvec[obj_index].data_flag=0;
                        LOCCTR+=3;
                        obj_index++;
                    }
                }
            }//end if word
            else if (topcode=="BYTE")
            {
                loc=toperand.find("X");
                if(loc!=string::npos)
                {
                    objvec.push_back(obj());
                    objvec[obj_index].objcode=string(toperand,2,toperand.size()-3);
                    objvec[obj_index].bytes=getbyte(toperand);
                    cout<<"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<getbyte(toperand)<<endl;;
                    objvec[obj_index].address=LOCCTR;
                     list << extend(toHex(LOCCTR)) << "\t";
                    objvec[obj_index].data_flag=0;
                    LOCCTR+=getbyte(toperand);
                    obj_index++;
                }
                else
                {
                    loc=toperand.find("C");
                    if(loc!=string::npos)
                    {
                        objvec.push_back(obj());
                        string s3=string(toperand,2,toperand.size()-3);//
                        int number =toperand.size()-3;
                        int i=0;
                        string s4 ;
                        while(number>0)
                        {
                            int ascii=int(s3[i++]);
                            s4=toHex(ascii);
                            objvec[obj_index].objcode+=s4;
                            number--;
                        }
                        objvec[obj_index].bytes=getbyte(toperand);
                        objvec[obj_index].address=LOCCTR;
                         list << extend(toHex(LOCCTR)) << "\t";
                        objvec[obj_index].data_flag=0;
                        LOCCTR+=getbyte(toperand);
                        obj_index++;
                    }
                    else
                    {
                        objvec.push_back(obj());
                        int number =atoi(toperand.c_str());
                        objvec[obj_index].objcode=toHex(number);
                        objvec[obj_index].bytes=getbyte(toperand);
                        objvec[obj_index].address=LOCCTR;
                        list << extend(toHex(LOCCTR)) << "\t";
                        objvec[obj_index].data_flag=0;
                        LOCCTR+=getbyte(toperand);
                        obj_index++;
                    }
                }

            }
            else if(topcode=="BASE")
            {
                base_reg=SYMTAB[toperand].address;

            }
            else if (topcode[0]=='+')
            {
                cout<<"FORMAT 4 "<<endl;
                flagbits[5]='1';
                flagbits[4]='0';
                flagbits[3]='0';
                int loc =toperand.find(",X");

                if(loc!=string::npos)
                {
                    flagbits[2]='1';
                    flagbits[0]=flagbits[1]='1';
                }
                else
                {
                    int  loc =toperand.find("#");
                    if(loc!=string::npos)
                    {cout<<"FORMAAAAAAAAAAAAAAT4 imm"<<endl;
                        flagbits[2]='0';
                        flagbits[1]='1';
                        flagbits[0]='0';
                    }
                    else
                    {
                        int loc =toperand.find("@");
                        if(loc!=string::npos)
                        {
                            flagbits[2]='0';
                            flagbits[1]='0';
                            flagbits[0]='1';
                            modification_flag++;
                            mod.push_back(LOCCTR);

                        }
                        else
                        {
                            flagbits[2]='0';
                            flagbits[1]='1';
                            flagbits[0]='1';
                            modification_flag++;
                            mod.push_back(LOCCTR);


                        }

                    }


                }
                string opcodeb;
                string without=string(topcode,1,string::npos);
                string op_bin =hex_str_to_bin_str(OPTAB[without].opcode);
                string op_six=string(op_bin,0,6);
                objvec.push_back(obj());
                opcodeb+=op_six;

                opcodeb+=flagbits;
                cout<<"FLAAAAAAAAAAAG BITS"<<flagbits<<endl;
                cout<<"FLAG BITS first "<<flagbits[0]<<endl;
                cout<<"FLAGBITS one "<<flagbits[1]<<endl;
                if(flagbits[1]=='1'&&flagbits[0]=='0')
                {                        cout<<"TTTTTTTTTTTTTTTTTTTTTTTTTT"<<endl;

                    string nohash=string(toperand,1,string::npos);
                    int number =atoi(nohash.c_str());
                    string add=hex_str_to_bin_str(extendtofiv(toHex(number)));
                    opcodeb+=add;
                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                }
                else if (flagbits[0]=='1'&&flagbits[1]=='0')
                {
                    string noat=string(toperand,1,string::npos);
                    string add=hex_str_to_bin_str(extendtofiv((toHex(SYMTAB[noat].address))));
                    opcodeb+=add;
                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                }

                else
                {cout<<"JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ"<<endl;
                    string add=hex_str_to_bin_str(extendtofiv((toHex(SYMTAB[toperand].address))));
                    opcodeb+=add;
                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);

                }

                objvec[obj_index].bytes=4;
                objvec[obj_index].address=LOCCTR;
                list << extend(toHex(LOCCTR)) << "\t";
                objvec[obj_index].data_flag=0;

                obj_index++;
                LOCCTR+=4;


            }
            else if(OPTAB[topcode].format==1)
            {
                objvec.push_back(obj());
                objvec[obj_index].objcode=OPTAB[topcode].opcode;
                objvec[obj_index].bytes=1;
                objvec[obj_index].address=LOCCTR;
                list << extend(toHex(LOCCTR)) << "\t"; list << extend(toHex(LOCCTR)) << "\t";
                objvec[obj_index].data_flag=0;
                obj_index++;
                LOCCTR++;
            }
            else if (OPTAB[topcode].format==2)
            {
                objvec.push_back(obj());
                loc=toperand.find(",");
                if(loc!=string::npos)
                {
                    objvec[obj_index].objcode=OPTAB[topcode].opcode;
                    string s4=string(toperand,0,loc);
                    objvec[obj_index].objcode+=toHex(REGISTER[s4].num);
                    s4=string(toperand,loc+1,1);
                    objvec[obj_index].objcode+=toHex(REGISTER[s4].num);
                }
                else
                {
                    objvec[obj_index].objcode=OPTAB[topcode].opcode;
                    objvec[obj_index].objcode+=toHex(REGISTER[toperand].num);
                    cout<<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<toHex(REGISTER[toperand].num)<<endl;
                    objvec[obj_index].objcode+='0';
                }

                objvec[obj_index].bytes=2;
                objvec[obj_index].address=LOCCTR;
                objvec[obj_index].data_flag=0;
                 list << extend(toHex(LOCCTR)) << "\t";
                obj_index++;
                LOCCTR+=2;

            }
            else if (OPTAB[topcode].format==3)
            {
                cout<<"FORMAT 3 "<<endl;
                if(topcode=="RSUB")
                {
                    cout<<"RSUB"<<endl;
                    objvec.push_back(obj());
                    objvec[obj_index].objcode="4F0000";
                    objvec[obj_index].bytes=3;
                    objvec[obj_index].address=LOCCTR;
                     list << extend(toHex(LOCCTR)) << "\t";
                    objvec[obj_index].data_flag=0;
                    obj_index++;
                    LOCCTR+=3;
                }
                else
                {
                    cout<<"NOT RSUB"<<endl;
                    string opcodeb;
                    objvec.push_back(obj());
                    string op_bin =hex_str_to_bin_str(OPTAB[topcode].opcode);
                    string op_six=string(op_bin,0,6);
                    opcodeb+=op_six;
                    // objvec[obj_index].objcode=op_six;
                    int displacment;
                    flagbits[5]='0';
                    int  loc =toperand.find("#");
                    if(loc!=string::npos)
                    {
                        cout<<"IMMEDIATEEEEEEEEE"<<endl;
                        flagbits[1]='1';
                        flagbits[0]='0';
                        flagbits[2]='0';
                        if(!isalpha(toperand[1]))

                        {
                            string number_neg;
                            cout<<"IMMEDIATE SERF "<<endl;
                            string nohash=string(toperand,1,string::npos);
                            int number =atoi(nohash.c_str());
                            if(-2048<=number&&number<=2047)

                            {
                                flagbits[4]='0';
                                flagbits[3]='0';
                                opcodeb+=flagbits;

                                string disp=hex_str_to_bin_str(extendtothree(toHex(number)));
                                opcodeb+=disp;


                                objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                objvec[obj_index].bytes=3;
                                objvec[obj_index].address=LOCCTR;
                                objvec[obj_index].data_flag=0;
                                obj_index++;
                                 list << extend(toHex(LOCCTR)) << "\t";
                                LOCCTR+=3;

                            }
                            else
                            {

                                error_flag=1;
                            }//error immediate large
                        }
                        else
                        {cout<<"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"<<SourceLine[Scnt]<<endl;
                            int flag=0;
                            string disp_neg;
                            cout<<"IMMEDIATE W LABEL "<<endl;
                            string nohash=string(toperand,1,string::npos);
                            int disp=(SYMTAB[nohash].address)-(LOCCTR+3);
                            if(-2048<=disp&&disp<=2047)
                            {cout<<"sssssssssssssss"<<disp<<endl;
                                if(disp<0)
                                {
                                    flag=1;
                                    disp=-disp;
                                    disp_neg=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    twos_comp(disp_neg);


                                }
                                flagbits[4]='1';
                                flagbits[3]='0';


                                opcodeb+=flagbits;
                                if(flag==0)

                                {
                                    opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                }
                                else
                                {
                                    opcodeb+=disp_neg;
                                }
                                objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                objvec[obj_index].bytes=3;
                                objvec[obj_index].address=LOCCTR;
                                objvec[obj_index].data_flag=0;
                                obj_index++;
                                 list << extend(toHex(LOCCTR)) << "\t";
                                LOCCTR+=3;


                            }
                            else
                            {
                                if(base_reg==0)
                                {
                                    error_flag=2;                    // out of range and no base directive
                                }
                                 disp=(SYMTAB[nohash].address)-base_reg;
                                 if  (disp>=0&&disp<=4096)
                                {
                                    flagbits[3]='1';
                                    flagbits[4]='0';

                                    opcodeb+=flagbits;
                                    opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                    objvec[obj_index].bytes=3;
                                    objvec[obj_index].address=LOCCTR;
                                    objvec[obj_index].data_flag=0;
                                    obj_index++;
                                     list << extend(toHex(LOCCTR)) << "\t";
                                    LOCCTR+=3;

                                }
                                else
                                {
                                    error_flag=3 ; // out of range
                                }
                            }
                        }
                    }
                    else
                    {
                        int flag=0;
                        string disp_neg;
                        cout<<"checking if indirect"<<endl;
                        int  loc =toperand.find("@");
                        if(loc!=string::npos)
                        {
                            flagbits[0]='1';
                            flagbits[1]='0';
                            flagbits[2]='0';

                            string noat=string(toperand,1,string::npos);
                            int disp=(SYMTAB[noat].address)-(LOCCTR+3);
                            if(-2048<=disp&&disp<=2047)
                            {
                                if(disp<0)
                                {
                                    flag=1;
                                    disp=-disp;
                                    disp_neg=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    twos_comp(disp_neg);


                                }
                                flagbits[4]='1';
                                flagbits[3]='0';
                                opcodeb+=flagbits;
                                if(flag==0)
                                    opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                else
                                {

                                    opcodeb+=disp_neg;
                                }
                                objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                objvec[obj_index].bytes=3;
                                objvec[obj_index].address=LOCCTR;
                                objvec[obj_index].data_flag=0;
                                obj_index++;
                                 list << extend(toHex(LOCCTR)) << "\t";
                                LOCCTR+=3;


                            }
                            else
                            {
                                if(base_reg==0)
                                {
                                    error_flag=2;                    // out of range and no base directive
                                }
                                 disp=(SYMTAB[noat].address)-base_reg;
                                 if (disp>=0&&disp<=4096)
                                {
                                    flagbits[3]='1';
                                    flagbits[4]='0';
                                    opcodeb+=flagbits;
                                    opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                    objvec[obj_index].bytes=3;
                                    objvec[obj_index].address=LOCCTR;
                                    objvec[obj_index].data_flag=0;

                                    obj_index++;
                                     list << extend(toHex(LOCCTR)) << "\t";
                                    LOCCTR+=3;
                                }
                                else
                                {
                                    error_flag=3; // error out of range
                                }
                            }
                        }
                        else
                        {
                            string disp_neg;
                            int flag=0;
                            cout<<"NOT INDIRECT CHECKING IF INDEXED"<<endl;
                            int  loc =toperand.find(",X");
                            if(loc!=string::npos)
                            {cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<SourceLine[Scnt]<<endl;
                                flagbits[0]='1';
                                flagbits[1]='1';
                                flagbits[2]='1';

                                string nox=string(toperand,0,loc);
                                int disp=(SYMTAB[nox].address)-(LOCCTR+3);
                                cout<<disp<<endl;
                                if(-2048<=disp&&disp<=2047)
                                {cout<<"FAULTTTTTTTTTTTTTTTTTTTTTTTTTTT"<<endl;
                                    if(disp<0)
                                    {
                                        flag=1;
                                        disp=-disp;
                                        disp_neg=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                        twos_comp(disp_neg);


                                    }
                                    flagbits[4]='1';
                                    flagbits[3]='0';
                                    opcodeb+=flagbits;
                                    //objvec[obj_index].objcode+=flagbits;
                                    // objvec[obj_index].objcode+=extendtothree(toHex(disp));
                                    if(flag==0)
                                    {
                                        opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    }
                                    else
                                    {
                                        opcodeb+=disp_neg;
                                    }
                                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                    objvec[obj_index].bytes=3;
                                    objvec[obj_index].address=LOCCTR;
                                    objvec[obj_index].data_flag=0;
                                    obj_index++;
                                     list << extend(toHex(LOCCTR)) << "\t";
                                    LOCCTR+=3;


                                }
                                else
                                {
                                    if(base_reg==0)
                                    {
                                        error_flag=2;                    // out of range and no base directive
                                    }
                                    disp=(SYMTAB[nox].address)-base_reg;
                                    cout<<"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK"<<disp<<endl;
                                     if (disp>=0&&disp<=4096)//////////////////
                                    {cout<<"BASE REEEEEEEEEEEEEEEEEEEEEEEEEG " <<base_reg<<endl;
                                        flagbits[3]='1';
                                        flagbits[4]='0';

                                        opcodeb+=flagbits;
                                        opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                        objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                        cout<<" FORMAAAAAT 33333333333333333333333333333333333333333333333333333333 "<<endl;
                                        cout<<"FLAG BITS "<<flagbits<<endl;
                                        cout<<"OPCODE 6"<<op_six<<endl;
                                        cout<<"disp"<<disp<<endl;
                                        objvec[obj_index].bytes=3;
                                        objvec[obj_index].address=LOCCTR;
                                        objvec[obj_index].data_flag=0;
                                        obj_index++;
                                         list << extend(toHex(LOCCTR)) << "\t";
                                        LOCCTR+=3;
                                    }
                                    else
                                    {
                                        error_flag=3;// error out of range

                                    }
                                }

                            }
                            else
                            {cout<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"<<SourceLine[Scnt]<<endl;
                                string disp_neg;
                                int flag=0;
                                cout<<"HENAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
                                cout<<SourceLine[Scnt]<<endl;
                                flagbits[0]='1';
                                flagbits[1]='1';
                                flagbits[2]='0';
                                int disp=(SYMTAB[toperand].address)-(LOCCTR+3);
                                cout<<SYMTAB[toperand].address<<endl;
                                cout<<LOCCTR+3<<endl;
                                cout<<disp<<endl;
                                if(-2048<=disp&&disp<=2047)
                                {
                                    if(disp<0)
                                    {
                                        flag=1;
                                        disp=-disp;
                                        cout<<disp<<endl;
                                        disp_neg=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                        cout<<"Without "<<disp_neg<<endl;
                                        twos_comp(disp_neg);
                                        cout<<"LOCCTR"<<toHex(LOCCTR)<<endl;
                                        cout<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"<<disp_neg<<endl;;

                                    }
                                    flagbits[4]='1';
                                    flagbits[3]='0';
                                    opcodeb+=flagbits;
                                    //objvec[obj_index].objcode+=flagbits;
                                    // objvec[obj_index].objcode+=extendtothree(toHex(disp));
                                    if(flag==0)

                                    {           cout<<toHex(disp)<<endl;
                                        opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                    }
                                    else
                                    {
                                        opcodeb+=disp_neg;
                                    }
                                    objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                    string s333=objvec[obj_index].objcode;
                                    cout<<"now"<<s333<<endl;
                                    objvec[obj_index].bytes=3;
                                    objvec[obj_index].address=LOCCTR;
                                    objvec[obj_index].data_flag=0;
                                    obj_index++;
                                     list << extend(toHex(LOCCTR)) << "\t";
                                    LOCCTR+=3;


                                }
                                else
                                {
                                    if(base_reg==0)
                                    {
                                        error_flag=2;                    // out of range and no base directive
                                    }
                                    disp=(SYMTAB[toperand].address)-base_reg;
                                     if (disp>=0&&disp<=4096)
                                    {
                                        flagbits[3]='1';
                                        flagbits[4]='0';

                                        opcodeb+=flagbits;
                                        opcodeb+=hex_str_to_bin_str(extendtothree(toHex(disp)));
                                        objvec[obj_index].objcode=binstringtohexstring(opcodeb);
                                        cout<<" FORMAAAAAT 33333333333333333333333333333333333333333333333333333333 "<<endl;
                                        cout<<"FLAG BITS "<<flagbits<<endl;
                                        cout<<"OPCODE 6"<<op_six<<endl;
                                        cout<<"disp"<<disp<<endl;
                                        objvec[obj_index].bytes=3;
                                        objvec[obj_index].address=LOCCTR;
                                        objvec[obj_index].data_flag=0;
                                        obj_index++;
                                         list << extend(toHex(LOCCTR)) << "\t";
                                        LOCCTR+=3;
                                    }
                                    else
                                    {
                                        error_flag=3;// error out of range

                                    }
                                }


                            }


                        }


                    }



                }
            }

        }

        list<<SourceLine[Scnt]<<"\t"<<endl;
        switch (error_flag)
        {
        case 1:
        {cout << '\a';
            list << "   error:large immediate" << endl;
            break;
        }
        case 2:
        {cout << '\a';
            list << "   error: out of range and no base directive" << endl;
            break;
        }
        case 4:
        {cout << '\a';
             list << "  error: tried the base relative but still out of range" << endl;
            break;
        }
        default:
            break;
        }

        Scnt++;

        cout<<topcode<<endl;
    }
    cout<<"OUT"<<endl;
    o::iterator ig ;
    int number_bytes1=0;
    vector<int> num;
    int count =0;
    //TO COUNT NUMBER OF BYTES
    for(ig=objvec.begin(); ig!=objvec.end(); ig++)
    {
        if(number_bytes1 <= 30 || ig->data_flag == 1)
        {
            if(ig->data_flag == 1)
            {if(number_bytes1)
                num.push_back(number_bytes1);
                number_bytes1=0;
                continue;
            }
            else if(number_bytes1<=30)
            {
                number_bytes1+=ig->bytes;
                if(number_bytes1>30)
                {
                    number_bytes1-=ig->bytes;
      cout<<"EEEEEEEEEEEEEEEEEEEEEEEEEEE"<<number_bytes1<<endl;
                    num.push_back(number_bytes1);
                    number_bytes1=ig->bytes;

                }
            }
        }

    }
    num.push_back(number_bytes1);
    vector<int> ::iterator k;
    cout<<"llllllllllllllllllll"<<endl;
    for(k=num.begin(); k!=num.end(); k++)
    {
        cout<<*k<<endl;
    }
    cout<<"DSADA"<<endl;
  o::iterator il=objvec.begin();
  int flag =1;
  int count2=0;
  int number_bytes=0;
  int flag3=0;
objfile<<"T^"<<extendtosix(toHex(il->address))<<"^"<<extendtotwo(toHex(num[count2]));
cout<<"----------------------"<<endl;
cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<num.size()<<endl;
 for(il=objvec.begin();il!=objvec.end();il++)
 {if(il->data_flag==1)
    continue;
     if(number_bytes==num[count2]&&count2!=(num.size()-1))
 {
     number_bytes=0;
     count2++;
     objfile<<endl;
     objfile<<"T^"<<extendtosix(toHex(il->address))<<"^"<<extendtotwo(toHex(num[count2]));
 }
 transform((il->objcode).begin(), (il->objcode).end(), (il->objcode).begin(),::toupper);

 objfile<<"^"<<il->objcode;
 number_bytes+=il->bytes;
 }
 cout<<"-------------------------"<<endl;
 objfile<<endl;

    if(modification_flag>0)

    {
        int i=0;
        while(modification_flag>0)
        {
            objfile <<"M^"<<extendtosix((toHex(mod[i]+1)))<<"^05"<<endl;
            cout<<mod[i]<<endl;
            i++;
            modification_flag--;
//cout<<i<<endl;
        }
    }
    objfile<<"E^"<<extendtosix(toHex(ENDval));


    o::iterator i ;
    for(i=objvec.begin(); i!=objvec.end(); i++)
        cout<<i->objcode<<endl;
}
