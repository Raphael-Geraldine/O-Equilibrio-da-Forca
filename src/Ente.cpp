#include "../include/Ente.h"
#include "../include/Gerenciador_Grafico.h"

#include <iostream>
using std::cout;
using std::endl;

// Inicializacao de atributos estaticos:
int OEquilibrioDaForca::Ente::cont = 0;

OEquilibrioDaForca::Gerenciadores::Gerenciador_Grafico* OEquilibrioDaForca::Ente::pGG = NULL;

OEquilibrioDaForca::Ente::Ente(): 
    id(cont++)
{
}

OEquilibrioDaForca::Ente::~Ente()
{
}

void OEquilibrioDaForca::Ente::desenhar()
{
    sf::RenderWindow* janela = pGG->getJanela();

    janela->draw(getDrawData());
}

void OEquilibrioDaForca::Ente::staticSetGG(
    OEquilibrioDaForca::Gerenciadores::Gerenciador_Grafico* pG
)
{
    pGG = pG;
}

int OEquilibrioDaForca::Ente::getID()
{
    return id;
}