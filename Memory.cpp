
#include "Memory.h"

Memory::Memory(const vector<uint8_t>& input):reg(32, 0), read_write(0x4000000, 0), executable(input), getch(0x4, 0), putch(0x4, 0), pc(0x10000000), hi(0), lo(0){
    executable.resize(0x1000000);
}

uint8_t Memory::read(const uint32_t& addr, bool newchar = true){
    if (addr >= 0x10000000 && addr < 0x11000000){
        return executable.at(addr - 0x10000000);
    }
    else if (addr >= 0x20000000 && addr < 0x24000000){
        return read_write.at(addr - 0x20000000);
    }
    else if (addr >= 0x30000000 && addr < 0x30000004){
        if (newchar == true){
            char val = getchar();
            uint8_t tmp_t = static_cast<uint8_t> (val);
            if (tmp_t == 255){
                getch.at(3) = 255;
                getch.at(2) = 255;
                getch.at(1) = 255;
                getch.at(0) = 255;
            }
            else {
                getch.at(3) = tmp_t;
                getch.at(2) = 0;
                getch.at(1) = 0;
                getch.at(0) = 0;
            }
        }
        return getch.at(addr - 0x30000000);
    }
    else {
        exit(-11);
    }
}

void Memory::write(const uint32_t& addr, const uint8_t& val){
    if (addr >= 0x20000000 && addr < 0x24000000){
        read_write.at(addr - 0x20000000) = val;
    }
    else if (addr >= 0x30000004 && addr < 0x30000008){
        char out = static_cast<char> (val);
        putchar(out);
        putch.at(addr - 0x30000004) = static_cast<uint8_t> (out);
    }
    else {
        exit(-11);
    }
}

void Memory::run(){
    while (pc != 0){
        if (reg[0] != 0){
            reg[0] = 0;
            exit(-12);
        }

        if (pc < 0x10000000 || pc >= 0x11000000){
            exit(-11);
        }

        uint32_t MSB = static_cast<uint32_t> (executable.at(pc - 0x10000000));
        uint32_t MSB1 = static_cast<uint32_t> (executable.at(pc - 0x10000000 + 1));
        uint32_t LSB1 = static_cast<uint32_t> (executable.at(pc - 0x10000000 + 2));
        uint32_t LSB = static_cast<uint32_t> (executable.at(pc - 0x10000000 + 3));

        int32_t x = (MSB << 24) | (MSB1 << 16) | (LSB1 << 8) | (LSB);

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
            case Addi : this->ADDI(x); break;
            case Addiu : this->ADDIU(x); break;
            case Andi : this->ANDI(x); break;
            case Beq : this->BEQ(x); break;

            case Bgez : {  
                int32_t funct = (x >> 16) & 0b11111;
                if (funct == 1) { this->BGEZ(x);}
                else if (funct == 0b10001) { this->BGEZAL(x);}
                else if (funct == 0) { this->BLTZ(x); }
                else if (funct == 0b10000) { this->BLTZAL(x);}
            }; break;

            case Bgtz : this->BGTZ(x); break;
            case Blez : this->BLEZ(x); break;
            case Bne : this->BNE(x); break;
            case Lb : this->LB(x); break;
            case Lbu : this->LBU(x); break;
            case Lh : this->LH(x); break;
            case Lhu : this->LHU(x); break;
            case Lui : this->LUI(x); break;
            case Lw : this->LW(x); break;
            case Lwl : this->LWL(x); break;
            case Lwr : this->LWR(x); break;
            case Ori : this->ORI(x); break;
            case Sb : this->SB(x); break;
            case Sh : this->SH(x); break;
            case Slti : this->SLTI(x); break;
            case Sltiu : this->SLTIU(x); break;
            case Sw : this->SW(x); break;
            case Xori : this->XORI(x); break;

        // J types
            case j : this->J(x); break;
            case Jal : this->JAL(x); break;
        }
        // invalid instruction error
    } 
    return;
}


