#include<iostream>
#include<fstream>
#include<cstdint>

void ifcheck(std::ifstream& ff){
    if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF) throw "file is empty\n"; 
}

void ofcheck(std::ofstream& ff){
    if(!ff) throw "file open error";
}

void fail_create(std::ifstream& ff,std::string fail_ad){
    std::ofstream fail_b(fail_ad, std::ios::out | std::ios::binary | std::ios::trunc);
    try {
        ofcheck(fail_b);
        char temp[56]{};
        while(ff.read(temp, 56)){
            if (temp[36] < 4 || temp[45] < 4 || temp[54] < 4 ){
                temp[26] = '\0';
                fail_b.write(reinterpret_cast<char*>(&temp), 28);
            }
        }
    } catch(const char*& error){
        std::cout << error;
    }
}

int main(){
    setlocale(LC_ALL, ".1251");
    std::string mark_bin_ad{"premium_mark"};
    std::ifstream m_bin(mark_bin_ad+".bin", std::ios::in | std::ios::binary);
    try{
        ifcheck(m_bin);
        fail_create(m_bin,"fail.bin");
    } catch (const char*& error){
        std::cout << error << '\n';
    }
    return 0;
}