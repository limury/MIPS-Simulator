#include "Memory.h"

void Memory::ADDI(int32_t x){
    pc += 4;

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);


    if (((reg[rsource] + immediate) > 0 && reg[rsource] < 0 && immediate < 0) || 
        ((reg[rsource] + immediate) < 0 && reg[rsource] > 0 && immediate > 0)){
        exit(-10);
    }
    // place result in register
    reg[rtmp] = (reg[rsource] + immediate);
}
void Memory::ADDIU(int32_t x){
    pc += 4;

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] + immediate);
}

void Memory::ANDI(int32_t x){
    pc += 4;

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] & immediate);
}

void Memory::BEQ(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (reg[rsource] == reg[rtmp]){
        pc += (immediate << 2);
    }
    else {
        pc += 4;
    }
}

void Memory::BGEZ(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 1){
        exit(-12);
    }

    if (reg[rsource] >= 0){
        pc += (immediate << 2);
    }
    else {
        pc += 4;
    }
}

void Memory::BGEZAL(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x11){
        exit(-12);
    }

    if (reg[rsource] >= 0){
        reg[31] = pc + 8;
        pc += (immediate << 2);

    }
    else {
        pc += 4;
    }
}

void Memory::BGTZ(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] > 0){
        pc += (immediate << 2);

    }
    else {
        pc += 4;
    }
}
void Memory::BLEZ(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] <= 0){
        pc += (immediate << 2);

    }
    else {
        pc += 4;
    }
}
void Memory::BLTZ(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] < 0){
        pc += (immediate << 2);

    }
    else {
        pc += 4;
    }
}
void Memory::BLTZAL(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] < 0){
        reg[31] = pc + 8;
        pc += (immediate << 2);
    }
    else {
        pc += 4;
    }
}
void Memory::BNE(int32_t x){

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (reg[rsource] != reg[rtmp]){
        pc += (immediate << 2);
    }

    else {
        pc += 4;
    }
}

void Memory::LB(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        int32_t val32b = executable[(mem_loc - 0x10000000)];
        int8_t val = static_cast<int8_t> (val32b >> (8 * (3 - byte_num)));
        reg[rtmp] = static_cast<int32_t> (val);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        int32_t val32b = read_write[(mem_loc - 0x20000000)];
        int8_t val = static_cast<int8_t> (val32b >> (8 * (3 - byte_num)));
        reg[rtmp] = static_cast<int32_t> (val);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        reg[rtmp] = static_cast<int32_t> (val);
    }
    else {
        exit(-11);
    }
}

void Memory::LBU(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        uint32_t val32b = static_cast<uint32_t> (executable[(mem_loc - 0x10000000)]);
        uint8_t val = static_cast<uint8_t> (val32b >> (8 * (3 - byte_num)));
        uint32_t tmp_t = static_cast<uint32_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        uint32_t val32b = static_cast<uint32_t> (read_write[(mem_loc - 0x20000000)]);
        uint8_t val = static_cast<uint8_t> ( val32b >> (8 * (3 - byte_num)));
        uint32_t tmp_t = static_cast<uint32_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        uint8_t tmp_t = static_cast<uint8_t> (val);
        reg[rtmp] = static_cast<uint32_t> (tmp_t);
    }
    else {
        exit(-11);
    }
}

void Memory::LH(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    if (byte_num == 1 || byte_num == 3){
        exit(-11);
    }

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        int32_t val32b = static_cast<int32_t> (executable[(mem_loc - 0x10000000)]);
        int16_t val = static_cast<int16_t> (val32b >> (8 * (2 - byte_num)));
        reg[rtmp] = static_cast<int32_t> (val);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        int32_t val32b = static_cast<int32_t> (read_write[(mem_loc - 0x20000000)]);
        int16_t val = static_cast<int16_t> ( val32b >> (8 * (2 - byte_num)));
        reg[rtmp] = static_cast<int32_t> (val);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        int16_t tmp_t = static_cast<int16_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else {
        exit(-11);
    }
}

void Memory::LHU(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    if (byte_num == 1 || byte_num == 3){
        exit(-11);
    }

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        uint32_t val32b = static_cast<uint32_t> (executable[(mem_loc - 0x10000000)]);
        uint16_t val = static_cast<uint16_t> (val32b >> (8 * (2 - byte_num)));
        int16_t tmp_t = static_cast<int16_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        uint32_t val32b = static_cast<uint32_t> (read_write[(mem_loc - 0x20000000)]);
        uint16_t val = static_cast<uint16_t> ( val32b >> (8 * (2 - byte_num)));
        int16_t tmp_t = static_cast<int16_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        uint16_t tmp_t = static_cast<uint16_t> (val);
        uint32_t newval = static_cast<uint32_t> (tmp_t);
        reg[rtmp] = static_cast<int32_t> (newval);
    }
    else {
        exit(-11);
    }
}

void Memory::LUI(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    uint16_t tmp = static_cast<uint16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
 
    if (rsource != 0){
        exit(-11);
    }
    reg[rtmp] = immediate << 16;
}

