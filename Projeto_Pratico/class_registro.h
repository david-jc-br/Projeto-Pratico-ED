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
		void exibir(Registro umRegistro);
		
		
};

void Registro :: exibir(Registro umRegistro) 
{
	std::cout << umRegistro.indice << "; ";
	std::cout << umRegistro.tempo << "; ";
	std::cout << umRegistro.origem << "; ";
	std::cout << umRegistro.destino << "; ";
	std::cout << umRegistro.protocolo << "; ";
	std::cout << umRegistro.tamanho << "; ";
	std::cout << umRegistro.informacao << std::endl;
}





#endif 