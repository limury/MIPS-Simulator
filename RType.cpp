#include "Memory.h"


void Memory::ADD(int32_t x){
    pc += 4;

    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    // store for overflow tests
    int32_t source1 = reg[rsource];
    int32_t source2 = reg[rsecond];

    // place result in register
    reg[rdest] = ((reg[rsource] << shift) + reg[rsecond]);
    
    if ((reg[rdest] > 0 && source1 < 0 && source2 < 0) || (reg[rdest] > 0 && source1 < 0 && source2 < 0)){
        exit(-10);
    }

}

void Memory::ADDU(int32_t x){
    pc+= 4;

    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = ((reg[rsource] << shift) + reg[rsecond]);
}

void Memory::AND(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = (reg[rsource] << shift) & reg[rsecond];
}

void Memory::OR(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = (reg[rsource] << shift) | reg[rsecond];
}

void Memory::DIV(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0){
        exit(-12);
    }

    lo = reg[rsource] / reg[rsecond];
    hi = reg[rsource] % reg[rsecond];

}

void Memory::DIVU(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0){
        exit(-12);
    }

    uint32_t src1 = (uint32_t) reg[rsource];
    uint32_t src2 = (uint32_t) reg[rsecond];
    lo = (int32_t) (src1 / src2);
    hi = (int32_t) (src1 % src2);
}

void Memory::JR(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || rsecond != 0 || shift != 0){
        exit(-12);
    }

    pc = reg[rsource];
}

void Memory::MFHI(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0 || shift != 0 || rsecond != 0){
        exit(-12);
    }

    reg[rdest] = hi;
}
void Memory::MFLO(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rsecond = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0 || shift != 0 || rsecond != 0){
        exit(-12);
    }

    reg[rdest] = lo;
}