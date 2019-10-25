#include "Memory.h"


void Memory::ADD(uint32_t x){
    pc += 4;

    uint32_t rsource = (x >> 21) & 0b11111;
    uint32_t rsecond = (x >> 16) & 0b11111;
    uint32_t rdest = (x >> 11) & 0b11111;
    uint32_t shift = (x >> 6) & 0b11111;
        
    // place result in register
    reg[rdest] = (reg[rsource] << shift + reg[rsecond]);
                
    // check for overflows
    uint64_t result, shifted, sr, st;
    sr = reg[rsource];
    st = reg[rsecond];
    shifted = sr << shift;
    result = shifted + st;

    if (!((result >> 32) == 0 || (result >> 32) == 0xFFFFFFFF)){
        exit(-10);
    }
    if (!((shifted >> 32) != 0 || (shifted >> 32) == 0xFFFFFFFF)){
        exit(-10);
    }
}

void Memory::ADDU(uint32_t x){
    pc+= 4;

    uint32_t rsource = (x >> 21) & 0b11111;
    uint32_t rsecond = (x >> 16) & 0b11111;
    uint32_t rdest = (x >> 11) & 0b11111;
    uint32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = (reg[rsource] << shift + reg[rsecond]);
}

void Memory::AND(uint32_t x){
    pc += 4;
    uint32_t rsource = (x >> 21) & 0b11111;
    uint32_t rsecond = (x >> 16) & 0b11111;
    uint32_t rdest = (x >> 11) & 0b11111;
    uint32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = (reg[rsource] << shift) & reg[rsecond];
}
void Memory::OR(uint32_t x){
    pc += 4;
    uint32_t rsource = (x >> 21) & 0b11111;
    uint32_t rsecond = (x >> 16) & 0b11111;
    uint32_t rdest = (x >> 11) & 0b11111;
    uint32_t shift = (x >> 6) & 0b11111;

    reg[rdest] = (reg[rsource] << shift) | reg[rsecond];
}
/*
void Memory::DIV(uint32_t x){
    uint32_t rsource = (x >> 21) & 0b11111;
    uint32_t rsecond = (x >> 16) & 0b11111;
    uint32_t rdest = (x >> 11) & 0b11111;
    uint32_t shift = (x >> 6) & 0b11111;

}*/