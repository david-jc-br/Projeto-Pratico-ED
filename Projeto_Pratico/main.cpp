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
	const int qtd_total_registros = 100000;
	const int num_bytes_registro = sizeof(Pacote);
	const int tamanho_arquivo = qtd_total_registros * num_bytes_registro; 
	const int tamanho_bloco = qtd_total_registros/4;

	Pacote *umPacote = new Pacote[25000];
	fstream registros;

	for (int i = 0; i < 1; i++) 
	{
		if(copiarResgistros(registros, i, tamanho_bloco, umPacote)) {
			cout << "registro Copiado";
		}
		else {
			cout << "Não foi possivél abrir o arquivo" << endl;
			return 0;
		}

	}

	for (int i = 0; i < 10; i++)
		umPacote[i].exibir(umPacote,i);


	delete [] umPacote;
	
	return 0;
}