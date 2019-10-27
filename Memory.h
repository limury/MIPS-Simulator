#ifndef MEMORY
#define MEMORY

#include "includes.h"


enum RCalls {   Add = 0x20, Addu = 0x21, And = 0x24, Div = 0x1A, Divu = 0x1B, 
                Jr = 0x08, Mfhi = 0x10, Mthi = 0x11, Mflo = 0x12, Mtlo = 0x13, 
                Mult = 0x18, Multu = 0x19, Xor = 0x26, Or = 0x25, Slt = 0x2A, 
                Sltu = 0x2B, Sll = 0x00, Sllv = 0x04, Srl = 0x02, Srlv = 0x06, 
                Sra = 0x03, Srav = 0x07, Sub = 0x22, Subu = 0x23, Jalr = 0x09};

enum OpCodes { RType = 0x0, j = 0x02, Jal = 0x03 };

class Memory{
    public:
        Memory(const vector<int32_t>& input);
        void run();
    
    private:
    // R type
        void ADD(int32_t x);
        void ADDU(int32_t x);
        void AND(int32_t x);
        void DIV(int32_t x);
        void DIVU(int32_t x);
        void JR(int32_t x);
        void JALR(int32_t x);
        void MFHI(int32_t x);
        void MFLO(int32_t x);
        void MTLO(int32_t x);
        void MTHI(int32_t x);
        void MULT(int32_t x);
        void MULTU(int32_t x);
        void XOR(int32_t x);
        void OR(int32_t x);
        void SLT(int32_t x);
        void SLTU(int32_t x);
        void SLL(int32_t x);
        void SLLV(int32_t x);
        void SRL(int32_t x);
        void SRLV(int32_t x);
        void SRA(int32_t x);
        void SRAV(int32_t x);
        void SUB(int32_t x);
        void SUBU(int32_t x);

    // I type

    // J type
        void J(int32_t x);
        void JAL(int32_t x);



        vector<int32_t> reg{32, 0};
        vector<int32_t> read_write{0x4000000, 0};
        vector<int32_t> executable {0x1000000, 0};
        int32_t pc;
        int32_t hi, lo;

};

#endif //MEMORY