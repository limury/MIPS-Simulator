#include "includes.h"
#include "memory.h"
vector<unsigned int> init(){
    ifstream file;
    file.open("test.bin");

    vector<unsigned int> vec;
    unsigned int val;

    if(file.is_open()){
        while(!file.eof()){
            file >> val;
            vec.push_back(val);
        }
    }
    file.close();
    vec.resize(0x1000000);
    return vec;
}
int main(int argc, char* argv[]){
    vector<unsigned int> vec = init();
    
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i];
    }
    return 0;
}