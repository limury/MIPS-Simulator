#include "includes.h"
#include "Memory.h"

#include <bitset>


int main(int argc, char* argv[]){

    string filename = argv[1];
    ifstream infile(filename, ios::binary); 

    if (!infile.is_open()){
        exit(0);
    }

    streampos file_size;
    infile.seekg(0, ios::end);
    file_size = infile.tellg();
    infile.seekg(0, ios::beg);


    // reading file size 

    vector<uint8_t> bin_in(file_size);

    infile.read((char*) &bin_in[0], file_size);

    // reading binary into instrmem

    // cout << "size of instrmem: " << bin_in.size() << endl;

    for (int i = 0; i < bin_in.size(); i++){
        cout << bitset<8> (bin_in[i]) << endl;
        cout << bin_in[i];
    }

    Memory memory(bin_in);
    memory.run();
    

    return 0;
}

