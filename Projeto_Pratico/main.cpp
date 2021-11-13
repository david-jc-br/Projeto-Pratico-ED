// Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe: David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include <iostream>
#include <fstream>
#include <cstdio>

#include "escreve_registro.hpp"
#include "copia_registros.hpp"
#include "registro.hpp"

using namespace std;

int main () {
    ifstream arquivo_principal;
    arquivo_principal.open("captura_pacotes.bin", ios::in | ios::binary);

    if (!arquivo_principal) {
        cerr << "Não foi possivél abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    arquivo_principal.seekg(0,ios::end);

    const long int tamanho_arquivo = arquivo_principal.tellg();
    const short tamanho_registro = sizeof(Registro);
    const long int qtd_registro = tamanho_arquivo/tamanho_registro;
    const int tamanho_pacotes = qtd_registro/2;

    Registro *umRegistro = new Registro[tamanho_pacotes];

    short escolha;
    int posicao_bytes;

    if (arquivo_principal) { 
        cout << "Digite, ordenar por:\n" 
             << "\n(1) Indice"
             << "\n(2) Informação\n\n->";

        cin >> escolha;

        if ((escolha != 1 ) && (escolha != 2)) {
            cerr << "\"Opção inexistente\"" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
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

            umRegistro->mergeSortInterno(umRegistro,tamanho_pacotes,escolha);	
		
            if (cont == 0) 
                escreveRegistros(arqTemp1, umRegistro, 0, tamanho_pacotes);
            else 
                escreveRegistros(arqTemp2, umRegistro, 0, tamanho_pacotes);
        }
    	delete [] umRegistro;
    }

    arquivo_principal.close();
    arqTemp1.close();
    arqTemp2.close();
	
    ofstream arquivoFinal("arquivoFinalOrdenado.bin",ios::binary);
	
    umRegistro->mergeSortExterno(arquivoFinal,escolha,qtd_registro);

	cout << "\n\n\'Ordenação Feita com Sucesso\'\n" << endl;
	
    arquivoFinal.close();

	//apagar arquivos auxiliares
    remove("arqTemp1.bin");
    remove("arqTemp2.bin");
    remove("arqTemp3.bin");

    cout << "\nGostaria de testar a ordenação ?\n" 
		 << "\nDigite (1) Sim ou (2) Não\n-> ";
	
	cin >> escolha;

	if (escolha == 1) {

		cout << "\nQuantos registros você deseja imprimir?\n-> ";

		int quantidade;
		cin >> quantidade;

		if (quantidade <= qtd_registro && quantidade > 0) {
			Registro *objAux= new Registro[qtd_registro];
			
			ifstream arq("arquivoFinalOrdenado.bin",ios::binary);
			
			copiaRegistros(arq, objAux, 0, qtd_registro);

			for(int i = 0; i < quantidade; i++) 
				objAux[i].imprime();

			arq.close();
			delete [] objAux;
		} else {
			cerr << "\nQuantidade inválida!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	
    return 0;
}
