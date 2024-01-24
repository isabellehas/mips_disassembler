

#ifndef mipsdisassembler_h
#define mipsdisassembler_h

#include <iomanip>
#include <iostream>
#include <array>
//#include <vector>
using namespace std;

class Disassembler
{
public:
    static const size_t instructionset = 11; // declare arrray size
    
    Disassembler(); // initial constructor
    void set_opcode(int instruction); // find opcode
    void r_format(int instruction); // r type
    void i_format(int instruction); // i type
    void branch(int instruction); // branch
    void set_function(int instruction); // find function
    void set_src_register1(int instruction); // set first register
    int get_src_register1(); // return first register
    void set_src_register2(int instruction); // set second register
    int get_src_register2(); // get second register
    void set_dest_register(int instruction); // set destination register
    int get_dest_register(); // get destination register
    void set_offset(int instruction); // set offset
    short get_offset(); // get offset
    void increment(); // increment address
    
private:
    int opcode;
    int address;
    int label;
    int function;
    int src_reg1;
    int src_reg2;
    int dest_reg;
    //int addresscount;
    short offset;
    array<int, instructionset> instructions; // delcare aray
};

#endif /* mipsdisassembler_h */
