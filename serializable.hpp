#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#define MAX_MSG_STRING 1000000

struct DataContainer {
  float velocidade_x;
  float velocidade_y;
  float posicao_x;
  float posicao_y;
  int tipo;
};

class RelevantData {
private:
    DataContainer data;

  public:
    RelevantData();
    RelevantData(float velocidade_x, float velocidade_y, float posicao_x, float posicao_y, int tipo);
    RelevantData(std::string buffer_in);
    float get_velocidade_x();
    float get_velocidade_y();
    float get_posicao_x();
    float get_posicao_y();
    int get_tipo();
    void serialize(std::string &buffer_out);
    void unserialize(std::string buffer_in);
    void dump();
};

#endif
