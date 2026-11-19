#pragma once
#include<iostream>
#include<cstdint>
#include <fstream>
#include <string>
#include"main.h"
#include "struct.h"

void txt_to_binary_st_d(std::ifstream& file, std::ofstream& bin) {
	std::string line{};
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		if (line.empty()) continue;
		size_t pos[3];
		size_t beg = 0, k = 0;
		for (; k < 3; ++k) {
			pos[k] = line.find(';', beg);
			if (pos[k] == std::string::npos) {
				break;
			}
			beg = pos[k] + 1;
		}
		if (k != 3 || line.find(';', beg) != std::string::npos) {
			throw "bad line'\n";
		}
		St_D student{};
			check_digits(line.substr(0, pos[0]));
			student.srb = static_cast<uint32_t>(std::stoul(line.substr(0, pos[0])));
			string_to_masschar(student.surname,20, line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
			string_to_masschar(student.name,20, line.substr(pos[1] + 1, pos[2] - pos[1] - 1));
			string_to_masschar(student.lastname,20, line.substr(pos[2] + 1));

		bin.write(reinterpret_cast<const char*>(&student), sizeof(St_D));
	}
}
void txt_to_binary_st_m(std::ifstream& file, std::ofstream& bin) { 
	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		if (line.empty()) continue;

		size_t pos[7];
		size_t beg = 0, k = 0;
		for (; k < 7; ++k) {
			pos[k] = line.find(';', beg);
			if (pos[k] == std::string::npos) {
				break;
			}
			beg = pos[k] + 1;
		}
		if (k != 7 || line.find(';', beg) != std::string::npos) {
			std::cout << "bad line: " << line << "\n";
			continue;
		}
		St_M marks{};
		try {
			check_digits(line.substr(0, pos[0]));
			marks.group = static_cast<uint8_t>(std::stoul(line.substr(0, pos[0])));
			check_digits(line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
			marks.srb = static_cast<uint32_t>(std::stoul(line.substr(pos[0] + 1, pos[1] - pos[0] - 1)));
			string_to_masschar(marks.sub_1,8, line.substr(pos[1] + 1, pos[2] - pos[1] - 1));
			check_digits(line.substr(pos[2] + 1, pos[3] - pos[2] - 1));
			marks.m_sub_1 = static_cast<uint8_t>(std::stoul(line.substr(pos[2] + 1, pos[3] - pos[2] - 1)));
			string_to_masschar(marks.sub_2,8, line.substr(pos[3] + 1, pos[4] - pos[3] - 1));
			check_digits(line.substr(pos[4] + 1, pos[5] - pos[4] - 1));
			marks.m_sub_2 = static_cast<uint8_t>(std::stoul(line.substr(pos[4] + 1, pos[5] - pos[4] - 1)));
			string_to_masschar(marks.sub_3,8, line.substr(pos[5] + 1, pos[6] - pos[5] - 1));
			check_digits(line.substr(pos[6] + 1));
			marks.m_sub_3 = static_cast<uint8_t>(std::stoul(line.substr(pos[6] + 1)));
		}
		catch (const char* message) {
			std::cout << message;
			continue;
		}
		bin.write(reinterpret_cast<const char*>(&marks), sizeof(St_M));
	}
}
void add_surname_to_st_m(std::ifstream& bin_st_d, std::ifstream& bin_st_m, std::ofstream& bin_prem_st_m) {
	St_M marks;
	while (bin_st_m.read(reinterpret_cast<char*>(&marks), sizeof(St_M))) {

		Prem_St_M prem_marks{};
		prem_marks.group = marks.group;
		prem_marks.srb = marks.srb;
		prem_marks.m_sub_1 = marks.m_sub_1;
		prem_marks.m_sub_2 = marks.m_sub_2;
		prem_marks.m_sub_3 = marks.m_sub_3;

		for (int i = 0; i < 8; ++i) {
			prem_marks.sub_1[i] = marks.sub_1[i];
			prem_marks.sub_2[i] = marks.sub_2[i];
			prem_marks.sub_3[i] = marks.sub_3[i];
		}

		bin_st_d.clear();
		bin_st_d.seekg(0, std::ios::beg);

		St_D student{};
		while (bin_st_d.read(reinterpret_cast<char*>(&student), sizeof(St_D))) {
			if (student.srb == marks.srb) {
				for (int j = 0; j < 20; ++j)
					prem_marks.surname[j] = student.surname[j];
				break;
			}
		}

		bin_prem_st_m.write(reinterpret_cast<const char*>(&prem_marks), sizeof(Prem_St_M));
	}
}

