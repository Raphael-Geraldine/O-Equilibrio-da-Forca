#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/ListaEntidades.h"
#include "../include/Menu.h"
#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Fase.h"
#include "../include/Mustafar.h"
#include "../include/Hoth.h"
#include "../include/Lava.h"
#include "../include/Gelo.h"
#include "../include/Stormtrooper.h"
using namespace Listas;
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;
using namespace Fases;

#include "../include/Principal.h"

#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include <SFML/Graphics.hpp>

OEquilibrioDaForca::Principal::Principal(): 
    pGG(OEquilibrioDaForca::Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico()), 
    pMenu(nullptr), 
    pFase(nullptr),
    pAnakin1(nullptr),
    pObi1(nullptr),
    estadoAtual(Estado::Menu)
{
    pGG = Gerenciador_Grafico::getGerenciadorGrafico();
    Ente::staticSetGG(pGG);

    nomeJog1.clear();
    nomeJog2.clear();

    pMenu = new Menu();
    executar();
}

OEquilibrioDaForca::Principal::~Principal()
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
}

void OEquilibrioDaForca::Principal::executar()
{
    pMenu->loadMenu(textOptions);
    sf::RenderWindow* janela = pGG->getJanela();
    carregarSaveMenu();
    while (janela->isOpen())
    {
        pGG->atualizarTempoPercorrido();

        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                salvarFechamento();
                janela->close();
            }
        }

        janela->clear(sf::Color::Black);

        //cout<<pMenu->getFaseEscolhida()<<endl;
        
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
                pGG->desenharRank(*janela, pMenu->getLinhasRank(), pMenu->getRankSprite());
                /*
                if (((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))||(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) 
                      && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
                {
                    salvar();
                    janela->close();
                }*/
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                break; 
            }
            case Estado::Carregar:
            {
                carregarSave();
                break;
            }
            case Estado::Comojogar:
            {
                pGG->desenharComoJogar(*janela, pMenu->getHowSprite());
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                break; 
            }
            case Estado::Jogando:
            {
                atualizarFase();

                if (getFase() != nullptr)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                    {
                        estadoAtual=Estado::Pause;
                        typingDelay.restart();
                    }
                    getFase()->executar();
                    pGG->desenharFase(getFase(), *janela);
                    pGG->desenharVida(*janela,pAnakin1,pObi1);
                    pGG->mostrar(*janela);
                }

                break;
            }
            case Estado::Pause:
            {
                pGG->desenharFase(getFase(), *janela);
                pGG->desenharVida(*janela,pAnakin1,pObi1);
                pGG->desenharMenuPause(*janela, pMenu->getMenuPause());
                pGG->mostrar(*janela);

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    estadoAtual=Estado::Jogando;
                    typingDelay.restart();
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    salvar();
                    limparFase();
                    estadoAtual=Estado::Menu;
                    typingDelay.restart();
                }

                break;
            }
        }
    }
}

Fase* OEquilibrioDaForca::Principal::getFase() const
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

