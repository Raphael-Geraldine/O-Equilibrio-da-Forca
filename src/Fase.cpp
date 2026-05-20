#define MUSTAFARPNG "../assets/images/Mustafar.png"

//#define MUSTAFARPNG "mustafar.png"

#include "../include/Fase.h"

#include <iostream>
using namespace std;

#include <SFML/graphics.hpp>

short int TrabalhoJogo::Fases::Fase::cont(0);

TrabalhoJogo::Fases::Fase::Fase(): minInimigosFaceis(3), maxInimigosFaceis(15), nFase(cont++)
{
    if (nFase == 0)
    {
        if (!texturaFundo.loadFromFile(MUSTAFARPNG))
        {
            cerr << "Erro de carregamento do Plano de Fundo de Mustafar" << endl;
        }
        else
        {
            fundo.setTexture(texturaFundo); 
        }
    }
    else
    {
        cout<<"nao existe ainda"<<endl;
    }
}
TrabalhoJogo::Fases::Fase::~Fase()
{

}
void TrabalhoJogo::Fases::Fase::executar()
{

}
void TrabalhoJogo::Fases::Fase::criarInimigosFaceis()
{

}
void TrabalhoJogo::Fases::Fase::criarPlataformas()
{

}
void TrabalhoJogo::Fases::Fase::criarCenario()
{

}

sf::Sprite TrabalhoJogo::Fases::Fase::getFundo()
{
    return fundo;
}