void Memory::LW(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    if (byte_num != 0){
        exit(-11);
    }

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        reg[rtmp] = (executable[(mem_loc - 0x10000000)]);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        reg[rtmp] = (read_write[(mem_loc - 0x20000000)]);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        int16_t tmp_t = static_cast<int16_t> (val);
        reg[rtmp] = static_cast<int32_t> (tmp_t);
    }
    else {
        exit(-11);
    }
}

void Memory::LWR(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    uint32_t data;

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        data = static_cast<uint32_t> (executable[(mem_loc - 0x10000000)]);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        data = static_cast<uint32_t> (read_write[(mem_loc - 0x20000000)]);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        uint8_t valtmp = static_cast<uint8_t> (val);
        data = static_cast<uint32_t> (valtmp);
    }
    else {
        exit(-11);
    }

    if (byte_num == 0){
        reg[rtmp] = reg[rtmp] & 0xFFFFFF00;
        reg[rtmp] = reg[rtmp] | (data >> 24);
    }
    else if (byte_num == 1){
        reg[rtmp] = reg[rtmp] & 0xFFFF0000;
        reg[rtmp] = reg[rtmp] | (data >> 16);
    }
    else if (byte_num == 2){
        reg[rtmp] = reg[rtmp] & 0xFF000000;
        reg[rtmp] = reg[rtmp] | (data >> 8);
    }
    else {
        reg[rtmp] = data;
    }

}
void Memory::LWL(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    uint32_t data;

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        data = static_cast<uint32_t> (executable[(mem_loc - 0x10000000)]);
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        data = static_cast<uint32_t> (read_write[(mem_loc - 0x20000000)]);
    }
    else if (mem_loc >= 0x30000000 && mem_loc < 0x30000004){
        char val = getchar();
        uint8_t valtmp = static_cast<uint8_t> (val);
        data = static_cast<uint32_t> (valtmp);
    }
    else {
        exit(-11);
    }

    if (byte_num == 0){
        reg[rtmp] = data;
    }
    else if (byte_num == 1){
        reg[rtmp] = reg[rtmp] & 0xFF;
        reg[rtmp] = reg[rtmp] | (data << 8);
    }
    else if (byte_num == 2){
        reg[rtmp] = reg[rtmp] & 0xFFFF;
        reg[rtmp] = reg[rtmp] | (data << 16);
    }
    else {
        reg[rtmp] = reg[rtmp] & 0xFFFFFF;
        reg[rtmp] = reg[rtmp] | (data << 24);
    }

}

void Memory::ORI(int32_t x){
    pc += 4;

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] | immediate);
}

void Memory::SB(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    uint32_t data = (reg[rtmp] & 0xFF);

    if (byte_num == 0){
        data = data << 24;
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFFFFFF);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFFFFFF);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }
    else if (byte_num == 1){
        data = data << 16;
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFF00FFFF);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFF00FFFF);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }
    else if (byte_num == 2){
        data = data << 8;
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFFFF00FF);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFFFF00FF);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }
    else {
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFFFFFF00);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFFFFFF00);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }


}

void Memory::SH(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    uint32_t data = (reg[rtmp] & 0xFFFF);

    if (byte_num == 1 || byte_num == 3){exit(-11);}

    else if (byte_num == 0){
        data = data << 16;
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFFFF);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFFFF);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }
    
    if (byte_num == 2){
        if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] & 0xFFFF0000);
            executable[(mem_loc - 0x11000000)] = (executable[(mem_loc - 0x11000000)] | data);
        }
        else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] & 0xFFFF0000);
            read_write[(mem_loc - 0x20000000)] = (read_write[(mem_loc - 0x20000000)] | data);
        }
        else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
            putchar(reg[rtmp] & 0xFF);
        }
        else {exit(-11);}
    }
}

void Memory::SLTI(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    (reg[rsource] < immediate) ? (reg[rtmp] = 1) : (reg[rtmp] = 0);
}

void Memory::SLTIU(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    uint32_t imm = static_cast<uint32_t> (immediate);
    uint32_t src = static_cast<uint32_t> (reg[rsource]);

    (src < imm) ? (reg[rtmp] = 1) : (reg[rtmp] = 0);
}

void Memory::SW(int32_t x){
    pc += 4;
    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    int32_t mem_loc = (reg[rsource] + immediate) / 4;
    int32_t byte_num = (reg[rsource] + immediate) % 4;

    if (byte_num != 0){exit(-11);}

    if (mem_loc >= 0x10000000 && mem_loc < 0x11000000){
        executable[(mem_loc - 0x11000000)] = reg[rtmp];
    }
    else if (mem_loc >= 0x20000000 && mem_loc < 0x24000000){
        read_write[(mem_loc - 0x20000000)] = reg[rtmp];
    }
    else if (mem_loc >= 0x30000004 && mem_loc < 0x30000008){
        putchar(reg[rtmp] & 0xFF);
    }
    else {exit(-11);}
}

void Memory::XORI(int32_t x){
    pc += 4;

    int32_t rsource = (x & 0x3E00000) >> 21;
    int32_t rtmp = (x & 0x1F0000) >> 16;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] ^ immediate);
}