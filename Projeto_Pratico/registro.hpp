//class_registro.h
#include <iostream> 
#include <fstream>
#include <cstring>

#ifndef CLASS_REGISTRO_HPP 
#define CLASS_REGISTRO_HPP

class Registro {
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
        void intercalacaoInterna(Registro umRegistro[], int pInicial, int q, int pFinal, int escolha_ordenacao);
        void mergeSortExterno (std::ofstream &arqSaida, int escolha_ordenacao , int qtd_registro);
        void intercalacaoExterna (std::ifstream auxE[2], std::ofstream &auxS, int passo, int escolha_ordenacao);
};

void Registro :: imprime() {
    std::cout << indice << "; ";
    std::cout << tempo << "; ";
    std::cout << origem << "; ";
    std::cout << destino << "; ";
    std::cout << protocolo << "; ";
    std::cout << tamanho << "; ";
    std::cout << informacao << std::endl;
}

void Registro :: intercalacaoInterna(Registro umRegistro[], int inicio, int meio, int fim, int escolha_ordenacao) {
    int i = inicio, j = meio;
    int tamanho = fim - inicio + 1;
    Registro *aux = new Registro [tamanho]; 
    int k = 0;

    while ((i < meio) && (j <= fim)) {
        if (escolha_ordenacao == 1) {                
            if (umRegistro[i].indice >= umRegistro[j].indice)  
                aux[k++] = umRegistro[i++]; 
            else  
                aux[k++] = umRegistro[j++]; 
        }
        else  {
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

void Registro :: mergeSortInterno(Registro umRegistro[], int tam, int escolha_ordenacao) {
    int inicio, fim, bloco = 1;

    while (bloco < tam) {
        inicio = 0;

        while (inicio + bloco < tam) {
            fim = inicio + 2*bloco - 1;

            if (fim >= tam)  
                fim = tam - 1;

            intercalacaoInterna(umRegistro, inicio, inicio+bloco, fim, escolha_ordenacao);
            inicio = inicio + 2*bloco;
        }
        bloco = 2*bloco; // dobra o tamanho do bloco
    } 
}

void Registro :: intercalacaoExterna (std::ifstream auxE[2], std::ofstream &auxS, int passo, int escolha_ordenacao) { 
    Registro dados[2];
    // posição relativa de leitura em cada um dos arquivos 
    int pos[2] = {0,0};
    
    //variavél para informar se os dados do arquivo são válidos
    bool valido[2] = {false, false};

    while (((pos[0] + pos[1] )) < (2*passo)) {
        // incialmente verificamos se há dados para ser lidos
        if ((pos[0] < passo) && (! valido[0])) {
            /*tentamos ler o arquivo verificando se a leitura foi válida */
            if (auxE[0].read((char *) &dados[0] , sizeof(Registro))) 
                valido[0] = true;
            else 
                pos[0] = passo;
        }

        //repetimos o processo para o segundo arquivo
        if ((pos[1] < passo) && (! valido[1])) {
            if (auxE[1].read((char *) &dados[1] , sizeof(Registro))) 
                valido[1] = true;
            else 
                pos[1] = passo;
        }
            
        //1° caso, os dois dados são válidos 
        if (valido[0] && valido[1]) {
            if (dados[0].indice >= dados[1].indice && escolha_ordenacao == 1) {
                //gravamos o maior valor no arquivo de saída
                auxS.write((const char *) (&dados[0]), sizeof(Registro));
                valido[0] = false;
                pos[0]++;
            }
            else if ((strcmp(dados[0].informacao,dados[1].informacao) < 0) && escolha_ordenacao == 2) {
                //gravamos o menor valor no arquivo de saída 
                auxS.write((const char *) (&dados[0]), sizeof(Registro));
                valido[0] = false;
                pos[0]++;
            }
            else {
                auxS.write((const char *) (&dados[1].indice), sizeof(Registro));
                valido[1] = false;
                pos[1]++;
            }          
        }
        //2° caso, apenas o primeiro dado é válido
        else if (valido[0]) {
            auxS.write((const char *) (&dados[0].indice), sizeof(Registro)); 
            valido[0] = false;
            pos[0]++;
        }
        // 3° caso, apenas o segundo dado é válido
        else if (valido[1]) {
            auxS.write((const char *) (&dados[1].indice), sizeof(Registro));
            valido[1] = false;
            pos[1]++;
        }
    }
}

void Registro :: mergeSortExterno (std::ofstream &arqSaida, int escolha_ordenacao, int qtd_registro) {
    Registro umDado;

    //arquivos auxiliares
    std::ifstream auxEntrada[2];
    std::ofstream auxSaida;

    //variavel para controle no intercalamento
    int passo = (qtd_registro/2) + 0.5;
   
    auxEntrada[0].open("arqTemp1.bin",std::ios::binary);
    auxEntrada[1].open("arqTemp2.bin",std::ios::binary);
    auxSaida.open("arqTemp3.bin",std::ios::binary);
   
    if ((! auxEntrada[0]) | (! auxEntrada[1]) | (! auxSaida)) {
        std::cerr << "Arquivos auxiliares não puderam ser abertos" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //enquanto não chegar ao final dos arquivos de entrada, vai intercalando o bloco
    while ((! auxEntrada[0].eof()) && (! auxEntrada[1].eof())) {
        intercalacaoExterna(auxEntrada,auxSaida,passo,escolha_ordenacao);
    }
        
    //fecha os arquivos para permitir troca (escrita<->leitura) na próxima interação
    auxEntrada[0].close();
    auxEntrada[1].close();
    auxSaida.close();   

    std::ifstream auxEnt;
    auxEnt.open ("arqTemp3.bin", std::ios::binary);
    
    if (! auxEnt) {
        std::cerr <<"Arquivo auxiliar não poder ser aberto" << std::endl;
        exit(EXIT_FAILURE);
    }

    //agora lemos do arquivo auxiliar para arquivo de saida
    while (auxEnt.read((char*)(&umDado),sizeof(Registro))) {
        arqSaida.write((const char*)(&umDado),sizeof(Registro));
    }

    auxEnt.close();
}

#endif 
