#include "Memory.h"

void Memory::ADDI(int32_t x){
    pc += 4;

    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
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

    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] + immediate);
}

void Memory::ANDI(int32_t x){
    pc += 4;

    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] & immediate);
}

void Memory::BEQ(int32_t x){

    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (reg[rsource] == reg[rtmp]){
        pc += (immediate << 2);
    }
}

void Memory::BGEZ(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 1){
        exit(-12);
    }

    if (reg[rsource] >= 0){
        pc += (immediate << 2);
    }
}

void Memory::BGEZAL(int32_t x){

    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0b10001){
        exit(-12);
    }

    if (reg[rsource] >= 0){
        reg[31] = pc + 4;
        pc += (immediate << 2);
    }
    else {
        pc += 4;
    }
}

void Memory::BGTZ(int32_t x){

    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] > 0){
        pc += (immediate << 2);

    }

}
void Memory::BLEZ(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] <= 0){
        pc += (immediate << 2);
    }
}
void Memory::BLTZ(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] < 0){
        pc += (immediate << 2);

    }
}
void Memory::BLTZAL(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (rtmp != 0x0){
        exit(-12);
    }

    if (reg[rsource] < 0){
        reg[31] = pc + 4;
        pc += (immediate << 2);
    }
}
void Memory::BNE(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    if (reg[rsource] != reg[rtmp]){
        pc += (immediate << 2);
    }
}

void Memory::LB(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    int32_t mem_loc = (reg[rsource] + immediate);

    int8_t tmp = static_cast<int8_t> (this->read(mem_loc));
    reg[rtmp] = static_cast<int32_t> (tmp);
}

void Memory::LBU(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    int32_t mem_loc = (reg[rsource] + immediate);

    uint32_t tmp = static_cast<uint32_t> (this->read(mem_loc));
    reg[rtmp] = static_cast<int32_t> (tmp);
}

void Memory::LH(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate);
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (byte_num == 1 || byte_num == 3){ exit(-11); }

    uint16_t MSB = static_cast<uint16_t> (this->read(mem_loc));
    uint16_t LSB = static_cast<uint16_t> (this->read(mem_loc + 1));
    uint16_t var = (MSB << 8) | LSB;
    int16_t out = static_cast<int16_t> (var);
    reg[rtmp] = static_cast<int32_t> (out);
}

void Memory::LHU(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate);
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (byte_num == 1 || byte_num == 3){ exit(-11); }

    uint16_t MSB = static_cast<uint16_t> (this->read(mem_loc));
    uint16_t LSB = static_cast<uint16_t> (this->read(mem_loc + 1));
    uint16_t var = (MSB << 8) | LSB;
    uint32_t out = static_cast<uint32_t> (var);
    reg[rtmp] = static_cast<int32_t> (out);
}

void Memory::LUI(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    uint16_t tmp = static_cast<uint16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
 
    if (rsource != 0){
        exit(-11);
    }
    reg[rtmp] = immediate << 16;
}

void Memory::LW(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate);
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (byte_num != 0){ exit(-11); }

    uint32_t MSB = static_cast<uint32_t> (this->read(mem_loc));
    uint32_t MSB1 = static_cast<uint32_t> (this->read(mem_loc + 1));
    uint32_t LSB1 = static_cast<uint32_t> (this->read(mem_loc + 2));
    uint32_t LSB = static_cast<uint32_t> (this->read(mem_loc + 3));

    uint32_t out = (MSB << 24) | (MSB1 << 16) | (LSB1 << 8) | (LSB);
    reg[rtmp] = static_cast<int32_t> (out);
}

void Memory::LWR(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    int32_t mem_loc = (reg[rsource] + immediate) - byte_num;

    uint32_t MSB = static_cast<uint32_t> (this->read(mem_loc));
    uint32_t MSB1 = static_cast<uint32_t> (this->read(mem_loc + 1));
    uint32_t LSB1 = static_cast<uint32_t> (this->read(mem_loc + 2));
    uint32_t LSB = static_cast<uint32_t> (this->read(mem_loc + 3));

    uint32_t data_t = (MSB << 24) | (MSB1 << 16) | (LSB1 << 8) | (LSB);
    int32_t data = static_cast<int32_t> (data_t);

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
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    int32_t mem_loc = (reg[rsource] + immediate) - byte_num;
    

    uint32_t MSB = static_cast<uint32_t> (this->read(mem_loc));
    uint32_t MSB1 = static_cast<uint32_t> (this->read(mem_loc + 1));
    uint32_t LSB1 = static_cast<uint32_t> (this->read(mem_loc + 2));
    uint32_t LSB = static_cast<uint32_t> (this->read(mem_loc + 3));

    uint32_t data_t = (MSB << 24) | (MSB1 << 16) | (LSB1 << 8) | (LSB);
    int32_t data = static_cast<int32_t> (data_t);

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

    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] | immediate);
}

void Memory::SB(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate);

    uint32_t data_t = static_cast<uint32_t> (reg[rtmp] & 0xFF);
    uint8_t data = static_cast<uint8_t> (data_t);

    this->write(mem_loc, data);
}

void Memory::SH(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    int32_t mem_loc = (reg[rsource] + immediate);
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (byte_num == 1 || byte_num == 3){ exit(-11); }
    
    uint32_t data_t = (reg[rtmp] & 0xFFFF);
    uint8_t LSB = static_cast<uint8_t> (data_t);
    uint8_t MSB = static_cast<uint8_t> (data_t >> 8);

    this->write(mem_loc, MSB);
    this->write(mem_loc + 1, LSB);
}

void Memory::SLTI(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);

    (reg[rsource] < immediate) ? (reg[rtmp] = 1) : (reg[rtmp] = 0);
}

void Memory::SLTIU(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    uint32_t imm = static_cast<uint32_t> (immediate);
    uint32_t src = static_cast<uint32_t> (reg[rsource]);

    (src < imm) ? (reg[rtmp] = 1) : (reg[rtmp] = 0);
}

void Memory::SW(int32_t x){
    pc += 4;
    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    int16_t tmp = static_cast<int16_t> (x);
    int32_t immediate = static_cast<int32_t> (tmp);
    
    int32_t mem_loc = (reg[rsource] + immediate);
    int32_t byte_num = (reg[rsource] + immediate) % 4;
    if (byte_num != 0){ exit(-11); }
    uint32_t data_t = static_cast<uint32_t> (reg[rtmp]);

    uint8_t MSB = static_cast<uint8_t> (data_t >> 24);
    uint8_t MSB1 = static_cast<uint8_t> (data_t >> 16);
    uint8_t LSB1 = static_cast<uint8_t> (data_t >> 8);
    uint8_t LSB = static_cast<uint8_t> (data_t);

    this->write(mem_loc, MSB);
    this->write(mem_loc + 1, MSB1);
    this->write(mem_loc + 2, LSB1);
    this->write(mem_loc + 3, LSB);
}

void Memory::XORI(int32_t x){
    pc += 4;

    int32_t rsource = (x >> 21) & 0x1F;
    int32_t rtmp = (x >> 16) & 0x1F;
    uint16_t tmp = static_cast<uint16_t> (x);
    uint32_t immediate = static_cast<uint32_t> (tmp);

    // place result in register
    reg[rtmp] = (reg[rsource] ^ immediate);
}