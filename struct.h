#pragma once
#include <cstdint>

struct St_D {
	uint32_t srb;
	char surname[20];
	char name[20];
	char lastname[20];
};
struct St_M {
	uint8_t group;
	uint32_t srb;
	char sub_1[8];
	uint8_t m_sub_1;  
	char sub_2[8];
	uint8_t m_sub_2;
	char sub_3[8];
	uint8_t m_sub_3;
};
struct Prem_St_M {
	uint8_t group;
	uint32_t srb;
	char surname[20];
	char sub_1[8];
	uint8_t m_sub_1;
	char sub_2[8];
	uint8_t m_sub_2;
	char sub_3[8];
	uint8_t m_sub_3;
};
struct St_Av {
	uint8_t group;
	uint32_t srb;
	char surname[20];
	float average;
};

struct St_Ex {
    uint8_t group;
    uint32_t srb;
    char surename[20];
};

struct Fail_Student{
    uint8_t group{};
    uint32_t srb{};
    char surename[20]{};
};