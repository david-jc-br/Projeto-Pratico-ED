#include <iostream>
#include <fstream>
#include "class_registro.hpp"

#ifndef VOID_COPIA_REGISTROS_HPP
#define VOID_COPIA_REGISTROS_HPP

void copiaRegistros (std::ifstream &arquivo, Registro umRegistro[], int posicao_bytes, int tamanho_pacotes) {
    arquivo.seekg(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < tamanho_pacotes; i++) //copiando regitros para vetor o de objetos
        arquivo.read((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

#endif
