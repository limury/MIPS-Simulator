#include "Memory.h"

void Memory::J(int32_t x){

    pc += 4;

    int32_t target = x & 0x3FFFFFF;

    pc = target << 2;

}

void Memory::JAL(int32_t x){

    int32_t target = x & 0x3FFFFFF;

    reg[31] = pc + 8;

    pc = target << 2;
}