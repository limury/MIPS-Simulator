
#include "Memory.h"

Memory::Memory(const vector<int32_t>& input): executable(input), pc(0x10000000), hi(0), lo(0){}

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
        if (opcode == 0){
            
            if (x & 0b1111100000000000 == 0){
                exit(-11);
            }
            int32_t funct = x & 0b111111;
            switch(funct){
                case Add : this->ADD(x); break;
                case Addu : this->ADDU(x); break;
                case And : this->AND(x); break;
            }
        }
        // I type
        // J types
        
    }
    return;
}


