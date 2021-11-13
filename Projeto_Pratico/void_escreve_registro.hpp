#include <iostream>
#include <fstream>
#include "class_registro.hpp"

#ifndef VOID_ESCREVE_REGISTROS_HPP
#define VOID_ESCREVE_REGISTROS_HPP

void escreveRegistros (std::ofstream &arquivo, Registro umRegistro[], int posicao_bytes, int tamanho_pacotes) {
    arquivo.seekp(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < tamanho_pacotes; i++) //escrevendo vetor de objetos no arquivo
        arquivo.write((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

#endif
