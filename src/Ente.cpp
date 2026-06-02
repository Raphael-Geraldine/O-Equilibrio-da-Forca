#include "../include/Ente.h"
#include "../include/Gerenciador_Grafico.h"

#include <iostream>
using std::cout;
using std::endl;

// Inicializacao de atributos estaticos:
int TrabalhoJogo::Ente::cont = 0;

TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* TrabalhoJogo::Ente::pGG = nullptr;

TrabalhoJogo::Ente::Ente(): 
    id(cont++)
{
}

TrabalhoJogo::Ente::~Ente()
{
}

void TrabalhoJogo::Ente::desenhar()
{
    cout << id << endl;
}

void TrabalhoJogo::Ente::staticSetGG(
    TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* pG
)
{
    pGG = pG;
}