#define MUSTAFARPNG "../assets/images/Mustafar.png"

#include "../include/Fase.h"

#include <iostream>
using namespace std;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include <SFML/Graphics.hpp>

short int TrabalhoJogo::Fases::Fase::cont(0);

TrabalhoJogo::Fases::Fase::Fase(Jogador* pJ): minInimigosFaceis(3), maxInimigosFaceis(15), nFase(cont++), gC(), pJog(pJ), pPlat()
{
    criarCenario();
    gC = new Gerenciador_Colisoes(pJ, pPlat);
}
TrabalhoJogo::Fases::Fase::~Fase()
{
    delete(gC);
    delete (pPlat);
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

    pPlat = new Plataforma();
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

sf::Sprite TrabalhoJogo::Fases::Fase::getPlataforma()
{
    return pPlat->getDrawData();
}