#define MUSTAFARPNG "../assets/images/Mustafar.png"

//#define MUSTAFARPNG "mustafar.png"

#include "../include/Fase.h"

#include <iostream>
using namespace std;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include <SFML/graphics.hpp>

short int TrabalhoJogo::Fases::Fase::cont(0);

TrabalhoJogo::Fases::Fase::Fase(Jogador* pJ): minInimigosFaceis(3), maxInimigosFaceis(15), nFase(cont++), gC(), pJog(pJ)
{
    criarCenario();
    gC = new Gerenciador_Colisoes(pJ);
}
TrabalhoJogo::Fases::Fase::~Fase()
{
    delete(gC);
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
    ground.setSize(sf::Vector2f(1280,15));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 710);
    
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

sf::Sprite TrabalhoJogo::Fases::Fase::getFundo()
{
    pJog->mover();
    bool g = gC->executar();
    if (g)
        pJog->gravity();
    return fundo;
}

sf::RectangleShape TrabalhoJogo::Fases::Fase::getGround()
{
    return ground;
}