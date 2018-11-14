// EA872 - LAB06
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)

#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include "portaudio.h"
#include <vector>
#include <thread>

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>

#define SCREEN_HEIGHT 20
#define SCREEN_WIDTH SCREEN_HEIGHT*2

#define COMIDA      998
#define SNAKE_HEAD  22
#define SNAKE_BODY  23

#define VELOCIDADE  20

#define FALSE 0
#define TRUE  1

class Corpo {
  private:
  float velocidade_x;
  float velocidade_y;
  float posicao_x;
  float posicao_y;
  int tipo;

  public:
  Corpo(  float velocidade_x,
          float velocidade_y,
          float posicao_x,
          float posicao_y,
          int tipo
        );

  void update(  float nova_velocidade_x,
                float nova_velocidade_y ,
                float nova_posicao_x,
                float nova_posicao_y
              );

  float get_velocidade_x();
  float get_velocidade_y();
  float get_posicao_x();
  float get_posicao_y();
  int get_tipo();

};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void remove_corpo(int indice);
    std::vector<Corpo*> *get_corpos();
};

// Controller de Snake
class SnakeController {
  private:
    ListaDeCorpos *lista;

  public:
    SnakeController(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void andar_para_cima(int user);
    void andar_para_baixo(int user);
    void andar_para_direita(int user);
    void andar_para_esquerda(int user);
    void update(float deltaT);
};

class Tela {
  private:
    ListaDeCorpos *lista, *lista_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void update();
    void update_lista(ListaDeCorpos *ldc);
};

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};

namespace Audio { //edit: Class from MP4 playback.hpp

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};


class Player {
  private:
    Sample *audio_sample;
    bool playing;

    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    PaTime              streamOpened;


  public:
    Player();
    ~Player();

    void init();
    void pause();
    void stop();
    void play(Sample *audiosample);
    Sample *get_data();
};

}

#endif
