#include "Memory.h"


void Memory::ADD(int32_t x){
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;
    if (shift != 0){
        exit(-10);
    }

    if ((((reg[rsource] + reg[rtmp]) > 0) && (reg[rsource] < 0) && (reg[rtmp] < 0)) || 
        (((reg[rsource] + reg[rtmp]) < 0) && (reg[rsource] > 0) && (reg[rtmp] > 0))){
        exit(-10);
    }
    // place result in register
    reg[rdest] = (reg[rsource] + reg[rtmp]);
    
    pc = npc;
    npc += 4;
}

void Memory::ADDU(int32_t x){
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-10);
    }

    reg[rdest] = (reg[rsource] + reg[rtmp]);
    pc = npc;
    npc += 4;
}

void Memory::AND(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-10);
    }

    reg[rdest] = reg[rsource] & reg[rtmp];
    pc = npc;
    npc += 4;
}

void Memory::OR(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-10);
    }

    reg[rdest] = reg[rsource] | reg[rtmp];
    pc = npc;
    npc += 4;
}

void Memory::DIV(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0){
        exit(-12);
    }
    if (reg[rtmp] == 0){
        exit(-10);
    }

    if  ((((reg[rsource] / reg[rtmp]) > 0) && (reg[rsource] > 0) && (reg[rtmp] < 0)) || 
        ((( reg[rsource] / reg[rtmp]) > 0) && (reg[rsource] < 0) && (reg[rtmp] > 0)) ||
        ((( reg[rsource] / reg[rtmp]) < 0) && (reg[rsource] < 0) && (reg[rtmp] < 0)) ||
        ((( reg[rsource] / reg[rtmp]) < 0) && (reg[rsource] > 0) && (reg[rtmp] > 0))){
            exit(-10);
        }

    lo = reg[rsource] / reg[rtmp];
    hi = reg[rsource] % reg[rtmp];

    pc = npc;
    npc += 4;
}

void Memory::DIVU(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0){
        exit(-12);
    }
    if (reg[rtmp] == 0){
        exit(-10);
    }

    uint32_t src1 = static_cast<uint32_t> (reg[rsource]);
    uint32_t src2 = static_cast<uint32_t> (reg[rtmp]);
    lo = static_cast<int32_t> (src1 / src2);
    hi = static_cast<int32_t> (src1 % src2);
    pc = npc;
    npc += 4;
}

void Memory::JR(int32_t x){
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || rtmp != 0 || shift != 0){
        exit(-12);
    }
    if ((reg[rsource] % 4) != 0){
        exit(-12);
    }
    pc = npc;
    npc = reg[rsource];
}
void Memory::JALR(int32_t x){

    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;
    if (rtmp != 0 || shift != 0){
        exit(-12);
    }
    reg[rdest] = pc + 8;
    pc = npc;
    npc = reg[rsource];

}

void Memory::MTHI(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0 || rtmp != 0){
        exit(-12);
    }

    hi = reg[rsource];

    pc = npc;
    npc += 4;
}
void Memory::MTLO(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rdest != 0 || shift != 0 || rtmp != 0){
        exit(-12);
    }

    lo = reg[rsource];
    pc = npc;
    npc += 4;
}

void Memory::MFHI(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0 || shift != 0 || rtmp != 0){
        exit(-12);
    }

    reg[rdest] = hi;
    pc = npc;
    npc += 4;
}

void Memory::MFLO(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0 || shift != 0 || rtmp != 0){
        exit(-12);
    }

    reg[rdest] = lo;
    pc = npc;
    npc += 4;
}

void Memory::MULTU(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;
    
    if (rdest != 0 || shift != 0){
        exit(-12);
    }
    
    uint64_t a = static_cast<uint64_t> (static_cast<uint32_t>(reg[rsource]));
    uint64_t b = static_cast<uint64_t> (static_cast<uint32_t>(reg[rtmp]));
    uint64_t result = a * b;
    lo = static_cast<int32_t> (result);
    hi = static_cast<int32_t> (result >> 32);
    pc = npc;
    npc += 4;
}
void Memory::MULT(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;
    
    if (rdest != 0 || shift != 0){
        exit(-12);
    }
    
    int64_t a = static_cast<int64_t> (reg[rsource]);
    int64_t b = static_cast<int64_t> (reg[rtmp]);
    int64_t result = a * b;
    lo = static_cast<int32_t> (result);
    hi = static_cast<int32_t> (result >> 32);
    pc = npc;
    npc += 4;
}


void Memory::XOR(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){ exit(-12); }

    reg[rdest] = (reg[rsource] ^ reg[rtmp]);
    pc = npc;
    npc += 4;
}

void Memory::SLT(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-12);
    }

    (reg[rsource] < reg[rtmp]) ? reg[rdest] = 1 : reg[rdest] = 0;
    pc = npc;
    npc += 4;
}

void Memory::SLTU(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-12);
    }
    uint32_t a = static_cast<uint32_t> (reg[rsource]);
    uint32_t b = static_cast<uint32_t> (reg[rtmp]);

    (a < b) ? reg[rdest] = 1 : reg[rdest] = 0;
    pc = npc;
    npc += 4;
}

void Memory::SLL(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0){
        exit(-12);
    }

    uint32_t a = static_cast<uint32_t> (reg[rtmp]);

    reg[rdest] = a << shift;
    pc = npc;
    npc += 4;
}

void Memory::SLLV(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-12);
    }

    uint32_t a = static_cast<uint32_t> (reg[rtmp]);
    uint32_t shift2 = static_cast<uint32_t> (reg[rsource]);

    reg[rdest] = a << shift2;
    pc = npc;
    npc += 4;
}

void Memory::SRL(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0){
        exit(-12);
    }

    uint32_t a = static_cast<uint32_t> (reg[rtmp]);

    reg[rdest] = a >> shift;
    pc = npc;
    npc += 4;
}
void Memory::SRLV(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-12);
    }

    uint32_t a = static_cast<uint32_t> (reg[rtmp]);
    uint32_t shift2 = static_cast<uint32_t> (reg[rsource]);

    reg[rdest] = a >> shift2;
    pc = npc;
    npc += 4;
}

void Memory::SRA(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (rsource != 0){
        exit(-12);
    }

    reg[rdest] = reg[rtmp] >> shift;
    pc = npc;
    npc += 4;
}

void Memory::SRAV(int32_t x){
    
    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-12);
    }

    uint32_t shift2 = static_cast<uint32_t> (reg[rsource]);

    reg[rdest] = reg[rtmp] >> shift2;
    pc = npc;
    npc += 4;
}

void Memory::SUB(int32_t x){
    

    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    // store for overflow tests
    int32_t source1 = reg[rsource];
    int32_t source2 = reg[rtmp];

    if (shift != 0){
        exit(-10);
    }

    // place result in register
    reg[rdest] = (reg[rsource] - reg[rtmp]);
    
    if ((source1 > 0 && source2 < 0 && reg[rdest] < 0) || 
        (source1 < 0 && source2 > 0 && reg[rdest] > 0)){
        exit(-10);
    }
    pc = npc;
    npc += 4;
}

void Memory::SUBU(int32_t x){

    int32_t rsource = (x >> 21) & 0b11111;
    int32_t rtmp = (x >> 16) & 0b11111;
    int32_t rdest = (x >> 11) & 0b11111;
    int32_t shift = (x >> 6) & 0b11111;

    if (shift != 0){
        exit(-10);
    }
    // place result in register
    reg[rdest] = (reg[rsource] - reg[rtmp]);
    pc = npc;
    npc += 4;

}