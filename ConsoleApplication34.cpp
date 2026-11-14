#include <iostream>
#include <fstream>
#include <string>

//g) формирования ведомости оценок для заданной группы, упорядоченной по алфавиту;
struct prem_st_m {
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
void Swap_structs(std::fstream& file, uint32_t i, uint32_t j, uint32_t size) {
    if (i == j) return;
    char* a = new char[size];
    char* b = new char[size];
    file.seekg(i * size, std::ios::beg);
    file.read(reinterpret_cast<char*>(a), size);
    if (!file) throw "read file error\n";
    file.seekg(j * size, std::ios::beg);
    file.read(reinterpret_cast<char*>(b), size);
    if (!file) { throw "input file error\n"; }
    file.seekp(i * size, std::ios::beg);
    file.write(reinterpret_cast<const char*>(b), size);
    file.seekp(j * size, std::ios::beg);
    file.write(reinterpret_cast<const char*>(a), size);
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
void Sort1(std::fstream& file, uint32_t size, uint32_t size_struct) {
    if (!file) { throw "input file error\n"; }
    char a[20] = {};
    char b[20] = {};
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(prem_st_m, surename), std::ios::beg);
            file.read(reinterpret_cast<char*>(a), 20);
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(prem_st_m, surename), std::ios::beg);
            file.read(reinterpret_cast<char*>(b), 20);
            if (compar1(a, b)) {
                Swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}
void Create_reports_groups_alf(uint8_t group, const std::string& name) {
    const uint16_t size_struct = sizeof(prem_st_m);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("reports_groups_alf.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint8_t temp, j = 0;
    prem_st_m stud;
    file.seekg(0, std::ios::end);        
    std::streamsize size_report = file.tellg();
    file.seekg(0, std::ios::beg);
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        temp = file.peek();
        if (temp == group) {
            file.read(reinterpret_cast<char*>(&stud), size_struct);
            newfile.write(reinterpret_cast<const char*>(&stud), size_struct);
            ++j;
        }
    }
    newfile.seekp(0, std::ios::beg);
    Sort1(newfile, j, size_struct);
    file.close();
    newfile.close();
}

//h) формирования ведомости оценок для заданной группы, упорядоченной по убыванию среднего балла;   
struct st_av {
    uint8_t group;
    uint32_t srb;
    char surename[20];
    float average;
};
bool compar2(float a, float b) {
    if (a < b) return true;
    return false;
}
void Sort2(std::fstream& file, uint32_t size, uint32_t size_struct) {
    if (!file) { throw "input file error\n"; }
    float a, b;
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(st_av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&a), sizeof(float));
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(st_av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&b), sizeof(float));
            if (compar2(a, b)) {
                Swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}
void Create_reports_groups_points(uint8_t group, const std::string& name) {
    const uint16_t size_struct = sizeof(st_av);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("reports_groups_points.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint16_t temp, j = 0;
    st_av stud;
    file.seekg(0, std::ios::end);
    std::streamsize size_report = file.tellg(); 
    file.seekg(0, std::ios::beg);
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        temp = file.peek();
        if (temp == group) {
            file.read(reinterpret_cast<char*>(&stud), size_struct);
            newfile.write(reinterpret_cast<const char*>(&stud), size_struct);
            ++j;
        }
    }
    newfile.seekp(0, std::ios::beg);
    Sort2(newfile, j, size_struct);
    file.close();
    newfile.close();
}

int main() {   
    try {
        setlocale(LC_ALL, ".1251");
        Create_reports_groups_points(4, "file_second.bin");

    }
    catch (const char* error) {
        std::cout << error;
    }

    return 0;
}