// Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include <iostream>
#include <fstream>
#include <cstdio>
#include "void_escreve_registro.h"
#include "class_registro.h"
#include "void_copia_registros.h"

using namespace std;

int main () 
{
	Registro *umRegistro = new Registro[25000];
	const int tamanho_pacotes = 100000/4;
	int escolha_ordenacao;
	int posicao_bytes;
	fstream arquivo;
    //char buffer[5300000];
	Registro objAux;

	if (arquivo) 
	{ // escolhe o tipo de ordenação
		arquivo.open("captura_pacotes.bin", std::ios::in | std::ios::binary);
		
		cout << "Digite, ordenar por:\n" 
			 << "\n(1) Indice"
			 << "\n(2) Informação\n\n->";

		cin >> escolha_ordenacao;

		if ((escolha_ordenacao != 1 ) && (escolha_ordenacao != 2)) 
		{
			cout << "\"Opção inexistente\"" << endl;
			return 0;
		}
	}
	else 
	{
		cout << "Não foi possivél ler o arquivo" << endl;
		return 0;
	}
	
	for (int cont = 0; cont < 4; cont++) // criar os 4 blocos ordenados
	{		
		posicao_bytes = sizeof(Registro) * (cont * tamanho_pacotes);

		copiaRegistros(arquivo, umRegistro, posicao_bytes, tamanho_pacotes);

		for (int i = 0; i < 10; i++) // teste
			umRegistro[i].imprime();
	}

	arquivo.close();

	delete [] umRegistro;
	
	return 0;
}