void Principal::limparFase()
{
    if (pFase == nullptr)
        return;

    cout << "Retorno do jogador" << endl; //continuar caminho voltar menu

    delete pFase;
    pFase = nullptr;

    //estadoAtual=Estado::Menu;

    if (pAnakin1 != nullptr)
    {
        //pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
        delete (pAnakin1);
        pAnakin1 = nullptr;
    }

    if (pObi1 != nullptr)
    {
        //pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
        delete (pObi1);
        pObi1 = nullptr;
    }

    nomeJog1.clear();
    nomeJog2.clear();
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
            pMenu->setFaseEscolhida(1,textOptions);

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

            if (pAnakin1 != nullptr)
            {
                pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
                delete (pAnakin1);
                pAnakin1 = nullptr;
            }

            if (pObi1 != nullptr)
            {
                pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
                delete (pObi1);
                pObi1 = nullptr;
            }

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

        if (pAnakin1 != nullptr)
        {
            pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
            delete (pAnakin1);
            pAnakin1 = nullptr;
        }

        if (pObi1 != nullptr)
        {
            pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
            delete (pObi1);
            pObi1 = nullptr;
        }

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

void Principal::salvarFechamento()
{
    ifstream dataIn("../assets/data.txt", ios::in);

    string estado;
    getline(dataIn,estado,'%');

    if (estado == "jogo")
    {
        cout<<"Tudo necessário já foi salvo"<<endl;
        return;
    }

    salvar();
}

void Principal::salvar()
{
    ofstream data("../assets/data.txt", ios::out); 
    
    if (!data) 
    {
        cerr << "Arquivo não pode ser aberto" << endl;
        return;
    }

    if (estadoAtual == Estado::Pause)
        data << "jogo" << '%';
    else 
        data << "menu" << '%';

    int tamanhoRank = static_cast<int>(pMenu->getTamanhoRank());
    int i = 0;

    while (i < tamanhoRank) 
    {
        string nome = pMenu->getNomeRank(i);
        int pontuacao = pMenu->getPontosRank(i);

        data << nome << ' ' << to_string(pontuacao);

        i++;

        // i == tamanhoRank - 1 e menos 1 porque começa em zero
        if (i == 5)
            data << '%';

        else
            data << ' ';
    }

    /*
    vector<ElemRank*> rankSave = pMenu->getRank();
    vector<ElemRank*>::iterator it = rankSave.begin();
    int i = 0;

    while(it != rankSave.end())
    {
        data << (*it)->getNome() << ' '
             << to_string((*it)->getPontos());

        i++;

        if(i==5)
            data<<'%';
        else
            data<<' ';

        ++it;
    }
    */

    while (i < 5)
    {
        data << '-' << ' ' << '-';
        i++;
        if(i == 5)
            data<<'%';
        else
            data<<' ';
    }

    if (estadoAtual != Estado::Pause)
    {
        data.close();
        return;
    }

//================== ESTADO E RANK ================================

    //short int plat = pFase->getPlatGeradas();
    //data<<to_string(plat)<<'%';

    int qntdJogsSave = pMenu->getJogsEscolhido();

    data<<to_string(pMenu->getFaseEscolhida())<<' '<<to_string(qntdJogsSave)<<'%';

//================== FASE E JOGADORES ================================

    if(nomeJog1.empty())
        data<<'-';
    else
        data<<nomeJog1;
    if (qntdJogsSave != 1)
    {
        if(nomeJog2.empty())
            data<<' '<<'-';
        else
        data<<' '<<nomeJog2;
    }
    data<<'%';

//================== NOMES JOGADORES ================================

    ListaEntidades* allEnts = pFase->getListaEntidades();

    allEnts->salvar(&data);

//================== ALL DATA ================================

    data.close();
}

void Principal::carregarSaveMenu()
{
    ifstream data("../assets/data.txt", ios::in);

    if (!data) 
    {
        cerr << "Arquivo não pode ser aberto ou não existe" << endl;
        estadoAtual=Estado::Menu;
        return;
    }
    
    pMenu->limparRank();

    string preRead;

    getline(data,preRead,'%');

    getline(data,preRead,'%');
    stringstream read(preRead);

    string nome;
    string pts;

    while(read>>nome>>pts)
    {
        if(nome!= "-" && pts!="-")
        {
            pMenu->salvarRank(stoi(pts),nome);
        }
    }
}

void Principal::carregarSave()
{
    ifstream data("../assets/data.txt", ios::in);

    //pMenu->limparRank();
    
    if (!data) 
    {
        cerr << "Arquivo não pode ser aberto ou não existe" << endl;
        estadoAtual=Estado::Menu;
        return;
    }

    string estado;

    getline(data,estado,'%');

    string preRead;
    getline(data,preRead,'%');
    //stringstream read(preRead);

    string d1;
    string d2;
    string d3;
    string d4;
    string d5;
    string d6;
    string d7;

    /*while(read>>d1>>d2)
    {
        if(d1!= "-" && d2!="-")
        {
            pMenu->salvarRank(stoi(d2),d1);
        }
    }*/

//================== ESTADO E RANK ================================

    if (estado != "jogo")
    {
        estadoAtual=Estado::Menu;
        cerr<<"Nada a ser lido!"<<endl;
        return;
    }

    getline(data,preRead,'%');
    //read.clear(); 
    //read.str(preRead);
    stringstream read(preRead);

    read>>d1>>d2;

    pMenu->setFaseEscolhida(stoi(d1),textOptions);
    pMenu->setJogsEscolhido(stoi(d2),textOptions);

    int fase = stoi(d1); 
    int jogs = stoi(d2);

    getline(data,preRead,'%');
    read.clear(); 
    read.str(preRead);
    read>>d1;
    if(d1 != "-")
        nomeJog1=d1;

    if (jogs != 1)
    {
        read>>d1;
        if(d1 != "-")
            nomeJog2=d1;
    }
    
    getline(data,preRead,'%');
    read.clear(); 
    read.str(preRead);
    read>>d1>>d2>>d3>>d4>>d5>>d6>>d7;
    pAnakin1 = new Jogador(stof(d1),stof(d2),stof(d3),stof(d4),stoi(d5),(short)(stoi(d6)),stoi(d7));

    if (jogs != 1)
    {
        getline(data,preRead,'%');
        read.clear(); 
        read.str(preRead);
        read>>d1>>d2>>d3>>d4>>d5>>d6>>d7;
        pObi1 = new Jogador(stof(d1),stof(d2),stof(d3),stof(d4),stoi(d5),(short)(stoi(d6)),stoi(d7));
    }

    if(!fase)
        pFase = new Mustafar(pAnakin1,pObi1,'s');
    else
        pFase = new Hoth(pAnakin1,pObi1,'s');

//================== FASE E JOGADORES ================================
    
    while(getline(data,preRead,'%'))
    {
        read.clear(); 
        read.str(preRead);
        read>>d1>>d2>>d3>>d4>>d5>>d6>>d7;

        if(d6 == "O")
        {
            if (d7 == "Plataforma")
            {
                Plataforma* pPlat = new Plataforma();
                if (pPlat == nullptr)
                    cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Obstaculo*>(pPlat));
                    pFase->incluirGCObstaculo(static_cast<Obstaculo*>(pPlat));
                    pFase->increasePlatGeradas();
                }  
            }
            else if (d7 == "Lava")
            {
                Lava* pLava = new Lava();
                if (pLava == nullptr)
                    cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Obstaculo*>(pLava));
                    pFase->incluirGCObstaculo(static_cast<Obstaculo*>(pLava));
                } 
            }
            else if (d7 == "Gelo")
            {
                Gelo* pGelo = new Gelo();
                if (pGelo == nullptr)
                    cerr << "Tentativa de incluir plataforma nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Obstaculo*>(pGelo));
                    pFase->incluirGCObstaculo(static_cast<Obstaculo*>(pGelo));
                } 
            }
            else
            {
                cerr<<"Ops, ocorreu um erro, arquivo corrompido!"<<endl;
            }
        }
        else
        {
            if (d7 == "Stormtrooper")
            {
                Stormtrooper* pStorm = new Stormtrooper(stof(d1),stof(d2),stof(d3),stof(d4),stoi(d5),stoi(d6));
                if (pStorm == nullptr)
                    cerr << "Tentativa de incluir Stormtrooper nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Inimigo*>(pStorm));
                    pFase->incluirGCInimigo(static_cast<Inimigo*>(pStorm)); 
                    pFase->increaseInimVivos();
                }
            }
            else if (d7 == "K_2SO")
            {
                K_2SO* pK2 = new K_2SO(stof(d1),stof(d2),stof(d3),stof(d4),stoi(d5),stoi(d6));
                if (pK2 == nullptr)
                    cerr << "Tentativa de incluir K-2SO nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Inimigo*>(pK2));
                    pFase->incluirGCInimigo(static_cast<Inimigo*>(pK2));  
                    pFase->increaseInimVivos();
                }
            }
            else if (d7 == "AT_ST")
            {
                AT_ST* pAT = new AT_ST(stof(d1),stof(d2),stof(d3),stof(d4),stoi(d5),stoi(d6));
                if (pAT == nullptr)
                    cerr << "Tentativa de incluir AT-ST nula na lista de entidades." << endl;
                else
                {
                    pFase->incluirEntidade(static_cast<Inimigo*>(pAT));
                    pFase->incluirGCInimigo(static_cast<Inimigo*>(pAT)); 
                    pAT->setAlvos(pAnakin1, pObi1);
                    pFase->increaseInimVivos();
                    
                    getline(data,preRead,'%');
                    read.clear(); 
                    read.str(preRead);
                    read>>d1>>d2>>d3>>d4>>d5>>d6>>d7;

                    Projetil* pProj = new Projetil(stof(d1),stof(d2),stof(d3),stof(d4),(short int)(stoi(d5)),(bool)(stoi(d6)));
                    if (pProj == nullptr)
                        cerr << "Tentativa de incluir projetil nulo na lista de entidades." << endl;
                    else
                    {
                        pFase->incluirEntidade(pProj); 
                        pFase->incluirGCProjetil(pProj);
                        pAT->setProjetil(pProj);           
                    } 
                } 
            }
            else
            {
                if (d7 != "Projetil")
                    cerr<<"Ops, ocorreu um erro, arquivo corrompido!"<<endl;
            }
        }
    }

//================== ALL DATA ================================

    ofstream dataOut("../assets/data.txt", ios::out); 
    dataOut.close();
    estadoAtual=Estado::Jogando;
}