#define MUSTAFARPNG "../assets/images/Mustafar.png"

#include "../include/Entidade.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
#include "../include/Plataforma.h"
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
    maxPlat(7),
    Ente(),
    nFase(cont++), 
    gC(nullptr),
    pJogador1(pJ1),
    pJogador2(pJ2),
    pPlat(nullptr) // Mudar depois eventualmente
{
    gC = new Gerenciador_Colisoes(&listaJogadores, &listaPlataformas, &listaInimigos);
    if (pJ1 != nullptr)
        incluirEntidade(pJ1);

    if (pJ2 != nullptr)
        incluirEntidade(pJ2);

    criarInimigosFaceis();
    
    criarCenario(); //as plataformas são criadas a partir daqui
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

    if (listaEntidades.getTamanho() != 0)
        listaEntidades.limpar();

    if (listaInimigos.getTamanho() != 0)
        listaInimigos.limpar();
}

void Fase::incluirJogador(Jogador* pJ)
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

void Fase::incluirInimigo(Inimigo* pI)
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

void Fase::criarCenario()
{
    ground.setSize(sf::Vector2f(1280,15));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 710);
    
    if (nFase == 0)
    {
        sf::Texture* pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(MUSTAFARPNG);
        
        if (pTexturaFundo == 0)
            cerr << "Erro de carregamento do Plano de Fundo de Mustafar" << endl;

        else
            fundo.setTexture(*pTexturaFundo); 
    }
    
    else
    {
        cout << "nao existe ainda"<<endl;
    }

    criarPlataformas();
}

void Fase::incluirEntidade(Entidade* pE) 
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
            Plataforma* pPlat = static_cast<Plataforma*>(pE);
            listaEntidades.incluir(pPlat);
            listaPlataformas.incluir(pPlat);
            break;
        }

        default:
        {
            listaEntidades.incluir(pE);
            break;
        }
    }
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

void Fase::criarPlataformas() //Está inicializando o máx, 7 plataformas, depois substituir por i < qntd
{
    int qntd = rand()%(maxPlat-minPlat+1) + minPlat;
    for (int i = 0; i < 7; i++)
    {
        Plataforma* pPlat = new Plataforma();
        if (pPlat == nullptr)
            cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
        else   
            incluirEntidade(static_cast<Obstaculo*>(pPlat));
    }
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