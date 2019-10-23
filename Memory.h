#ifndef MEMORY
#define MEMORY

#include "includes.h"


class Memory{
    public:
        
    
    private:
        vector<unsigned int> reg[32];
        unsigned int PC;
        const vector<unsigned int> executable[0x1000000];
        vector<unsigned int> read_write[0x4000000];

};



#endif //MEMORY