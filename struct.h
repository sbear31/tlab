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
	uint8_t group; // 0 4
	uint32_t srb; //4 4
	char surname[20];// 8 20
	float average; //28 4
};

struct St_Ex {
    uint8_t group;
    uint32_t srb;
    char surname[20];
};