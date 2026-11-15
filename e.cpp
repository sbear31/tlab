#include<iostream>
#include<fstream>
#include<cstdint>
#include <cstring>
#include <algorithm>

struct Fail_Student{
    uint8_t group{};
    uint32_t srb{};
    char surename[20]{};
};

void ifcheck(std::ifstream& ff){
    if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF){
        ff.clear();
        throw "file is empty\n";
    }  
}

void ofcheck(std::ofstream& ff){
    if(!ff) throw "file open error";
}


bool fail_comp(const Fail_Student& a,const Fail_Student& b){
    if (a.group != b.group) return a.group > b.group;
    int c = strcmp(a.surename,b.surename);
    if (c != 0){
        return c > 0;
    }
    return a.srb > b.srb;
}

template <typename T>
void heapify(T*arr, int top, int size, bool(*comp)(const T& a,const T& b)){
    int l = top*2 + 1;
    int r  = top*2 + 2;
    int max = top;
    if (r < size && comp(arr[r],arr[max])) max = r ;
    if ( l < size && comp(arr[l],arr[max])) max = l;
    if (max != top){
        std::swap(arr[max], arr[top]);
        heapify(arr,max,size,comp);
    }
}
template <typename T>
void tree_sort(T*arr, int size, bool(*comp)(const T& a,const T& b)){
    for(int i = size / 2 - 1; i >=0; --i){
        heapify(arr,i,size,comp);
    }
    for(int j = size - 1 ; j > 0;--j){
        std::swap(arr[0],arr[j]);
        heapify(arr,0,j,comp);
    }
}

void fail_sort_create(std::ifstream& ff,std::string f_s_ad){
    std::ofstream ff_s_b(f_s_ad, std::ios::out | std::ios::binary | std::ios::trunc);
    try{
        ofcheck(ff_s_b);
        ff.seekg(0,std::ios::end);
        long long size = ff.tellg();
        ff.seekg(0, std::ios::beg);
        if(size%sizeof(Fail_Student)) throw "before fail";
        uint32_t k = size/sizeof(Fail_Student);
        
        Fail_Student* arr = new Fail_Student[k]{};
        uint32_t i{};
        while(i < k && ff.read(reinterpret_cast<char*>(&arr[i]), sizeof(Fail_Student))){
            ++i;
        }
        if (i != k){
            delete[] arr;
            arr = nullptr;
            throw "break read file";
        } 
        tree_sort(arr,k,fail_comp);
        i = 0;
        while ( i < k  && ff_s_b.write(reinterpret_cast<char*>(&arr[i]), sizeof(Fail_Student))){
            ++i;
        }
        ff_s_b.close();
        if(i != k || !ff_s_b) {
            delete[] arr;
            arr = nullptr;
            throw "break write file";
        }
        delete[] arr;
        arr = nullptr;
    }catch (const char* error){
        std::cout << error << '\n';
    }
}

int main(){
    setlocale(LC_ALL, ".1251");
    std::ifstream m_bin("fail.bin", std::ios::in | std::ios::binary);
    try{
        ifcheck(m_bin);
        fail_sort_create(m_bin,"fail_sort.bin");
    } catch (const char* error){
        std::cout << error << '\n';
    }
    return 0;
}