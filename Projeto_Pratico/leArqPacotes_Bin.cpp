#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;


// dados armazenados no arquivo
struct pacote {
    unsigned indice;
    float tempo;
    char origem[40];
    char destino[40];
    char protocolo[18];
    unsigned tamanho;
    char informacao[100]; 
};


void le_arquivo_bin(ifstream& arquivo) {
    pacote *umPacote = new pacote[100000];
    int i = 0;
    while(arquivo.read((char*) &umPacote[i], sizeof(umPacote[i]))) {
        cout << umPacote[i].indice << "; ";
        cout << umPacote[i].tempo << "; ";
        cout << umPacote[i].origem << "; ";
        cout << umPacote[i].destino << "; ";
        cout << umPacote[i].protocolo << "; ";
        cout << umPacote[i].tamanho << "; ";
        cout << umPacote[i].informacao << endl;
        i++;
    }
    delete [] umPacote;
}


int main(){
    ifstream arquivo_bin_read("captura_pacotes.bin",ios::binary | ios::in);

    le_arquivo_bin(arquivo_bin_read);

    return 0;
}
