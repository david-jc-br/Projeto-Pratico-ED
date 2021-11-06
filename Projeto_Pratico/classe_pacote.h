#include <iostream> 
#include <fstream>

#ifndef CLASSE_PACOTE_H 
#define CLASSE_PACOTE_H

class  Pacote 
{
	private:
		unsigned indice;
		float tempo;
		char origem[40];
		char destino[40];
		char protocolo[18];
		unsigned tamanho;
		char informacao[100];

	public:
		void exibir(Pacote umPacote[], int posicao);
		
		
};

void Pacote::exibir(Pacote umPacote[], int posicao) 
{
	std::cout << umPacote[posicao].indice << "; ";
	std::cout << umPacote[posicao].tempo << "; ";
	std::cout << umPacote[posicao].origem << "; ";
	std::cout << umPacote[posicao].destino << "; ";
	std::cout << umPacote[posicao].protocolo << "; ";
	std::cout << umPacote[posicao].tamanho << "; ";
	std::cout << umPacote[posicao].informacao << std::endl;
}





#endif 