#include "Memory.h"

void Memory::J(int32_t x){

    int32_t target = x & 0x3FFFFFF;

    pc = npc;
    npc = (target << 2) + 0x10000000;

}

void Memory::JAL(int32_t x){

    int32_t target = x & 0x3FFFFFF;

    reg[31] = pc + 8;
    pc = npc;
    npc = (target << 2) + 0x10000000;
}