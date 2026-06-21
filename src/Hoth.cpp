#define HOTHPNG "../assets/images/Hoth.png"

#include "../include/AT_ST.h"
#include "../include/Gelo.h"
#include "../include/Entidade.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Projetil.h"
#include "../include/Obstaculo.h"
#include "../include/Plataforma.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Hoth.h"
using namespace OEquilibrioDaForca;
using namespace Listas;
using namespace Entidades;
using namespace Obstaculos;
using namespace Fases;
using namespace Gerenciadores;

#include <stdlib.h>

Hoth::Hoth(Jogador* pJ1, Jogador* pJ2): 
    Fase(),
    minChefoes(3),
    maxChefoes(6),
    minObstDificil(3),
    maxObstDificil(4)
{   
    sf::Texture* pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(HOTHPNG);
        
    if (pTexturaFundo == 0)
        cerr << "Erro de carregamento do Plano de Fundo de Hoth" << endl;

    else
        fundo.setTexture(*pTexturaFundo); 
    
    for (int i = platGeradas; i < maxPlat; i++)
    {
        Plataforma* pClearList = new Plataforma();
        platGeradas++;
        delete (pClearList);
    }
    
    inicializar(pJ1,pJ2);
}

Hoth::Hoth(Jogador* pJ1, Jogador* pJ2, char c): 
    Fase(),
    minChefoes(3),
    maxChefoes(6),
    minObstDificil(3),
    maxObstDificil(4)
{   
    sf::Texture* pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(HOTHPNG);
        
    if (pTexturaFundo == 0)
        cerr << "Erro de carregamento do Plano de Fundo de Hoth" << endl;

    else
        fundo.setTexture(*pTexturaFundo); 
    
    for (int i = platGeradas; i < maxPlat; i++)
    {
        Plataforma* pClearList = new Plataforma();
        platGeradas++;
        delete (pClearList);
    }
    
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

    chao.setSize(sf::Vector2f(1280,15));
    sf::Color brown(27,14,10,255);
    chao.setFillColor(brown);
    chao.setPosition(0, 710);
}

Hoth::~Hoth()
{
    for (int i = platGeradas; i < 2*maxPlat; i++)
    {
        Plataforma* pClearList = new Plataforma();
        delete (pClearList);
    }
    platGeradas=0;
}

void Hoth::criarInimigos()
{
    int qntd = rand()%(maxChefoes-minChefoes+1) + minChefoes;
    for (int i = 0; i < qntd; i++)
    {
        AT_ST* pAT = new AT_ST();
        if (pAT == NULL)
            cerr << "Tentativa de incluir AT-ST nula na lista de entidades." << endl;
        else
        {
            Fase::incluirEntidade(static_cast<Inimigo*>(pAT));
            incluirGCInimigo(static_cast<Inimigo*>(pAT)); 
            criarProjeteis(qntd, pAT);
            pAT->setAlvos(pJogador1, pJogador2);
            entsAlive++;
        } 
    }
}

void Hoth::criarObstaculos()
{
    int qntd = rand()%(maxObstDificil-minObstDificil+1) + minObstDificil;
    for (int i = 0; i < qntd; i++)
    {
        Gelo* pGelo = new Gelo();
        if (pGelo == NULL)
            cerr << "Tentativa de incluir gelo nula na lista de entidades." << endl;
        else   
        {
            Fase::incluirEntidade(static_cast<Obstaculo*>(pGelo));
            incluirGCObstaculo(static_cast<Obstaculo*>(pGelo));
        }
    }
}

void Hoth::criarProjeteis(int qntd, AT_ST* pAT)
{
    int random = rand()%11;
    Projetil* pProj = new Projetil(5+random);
    if (pProj == NULL)
        cerr << "Tentativa de incluir projetil nulo na lista de entidades." << endl;
    else
    {
        Fase::incluirEntidade(pProj); 
        incluirGCProjetil(pProj);
        pAT->setProjetil(pProj);           
    }   
}

sf::Sprite Hoth::getDrawData() const
{
    return fundo;
}
