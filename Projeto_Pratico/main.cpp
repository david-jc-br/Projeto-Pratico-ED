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
	ifstream arquivo_principal;
	arquivo_principal.open("captura_pacotes.bin", ios::in | ios::binary);
	arquivo_principal.seekg(0,ios::end);

	const long int tamanho_arquivo = arquivo_principal.tellg();
	const short tamanho_registro = sizeof(Registro);
	const long int qtd_registro = tamanho_arquivo/tamanho_registro;
	const int tamanho_pacotes = qtd_registro/2;

	Registro *umRegistro = new Registro[tamanho_pacotes];

	short escolha_ordenacao;
	int posicao_bytes;

	if (arquivo_principal) 
	{ 
		cout << "Digite, ordenar por:\n" 
			 << "\n(1) Indice"
			 << "\n(2) Informação\n\n->";

		cin >> escolha_ordenacao;

		if ((escolha_ordenacao != 1 ) && (escolha_ordenacao != 2)) 
		{
			cerr << "\"Opção inexistente\"" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		cerr << "Não foi possivél ler o arquivo" << endl;
		exit(EXIT_FAILURE);
	}
	
	ofstream arqTemp1("arqTemp1.bin", ios::binary);
	ofstream arqTemp2("arqTemp2.bin", ios::binary);
	
	if((! arqTemp1) | (! arqTemp2)) {
		cerr << "Não foi possivél abrir o arquivo" << endl;
		exit(EXIT_FAILURE);
    }
    else {
	    for (int cont = 0; cont < 2; cont++) {	
		    posicao_bytes = tamanho_registro * (cont * tamanho_pacotes);

		    copiaRegistros(arquivo_principal, umRegistro, posicao_bytes, tamanho_pacotes);

	        umRegistro->mergeSortInterno(umRegistro,tamanho_pacotes,escolha_ordenacao);	
		
		    if (cont == 0) 
                escreveRegistros(arqTemp1, umRegistro, 0, tamanho_pacotes);
		    else 
		        escreveRegistros(arqTemp2, umRegistro, 0, tamanho_pacotes);
	    }
    }

	arquivo_principal.close();
	arqTemp1.close();
	arqTemp2.close();
	
	ofstream arquivoFinal("arquivoFinal.bin",ios::binary);
	
	umRegistro->mergeexterno(arquivoFinal,escolha_ordenacao,qtd_registro);
	
	arquivoFinal.close();
	
    Registro *objAux= new Registro[qtd_registro];
    
    ifstream arq("arquivoFinal.bin",ios::binary);
    
    copiaRegistros(arq, objAux, 0, qtd_registro); 
    
        
    for(int i = 0; i < 5; i++) // teste
			objAux[i].imprime();
	objAux[25000].imprime();
    objAux[25000+1].imprime();
    objAux[50000-1].imprime();
    objAux[50000].imprime();
    objAux[100000-1].imprime();
	arq.close();
	
	//apagar arquivos auxiliares
    remove("arqTemp1.bin");
    remove("arqTemp2.bin");
    remove("arqTemp3.bin");

	delete [] umRegistro;
	
	return 0;
}
