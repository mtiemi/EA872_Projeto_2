
#include "serializable.hpp"
#include <stdio.h>
#include <string>
#include <cstring>
#include <algorithm>


/*
class RelevantData {
  private:
    int a;
    char b;

  public:
    RelevantData(int a, char b);
    RelevantData(std::string serial_data);
    std::string serialize();
};
*/

RelevantData::RelevantData() {
};

RelevantData::RelevantData (  float velocidade_x,
                float velocidade_y,
                float posicao_x,
                float posicao_y,
                int tipo
              ) {
  this->data.velocidade_x = velocidade_x;
  this->data.velocidade_y = velocidade_y;
  this->data.posicao_x = posicao_x;
  this->data.posicao_y = posicao_y;
  this->data.tipo = tipo;
}

RelevantData::RelevantData(std::string buffer_in) {
  this->unserialize(buffer_in);
}

float RelevantData::get_velocidade_x() {
  return this->data.velocidade_x;
}
float RelevantData::get_velocidade_y(){
  return this->data.velocidade_y;
}
float RelevantData::get_posicao_x(){
  return this->data.posicao_x;
}
float RelevantData::get_posicao_y(){
  return this->data.posicao_y;
}
int RelevantData::get_tipo(){
  return this->data.tipo;
}

    
void RelevantData::serialize(std::string &buffer_out) {
  //std::memcpy((void*)buffer_out.c_str(), &(this->data), sizeof(DataContainer));
  // float a = this->data.velocidade_x;
  // float b = this->data.velocidade_y;
  // float c =this->data.posicao_x;
  // float d = this->data.posicao_y;
  // int e = this->data.tipo;
  sprintf((char*) buffer_out.c_str() , "%f %f %f %f %d", this->data.velocidade_x, this->data.velocidade_y, this->data.posicao_x, this->data.posicao_y, this->data.tipo);
}

void RelevantData::unserialize(std::string buffer_in) {
  //std::memcpy(&(this->data), (void*)buffer_in.c_str(), sizeof(DataContainer));
  float a, b, c, d;
  int e;
  sscanf(buffer_in.c_str(), "%f %f %f %f %d", &this->data.velocidade_x, &this->data.velocidade_y, &this->data.posicao_x, &this->data.posicao_y, &this->data.tipo);
  //this->data.velocidade_x = a;
  //this->data.velocidade_y = b;
  //this->data.posicao_x = c;
  //this->data.posicao_y = d;
  //this->data.tipo = e;
}

void RelevantData::dump() {
  std::cout << "Velocidade x:" << this->data.velocidade_x << '\n' << "Velocidade y:" <<this->data.velocidade_y << '\n';
  std::cout << "Posicao x:" << this->data.posicao_x << '\n' << "Posicao y:" <<this->data.posicao_y << '\n';
  std::cout << "Tipo:" << this->data.tipo << '\n' ;
}
