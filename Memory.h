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
        Memory(const vector<uint8_t>& input);
        void run();
        uint8_t read (const uint32_t& addr);
        void write (const uint32_t& addr, const uint8_t& val);
    
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
    
        void ADDI(int32_t x);
        void ADDIU(int32_t x);
        void ANDI(int32_t x);
        void BEQ(int32_t x);
        void BGEZ(int32_t x);
        void BGEZAL(int32_t x);
        void BGTZ(int32_t x);
        void BLEZ(int32_t x);
        void BLTZ(int32_t x);
        void BLTZAL(int32_t x);
        void BNE(int32_t x);
        void LB(int32_t x);
        void LBU(int32_t x);
        void LH(int32_t x);
        void LHU(int32_t x);
        void LUI(int32_t x);
        void LW(int32_t x);
        void LWL(int32_t x);
        void LWR(int32_t x);
        void ORI(int32_t x);
        void SB(int32_t x);
        void SH(int32_t x);
        void SLTI(int32_t x);
        void SLTIU(int32_t x);
        void SW(int32_t x);
        void XORI(int32_t x);

    // J type
        void J(int32_t x);
        void JAL(int32_t x);



    // Declarations
        vector<int32_t> reg;
        vector<uint8_t> read_write;
        vector<uint8_t> executable;
        vector<uint8_t> getch;
        vector<uint8_t> putch;
        int32_t pc;
        int32_t hi, lo;

};

#endif //MEMORY