//Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include "class_registro.h"
#include "merge_sort.h"
#include "copiar_registros.h"
#include <iostream>
#include <fstream>

using namespace std;

int main () 
{
	const int tamanho_arquivo = 100000 * sizeof(Registro); 
	const int tamanho_pacotes = 100000/4;

	Registro *pacote = new Registro[25000];
	fstream registros;

	registros.open("capturas_Registros.bin", std::ios::binary|std::ios::in);

	for (int i = 0; i < 4; i++) 
	{
		//copia os registros para os objetos
		copiarResgistros(registros, i, tamanho_pacotes, pacote); 
		// ordena o pacote, cria um novo arquivo e armazena o bloco nesse novo arquivo
		mergeSort(); 
		cout << "Registro (" << i << ")criado" << endl;
	}

	for (int i = 0; i < 10; i++)
		pacote[i].imprime(pacote[i]);


	delete [] pacote;
	
	return 0;
}