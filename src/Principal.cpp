#define RANKPNG "../assets/images/Ranking.png"
#define HOWPNG "../assets/images/ComoJogarDEMO.png"

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

    rank.clear();
    nomeJog1.clear();
    nomeJog2.clear();

    sf::Texture* pTextRank = pGG->carregarTextura(RANKPNG);
    if (pTextRank == 0)
        cerr << "Erro de carregamento do Plano de Fundo do Ranking" << endl;

    else
        rankSprite.setTexture(*pTextRank);

    sf::Texture* pTextHow = pGG->carregarTextura(HOWPNG);
    if (pTextHow == 0)
        cerr << "Erro de carregamento do Plano de Fundo de 'Como jogar?' " << endl;

    else
        howSprite.setTexture(*pTextHow);

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

    nomeJog1.clear();
    nomeJog2.clear();

    vector<Ranking*>::iterator it;
    for(it=rank.begin(); it!=rank.end();++it)
        delete(*it);
    rank.clear();
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
            {
                pGG->desenharRank(*janela, rank, rankSprite);
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                break; 
            }
            case Estado::Carregar:
                estadoAtual=Estado::Menu;
                break;
            case Estado::Comojogar:
            {
                pGG->desenharComoJogar(*janela, howSprite);
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                break; 
            }
            case Estado::Jogando:
            {
                atualizarFase();

                if (getFase() != nullptr)
                {
                    pGG->desenharFase(getFase(), *janela);
                    pGG->desenharVida(*janela,pAnakin1,pObi1);
                }
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

    //cout<<pFase->numJogsVivos()<<endl;
    if (!(pFase->getInimVivos()) && pFase->numJogsVivos()) //ou seja, quando derrotar todos inimigos
    {
        Mustafar* pMustafar = dynamic_cast<Mustafar*>(pFase);

        if (pMustafar != nullptr)
        {
            delete pFase;
            pFase = new Hoth(pAnakin1, pObi1);

            if (pAnakin1 != nullptr)
            {
                pAnakin1->setX(20);
                pAnakin1->setY(570);
            }
            if (pObi1 != nullptr)
            {
                pObi1->setX(100);
                pObi1->setY(570);
            }
        }
        else
        {
            cout << "Cabou!" << endl; //continuar caminho voltar menu

            delete pFase;
            pFase = nullptr;

            estadoAtual=Estado::Menu;

            salvarRank(pAnakin1,nomeJog1);
            salvarRank(pObi1,nomeJog2);

            if (pAnakin1 != nullptr)
                delete (pAnakin1);
            pAnakin1 = nullptr;

            if (pObi1 != nullptr)
                delete (pObi1);
            pObi1 = nullptr;

            nomeJog1.clear();
            nomeJog2.clear();
        }
    }
    else if (!(pFase->numJogsVivos()))
    {
        cout << "Cabou!" << endl; //continuar caminho voltar menu

        delete pFase;
        pFase = nullptr;
        estadoAtual=Estado::Menu;

        salvarRank(pAnakin1,nomeJog1);
        salvarRank(pObi1,nomeJog2);

        if (pAnakin1 != nullptr)
            delete (pAnakin1);
        pAnakin1 = nullptr;

        if (pObi1 != nullptr)
            delete (pObi1);
        pObi1 = nullptr;

        nomeJog1.clear();
        nomeJog2.clear();
    }
}

string& Principal::getNome(short int n)
{
    if (n==1)
        return this->nomeJog1;
    return this->nomeJog2;
}

void Principal::salvarRank(Jogador* pJ, string nome)
{
    if ( nome.empty() || pJ == nullptr )
        return;

    rank.push_back(new Ranking(nome,pJ->getPontos()));
    if(!(rank.empty()))
    {
        vector<Ranking*>::iterator it;

        for (it=rank.begin(); *it != rank.back(); ++it)
        {
            if(pJ->getPontos() > (*it)->pontos)
            {
                rank.pop_back();
                rank.insert(it,new Ranking(nome,pJ->getPontos()));
                break;
            }
        }

        if (rank.size()>5)
        {
            delete(rank.back());
            rank.pop_back();
        }
    }

    /* for de testes
    for (int i = 0; i < rank.size(); ++i) 
    {
        if (rank[i] != NULL) 
        {
            cout << i + 1 << "o Lugar: " << rank[i]->nome << " - " << rank[i]->pontos << " pts"<<endl;
        }
    }
    */
}
