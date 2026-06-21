#define MUSTAFARPNG "../assets/images/Mustafar.png"

#include "../include/Entidade.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/K_2SO.h"
#include "../include/Obstaculo.h"
#include "../include/Lava.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Mustafar.h"
using namespace OEquilibrioDaForca;
using namespace Listas;
using namespace Entidades;
using namespace Obstaculos;
using namespace Fases;
using namespace Gerenciadores;

Mustafar::Mustafar(Jogador* pJ1, Jogador* pJ2): 
    Fase(),
    minInimigosMedios(3),
    maxInimigosMedios(7),
    minObstMedios(3),
    maxObstMedios(5)
{   
    sf::Texture* pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(MUSTAFARPNG);
        
    if (pTexturaFundo == 0)
        cerr << "Erro de carregamento do Plano de Fundo de Mustafar" << endl;

    else
        fundo.setTexture(*pTexturaFundo); 
    
    inicializar(pJ1,pJ2);
}

Mustafar::Mustafar(Jogador* pJ1, Jogador* pJ2, char c): 
    Fase(),
    minInimigosMedios(3),
    maxInimigosMedios(7),
    minObstMedios(3),
    maxObstMedios(5)
{   
    sf::Texture* pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(MUSTAFARPNG);
        
    if (pTexturaFundo == 0)
        cerr << "Erro de carregamento do Plano de Fundo de Mustafar" << endl;

    else
        fundo.setTexture(*pTexturaFundo); 
    
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

Mustafar::~Mustafar()
{
    for (int i = platGeradas; i < 2*maxPlat; i++)
    {
        Plataforma* pClearList = new Plataforma();
        delete (pClearList);
    }
    platGeradas=0;
}

void Mustafar::criarInimigos()
{
    int qntd = rand()%(maxInimigosMedios-minInimigosMedios+1) + minInimigosMedios;
    for (int i = 0; i < qntd; i++)
    {
        K_2SO* pK2 = new K_2SO();
        if (pK2 == NULL)
            cerr << "Tentativa de incluir K-2SO nula na lista de entidades." << endl;
        else
        {
            Fase::incluirEntidade(static_cast<Inimigo*>(pK2));
            incluirGCInimigo(static_cast<Inimigo*>(pK2));  
            entsAlive++;
        }
    }
}

void Mustafar::criarObstaculos()
{
    int qntd = rand()%(maxObstMedios-minObstMedios+1) + minObstMedios;
    for (int i = 0; i < qntd; i++)
    {
        Lava* pLava = new Lava();
        if (pLava == NULL)
            cerr << "Tentativa de incluir lava nula na lista de entidades." << endl;
        else   
        {
            Fase::incluirEntidade(static_cast<Obstaculo*>(pLava));
            incluirGCObstaculo(static_cast<Obstaculo*>(pLava));
        }
    }
}

sf::Sprite Mustafar::getDrawData() const 
{
    return fundo;
}
