#include "classe_pacote.h"
#include <iostream> 
#include <fstream>

#ifndef COPIAR_REGISTROS_H 
#define COPIAR_REGISTROS_H

bool copiarResgistros(std::fstream &arquivo, int posicao, int tamanho_bloco, Pacote umPacote[])
{
    arquivo.open("capturas_Pacotes.bin", std::ios::binary|std::ios::in);

    arquivo.seekg(posicao*tamanho_bloco);

    for (int i = 0; i < tamanho_bloco; i++) {
        arquivo.seekg(i*sizeof(Pacote));
        arquivo.read((char*) &umPacote[i], sizeof(umPacote));   
    }
       
    return true;
}


#endif 
