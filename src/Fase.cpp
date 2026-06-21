#include "../include/Entidade.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
#include "../include/Plataforma.h"
#include "../include/Projetil.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
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

Fase::Fase(): 
    minInimigosFaceis(3), 
    maxInimigosFaceis(15), 
    minPlat(3),
    maxPlat(6),
    entsAlive(0),
    nJogs(0),
    Ente(),
    //nFase(cont++), 
    pJogador1(NULL),
    pJogador2(NULL),
    gC(NULL)
{
    gC = new Gerenciador_Colisoes();
    
    if (gC != NULL)
        gC->incluirChao(&chao); 
}

Fase::~Fase()
{
    if (gC != NULL)
    {
        delete gC;
        gC = NULL;
    }

    // Ver se não é entidade.
    //if (pPlat != NULL)
    //{
    //    delete pPlat;
    //    pPlat = NULL;
    //}

    int tamanhoEnt = listaEntidades.getTamanho();
    
    for (int i = 0; i < tamanhoEnt; i++) 
    {
        Entidade* pEnt = listaEntidades[i];

        if (pEnt != NULL)
        {   
            if (pJogador1 != NULL && (pEnt->getID() != pJogador1->getID()))
            {   
                if (pJogador2 == NULL)
                {
                    delete pEnt;
                }
                else if (pEnt->getID() != pJogador2->getID())
                    delete pEnt;
            }
        }
    }

    listaEntidades.limpar();

    pJogador1 = NULL;
    pJogador2 = NULL;
}

void Fase::inicializar(Jogador* pJ1, Jogador* pJ2)
{
    if (pJ1 != NULL)
    {
        incluirEntidade(pJ1);
        if (gC != NULL)
            gC->setJog1(pJ1);
        pJogador1=pJ1;
        nJogs++;
    }

    if (pJ2 != NULL)
    {
        incluirEntidade(pJ2);
        if (gC != NULL)
            gC->setJog2(pJ2);
        pJogador2=pJ2;
        nJogs++;
    }
    
    criarInimigosFaceis();   
    criarInimigos();
    criarCenario(); //as plataformas são criadas a partir daqui
    criarObstaculos();
}

void Fase::incluirEntidade(Entidade* pE)
{
    if (pE == NULL)
        cerr << "Erro: Tentativa de incluir entidade nula em fase." << endl;
    else
        listaEntidades.incluir(pE);
}

void Fase::incluirGCInimigo(Inimigo* pInim)
{
    if (pInim == NULL)
        cerr << "Erro: Tentativa de incluir inimigo nulo em GC." << endl;
    else if (gC != NULL)
        gC->incluirInimigo(pInim); 
}

void Fase::incluirGCObstaculo(Obstaculo* pObs)
{
    if (pObs == NULL)
        cerr << "Erro: Tentativa de incluir obstaculo nulo em GC." << endl;
    else if (gC != NULL)
        gC->incluirObstaculo(pObs);
}

void Fase::incluirGCProjetil(Projetil* pProj)
{
    if (pProj == NULL)
        cerr << "Erro: Tentativa de incluir projétil nulo em GC." << endl;
    else if (gC != NULL)
        gC->incluirProjetil(pProj);
}

void Fase::criarCenario()
{
    chao.setSize(sf::Vector2f(1280,15));
    sf::Color brown(27,14,10,255);
    chao.setFillColor(brown);
    chao.setPosition(0, 710);

    criarPlataformas();
}

ListaEntidades* Fase::getListaEntidades()
{
    return &listaEntidades;
}

void Fase::executar()
{
    int tamEnt = listaEntidades.getTamanho();

    for (int i = 0; i < tamEnt; i++)
    {
        if (listaEntidades[i] == NULL) 
            continue;
        
        Entidade* pEnt = listaEntidades[i];
        
        Inimigo* pInim = dynamic_cast<Inimigo*>(pEnt);

        if (pInim != NULL && pInim->getVida() <= 0)
        {
            if (gC != NULL)
                gC->removerInimigo(pInim);

            listaEntidades.remover(pInim);

            delete(pInim);
            pInim = NULL;

            i--; // pois não pode ser acrescido na prox. iteração
            entsAlive--;
        }
    }

    if (pJogador2 != NULL)
    {
        if ((pJogador1 != NULL && pJogador1->getVida() <= 0) && (pJogador2 != NULL && pJogador2->getVida() <= 0))
            nJogs=0;
        else if ((pJogador1 != NULL && pJogador1->getVida() <= 0) || (pJogador2 != NULL && pJogador2->getVida() <= 0))
            nJogs=1;
    }
    else if (pJogador1 != NULL && pJogador1->getVida() <= 0)
        nJogs=0;

    listaEntidades.executar();

    if (gC != NULL)
        gC->executar();

    /*
    NÃO FUNCIONOU:
    bool aplicarGravidade = true;

    if (gC != NULL)
        aplicarGravidade = gC->executar();

    if(aplicarGravidade)
    {
        if (pJogador1 != NULL)
        pJogador1->gravity();

        if (pJogador2 != NULL)
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
        if (pStorm == NULL)
            cerr << "Tentativa de incluir Stormtrooper nula na lista de entidades." << endl;
        else
        {
            incluirEntidade(static_cast<Inimigo*>(pStorm));
            incluirGCInimigo(static_cast<Inimigo*>(pStorm)); 
            entsAlive++;
        }
    }
}

void Fase::criarPlataformas()
{
    int qntd = rand()%(maxPlat-minPlat+1) + minPlat;
    platGeradas += qntd;
    for (int i = 0; i < qntd; i++)
    {
        Plataforma* pPlat = new Plataforma();
        if (pPlat == NULL)
            cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
        else
        {
            incluirEntidade(static_cast<Obstaculo*>(pPlat));
            incluirGCObstaculo(static_cast<Obstaculo*>(pPlat));
        }   
    }
}

short int Fase::numJogsVivos() const
{
    //cout<<nJogs<<endl;
    return nJogs;
}

short int Fase::getInimVivos() const
{
    return entsAlive;
}

void Fase::increaseInimVivos()
{
    entsAlive++;
}

sf::RectangleShape Fase::getChao() const
{
    return chao;
}
void Fase::increasePlatGeradas()
{
    platGeradas++;
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