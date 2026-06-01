#include "../include/Gerenciador_Grafico.h"
#include "../include/Ente.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


int Ente::cont(0);

Ente::Ente(): id(cont++)
{}

Ente::~Ente()
{}

void Ente::desenhar()
{
    cout<<id<<endl;
}
void staticSetGG(Gerenciador_Grafico* pG)
{
    cout<<"ok"<<endl;
}