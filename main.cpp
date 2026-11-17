#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include<struct.h>
#include<main.h>

template <size_t N>
void string_to_masschar(char(&str_c)[N], const std::string& str_s) {
	for (std::size_t i = 0; i < N; ++i)
		str_c[i] = '\0';

	std::size_t len;
	if (str_s.size() < N - 1)
		len = str_s.size();
	else
		len = N - 1;

	for (std::size_t i = 0; i < len; ++i)
		str_c[i] = str_s[i];

	str_c[N - 1] = '\0';
}
void check_digits(const std::string& str) {
	if (str.empty()) {
		throw "empty code";
	}	
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] < '0' || str[i] > '9') {
			throw "code is not a number";
		}
	}	
}

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

bool check_stex(const Prem_St_M& stud) {
    if (stud.m_sub_1 < 8) return false;
    if (stud.m_sub_2 < 8) return false;
    if (stud.m_sub_3 < 8) return false;
    return true;
}

void rewrite_struct(const Prem_St_M& stud, St_Ex& newstud) {
    newstud.group = stud.group;
    newstud.srb = stud.srb;
    strcpy(newstud.surename, stud.surname);
}

void sort_reports_groups_alf(std::fstream& file, uint32_t size, uint16_t size_struct) {
    if (!file) { throw "input file error\n"; }
    char a[20] = {};
    char b[20] = {};
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(Prem_St_M, surname), std::ios::beg);
            file.read(reinterpret_cast<char*>(a), 20);
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(Prem_St_M, surname), std::ios::beg);
            file.read(reinterpret_cast<char*>(b), 20);
            if (compar1(a, b)) {
                swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}
void create_reports_groups_alf(uint8_t group, const std::string& name) {//принимает группу и файл с Prem_st_m
    const uint16_t size_struct = sizeof(Prem_St_M);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("Reports_groups_alf.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint16_t temp, j = 0;
    Prem_St_M stud;
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

void sort_reports_groups_points(std::fstream& file, uint32_t size, uint16_t size_struct) {
    if (!file) { throw "input file error\n"; }
    float a{}, b{};
    bool puls = true;
    for (uint32_t i = 0; puls; ++i) {
        puls = false;
        for (uint32_t j = 0; j < size - i - 1; ++j) {
            file.seekg(j * size_struct + offsetof(St_Av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&a), sizeof(float));
            if (!file) { throw "read file error\n"; }
            file.seekg((j + 1) * size_struct + offsetof(St_Av, average), std::ios::beg);
            file.read(reinterpret_cast<char*>(&b), sizeof(float));
            if (compar2(a, b)) {
                swap_structs(file, j, j + 1, size_struct);
                puls = true;
            }
        }
    }
}

void create_reports_groups_points(uint8_t group, const std::string& name) {//принимает группу и файл St_av
    const uint16_t size_struct = sizeof(St_Av);
    std::ifstream file(name, std::ios::binary);
    std::fstream newfile("Reports_groups_points.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    uint16_t temp, j = 0;
    St_Av stud;
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