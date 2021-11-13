#include <iostream>
#include <fstream>
#include "registro.hpp"

#ifndef COPIA_REGISTROS_HPP
#define COPIA_REGISTROS_HPP

void copiaRegistros (std::ifstream &arquivo, Registro umRegistro[], int posicao_bytes, int tamanho_pacotes) {
    arquivo.seekg(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < tamanho_pacotes; i++) //copiando regitros para vetor o de objetos
        arquivo.read((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

#endif
