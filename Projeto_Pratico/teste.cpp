#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main () 
{
    FILE* arquivo = NULL;
 
    unsigned int teste[11] = {0,1,2,3,4,7,6,7,8,9,11};

    char *aux[33];
    
    char buffer[33];

    for (int i = 0; i < 11; i++) {
        aux[i] = itoa(teste[i], buffer, 16);
    }

    for (int i = 0; i < 33; i++) 
        cout << *aux[i] << endl;


    /*for (int i = 0; i < 11; i++) {
        letra = to_string(teste[i]);
        bufferAUX2[i] = letra[i];
    }

    arquivo = tmpfile();

    if (arquivo) {
        fputs(bufferAUX2,arquivo);
        fseek(arquivo, 0, SEEK_SET);
        fgets(buffer, 11, arquivo);

        fclose(arquivo);

       cout << "o conteúdo de arquivo é " << buffer << endl;
    }
    else {

       cout << "ok" << endl;

    }*/



    return 0;
}
