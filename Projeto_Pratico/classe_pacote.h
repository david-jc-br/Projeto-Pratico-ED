#include <iostream>

#ifndef CLASSE_PACOTE_H 
#define CLASSE_PACOTE_H

class Pacote 
{
	private:
		unsigned indice;
		float tempo;
		char *origem;
		char *destino;
		char *protocolo;
		unsigned tamanho;
		char *informacao;

	public:
		Pacote();
		~Pacote();
		void inserir();
};

Pacote :: Pacote()
{
    origem = new char[40];
    destino = new char[40];
    protocolo = new char[18];
    informacao = new char[100];
}

Pacote :: ~Pacote() 
{
    delete [] origem;
    delete [] destino;
    delete [] protocolo;
    delete [] informacao;
}

void Pacote :: inserir () 
{
    std::cout << "hello" << std::endl;
}

#endif /* CLASSE_PACOTE_H */