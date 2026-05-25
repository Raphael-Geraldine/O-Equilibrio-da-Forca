#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include "../include/Ente.h"

#include <iostream>
using namespace std;

int TrabalhoJogo::Ente::cont(0);

TrabalhoJogo::Ente::Ente(): id(cont++)
{}

TrabalhoJogo::Ente::~Ente()
{}

void TrabalhoJogo::Ente::desenhar()
{
    cout<<id<<endl;
}
void TrabalhoJogo::Ente::staticSetGG(Gerenciador_Grafico* pG)
{
    cout<<"ok"<<endl;
}