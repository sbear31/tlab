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
  uint8_t group;
  uint32_t srb;
  char surename[20];
  char sub_1[8];
  uint8_t m_sub_1;
  char sub_2[8];
  uint8_t m_sub_2;
  char sub_3[8];
  uint8_t m_sub_3;
};
struct st_av (Student Average) {
  uint8_t group;
  uint32_t srb;
  char surename[20];
  float average;
};
struct st_ex (Exelent Student) {
    uint8_t group;
    uint32_t srb;
    char surename[20];
};

