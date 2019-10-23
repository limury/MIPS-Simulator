#ifndef MEMORY
#define MEMORY

#include "includes.h"


class Memory{
    public:
        Memory(const vector<const unsigned int>& input);
    
    private:
        vector<unsigned int> reg{32, 0};
        unsigned int pc;
        vector<const unsigned int> executable{0x1000000, 0};
        vector<unsigned int> read_write{0x4000000, 0};

};
Memory::Memory(const vector<const unsigned int>& input): executable(input), pc(0){}


#endif //MEMORY