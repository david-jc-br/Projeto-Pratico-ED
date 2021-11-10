#include <iostream>
#include <fstream>
#include "class_registro.h"

#ifndef VOID_ESCREVE_REGISTROS_H
#define VOID_ESCREVE_REGISTROS_H

void escreveRegistros (std::fstream &arquivo, Registro umRegistro[], int posicao_bytes, int tamanho_pacotes)
{
    arquivo.seekp(posicao_bytes); // Posiciona a cabeça de leitura 
	
    for (int i = 0; i < tamanho_pacotes; i++) //copiando regitros para vetor o de objetos
        arquivo.write((char*) &umRegistro[i], sizeof(umRegistro[i]));
}



#endif