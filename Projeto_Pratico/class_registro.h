//class_registro.h
#include <iostream> 
#include <fstream>
#include <cstring>

#ifndef CLASS_REGISTRO_H 
#define CLASS_REGISTRO_H

class Registro 
{
	private:
		unsigned int indice;
		float tempo;
		char origem[40];
		char destino[40];
		char protocolo[18];
		unsigned int tamanho;
		char informacao[100];

	public:
		void imprime();
		void mergeSortInterno(Registro umRegistro[], int tamanho, int escolha_ordenacao);
		void mergeSortInterno_AUX(Registro umRegistro[], int pInicial, int q, int pFinal, int escolha_ordenacao);

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

void Registro :: mergeSortInterno_AUX(Registro umRegistro[], int inicio, int meio, int fim, int escolha_ordenacao)
{
    int i = inicio, j = meio;
    int tamanho = fim - inicio + 1;
    Registro *aux = new Registro [tamanho]; 
    int k = 0;

    while ((i < meio) && (j <= fim)) 
	{
       if (escolha_ordenacao == 1) 
		{                
            if (umRegistro[i].indice >= umRegistro[j].indice)  
                aux[k++] = umRegistro[i++]; 
		    else  
			    aux[k++] = umRegistro[j++]; 
	    }
	    else 
		{
		    if (strcmp(umRegistro[i].informacao,umRegistro[j].informacao) < 0)  
                aux[k++] = umRegistro[i++];
		    else  
			    aux[k++] = umRegistro[j++];    
		} 
	}
	                           
	while (i < meio) {
        aux[k++] = umRegistro[i++];
	}
    
    while (j <= fim) {
        aux[k++] = umRegistro[j++]; 
	}
    
	for (int m = 0; m < tamanho; m++) 
		umRegistro[inicio + m] = aux[m];
	
}   

void Registro :: mergeSortInterno(Registro umRegistro[], int tam, int escolha_ordenacao) 
{
    int inicio, fim, bloco = 1;

    while (bloco < tam) 
	{
        inicio = 0;

        while (inicio + bloco < tam) 
		{
            fim = inicio + 2*bloco - 1;

            if (fim >= tam)  
                fim = tam - 1;

            mergeSortInterno_AUX(umRegistro, inicio, inicio+bloco, fim, escolha_ordenacao);

            inicio = inicio + 2*bloco;
        }
        bloco = 2*bloco; // dobra o tamanho do bloco
    } 
}

#endif 
