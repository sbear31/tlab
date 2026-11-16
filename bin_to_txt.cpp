#include <iostream>
#include<fstream>
#include <cstdint>

struct Fail_Student{
    uint8_t group{};
    uint32_t srb{};
    char surename[20]{};
};

void ifcheck(std::ifstream& ff){
    if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF) throw "file is empty\n"; 
}

void ofcheck(std::ofstream& ff){
    if(!ff) throw "file open error";
}

void bin_to_txt(std::ifstream& ff, std::string out_ad){
    std::ofstream out(out_ad+".txt", std::ios::out | std::ios::trunc);
    try{
        ofcheck(out);
        ff.seekg(0,std::ios::end);
        long long size = ff.tellg();
        ff.seekg(0, std::ios::beg);
        if(size%sizeof(Fail_Student)) throw "before fail";
        uint32_t k = size/sizeof(Fail_Student);
        Fail_Student temp{};
        uint32_t i{};
        while(i < k && ff.read(reinterpret_cast<char*>(&temp),sizeof(Fail_Student))){
            temp.surename[18] = '\0';
            out << static_cast<int>(temp.group) << ";" << static_cast<int>(temp.srb) << ";" << temp.surename << '\n'; 
            ++i;  
        }
        if (i != k) throw "break file";
    }catch(const char* error){
        std::cout << error << '\n';
    }
}

int main(){
    std::ifstream fail("adres.bin", std::ios::in | std::ios::binary);
    try {
        ifcheck(fail);
        bin_to_txt(fail, "fail_sort");
    }catch (const char* error){
        std::cout << error << '\n';
    }
    return 0;
}