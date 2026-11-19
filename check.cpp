#pragma once
#include <fstream>
#include"main.h"

void ifcheck(std::ifstream& ff){
    if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF) throw "file is empty\n"; 
}

void ofcheck(std::ofstream& ff){
    if(!ff) throw "file open error";
}

void fchecko(std::fstream& ff){
	if(!ff) throw "file open error";
}

void fchecki(std::fstream& ff){
	if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF) throw "file is empty\n"; 
}