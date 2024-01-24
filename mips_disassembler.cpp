
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "mips_disassembler.hpp"

Disassembler::Disassembler()
{
    // input instructions into array
    instructions[0] = 0x1107000A;
    instructions[1] = 0x8CE90014;
    instructions[2] = 0x12A90003;
    instructions[3] = 0x022DA822;
    instructions[4] = 0xADB30020;
    instructions[5] = 0x02697824;
    instructions[6] = 0xAE8FFFF4;
    instructions[7] = 0x018C6020;
    instructions[8] = 0x02A4A825;
    instructions[9] = 0x158FFFF7;
    instructions[10] = 0x8ECDFFF0;

    // initialize address
    address = 0x9a000;
    
    // increment address and figure out opcode for every instruction
    for(int i = 0; i <= 10; ++i)
    {
        cout << hex << address << " ";
        increment();
        set_opcode(instructions[i]);
    }
    
}

// set opcode
void Disassembler::set_opcode(int instruction)
{
    opcode = (instruction & 0xFC000000) >> 26;
    
    // if opcode = 0, go to rtype disassembler
    if(opcode == 0)
    {
        r_format(instruction);
    }
    // if not, go to itype disassembler
    else
    {
        i_format(instruction);
    }
}

// set first register
void Disassembler::set_src_register1(int instruction)
{
    src_reg1 = (instruction & 0x03E00000) >> 21;
}

// get first register
int Disassembler::get_src_register1()
{
    return src_reg1;
}

// set second register
void Disassembler::set_src_register2(int instruction)
{
    src_reg2 = (instruction & 0x001F0000) >> 16;
}

// get second register
int Disassembler::get_src_register2()
{
    return src_reg2;
}

// set destination register
void Disassembler::set_dest_register(int instruction)
{
    dest_reg = (instruction & 0x0000F800) >> 11;
}

// get desitination register
int Disassembler::get_dest_register()
{
    return dest_reg;
}

// set offset
void Disassembler::set_offset(int instruction)
{
    offset = (instruction & 0x0000FFFF);
    
    // for branches, bit shift
    if(opcode == 4 || opcode == 5) offset <<= 2;
    
}

// get offset
short Disassembler::get_offset()
{
    return offset;
}

// set function
void Disassembler::set_function(int instruction)
{
    function = (instruction & 0x0000003F);
    
    // print different functions
    if(function == 32)
    {
        cout << "add ";
    }
    else if(function == 34)
    {
        cout << "sub ";
    }
    else if(function == 36)
    {
        cout << "and ";
    }
    else if(function == 37)
    {
        cout << "or ";
    }
    
}

// disassemble r-format instruction
void Disassembler::r_format(int instruction)
{
    set_function(instruction);
    
    set_dest_register(instruction);
    cout << dec << "$" << get_dest_register() << ", ";
    
    set_src_register1(instruction);
    cout<< dec << "$" << get_src_register1() << ", ";
    
    set_src_register2(instruction);
    cout<< dec <<"$" << get_src_register2() << " \n";
}

// disassemble i-format instruction
void Disassembler::i_format(int instruction)
{
    if(opcode == 4 || opcode == 5)
    {
        branch(instruction);
    }
    else
    {
        if(opcode == 35)
        {
            cout << "lw ";
            
        }
        else if(opcode == 43)
        {
            cout << "sw ";
        }

        set_src_register2(instruction);
        cout<< dec << "$" << get_src_register2() << ", ";
        
        set_offset(instruction);
        cout<< dec << get_offset() << " ";
        
        set_src_register1(instruction);
        cout<< dec << "($" << get_src_register1() << ") \n";
    }
}

// disassemble branch
void Disassembler::branch(int instruction)
{
    if(opcode == 4)
    {
        cout << "beq ";
    }
    else if(opcode == 5)
    {
        cout << "bne ";
    }
    
    set_src_register2(instruction);
    cout<< dec << "$" << get_src_register2() << ", ";
    
    set_src_register1(instruction);
    cout<< dec <<"$" << get_src_register1() << ", ";

    set_offset(instruction);
    label = offset + address;
    cout<< "address " << hex << label << " \n";
}

// increment address
void Disassembler::increment()
{
    address += 4;
    
}
