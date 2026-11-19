#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "struct.h"
#include <cstring>
#include"main.h"

bool fail_comp(const St_Ex& a,const St_Ex& b){
    if (a.group != b.group) return a.group > b.group;
    int c = strcmp(a.surname,b.surname);
    if (c != 0){
        return c > 0;
    }
    return a.srb > b.srb;
}

bool compar1(char* a, char* b) {
    int i = 0;
    for (; a[i] != '\0' || b[i] != '\0'; ++i) if (a[i] > b[i]) return true;
    if (a[i] != '\0') return true;
    else if (b[i] != '\0') return true;
    return false;
}

bool compar2(float a, float b) {
    if (a < b) return true;
    return false;
}