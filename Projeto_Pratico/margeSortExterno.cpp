#include <iostream>
#include <fstream>
#include <cstdio> // para remover arquivos
#include <cstdlib>

using namespace std;

//estrutura a ser lida do arquivo
struct Dado {
    public:
        int chave1;
        int chave2;
        float valor1;
        char campo1[5];
        char campo2[20];
        char lixo[500];  
};

bool intercalaBloco (ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    // consideramos incialmente que naão irá fazer nenhuma intercalação 
    bool intercalou = false;
    Dado dados[2];
    // posição relativa de leitura em cada um dos arquivos 
    int pos[2] = {0,0};
    
    /* variavél para informar se od dados do arquivo são válidos (se foram lidos do arquivo de entrada e ainda não gravados no arquivo de saída)*/

    bool valido[2] = {false, false};

    /*em cada passo de tamanho n lemos n dados de cada arquivo e fazemos a intercalação parcial em um novo bloco de 2*n no arquivo de saída ultilizado*/

    while (((pos[0] + pos[1] )) < (2*passo)) {
        // incialmente verificamos se há dados para ser lidos
        if ((pos[0] < passo) && (!valido[0])) {
            /*tentamos ler o arquivo verificando se a leitura foi válida */
            //leitura inválida -> final do arquivo
            if (auxE[0].read((char *) &dados[0] , sizeof(Dado))) {
                // cout << "leu arq1: " << auxE[0].tellg() << endl;
                valido[0] = true;
            }
            else {
                // para encerrar o while e não entrar no if novamente 
                pos[0] = passo;
                // cout << "arq1 terminou" << endl;
            }
        }

        //repetimos o processo para o segundo arquivo
        if ((pos[0] < passo) && (!valido[1])) {
            /*tentamos ler o arquivo verificando se a leitura foi válida */
            //leitura inválida -> final do arquivo
            if (auxE[1].read((char *) &dados[1] , sizeof(Dado))) {
                // cout << "leu arq1: " << auxE[0].tellg() << endl;
                valido[1] = true;
            }
            else {
                // para encerrar o while e não entrar no if novamente 
                pos[1] = passo;
                // cout << "arq1 terminou" << endl;
            }

            /* nesse momento temos dados lidos dos dois arquivos a 
            não ser que um (ou ambos) tenham chegado a o fim*/
            
            //1° caso, os dois dados são válidos 
            if (valido[0] && valido[1]) {
                // marca que intercalou
                intercalou = true;
                // gravamos o menor valor no arquivo de saída 
                if (dados[0].chave1 <= dados[1].chave1) {
                    auxS[saida].write((const char *) (&dados[0]), sizeof(Dado));
                    // dado utlizado não é mais válido, avança posição
                    valido[0] = false;
                    pos[0]++;
                }
                 else {
                     auxS[saida].write((const char *) (&dados[1].chave1), sizeof(Dado));
                     // dado ultilizado não é mais válido, avança posição 
                     valido[1] = false;
                     pos[1]++;
                 }          
            }
            //2° caso, apenas o primeiro dado é válido
            else if (valido[0]) {
                // marca que intercalou 
                intercalou = true;
                auxS[saida].write((const char *) (&dados[0].chave1), sizeof(Dado));
                // dado ultilizado não é mais válido, avança posição 
                valido[0] = false;
                pos[0]++;
            }
            // 3° caso, apenas o segundo dado é válido
            else if (valido[1]) {
                // marca que intercalou 
                intercalou = true;
                auxS[saida].write((const char *) (&dados[1].chave1), sizeof(Dado));
                // dado ultilizado não é mais válido, avança posição 
                valido[1] = false;
                pos[1]++;
            }
            // se chegou aqui, termina o whilw na próxima iteração
            else {
                //cout << "circulando, circulando..." << endl;
            }
        }
    }
    return intercalou;
}

