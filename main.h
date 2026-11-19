#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "struct.h"
#include<algorithm>


void check_digits(const std::string& str);
void string_to_masschar(char* str_c, uint16_t N, const std::string& str_s);
void txt_to_binary_st_d(std::ifstream& file, std::ofstream& bin);
void txt_to_binary_st_m(std::ifstream& file, std::ofstream& bin);
void add_surname_to_st_m(std::ifstream& bin_st_d, std::ifstream& bin_st_m, std::ofstream& bin_prem_st_m);
void average_to_bin(std::ifstream& bin_prem_st_m, std::ofstream& bin_avg);

void swap_structs(std::fstream& file, uint32_t i, uint32_t j, uint16_t size_struct);
bool compar1(char* a, char* b);
void sort_reports_groups_alf(std::fstream& file, uint32_t size, uint16_t size_struct);
void create_reports_groups_alf(uint8_t group, const std::string& name,const std::string& ad);
bool compar2(float a, float b);
void sort_reports_groups_points(std::fstream& file, uint32_t size, uint16_t size_struct);
void create_reports_groups_points(uint8_t group, const std::string& name,const std::string& ad);
bool check_stex(const Prem_St_M& stud);
void rewrite_struct(const Prem_St_M& stud, St_Ex& newstud);
void create_reports_exstud(const std::string& name);

void ifcheck(std::ifstream& ff);
void ofcheck(std::ofstream& ff);
void fail_create(std::ifstream& ff,std::string fail_ad);
bool fail_comp(const St_Ex& a,const St_Ex& b);
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
void fail_sort_create(std::ifstream& ff,std::string f_s_ad);
void bin_to_txt(std::ifstream& ff, std::string out_ad);

void fchecki(std::fstream& ff);
void fchecko(std::fstream& ff);
