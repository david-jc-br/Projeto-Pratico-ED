// Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include <iostream>
#include <fstream>
#include <cstdio>

#include "void_escreve_registro.h"
#include "void_copia_registros.h"
#include "class_registro.h"

using namespace std;

int main () 
{
	short escolha_ordenacao;
	int posicao_bytes;
	int posicao_arquivoTemp;

	cout << "Digite, ordenar por:\n" 
		 << "\n(1) Indice"
		 << "\n(2) Informação\n\n->";

	cin >> escolha_ordenacao;

	if ((escolha_ordenacao != 1 ) && (escolha_ordenacao != 2)) 
	{
		cerr << "\"Opção inexistente\"" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream arquivo_entrada;
	ofstream ArquivoTemporario1 ("arqTemp1.bin");
	ofstream ArquivoTemporario2 ("arqTemp2.bin");

	if ((!ArquivoTemporario1) | (!ArquivoTemporario2) | (!arquivo_entrada)) 
	{
		arquivo_entrada.close();
		ArquivoTemporario1.close();
		ArquivoTemporario2.close();	
		remove("arqTemp1.bin");
		remove("arqTemp2.bin");

		cerr << "Não foi possivél criar os arquivos para a ordenação" << endl;
		exit(EXIT_FAILURE);
	}

	arquivo_entrada.open("captura_pacotes.bin", ios::in | ios::binary);
	arquivo_entrada.seekg(0,ios::end);

	const long int tamanho_arquivo = arquivo_entrada.tellg();
	const short tamanho_registro = sizeof(Registro);
	const long int qtd_registro = tamanho_arquivo/tamanho_registro;
	const int tamanho_pacotes = qtd_registro/4;

	ArquivoTemporario1.open("arqTemp1.bin", ios::binary);
	ArquivoTemporario2.open("arqTemp2.bin", ios::binary);

	Registro *umRegistro = new Registro[tamanho_pacotes];
	Registro objAux;

	for (int cont = 0; cont < 4; cont++) 
	{		
		posicao_bytes = tamanho_registro * (cont * tamanho_pacotes);

		copiaRegistros(arquivo_entrada, umRegistro, posicao_bytes, tamanho_pacotes);

		objAux.mergeSortInterno(umRegistro,tamanho_pacotes,escolha_ordenacao);

		if ((cont == 0) || (cont == 1)) 
			posicao_arquivoTemp = 0;
		else
			posicao_arquivoTemp = tamanho_registro * (2 * tamanho_pacotes);

        if (cont == 0 | cont == 2)
			escreveRegistros(ArquivoTemporario1, umRegistro, posicao_arquivoTemp, tamanho_pacotes);
		else 
		    escreveRegistros(ArquivoTemporario2, umRegistro, posicao_arquivoTemp, tamanho_pacotes);

		/*for(int i = 0; i < 20; i++) // teste
			umRegistro[i].imprime();
		
		cout << "criado " << cont << endl;*/
	}

	ArquivoTemporario1.close();
	ArquivoTemporario2.close();

	remove("arqTemp1.bin");
	remove("arqTemp2.bin");

	arquivo_entrada.close();

	delete [] umRegistro;
	
	return 0;
}