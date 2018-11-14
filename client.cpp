//EA872 - Projeto Final
// Gabriela Shima RA:13589  Mariane Tiemi Iguti RA:147279

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <pthread.h>
#include <string.h>
#include <mutex>

#include "serializable.hpp"
#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}


ListaDeCorpos *l = new ListaDeCorpos();
Tela *tela = new Tela(l, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
  
int socket_fd;
//std::mutex mtx;           // mutex for critical section

void *receber_respostas(void *parametros) {
  /* Recebendo resposta */
  char reply[MAX_MSG_STRING];
  int msg_len;
  int msg_num;
  msg_num = 0;

  RelevantData DadosCorpo(0,0,0,0,0);
  while(1) {

    msg_len = recv(socket_fd, reply, MAX_MSG_STRING, MSG_DONTWAIT);

    if (msg_len > 0) {
      //printf("[%d][%d] RECEBI:\n%s\n", msg_num, msg_len, reply);
      char *ptr = strtok (reply,"#");//tokeniza reply
      std::vector<Corpo *> *c_ptr = l->get_corpos();
      int h = 0;
      //mtx.lock();
      while(ptr != NULL) {
        DadosCorpo.unserialize(ptr);
        //DadosCorpo.dump();
        ptr = strtok (NULL,"#\n\0");

       if( h < (*c_ptr).size() ) { //caso os corpos já existam ele apenas atualiza os dados
    
          (*c_ptr)[h]->update(  DadosCorpo.get_velocidade_x(),\
                                DadosCorpo.get_velocidade_y(),\
                                DadosCorpo.get_posicao_x(),\
                                DadosCorpo.get_posicao_y() );
        }
        else { //acabaram os corpos existentes, adicionar novos corpos
          //printf("Vou adicionar corpo novo!\n");
          Corpo *c1 = new Corpo(DadosCorpo.get_velocidade_x(),\
                                DadosCorpo.get_velocidade_y(),\
                                DadosCorpo.get_posicao_x(),\
                                DadosCorpo.get_posicao_y(),\
                                DadosCorpo.get_tipo() );
          l->add_corpo(c1);
        }
        h++;
      }
    }
  }

}

int main() {
    struct sockaddr_in target;
    pthread_t receiver;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    //String que recebe o buffer do servidor
    char *reply;
    reply = (char *) malloc(100);
    int msg_len;

    target.sin_family = AF_INET;
    target.sin_port = htons(3001);
    inet_aton("127.0.0.1", &(target.sin_addr));
    
    if (connect(socket_fd, (struct sockaddr*)&target, sizeof(target)) != 0) {
        //printf("Problemas na conexao\n");
        return 0;
    }
    //printf("Conectei ao servidor\n");
    
    //Inicializa o player
    Audio::Sample *asample;
    asample = new Audio::Sample();
    asample->load("assets/blip.dat");

    Audio::Player *player;
    player = new Audio::Player();
    player->init();
        //Inicializa a Tela e o Teclado
    tela->init();
    Teclado *teclado = new Teclado();
    teclado->init();
    
    pthread_create(&receiver, NULL, receber_respostas, NULL);

    
    while(1) {
        /* Agora, meu socket funciona como um descritor de arquivo usual */
        
            //envia os caracteres para o servidor
        char c = 'k';
        c = teclado->getchar(); //envia caracter o tempo todo para o server
        if(c == 'w' || c == 's' || c == 'a' || c == 'd'){

            send(socket_fd, &c, 1, 0);
            player->play(asample);
            asample->set_position(0);
        }
        else if(c == 'q') {
            send(socket_fd, &c, 1, 0);
            player->play(asample);
            asample->set_position(0);
            tela->stop();
            teclado->stop();
            return 0;
        }
        else { send(socket_fd, "k", 1, 0);}

        //Imprime lista de Corpos
        // printf("========== Lista de Corpos da Main() ==========\n");
        // std::vector<Corpo *> *c_ptr = l->get_corpos();
        // for( int h = 0; h < (*c_ptr).size(); h++)
        //   printf("%f %f %f %f %d\n", (*c_ptr)[h]->get_velocidade_x(), (*c_ptr)[h]->get_velocidade_y(), (*c_ptr)[h]->get_posicao_x(), (*c_ptr)[h]->get_posicao_y(), (*c_ptr)[h]->get_tipo());

        //processa Tela
        tela->update_lista(l);
        tela->update();   
        std::this_thread::sleep_for (std::chrono::milliseconds(100));  
    
    }
    return 0;
}