void mergeexterno (ifstream &arqEntrada, ofstream &arqSaida){
    ofstream arqB1("arqB1.dat",ios::binary);
    ofstream arqB2("arqB2.dat",ios::binary);

    if ((!arqB1) | (!arqB2)){
        cerr << "Arquivos auxiliares não puderam ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    Dado umDado;

    //posicionando ponteiro de leitura no final do arquivo
    arqEntrada.seekg(0,ios::end);
    //obtendo a posicao final do arquivo
    int tamanho = arqEntrada.tellg();
    //dado o tamanho do arquivo, sabe-se quantos registros no arquivo
    int num_registros = tamanho / sizeof(Dado);
    //metade do numero de registro (arredondado pra cima)
    int metade = (num_registros / 2) + 0.5;
    
    //posicionado ponteiro de leitura no inicio do arquivo
    arqEntrada.seekg(0,ios::beg);

    //copiando os dados para os dois arquivo auxiliares
    for (int i = 0; i < metade; i++) {
        arqEntrada.read((char*) &umDado, sizeof(Dado));
        arqB1.write((char*) &umDado, sizeof(Dado));
    }
    for (int i = metade; i < num_registros; i++) {
        arqEntrada.read((char*) &umDado, sizeof(Dado));
        arqB2.write((char*) &umDado, sizeof(Dado));
    }

    //finalizaçao da primeira etapa
    arqB1.close();
    arqB2.close();
    arqEntrada.close();

    //arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    //variaveis de controle
    int passo = 1;
    bool ida = true;
    bool ultimo[2];

    //laço principal
    while (passo <= num_registros){
        if(ida){
            auxEntrada[0].open("arqB1.dat",ios::binary);
            auxEntrada[1].open("arqB2.dat",ios::binary);
            auxSaida[0].open("arqC1.dat",ios::binary);
            auxSaida[1].open("arqC2.dat",ios::binary);
        }
        else {
            auxEntrada[0].open("arqC1.dat",ios::binary);
            auxEntrada[1].open("arqC2.dat",ios::binary);
            auxSaida[0].open("arqB1.dat",ios::binary);
            auxSaida[1].open("arqB2.dat",ios::binary);
        }
        if ((! auxEntrada[0]) | (! auxEntrada[1]) | (! auxSaida[0]) | (! auxSaida[1])) {
            cerr << "Arquivos auxiliares não puderam abertos" << endl;
            exit(EXIT_FAILURE);
        }
        //enquanto não chegar ao final dos arquivos de entrada, vai intercalando os blocos
        while ((! auxEntrada[0].eof()) && (! auxEntrada[1].eof())){
            ultimo[0] = intercalaBloco(auxEntrada,auxSaida,passo,0);
            ultimo[1] = intercalaBloco(auxEntrada,auxSaida,passo,1);
        }
        
        //fecha os arquivos para permitir troca (escrita<->leitura) na próxima interação
        auxEntrada[0].close();
        auxEntrada[0].close();
        auxSaida[0].close();
        auxSaida[1].close();
        
        //prepara próxima interação, invertendo arquivos e dobrando tamanho do passo
        ida = !(ida);
        passo *= 2;
    }

    //merge terminando, agora lemos do arquivo auxiliar para arquivo de saida
    ifstream auxEnt;

    //identifica o arquivo auxiliar com dados ordenados
    if (ida) {
        if (ultimo[0]) {
            auxEnt.open ("arqB1.dat", ios::binary);
        }
        else {
            auxEnt.open ("arqB2.dat", ios::binary);
        }
    }
    else {
        if (ultimo[0]) {
            auxEnt.open ("arqC1.dat", ios::binary);
        }
        else {
            auxEnt.open ("arqC2.dat", ios::binary);
        }
    }

    if (! auxEnt) {
        cerr <<"Arquivo auxiliar não poder ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    while (auxEnt.read((char*)(&umDado),sizeof(Dado))) {
        arqSaida.write((const char*)(&umDado),sizeof(Dado));
    }

    auxEnt.close();

    //cereja do bolo, apagar arquivos auxiliares
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");
}

int main () {
    ifstream entrada("captura_pacotes.bin",ios::binary);
    ofstream saida("saida.bin",ios::binary);

    if (! entrada) {
        cerr <<"Arquivo de entrada não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    if (! saida) {
        cerr <<"Arquivo de saida não pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    mergeexterno(entrada,saida);
    
    entrada.close();
    saida.close();
    
    return 0;
    
}