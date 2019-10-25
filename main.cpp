#include "includes.h"
#include "memory.h"

vector<int32_t> init(){
    ifstream file;
    file.open("test.bin");

    vector<int32_t> vec;
    string tmp;
    int32_t val;

    if(file.is_open()){
        while(!file.eof()){
            file >> tmp;
            vec.push_back(val);
        }
    }
    cout << vec[0] << endl;
    file.close();
    vec.resize(0x1000000);
    return vec;
}


int main(int argc, char* argv[]){
    
    vector<int32_t> vec = init();

    for (int i = 0; i < vec.size(); i++){
        cout << vec[i];
    }
    return 0;
}