//Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include "classe_Pacote.h"
#include "merge_sort.h"
#include "copiar_Registros.h"
#include <iostream>
#include <fstream>

using namespace std;

int main () 
{
	const int tamanho_arquivo = 100000 * sizeof(Pacote); 
	const int tamanho_bloco = 100000/4;

	Pacote *umPacote = new Pacote[25000];
	fstream registros;

	for (int i = 0; i < 4; i++) 
	{
		//copia os registros para os objetos
		copiarResgistros(registros, i, tamanho_bloco, umPacote); 
		// ordena o bloco, cria um novo arquivo e armazena o bloco nesse novo arquivo
		mergeSort(); 
		cout << "Pacote (" << i << ")criado" << endl;
	}

	for (int i = 0; i < 10; i++)
		umPacote[i].exibir(umPacote[i]);


	delete [] umPacote;
	
	return 0;
}