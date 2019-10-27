
#include "Memory.h"

Memory::Memory(const vector<int32_t>& input): executable(input), pc(0x10000000), hi(0), lo(0){
    
}

void Memory::run(){
    while (pc != 0){

        if (pc < 0x10000000 || pc >= 0x11000000){
            exit(-12);
        }

        int32_t x = executable.at(pc - 0x10000000);
        // if no instruction continue
        if (x == 0){continue;}

        int32_t opcode = x >> 26;
        
        // R type
        switch (opcode){
            case RType : {

            if ((x & 0b1111100000000000) == 0){
                exit(-11);
            }
            int32_t funct = x & 0b111111;

            switch(funct){
                case Add : this->ADD(x); break;
                case Addu : this->ADDU(x); break;
                case And : this->AND(x); break;
                case Div : this->DIV(x); break;
                case Divu : this->DIVU(x); break;
                case Jr : this->JR(x); break;
                case Jalr : this->JALR(x); break;
                case Mfhi : this->MFHI(x); break;
                case Mflo : this->MFLO(x); break;
                case Mthi : this->MTHI(x); break;
                case Mtlo : this->MTLO(x); break;
                case Mult : this->MULT(x); break;
                case Multu : this->MULTU(x); break;
                case Xor : this->XOR(x); break;
                case Or : this->OR(x); break;
                case Slt : this->SLT(x); break;
                case Sltu : this->SLTU(x); break;
                case Sll : this->SLL(x); break;
                case Sllv : this->SLLV(x); break;
                case Srl : this->SRL(x); break;
                case Sra : this->SRA(x); break;
                case Srav : this->SRAV(x); break;
                case Sub : this->SUB(x); break;
                case Subu : this->SUBU(x); break;
        }}; break;
        
        // I type
        // J types
            case j : J(x); break;
            case Jal : JAL(x); break;
        }
    } 
    return;
}


