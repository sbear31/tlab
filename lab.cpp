#include <iostream>
#include "struct.h"
#include "main.h"
#include "check.cpp"
#include "main.cpp"
#include "convertor.cpp"
#include <string>
#include "comp.cpp"
int main(){
  setlocale(LC_ALL, ".1251");

  std::ifstream file_st_d("student_data.txt", std::ios::in);
  std::ifstream file_st_m("student_mark.txt", std::ios::in);

  std::ofstream bin_st_d("student_data.bin", std::ios::binary | std::ios::trunc);
  std::ofstream bin_st_m("student_mark.bin", std::ios::binary | std::ios::trunc);
  std::ofstream bin_prem("premium_mark.bin", std::ios::binary | std::ios::trunc);
  std::ofstream bin_avg("average_mark.bin", std::ios::binary | std::ios::trunc);

  try {
        ifcheck(file_st_d);
        ifcheck(file_st_m);
        ofcheck(bin_st_d);
        ofcheck(bin_st_m);
        ofcheck(bin_prem);
        ofcheck(bin_avg);
        //a.1
        txt_to_binary_st_d(file_st_d, bin_st_d);
        file_st_d.clear();
        bin_st_d.clear();
        file_st_d.close();
        bin_st_d.close();
        //a.2
        txt_to_binary_st_m(file_st_m, bin_st_m);
        file_st_m.clear();
        bin_st_m.clear();
        file_st_m.close();
        bin_st_m.close();
        //b
        std::ifstream bin_st_d_in("student_data.bin", std::ios::binary);
        std::ifstream bin_st_m_in("student_mark.bin", std::ios::binary);
        ifcheck(bin_st_d_in);
        ifcheck(bin_st_m_in);
        add_surname_to_st_m(bin_st_d_in, bin_st_m_in, bin_prem);
        bin_st_d_in.clear();
        bin_st_m_in.clear();
        bin_prem.clear();
        bin_st_d_in.close();
        bin_st_m_in.close();
        bin_prem.close();
        //c
        std::ifstream bin_prem_in("premium_mark.bin", std::ios::binary);
        ifcheck(bin_prem_in);
        average_to_bin(bin_prem_in, bin_avg);
        
        bin_prem_in.clear();
        bin_avg.clear();
        bin_prem_in.close();
        bin_avg.close();

         //d
        std::ifstream prem_bin("premium_mark.bin", std::ios::in | std::ios::binary);
        ifcheck(prem_bin);
        fail_create(prem_bin,"fail.bin");
        prem_bin.clear();
        prem_bin.close();
        //e
        std::ifstream fail("fail.bin", std::ios::in | std::ios::binary);
        ifcheck(fail);
        fail_sort_create(fail,"fail_sort.bin");
        //f
        std::cout << "Список неуспевающих" << '\n';
        bin_to_txt(fail, "fail_not_sotr.txt");
        fail.clear();
        fail.close();
        std::ifstream fail_sort("fail_sort.bin", std::ios::in | std::ios::binary);
        ifcheck(fail_sort);
        std::cout << "Список отсортированных неуспевающих" << '\n';
        bin_to_txt(fail_sort, "fail_sotr.txt");
        fail_sort.clear();
        fail_sort.close();
        //g and h
        std::string ad_of_av_m_bin{"average_mark.bin"};
        std::string prem_m_bin{"premium_mark.bin"};
        for(int i = 1;i < 6; ++i ){
            std::string num = std::to_string(i);
            create_reports_groups_alf(i,prem_m_bin,"res_ad_reports_groups_alf_"+num+".bin");
            create_reports_groups_points(i,ad_of_av_m_bin,"res_ad_reports_groups_points_"+num+".bin");
        }
        //i
        create_reports_exstud(prem_m_bin);

        std::string ad {"reports_groups_exstud.bin"};
        std::ifstream ff (ad, std::ios::in | std::ios::binary);
        ifcheck(ff);
        fail_sort_create(ff,"temp1.bin");
        std::ifstream temp("temp1.bin", std::ios::in | std::ios::binary);
        ifcheck(temp);
        std::cout << "Список отличников" << '\n';
        bin_to_txt(temp,"reports_groups_exstud_sort.txt");
  }
  catch (const char* error) {
    std::cout << error << '\n';
  }
    return 0;
}