#include <fstream>

bool check_file(std::ifstream& file) {
	if (!file.good()) {
		throw "file isn't exist\n";
	}
	if (!file) {
		throw "input file error\n";
	}
	if (file.peek() == EOF) {
		throw "file is  empty!\n";
	}
	return true;
}

void ifcheck(std::ifstream& ff){
    if(!ff.good()) throw "file isn't exit\n";
    if(!ff) throw "file open error\n";
    if(ff.peek()==EOF) throw "file is empty\n"; 
}

void ofcheck(std::ofstream& ff){
    if(!ff) throw "file open error";
}