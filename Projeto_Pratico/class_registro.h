//class_registro.h
#include <iostream> 
#include <fstream>

#ifndef CLASS_REGISTRO_H 
#define CLASS_REGISTRO_H

class  Registro 
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
		void imprime();
};

void Registro :: imprime() 
{
	std::cout << indice << "; ";
	std::cout << tempo << "; ";
	std::cout << origem << "; ";
	std::cout << destino << "; ";
	std::cout << protocolo << "; ";
	std::cout << tamanho << "; ";
	std::cout << informacao << std::endl;
}

#endif 