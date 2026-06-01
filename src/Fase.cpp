#define MUSTAFARPNG "../assets/images/Mustafar.png"

#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Listas;
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

Fase::Fase(): 
    minInimigosFaceis(3), 
    maxInimigosFaceis(15), 
    nFase(cont++), 
    gC(), 
    pPlat()
{
    criarCenario();
    gC = new Gerenciador_Colisoes(&listaEntidades);
}

Fase::~Fase()
{
    if (gC != nullptr)
    {
        delete gC;
        gC = nullptr;
    }

    if (pPlat != nullptr)
    {
        delete pPlat;
        pPlat = nullptr;
    }
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
        cout << "nao existe ainda"<<endl;
    }

    pPlat = new Plataforma();

    if (pPlat == nullptr)
        cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
    
    else   
        listaEntidades.incluir(pPlat);
}

void Fase::incluirEntidade(Entidade* pE) 
{
    if (pE == nullptr)
    {
        std::cerr << "Erro: tentativa de incluir entidade nula na fase." << std::endl;
        return;
    }

    listaEntidades.incluir(pE);
}

Listas::ListaEntidades* Fase::getListaEntidades() 
{
    return &listaEntidades;
}
void Fase::executar()
{
    listaEntidades.executar();
    
    if (gC != nullptr)
        gC->executar();
}
void Fase::criarInimigosFaceis()
{

}
void Fase::criarPlataformas()
{

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
    if (pPlat == NULL)
    {
        std::cerr << "Erro: pPlat nulo." << endl;
        return sf::Sprite();
    }

    return pPlat->getDrawData();
}

/*
void desenharFase(Fase* pF, sf::RenderWindow& janela) 
{
    if (pF == NULL) 
    {
        cerr << "Erro: Ponteiro para fase nulo." << endl;
        return;
    }

    pF->executar();

    janela.draw(pF->getFundo());
    janela.draw(pF->getGround());
    // janela.draw(pF->getPlataforma()); É entidade.

    ListaEntidades* lEntidades = pF->getListaEntidades();
    int tamanho = static_cast<int> ((pF->getListaEntidades())->getTamanho());

    for (int i = 0; i < tamanho; i++) 
    {
        if (lEntidades == NULL) 
            cout << "Lista de entidades vazia." << endl;
        
        janela.draw((*lEntidades)[i]->getDrawData());
    }

    janela.display();
}
*/