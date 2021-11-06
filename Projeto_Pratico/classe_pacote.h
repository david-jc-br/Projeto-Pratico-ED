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
		void exibir(Pacote umPacote, int posicao);
		
		
};

void Pacote::exibir(Pacote umPacote, int posicao) 
{
	std::cout << umPacote.indice << "; ";
	std::cout << umPacote.tempo << "; ";
	std::cout << umPacote.origem << "; ";
	std::cout << umPacote.destino << "; ";
	std::cout << umPacote.protocolo << "; ";
	std::cout << umPacote.tamanho << "; ";
	std::cout << umPacote.informacao << std::endl;
}





#endif 