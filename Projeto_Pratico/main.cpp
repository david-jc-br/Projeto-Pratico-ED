//Projeto Final - Ordenação em Memória Secundária - Grupo 12
// Equipe:David de Jesus Costa, Guilherme Grego Santos, Pedro Henrique Maciel Alves.

#include "classe_Pacote.h"
#include <iostream>
#include <fstream>

using namespace std;


int main () 
{
	Pacote *umaClasse = new Pacote[25000];

	fstream arquivo ("capturas_Pacotes.bin", ios::in|ios::ate);
	long int tamanho_bytes = sizeof(Pacote)*100000; 
	long int num_regs = int (tamanho_bytes/sizeof(Pacote));
	int tam_bytes_regs = sizeof(Pacote);
	int tamanho_bloco = num_regs/4;


	for (int i = 0; i < num_regs; i += 25000) 
	{
		for (int j = i; j < 100 ; j++) 
		{
			arquivo.seekp((j) * tam_bytes_regs);
			arquivo.read((char*) &umaClasse, sizeof(Pacote));
			cout << &umaClasse[j] << endl;
			umaClasse[j].mostrar();
		}
	}
	
	return 0;
}