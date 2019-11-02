#include "Memory.h"

void Memory::J(int32_t x){

    int32_t target = x & 0x3FFFFFF;

    int32_t tmp = pc & 0xF0000000;
    pc = npc;
    npc = (target << 2) | tmp;

}

void Memory::JAL(int32_t x){

    int32_t target = x & 0x3FFFFFF;
    int32_t tmp = pc & 0xF0000000;
    reg[31] = pc + 8;
    pc = npc;
    npc = (target << 2) | tmp;
}