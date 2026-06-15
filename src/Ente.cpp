#include "../include/Ente.h"
#include "../include/Gerenciador_Grafico.h"

#include <iostream>
using std::cout;
using std::endl;

// Inicializacao de atributos estaticos:
int OEquilibrioDaForca::Ente::cont = 0;

OEquilibrioDaForca::Gerenciadores::Gerenciador_Grafico* OEquilibrioDaForca::Ente::pGG = nullptr;

OEquilibrioDaForca::Ente::Ente(): 
    id(cont++)
{
}

OEquilibrioDaForca::Ente::~Ente()
{
}

void OEquilibrioDaForca::Ente::desenhar()
{
    cout << id << endl;
}

void OEquilibrioDaForca::Ente::staticSetGG(
    OEquilibrioDaForca::Gerenciadores::Gerenciador_Grafico* pG
)
{
    pGG = pG;
}