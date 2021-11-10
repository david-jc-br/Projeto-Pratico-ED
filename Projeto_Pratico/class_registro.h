//class_registro.h
#include <iostream> 
#include <fstream>
#include <cstring>

#ifndef CLASS_REGISTRO_H 
#define CLASS_REGISTRO_H

class  Registro 
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
		void merge(Registro umRegistro[], int tamanho, int escolha_ordenacao);
		void intercala (Registro umRegistro[], int pInicial, int q, int pFinal, int escolha_ordenacao);
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

void Registro::intercala(Registro umRegistro[], int inicio, int meio, int fim, int escolha_ordenacao){
    int i = inicio, j = meio;
    int tamanho = fim - inicio + 1;
    Registro *aux = new Registro [tamanho]; // vetor auxiliar
    int k = 0;
    while ((i < meio) && (j <= fim)) {
       if (escolha_ordenacao == 1) {                
            if (umRegistro[i].indice >= umRegistro[j].indice)  {
                aux[k++] = umRegistro[i++]; /* aux[k] = umRegistro[i]; k++; i++; */
		    } else  {
			    aux[k++] = umRegistro[j++]; /* aux[k] = umRegistro[j]; k++; j++; */
		    }
	    }
	    else {
		    if (strcmp(umRegistro[i].informacao,umRegistro[j].informacao) < 0)  {
                aux[k++] = umRegistro[i++]; /* aux[k] = umRegistro[i]; k++; i++; */
		    } else  {
			    aux[k++] = umRegistro[j++]; /* aux[k] = umRegistro[j]; k++; j++; */
		    }
		} 
	}
	// terminou um dos vetores, agora copia o outro                           
	while (i < meio) {
        aux[k++] = umRegistro[i++];
    }
    while (j <= fim) {
        aux[k++] = umRegistro[j++]; 
    }
    // agora copiamos do vetor auxiliar aux[] em umRegistro[inicio:fim]
	for (int m = 0; m < tamanho; m++){ 
		umRegistro[inicio + m] = aux[m];
    }
}   


void Registro::merge(Registro umRegistro[], int tam, int escolha_ordenacao) {
    int inicio, fim, bloco = 1;
    while (bloco < tam) {
        inicio = 0;
        while (inicio + bloco < tam) {
            fim = inicio + 2*bloco - 1;
            if (fim >= tam)  
                fim = tam - 1;
            intercala(umRegistro, inicio, inicio+bloco, fim, escolha_ordenacao);
            inicio = inicio + 2*bloco;
        }
        bloco = 2*bloco; // dobra o tamanho do bloco
    } 
}

#endif 
