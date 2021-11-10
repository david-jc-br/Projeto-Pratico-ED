#include <iostream>
#include <fstream>
#include "class_registro.h"

#ifndef VOID_ESCREVE_REGISTROS_H
#define VOID_ESCREVE_REGISTROS_H

void escreveOsRegistrosOrdenados ()
{
    std::ofstream arquivo_saida;

    arquivo_saida.open("captura_pacotes.bin", std::ios::trunc| std::ios::out);

    arquivo_saida.seekp(0,std::ios::beg); 
	
}

#endif