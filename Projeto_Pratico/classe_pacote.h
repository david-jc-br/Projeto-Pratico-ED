#include <iostream> 

#ifndef CLASSE_PACOTE_H 
#define CLASSE_PACOTE_H

class Pacote 
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
		void mostrar();
};


void Pacote :: mostrar() 
{
	std::cout << indice << std::endl;

}

#endif 