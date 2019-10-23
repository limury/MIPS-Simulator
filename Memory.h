#ifndef MEMORY
#define MEMORY

#include "includes.h"

enum Errors { RESULT_OVERFLOW = 0, SHIFT_OVERFLOW = 1, MEMFAIL = 2 };
enum RCalls {   Add = 0x20, Addu = 0x21, And = 0x24, Div = 0x1A, Divu = 0x1B, 
                Jr = 0x08, Mfhi = 0x10, Mthi = 0x11, Mflo = 0x12, Mtlo = 0x13, 
                Mult = 0x18, Multu = 0x19, Nor = 0x27, Xor = 0x26, Or = 0x25, 
                Slt = 0x2A, Sltu = 0x2B, Sll = 0x00, Srl = 0x02, Sra = 0x03, 
                Sub = 0x22, Subu = 0x23};

class Memory{
    public:
        Memory(const vector<uint32_t>& input);
        void run();
    
    private:
        void ADD(uint32_t x);
        void ADDU(uint32_t x);
        void AND(uint32_t x);
        void DIV(uint32_t x);


        vector<uint32_t> reg{32, 0};
        uint32_t pc;
        vector<uint32_t> executable{0x1000000, 0};
        vector<uint32_t> read_write{0x4000000, 0};

};

#endif //MEMORY