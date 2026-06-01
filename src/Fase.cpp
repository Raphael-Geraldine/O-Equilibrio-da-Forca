#define MUSTAFARPNG "../assets/images/Mustafar.png"

#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;
using namespace Fases;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

short int Fase::cont(0);

Fase::Fase(Jogador* pJ): minInimigosFaceis(3), maxInimigosFaceis(15), nFase(cont++), gC(), pPlat()
{
    criarCenario();
    gC = new Gerenciador_Colisoes(pJ, pPlat);
}
Fase::~Fase()
{
    delete(gC);
    delete (pPlat);
}

void Fase::incluirEntidade(Entidade* pE) 
{
    listaEntidades.incluir(pE);
}

Listas::ListaEntidades* Fase::getListaEntidades() 
{
    return &listaEntidades;
}
void Fase::executar()
{

}
void Fase::criarInimigosFaceis()
{

}
void Fase::criarPlataformas()
{

}
void Fase::criarCenario()
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

sf::Sprite Fase::getFundo()
{
    //listaEntidades.executar();
    //bool g = gC->executar();
    //Em jogador por or:
    // if (g)
    //    pJog->gravity();
    return fundo;
}

sf::RectangleShape Fase::getGround()
{
    return ground;
}

sf::Sprite Fase::getPlataforma()
{
    return pPlat->getDrawData();
}