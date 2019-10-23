
#include "Memory.h"

Memory::Memory(const vector<unsigned int>& input): executable(input), pc(0){}

void Memory::run(){
    for (unsigned int x: executable){
        // if no instruction continue
        if (x == 0){continue;}

        unsigned int opcode = x >> 26;
        // R type
        if (opcode == 0){

            unsigned int funct = x && 0b111111;
            unsigned int rsource = (x >> 21) && 0b11111;
            unsigned int rsecond = (x >> 16) && 0b11111;
            unsigned int rdest = (x >> 11) && 0b11111;
            unsigned int shift = (x >> 6) && 0b11111;

            // add
            try{
                if ( funct == 0x20 ){
                    // place result in register
                    reg[rdest] = (reg[rsource] << shift + reg[rsecond]);
                    
                    // check for overflows
                    uint64_t result, shifted, sr, st;
                    sr = reg[rsource];
                    st = reg[rsecond];
                    shifted = sr << shift;
                    result = shifted + st;

                    if ((result >> 32) != 0){
                        throw RESULT_OVERFLOW;
                    }
                    if ((shifted >> 32) != 0){
                        throw SHIFT_OVERFLOW;
                    }
                    
                }
            }
            catch (int e){
        //----------------------------------------------------------------------------------------
            }
    }
}


