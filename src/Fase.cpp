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

//short int Fase::cont(0);

short int Fase::platGeradas(0);

Fase::Fase(Jogador* pJ1, Jogador* pJ2): 
    minInimigosFaceis(3), 
    maxInimigosFaceis(15), 
    minPlat(3),
    maxPlat(6),
    entsAlive(0),
    Ente(),
    //nFase(cont++), 
    pJogador1(pJ1),
    pJogador2(pJ2),
    gC(nullptr)
{
    gC = new Gerenciador_Colisoes(pJogador1, &chao);

    if (pJogador2 != nullptr)
    {
        gC->setJog2(pJogador2);
    }
}

Fase::~Fase()
{
    if (gC != nullptr)
    {
        delete gC;
        gC = nullptr;
    }

    // Ver se não é entidade.
    //if (pPlat != nullptr)
    //{
    //    delete pPlat;
    //    pPlat = nullptr;
    //}

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

    pJogador1 = nullptr;
    pJogador2 = nullptr;
}

void Fase::inicializar(Jogador* pJ1, Jogador* pJ2)
{
    if (pJ1 != nullptr)
        incluirEntidade(pJ1);

    if (pJ2 != nullptr)
        incluirEntidade(pJ2);
    
    criarInimigosFaceis();   
    criarInimigos();
    criarCenario(); //as plataformas são criadas a partir daqui
    criarObstaculos();
}

void Fase::incluirEntidade(Entidade* pE)
{
    if (pE == nullptr)
    {
        cerr << "Erro: Tentativa de incluir entidade nula em fase." << endl;
        return;
    }

    listaEntidades.incluir(pE);

    // Dynamic_cast testa se conversão é razoável, senão retorna nulo.
    Jogador* pJog = dynamic_cast<Jogador*>(pE); 

    if (pJog != nullptr)
    {
        if (pJogador1 == nullptr)
        {
            pJogador1 = pJog;

            if (gC != nullptr)
                gC->setJog1(pJog);
        }
        else if (pJogador2 == nullptr && pJog != pJogador1)
        {
            pJogador2 = pJog;

            if (gC != nullptr)
                gC->setJog2(pJog);
        }

        return;
    }

    Inimigo* pInim = dynamic_cast<Inimigo*>(pE);

    if (pInim != nullptr)
    {
        if (gC != nullptr)
            gC->incluirInimigo(pInim);

        return;
    }

    Obstaculo* pObs = dynamic_cast<Obstaculo*>(pE);

    if (pObs != nullptr)
    {
        if (gC != nullptr)
            gC->incluirObstaculo(pObs);

        return;
    }
}

void Fase::criarCenario()
{
    chao.setSize(sf::Vector2f(1280,15));
    sf::Color brown(27,14,10,255);
    chao.setFillColor(brown);
    chao.setPosition(0, 710);

    criarPlataformas();
}

const ListaEntidades* Fase::getListaEntidades() const
{
    return &listaEntidades;
}

void Fase::executar()
{
    int tamEnt = listaEntidades.getTamanho();

    for (int i = 0; i < tamEnt; i++)
    {
        if (listaEntidades[i] == nullptr) 
            continue;
        
        Entidade* pEnt = listaEntidades[i];
        
        Inimigo* pInim = dynamic_cast<Inimigo*>(pEnt);

        if (pInim != nullptr && pInim->getVida() <= 0)
        {
            if (gC != nullptr)
                gC->removerInimigo(pInim);

            listaEntidades.remover(pInim);

            delete(pInim);
            pInim = nullptr;

            i--; // pois não pode ser acrescido na prox. iteração
            entsAlive--;
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
        {
            incluirEntidade(static_cast<Inimigo*>(pStorm)); 
            entsAlive++;
        }
    }
}

void Fase::criarPlataformas()
{
    platGeradas = rand()%(maxPlat-minPlat+1) + minPlat;
    for (int i = 0; i < platGeradas; i++)
    {
        Plataforma* pPlat = new Plataforma();
        if (pPlat == nullptr)
            cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
        else   
            incluirEntidade(static_cast<Obstaculo*>(pPlat));
    }
}

short int Fase::getVivos() const
{
    return entsAlive;
}

sf::RectangleShape Fase::getChao() const
{
    return chao;
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