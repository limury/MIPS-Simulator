#ifndef MEMORY
#define MEMORY

#include "includes.h"

enum Errors { RESULT_OVERFLOW = 0, SHIFT_OVERFLOW = 1, MEMFAIL = 2 };
class Memory{
    public:
        Memory(const vector<unsigned int>& input);
        void run();
    
    private:
        vector<unsigned int> reg{32, 0};
        unsigned int pc;
        vector<unsigned int> executable{0x1000000, 0};
        vector<unsigned int> read_write{0x4000000, 0};

};

#endif //MEMORY