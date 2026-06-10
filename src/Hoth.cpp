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
using namespace TrabalhoJogo;
using namespace Listas;
using namespace Entidades;
using namespace Obstaculos;
using namespace Fases;
using namespace Gerenciadores;

#include <stdlib.h>

Hoth::Hoth(Jogador* pJ1, Jogador* pJ2): 
    Fase(pJ1, pJ2),
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
        delete (pClearList);
    }
    
    inicializar(pJ1,pJ2);
    //criarObstaculos();
    //criarInimigos();
}

Hoth::~Hoth()
{

}

void Hoth::criarInimigos()
{
    int qntd = rand()%(maxChefoes-minChefoes+1) + minChefoes;
    for (int i = 0; i < qntd; i++)
    {
        AT_ST* pAT = new AT_ST();
        if (pAT == nullptr)
            cerr << "Tentativa de incluir AT-ST nula na lista de entidades." << endl;
        else
        {
            Fase::incluirEntidade(static_cast<Inimigo*>(pAT));
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
        if (pGelo == nullptr)
            cerr << "Tentativa de incluir gelo nula na lista de entidades." << endl;
        else   
            Fase::incluirEntidade(static_cast<Obstaculo*>(pGelo));
    }
}

void Hoth::criarProjeteis(int qntd, AT_ST* pAT)
{
    int random = rand()%11;
    Projetil* pProj = new Projetil(20+random);
    if (pProj == nullptr)
        cerr << "Tentativa de incluir projetil nulo na lista de entidades." << endl;
    else
    {
        Fase::incluirEntidade(pProj); 
        pAT->setProjetil(pProj);           
    }   
}

sf::Sprite Hoth::getDrawData() const
{
    return fundo;
}

/*
void Hoth::incluirEntidade(Entidade* pE) 
{
    if (pE == nullptr)
    {
        std::cerr << "Erro: tentativa de incluir entidade nula na fase." << std::endl;
        return;
    }

    // Inspiração no menu do Sistema Acadêmico, visto em sala,
    // durante aula do Prof. Dr. Jean Simão.
    switch (pE->getID())
    {
        // Depois restringir ao usar inimigos e afins.
        case jogador:
        {
            incluirJogador(static_cast<Jogador*>(pE));
            break;
        }

        case inimigo:
        {
            incluirInimigo(static_cast<Inimigo*>(pE));
            break;
        }

        case obstaculo:
        {
            incluirObstaculo(static_cast<Obstaculo*>(pE));
            break;
        }

        default:
        {
            listaEntidades.incluir(pE);
            break;
        }
    }
}

void Hoth::incluirJogador(Jogador* pJ)
{
    if (pJ == nullptr)
    {
        cerr << "Erro: tentativa de incluir jogador nulo na fase." << endl;
        return;
    }

    if (listaJogadores.getTamanho() >= 2)
    {
        cerr << "Erro: a fase suporta no maximo 2 jogadores." << endl;
        return;
    }

    listaEntidades.incluir(pJ);
    listaJogadores.incluir(pJ);
}

void Hoth::incluirInimigo(Inimigo* pI)
{
    if (pI == nullptr)
    {
        cerr << "Erro: tentativa de incluir inimigo nulo na fase." << endl;
        return;
    }

    if (listaInimigos.getTamanho() >= 45)
    {
        cerr << "Erro: a fase suporta no maximo 45 inimigos." << endl;
        return;
    }

    listaEntidades.incluir(static_cast<Entidade*>(pI));
    listaInimigos.incluir(pI);
}

void Hoth::incluirObstaculo(Obstaculo* pO)
{
    if (pO == nullptr)
    {
        cerr << "Erro: tentativa de incluir obstaculo nulo na fase." << endl;
        return;
    }

    if (listaObstaculos.getTamanho() >= 45)
    {
        cerr << "Erro: a fase suporta no maximo 45 obstaculos." << endl;
        return;
    }

    listaEntidades.incluir(static_cast<Entidade*>(pO));
    listaObstaculos.incluir(pO);
}
*/