void average_to_bin(std::ifstream& bin_prem_st_m, std::ofstream& bin_avg) // prem,bin --->bin
{
	Prem_St_M prem_marks;
	while (bin_prem_st_m.read(reinterpret_cast<char*>(&prem_marks), sizeof(Prem_St_M))) {
		St_Av averager;
		averager.group = prem_marks.group;
		averager.srb = prem_marks.srb;
		for (int i = 0; i < sizeof(prem_marks.surname); ++i) {
			averager.surname[i] = prem_marks.surname[i];
		}
		averager.average = (static_cast<float>(prem_marks.m_sub_1) +
			static_cast<float>(prem_marks.m_sub_2) +
			static_cast<float>(prem_marks.m_sub_3)) / 3.0f;
		bin_avg.write(reinterpret_cast<const char*>(&averager), sizeof(St_Av));
	}
}

void bin_to_txt(std::ifstream& ff, std::string out_ad){
    std::ofstream out(out_ad, std::ios::out | std::ios::trunc);
    try{
        ofcheck(out);
        ff.seekg(0,std::ios::end);
        long long size = ff.tellg();
        ff.seekg(0, std::ios::beg);
        if(size%sizeof(St_Ex)) throw "before fail";
        uint32_t k = size/sizeof(St_Ex);
        St_Ex temp{};
        uint32_t i{};
        while(i < k && ff.read(reinterpret_cast<char*>(&temp),sizeof(St_Ex))){
            temp.surname[18] = '\0';
            out << static_cast<int>(temp.group) << ";" << static_cast<int>(temp.srb) << ";" << temp.surname << '\n'; 
			std::cout << static_cast<int>(temp.group) << ";" << static_cast<int>(temp.srb) << ";" << temp.surname << '\n';
            ++i;  
        }
        if (i != k) throw "break file";
    }catch(const char* error){
        std::cout << error << '\n';
    }
}

void fail_sort_create(std::ifstream& ff,std::string f_s_ad){
    std::ofstream ff_s_b(f_s_ad, std::ios::out | std::ios::binary | std::ios::trunc);
        ofcheck(ff_s_b);
        ff.seekg(0,std::ios::end);
        long long size = ff.tellg();
        ff.seekg(0, std::ios::beg);
        if(size%sizeof(St_Ex)) throw "before fail";
        uint32_t k = size/sizeof(St_Ex);
        
        St_Ex* arr = new St_Ex[k]{};
        uint32_t i{};
        while(i < k && ff.read(reinterpret_cast<char*>(&arr[i]), sizeof(St_Ex))){
            ++i;
        }
        if (i != k){
            delete[] arr;
            arr = nullptr;
            throw "break read file";
        } 
        tree_sort(arr,k,fail_comp);
        i = 0;
        while ( i < k  && ff_s_b.write(reinterpret_cast<char*>(&arr[i]), sizeof(St_Ex))){
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
}

void create_reports_exstud(const std::string& name) {
    const uint16_t size_struct = sizeof(Prem_St_M);
    std::ifstream file(name, std::ios::binary);
    std::ofstream newfile("reports_groups_exstud.bin", std::ios::binary | std::ios::trunc);
    Prem_St_M stud;
	ifcheck(file);
	ofcheck(newfile);
    file.seekg(0, std::ios::end);
    std::streamsize size_report = file.tellg();
    for (int i = 0; i * size_struct < (uint32_t)size_report; ++i) {
        file.seekg(i * size_struct, std::ios::beg);
        file.read(reinterpret_cast<char*>(&stud), size_struct);
        if (check_stex(stud)) {
            St_Ex newstud;
            rewrite_struct(stud, newstud);
            newfile.write(reinterpret_cast<const char*>(&newstud), sizeof(St_Ex));
        }
    }
    file.close();
    newfile.close();
}


void fail_create(std::ifstream& ff,std::string fail_ad){
    std::ofstream fail_b(fail_ad, std::ios::out | std::ios::binary | std::ios::trunc);
	ofcheck(fail_b);
        char temp[sizeof(Prem_St_M)]{};
        while(ff.read(reinterpret_cast<char*>(&temp), sizeof(Prem_St_M))){
            if (static_cast<int>(temp[36]) < 4 || static_cast<int>(temp[45]) < 4 || static_cast<int>(temp[54]) < 4 ){
                fail_b.write(reinterpret_cast<char*>(&temp), sizeof(St_Ex));
            }
        }
}

