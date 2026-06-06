#include "../include/Entidade.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
#include "../include/Plataforma.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Grafico.h"
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

#include <stdlib.h>

short int Fase::cont(0);

Fase::Fase(Jogador* pJ1, Jogador* pJ2): 
    minInimigosFaceis(3), 
    maxInimigosFaceis(15), 
    minPlat(3),
    maxPlat(6),
    Ente(),
    nFase(cont++), 
    gC(nullptr),
    pJogador1(pJ1),
    pJogador2(pJ2),
    pPlat(nullptr) // Mudar depois eventualmente
{
    gC = new Gerenciador_Colisoes(&listaJogadores, &listaObstaculos, &listaInimigos, &ground);
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

    if (listaInimigos.getTamanho() != 0)
        listaInimigos.limpar();


    int tamanhoEnt = listaEntidades.getTamanho();
    
    for (int i = 0; i < tamanhoEnt; i++) 
    {
        Entidade* pEnt = listaEntidades[i];
        
        if (pEnt != nullptr) 
        {
            Jogador* testPlayer = dynamic_cast<Jogador*>(pEnt);
            
            if (testPlayer == nullptr) 
            {
                delete pEnt; 
            }
        }
    }
    listaEntidades.limpar();
}

void Fase::inicializar(Jogador* pJ1, Jogador* pJ2)
{
    if (pJ1 != nullptr)
        incluirEntidade(pJ1);

    if (pJ2 != nullptr)
        incluirEntidade(pJ2);
    
    criarInimigosFaceis();    
    criarCenario(); //as plataformas são criadas a partir daqui
}

void Fase::criarCenario()
{
    ground.setSize(sf::Vector2f(1280,15));
    sf::Color brown(27,14,10,255);
    ground.setFillColor(brown);
    ground.setPosition(0, 710);

    criarPlataformas();
}

ListaEntidades* Fase::getListaEntidades() 
{
    return &listaEntidades;
}
void Fase::executar()
{
    int tamInim = listaInimigos.getTamanho();
    for (int i = 0; i < tamInim; i++)
    {
        if (listaInimigos[i]->getVida() <= 0)
        {
            Inimigo* inimMorto = listaInimigos[i];
            delete(inimMorto);
            listaEntidades.remover(inimMorto);
            listaInimigos.remover(i);
            i--; // pois não pode ser acrescido na prox. iteração
            tamInim--;
        }
    }

    listaEntidades.executar();

    if (gC != nullptr)
        gC->executar();
    /*
    NÃO FUNCIONOU:
    bool aplicarGravidade = true;

    if (gC != nullptr)
        aplicarGravidade = gC->executar();

    if(aplicarGravidade)
    {
        if (pJogador1 != nullptr)
        pJogador1->gravity();

        if (pJogador2 != nullptr)
        pJogador2->gravity();
    }
        
    listaEntidades.executar();
    
    */
}

void Fase::criarInimigosFaceis()
{
    int qntd = rand()%(maxInimigosFaceis-minInimigosFaceis+1) + minInimigosFaceis;
    for (int i = 0; i < qntd; i++)
    {
        Stormtrooper* pStorm = new Stormtrooper();
        if (pStorm == nullptr)
            cerr << "Tentativa de incluir Stormtrooper nula na lista de entidades." << endl;
        else
            incluirEntidade(static_cast<Inimigo*>(pStorm)); 
    }
}

void Fase::criarPlataformas()
{
    int qntd = rand()%(maxPlat-minPlat+1) + minPlat;
    for (int i = 0; i < 6; i++)
    {
        Plataforma* pPlat = new Plataforma();
        if (pPlat == nullptr)
            cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
        else   
            incluirEntidade(static_cast<Obstaculo*>(pPlat));
    }
}

sf::RectangleShape Fase::getGround()
{
    return ground;
}

/*
sf::Sprite Fase::getPlataforma() // a princípo não usamos mais, pode apagar
{
    if (pPlat == NULL)
    {
        std::cerr << "Erro: pPlat nulo." << endl;
        return sf::Sprite();
    }

    return pPlat->getDrawData();
}


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