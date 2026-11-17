#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
struct ST_D {
	uint32_t srb;
	char surname[20];
	char name[20];
	char lastname[20];
};
struct ST_M {
	uint8_t group;
	uint32_t srb;
	char sub_1[8];
	uint8_t m_sub_1;
	char sub_2[8];
	uint8_t m_sub_2;
	char sub_3[8];
	uint8_t m_sub_3;
};
struct PREM_ST_M {
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
struct ST_AV {
	uint8_t group;
	uint32_t srb;
	char surname[20];
	float average;
};
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
void txt_to_binary_st_d(std::ifstream& file, std::ofstream& bin) {
	std::string line;
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
			std::cout << "bad line: " << line << "\n";
			continue;
		}
		ST_D student{};
		try {
			check_digits(line.substr(0, pos[0]));
			student.srb = static_cast<uint32_t>(std::stoul(line.substr(0, pos[0])));
			string_to_masschar<20>(student.surname, line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
			string_to_masschar<20>(student.name, line.substr(pos[1] + 1, pos[2] - pos[1] - 1));
			string_to_masschar<20>(student.lastname, line.substr(pos[2] + 1));
		}
		catch (const char* message) {
			std::cout << message;
			continue;
		}
		bin.write(reinterpret_cast<const char*>(&student), sizeof(ST_D));
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
		ST_M marks{};
		try {
			check_digits(line.substr(0, pos[0]));
			marks.group = static_cast<uint8_t>(std::stoul(line.substr(0, pos[0])));
			check_digits(line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
			marks.srb = static_cast<uint32_t>(std::stoul(line.substr(pos[0] + 1, pos[1] - pos[0] - 1)));
			string_to_masschar<8>(marks.sub_1, line.substr(pos[1] + 1, pos[2] - pos[1] - 1));
			check_digits(line.substr(pos[2] + 1, pos[3] - pos[2] - 1));
			marks.m_sub_1 = static_cast<uint8_t>(std::stoul(line.substr(pos[2] + 1, pos[3] - pos[2] - 1)));
			string_to_masschar<8>(marks.sub_2, line.substr(pos[3] + 1, pos[4] - pos[3] - 1));
			check_digits(line.substr(pos[4] + 1, pos[5] - pos[4] - 1));
			marks.m_sub_2 = static_cast<uint8_t>(std::stoul(line.substr(pos[4] + 1, pos[5] - pos[4] - 1)));
			string_to_masschar<8>(marks.sub_3, line.substr(pos[5] + 1, pos[6] - pos[5] - 1));
			check_digits(line.substr(pos[6] + 1));
			marks.m_sub_3 = static_cast<uint8_t>(std::stoul(line.substr(pos[6] + 1)));
		}
		catch (const char* message) {
			std::cout << message;
			continue;
		}
		bin.write(reinterpret_cast<const char*>(&marks), sizeof(ST_M));
	}
}
void add_surname_to_st_m(std::ifstream& bin_st_d, std::ifstream& bin_st_m, std::ofstream& bin_prem_st_m) {
	ST_M marks;
	while (bin_st_m.read(reinterpret_cast<char*>(&marks), sizeof(ST_M))) {

		PREM_ST_M prem_marks{};
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

		ST_D student{};
		while (bin_st_d.read(reinterpret_cast<char*>(&student), sizeof(ST_D))) {
			if (student.srb == marks.srb) {
				for (int j = 0; j < 20; ++j)
					prem_marks.surname[j] = student.surname[j];
				break;
			}
		}

		bin_prem_st_m.write(reinterpret_cast<const char*>(&prem_marks), sizeof(PREM_ST_M));
	}
}
void average_to_bin(std::ifstream& bin_prem_st_m, std::ofstream& bin_avg)
{
	PREM_ST_M prem_marks;
	while (bin_prem_st_m.read(reinterpret_cast<char*>(&prem_marks), sizeof(PREM_ST_M))) {
		ST_AV averager;
		averager.group = prem_marks.group;
		averager.srb = prem_marks.srb;
		for (int i = 0; i < sizeof(prem_marks.surname); ++i) {
			averager.surname[i] = prem_marks.surname[i];
		}
		averager.average = (static_cast<float>(prem_marks.m_sub_1) +
			static_cast<float>(prem_marks.m_sub_2) +
			static_cast<float>(prem_marks.m_sub_3)) / 3.0f;
		bin_avg.write(reinterpret_cast<const char*>(&averager), sizeof(ST_AV));
	}
}
int main() {
	setlocale(LC_ALL, ".1251");

	std::ifstream file_st_d("student_data.txt", std::ios::in);
	std::ifstream file_st_m("student_mark.txt", std::ios::in);

	std::ofstream bin_st_d("student_data.bin", std::ios::binary | std::ios::trunc);
	std::ofstream bin_st_m("student_mark.bin", std::ios::binary | std::ios::trunc);
	std::ofstream bin_prem("premium_mark.bin", std::ios::binary | std::ios::trunc);
	std::ofstream bin_avg("average_mark.bin", std::ios::binary | std::ios::trunc);

	try {
		check_file(file_st_d);
		check_file(file_st_m);
	}
	catch (const char* message) {
		std::cout << message;
		return 1;
	}

	if (!bin_st_d || !bin_st_m || !bin_prem || !bin_avg) {
		std::cerr << "cannot open output\n";
		return 1;
	}
//1
	txt_to_binary_st_d(file_st_d, bin_st_d);
	file_st_d.close();
	bin_st_d.close();

//2
	txt_to_binary_st_m(file_st_m, bin_st_m);
	file_st_m.close();
	bin_st_m.close();

//3
	std::ifstream bin_st_d_in("student_data.bin", std::ios::binary);
	std::ifstream bin_st_m_in("student_mark.bin", std::ios::binary);
	check_file(bin_st_d_in);
	check_file(bin_st_m_in);
	add_surname_to_st_m(bin_st_d_in, bin_st_m_in, bin_prem);
	bin_st_d_in.close();
	bin_st_m_in.close();
	bin_prem.close();

//4
	std::ifstream bin_prem_in("premium_mark.bin", std::ios::binary);
	check_file(bin_prem_in);
	average_to_bin(bin_prem_in, bin_avg);
	bin_prem_in.close();
	bin_avg.close();

	std::cout << "all tasks done\n";
	return 0;
}
