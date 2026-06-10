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
using namespace TrabalhoJogo;
using namespace Listas;
using namespace Entidades;
using namespace Obstaculos;
using namespace Fases;
using namespace Gerenciadores;

Mustafar::Mustafar(Jogador* pJ1, Jogador* pJ2): 
    Fase(pJ1, pJ2),
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
    //criarObstaculos();
    //criarInimigos();
}

Mustafar::~Mustafar()
{
    //fixing memory leaks
    //delete(fundo.getTexture());
}

void Mustafar::criarInimigos()
{
    int qntd = rand()%(maxInimigosMedios-minInimigosMedios+1) + minInimigosMedios;
    for (int i = 0; i < qntd; i++)
    {
        K_2SO* pK2 = new K_2SO();
        if (pK2 == nullptr)
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
        if (pLava == nullptr)
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

/*
void Mustafar::incluirEntidade(Entidade* pE) 
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

void Mustafar::incluirJogador(Jogador* pJ)
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

void Mustafar::incluirInimigo(Inimigo* pI)
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

void Mustafar::incluirObstaculo(Obstaculo* pO)
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