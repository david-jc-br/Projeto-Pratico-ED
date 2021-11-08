//Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include "class_registro.h"
#include "void_copia_registros.h"
#include "void_merge_sort.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main () 
{
	Registro *umRegistro = new Registro[25000];
	const int tamanho_pacotes = 100000/4;
	int posicao_bytes;
	int escolha_ordenacao;
	fstream arquivo;

	if (arquivo) {
		arquivo.open("captura_pacotes.bin", std::ios::in | std::ios::binary);
		
		cout << "Digite, ordenar por:\n" 
			 << "\n(1) Indice"
			 << "\n(2) Informação\n\n->";

		cin >> escolha_ordenacao;
	}
	else {
		cout << "Não foi possivél ler o arquivo" << endl;
		return 0;
	}
	
	for (int cont = 0; cont < 4; cont++) // criar os 4 blocos ordenados
	{		
		posicao_bytes = sizeof(Registro) * (cont * tamanho_pacotes);

		copiaRegistros(arquivo, umRegistro, posicao_bytes, tamanho_pacotes);

		mergeSort(escolha_ordenacao); 

		for (int i = 0; i < 10; i++) // teste
			umRegistro[i].imprime();

		cout << "Arquivo temporário (" << cont+1 << ")criado" << endl;
	}

	arquivo.close();

	delete [] umRegistro;
	
	return 0;
}