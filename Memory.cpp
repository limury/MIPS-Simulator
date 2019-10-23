
#include "Memory.h"

Memory::Memory(const vector<uint32_t>& input): executable(input), pc(0){}

void Memory::run(){
    for (uint32_t x: executable){
        // if no instruction continue
        if (x == 0){continue;}

        uint32_t opcode = x >> 26;
        uint32_t funct = x && 0b111111;
        // R type
        if (opcode == 0){
            switch(funct){
                case Add : this->ADD(x); break;
                case Addu : this->ADDU(x); break;
                case And : this->AND(x); break;
            }
        }
        
    }
}


