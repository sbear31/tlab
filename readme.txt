формат структур:
struct st_d (Student Data) {
  uint32_t srb (номер зачетки);
  char surename[20];
  char name[20];
  char lastname[20];
};
struct st_m {
  uint8_t group;
  uint32_t srb;
  char sub_1[8];
  uint8_t m_sub_1;  
  char sub_2[8];
  uint8_t m_sub_2;
  char sub_3[8];
  uint8_t m_sub_3;
};
struct prem_st_m {
  uint8_t group; //0 4
  uint32_t srb; //4 4
  char surename[20]; //8 20
  char sub_1[8]; //28 8
  uint8_t m_sub_1; //36 1
  char sub_2[8]; //37 8
  uint8_t m_sub_2; //45 1
  char sub_3[8]; //46 8
  uint8_t m_sub_3; //54 2
};
struct st_av (Student Average) {
  uint8_t group;
  uint32_t srb;
  char surename[20];
  float average;
};

