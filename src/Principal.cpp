#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Menu.h"
#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Fase.h"
#include "../include/Mustafar.h"
#include "../include/Hoth.h"

using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;
using namespace Fases;

#include "../include/Principal.h"

#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>

TrabalhoJogo::Principal::Principal(): 
    pGG(TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico()), 
    pMenu(nullptr), 
    pFase(nullptr),
    pAnakin1(nullptr),
    pObi1(nullptr),
    estadoAtual(Estado::Menu)
{
    pGG = Gerenciador_Grafico::getGerenciadorGrafico();
    Ente::staticSetGG(pGG);

    pMenu = new Menu();
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete (pMenu);
    pMenu = nullptr;

    if (pFase != nullptr)
        delete (pFase);
    pFase = nullptr;

    if (pAnakin1 != nullptr)
        delete (pAnakin1);
    pAnakin1 = nullptr;

    if (pObi1 != nullptr)
        delete (pObi1);
    pObi1 = nullptr;

    // Cuidado: Gerenciador_Grafico é singleton, não deleta aqui.
    pGG = nullptr;

    LEntidades.limpar();
}

void TrabalhoJogo::Principal::executar()
{
    pMenu->loadMenu(textOptions);
    sf::RenderWindow* janela = pGG->getJanela();
    while (janela->isOpen())
    {
        pGG->atualizarTempoPercorrido();

        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela->close();
        }

        janela->clear(sf::Color::Black);
        
        switch(estadoAtual)
        {
            case Estado::Menu:
            {
                estadoAtual = pMenu->manager(*janela,textOptions);
                pGG->desenharMenu(pMenu,textOptions);
                break;
            }
            case Estado::Nomejog1:
            {
                short int qntd = pMenu->getJogsEscolhido();
                if (qntd == 1)
                    pGG->desenharSolicitar1Nome(*janela, event, pMenu->getNomeBack(1), getNome(1));
                else
                    pGG->desenharSolicitar1Nome(*janela, event, pMenu->getNomeBack(1), getNome(1));

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    if (qntd==1)
                    {
                        inicializarJogo();
                        estadoAtual=Estado::Jogando;
                    }
                    else
                        estadoAtual=Estado::Nomejog2;

                    typingDelay.restart();
                }
                break;
            }
            case Estado::Nomejog2:
            {
                pGG->desenharSolicitar1Nome(*janela, event, pMenu->getNomeBack(2), getNome(2));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    inicializarJogo();
                    estadoAtual=Estado::Jogando;
                }    
                break;
            }
            case Estado::Ranking:
                estadoAtual=Estado::Menu;
                break;
            case Estado::Carregar:
                estadoAtual=Estado::Menu;
                break;
            case Estado::Comojogar:
                estadoAtual=Estado::Menu;
                break;
            case Estado::Jogando:
            {
                atualizarFase();

                if (getFase() != nullptr)
                    pGG->desenharFase(getFase(), *janela);
                break;
            }
        }
    }
}

Fase* TrabalhoJogo::Principal::getFase() const
{
    return pFase;
}

void Principal::inicializarJogo()
{
    short int qntd = pMenu->getJogsEscolhido();
    short int fase = pMenu->getFaseEscolhida();

    pAnakin1 = new Jogador();

    if (qntd != 1)
        pObi1 = new Jogador();
    else
        pObi1 = nullptr;

    if (!fase)
        pFase = new Mustafar(pAnakin1, pObi1);

    else
        pFase = new Hoth(pAnakin1, pObi1);
}

void Principal::atualizarFase()
{
    if (pFase == nullptr)
        return;

    if (!(pFase->getVivos())) //ou seja, quando derrotar todos inimigos
    {
        Mustafar* pMustafar = dynamic_cast<Mustafar*>(pFase);

        if (pMustafar != nullptr)
        {
            delete pFase;
            pFase = new Hoth(pAnakin1, pObi1);
        }
        else
        {
            cout << "Cabou!" << endl; //preparar caminho voltar menu
            // Depois preparar retorno ao menu.
        }
    }
}

string& Principal::getNome(short int n)
{
    if (n==1)
        return this->nomeJog1;
    return this->nomeJog2;
}