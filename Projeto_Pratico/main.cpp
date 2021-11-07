//Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include "class_registro.h"
#include "merge_sort.h"
#include <iostream>
#include <fstream>

using namespace std;

int main () 
{
	const int tamanho_pacotes = 100000/4;

	Registro *umRegistro = new Registro[25000];
	ifstream arquivo;

	arquivo.open("my_registros.bin", std::ios::in | std::ios::binary);

	for (int cont = 0; cont < 4; cont++) 
	{		
		arquivo.seekg(sizeof(Registro) * (cont * tamanho_pacotes)); // calcula posição da cabeça de leitura

		for (int i = 0; i < tamanho_pacotes; i++) //copiando regitros para vetor o de objetos
			arquivo.read((char*) &umRegistro[i], sizeof(umRegistro[i]));

		mergeSort(); //ordena vetor de objetos e gera um novo arquivo armazenado os registros ordenados;

		for (int i = 0; i < 10; i++) // teste
			umRegistro[i].imprime();

		cout << "Bloco (" << cont << ")criado" << endl;
	}

	
	arquivo.close();

	delete [] umRegistro;
	
	return 0;
}