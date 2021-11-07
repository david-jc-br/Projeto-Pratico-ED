#include <iostream> 
#include <fstream>
#include "class_registro.h"

#ifndef COPIAR_REGISTROS_H 
#define COPIAR_REGISTROS_H

void copiarResgistros(std::fstream &arquivo, int posicao, int tamanho_pacotes, Registro umRegistro[])
{
    arquivo.seekg(posicao * tamanho_pacotes);

    for (int i = 0; i < tamanho_pacotes; i++) 
    {
        arquivo.seekg((i*sizeof(Registro)));
        arquivo.read((char*) &umRegistro, sizeof(Registro));   
    }
}

#endif 