#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstddef>
#include <cstdint>

//g) формирования ведомости оценок для заданной группы, упорядоченной по алфавиту;
struct Prem_st_m {
    uint8_t group;
    uint32_t srb;
    char surename[20];
    char sub_1[8];
    uint8_t m_sub_1;
    char sub_2[8];
    uint8_t m_sub_2;
    char sub_3[8];
    uint8_t m_sub_3;
};
void swap_structs(std::fstream& file, uint32_t i, uint32_t j, uint16_t size_struct) {
    if (i == j) return;
    char* a = new char[size_struct];
    char* b = new char[size_struct];
    file.seekg(i * size_struct, std::ios::beg);
    file.read(reinterpret_cast<char*>(a), size_struct);
    if (!file) throw "read file error\n";
    file.seekg(j * size_struct, std::ios::beg);
    file.read(reinterpret_cast<char*>(b), size_struct);
    if (!file) { throw "input file error\n"; }
    file.seekp(i * size_struct, std::ios::beg);
    file.write(reinterpret_cast<const char*>(b), size_struct);
    file.seekp(j * size_struct, std::ios::beg);
    file.write(reinterpret_cast<const char*>(a), size_struct);
    delete[] a;
    delete[] b;
}
bool compar1(char* a, char* b) {
    int i = 0;
    for (; a[i] != '\0' || b[i] != '\0'; ++i) if (a[i] > b[i]) return true;
    if (a[i] != '\0') return true;
    else if (b[i] != '\0') return true;
    return false;
}
void sort_reports_groups_alf(std::fstream& file, uint32_t size, uint16_t size_struct) {
    if (!file) { throw "input file error\n"; }
    char a[20] = {};
    char b[20] = {};
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(Prem_st_m, surename), std::ios::beg);
            file.read(reinterpret_cast<char*>(a), 20);
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(Prem_st_m, surename), std::ios::beg);
            file.read(reinterpret_cast<char*>(b), 20);
            if (compar1(a, b)) {
                swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}
void create_reports_groups_alf(uint8_t group, const std::string& name) {//принимает группу и файл с Prem_st_m
    const uint16_t size_struct = sizeof(Prem_st_m);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("Reports_groups_alf.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint16_t temp, j = 0;
    Prem_st_m stud;
    file.seekg(0, std::ios::end);        
    std::streamsize size_report = file.tellg();
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        temp = file.peek();
        if (temp == group) {
            file.read(reinterpret_cast<char*>(&stud), size_struct);
            newfile.write(reinterpret_cast<const char*>(&stud), size_struct);
            ++j;
        }
    }
    newfile.seekg(0, std::ios::beg);
    newfile.seekp(0, std::ios::beg);
    sort_reports_groups_alf(newfile, j, size_struct);
    file.close();
    newfile.close();
}
//h) формирования ведомости оценок для заданной группы, упорядоченной по убыванию среднего балла;   
struct St_av {
    uint8_t group;
    uint32_t srb;
    char surename[20];
    float average;
};
bool compar2(float a, float b) {
    if (a < b) return true;
    return false;
}
void sort_reports_groups_points(std::fstream& file, uint32_t size, uint16_t size_struct) {
    if (!file) { throw "input file error\n"; }
    float a{}, b{};
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(St_av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&a), sizeof(float));
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(St_av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&b), sizeof(float));
            if (compar2(a, b)) {
                swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}
void create_reports_groups_points(uint8_t group, const std::string& name) {//принимает группу и файл St_av
    const uint16_t size_struct = sizeof(St_av);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("Reports_groups_points.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint16_t temp, j = 0;
    St_av stud;
    file.seekg(0, std::ios::end);
    std::streamsize size_report = file.tellg(); 
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        temp = file.peek();
        if (temp == group) {
            file.read(reinterpret_cast<char*>(&stud), size_struct);
            newfile.write(reinterpret_cast<const char*>(&stud), size_struct);
            ++j;
        }
    }
    newfile.seekg(0, std::ios::beg);
    newfile.seekp(0, std::ios::beg);
    sort_reports_groups_points(newfile, j, size_struct);
    file.close();
    newfile.close();
}
//i) формирования списка отличников, состоящего из фамилии, номера группы, номера зачетки;
struct St_ex {
    uint8_t group;
    uint32_t srb;
    char surename[20];
};
bool check_stex(const Prem_st_m& stud) {
    if (stud.m_sub_1 < 8) return false;
    if (stud.m_sub_2 < 8) return false;
    if (stud.m_sub_3 < 8) return false;
    return true;
}
void rewrite_struct(const Prem_st_m& stud, St_ex& newstud) {
    newstud.group = stud.group;
    newstud.srb = stud.srb;
    strcpy(newstud.surename, stud.surename);
}
void create_reports_exstud(const std::string& name) {//принимает файл с Prem_st_m
    const uint16_t size_struct = sizeof(Prem_st_m);
    std::ifstream file(name, std::ios::binary);
    std::ofstream newfile("Reports_groups_exstud.bin", std::ios::binary | std::ios::trunc);
    Prem_st_m stud;
    file.seekg(0, std::ios::end);
    std::streamsize size_report = file.tellg();
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        file.read(reinterpret_cast<char*>(&stud), size_struct);
        if (check_stex(stud)) {
            St_ex newstud;
            rewrite_struct(stud, newstud);
            newfile.write(reinterpret_cast<const char*>(&newstud), sizeof(St_ex));
        }
    }
    file.close();
    newfile.close();
}

int main() {   
    try {
        create_reports_exstud("file.bin");

    }
    catch (const char* error) {
        std::cout << error;
    }
    return 0;
}