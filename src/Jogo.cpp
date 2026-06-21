#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/ListaEntidades.h"
#include "../include/Menu.h"
#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Fase.h"
#include "../include/Mustafar.h"
#include "../include/Hoth.h"
#include "../include/Lava.h"
#include "../include/Gelo.h"
#include "../include/Stormtrooper.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Gerenciador_Eventos.h"
#include "../include/Observador_Teclado.h"
using namespace Listas;
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;
using namespace Fases;

#include "../include/Jogo.h"

#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include <SFML/Graphics.hpp>

Jogo::Jogo(): 
    pGG(Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico()), 
    pGerEventos(NULL),
    pObsTeclado(NULL),
    pObsMenu(NULL),
    pMenu(NULL), 
    pFase(NULL),
    pAnakin1(NULL),
    pObi1(NULL),
    estadoAtual(Estado::Menu)
{
    pGG = Gerenciador_Grafico::getGerenciadorGrafico();
    Ente::staticSetGG(pGG);

    nomeJog1.clear();
    nomeJog2.clear();

    pMenu = new Menu();

    pGerEventos = new Gerenciador_Eventos();

    pObsTeclado = new Observador_Teclado();
    pObsTeclado->setJogo(this);

    pObsMenu = new Observador_Menu();
    pObsMenu->setMenu(pMenu);
    pObsMenu->setEstadoAtual(&estadoAtual);
    pObsMenu->setTextosMenu(&textOptions);
    pObsMenu->setAtivo(false);

    pGerEventos->anexar(pObsMenu);
    pGerEventos->anexar(pObsTeclado);

    executar();
}

OEquilibrioDaForca::Jogo::~Jogo()
{
    delete (pMenu);
    pMenu = NULL;

    if (pFase != NULL) {
        delete (pFase);
        pFase = NULL;
    }

    if (pAnakin1 != NULL) {
        delete (pAnakin1);
        pAnakin1 = NULL;
    }

    if (pObi1 != NULL) {
        delete (pObi1);
        pObi1 = NULL;
    }

    if (pObsMenu != NULL)
    {
        delete pObsMenu;
        pObsMenu = NULL;
    }

    if (pObsTeclado != NULL)
    {
        delete pObsTeclado;
        pObsTeclado = NULL;
    }

    if (pGerEventos != NULL) 
    {
        delete pGerEventos;
        pGerEventos = NULL;
    }

    // Cuidado: Gerenciador_Grafico é singleton, não deleta aqui.
    pGG = NULL;

    LEntidades.limpar();

    nomeJog1.clear();
    nomeJog2.clear();
}

int paraInt(const string& texto)
{
    stringstream fluxo(texto);
    int valor = 0;
    fluxo >> valor;
    return valor;
}

float paraFloat(const string& texto)
{
    stringstream fluxo(texto);
    float valor = 0.0f;
    fluxo >> valor;
    return valor;
}

void OEquilibrioDaForca::Jogo::executar()
{
    pMenu->loadMenu(textOptions);
    sf::RenderWindow* janela = pGG->getJanela();
    carregarSaveMenu();
    while (janela->isOpen())
    {
        pGG->atualizarTempoPercorrido();

        pObsMenu->setAtivo(estadoAtual == Estado::Menu);
        pObsMenu->setTextosMenu(&textOptions);
        
        sf::Event evento;
        while (janela->pollEvent(evento))
        {
            pGerEventos->setEvento(evento, janela);
            pGerEventos->notificar();
            /*
            if (evento.type == sf::Event::Closed)
            {
                salvarFechamento();
                janela->close();
            }
            */
        }

        janela->clear(sf::Color::Black);

        //cout<<pMenu->getFaseEscolhida()<<endl;
        
        switch(estadoAtual)
        {
            case Estado::Menu:
            {
                // Agora quem muda o estadoAtual é o observador // estadoAtual = pMenu->manager(textOptions); // Muda o estado do observado.
                pGG->desenharMenu(pMenu,textOptions);
                break;
            }
            
            case Estado::NomeJog1:
            {                       
                short int qntd = pMenu->getJogsEscolhido();
                if (qntd == 1)
                    pGG->desenharSolicitar1Nome(evento, pMenu->getNomeBack(1), getNome(1));
                else
                    pGG->desenharSolicitar1Nome(evento, pMenu->getNomeBack(1), getNome(1));

                /*
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    if (qntd==1)
                    {
                        inicializarJogo();
                        estadoAtual=Estado::Jogando;
                    }
                    else
                        estadoAtual=Estado::NomeJog2;

                    typingDelay.restart();
                }
                */

                break;
            }
            
            case Estado::NomeJog2:
            {
                pGG->desenharSolicitar1Nome(evento, pMenu->getNomeBack(2), getNome(2));
                /*
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    inicializarJogo();
                    estadoAtual=Estado::Jogando;
                } 
                */   
                break;
            }
            case Estado::Ranking:
            {
                pGG->desenharRank(pMenu->getLinhasRank(), pMenu->getRankSprite());
                
                /*
                if (((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))||(sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) 
                      && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
                {
                    salvar();
                    janela->close();
                }
                */

                /*
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                */

                break; 
            }
            case Estado::Carregar:
            {
                carregarSave();
                break;
            }
            case Estado::ComoJogar:
            {
                pGG->desenharComoJogar(pMenu->getHowSprite());
                /*
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                    estadoAtual=Estado::Menu;
                */
                break; 
            }
            case Estado::Jogando:
            {
                atualizarFase();

                if (getFase() != NULL)
                {
                    /*
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                    {
                        estadoAtual=Estado::Pause;
                        typingDelay.restart();
                    }
                    */
                    getFase()->executar();
                    pGG->desenharFase(getFase());
                    pGG->desenharVida(pAnakin1,pObi1);
                    pGG->mostrar();
                }

                break;
            }
            case Estado::Pause:
            {
                pGG->desenharFase(getFase());
                pGG->desenharVida(pAnakin1,pObi1);
                pGG->desenharMenuPause(pMenu->getMenuPause());
                pGG->mostrar();

                /*
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    estadoAtual=Estado::Jogando;
                    typingDelay.restart();
                }
                */

                /*
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && typingDelay.getElapsedTime().asMilliseconds()>=200)
                {
                    salvar();
                    limparFase();
                    estadoAtual=Estado::Menu;
                    typingDelay.restart();
                }
                */

                break;
            }
        }
    }
}

Fase* OEquilibrioDaForca::Jogo::getFase() const
{
    return pFase;
}

void Jogo::inicializarJogo()
{
    short int qntd = pMenu->getJogsEscolhido();
    short int fase = pMenu->getFaseEscolhida();

    pAnakin1 = new Jogador();

    if (qntd != 1)
        pObi1 = new Jogador();
    else
        pObi1 = NULL;

    if (!fase)
        pFase = new Mustafar(pAnakin1, pObi1);

    else
        pFase = new Hoth(pAnakin1, pObi1);
}

void Jogo::limparFase()
{
    if (pFase == NULL)
        return;

    cout << "Retorno do jogador" << endl; //continuar caminho voltar menu

    delete pFase;
    pFase = NULL;

    //estadoAtual=Estado::Menu;

    if (pAnakin1 != NULL)
    {
        //pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
        delete (pAnakin1);
        pAnakin1 = NULL;
    }

    if (pObi1 != NULL)
    {
        //pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
        delete (pObi1);
        pObi1 = NULL;
    }

    nomeJog1.clear();
    nomeJog2.clear();
}

void Jogo::atualizarFase()
{
    if (pFase == NULL)
        return;

    //cout<<pFase->numJogsVivos()<<endl;
    if (!(pFase->getInimVivos()) && pFase->numJogsVivos()) //ou seja, quando derrotar todos inimigos
    {
        //Mustafar* pMustafar = dynamic_cast<Mustafar*>(pFase);

        if (!(pMenu->getFaseEscolhida()))
        {
            delete pFase;
            pFase = new Hoth(pAnakin1, pObi1);
            pMenu->setFaseEscolhida(1,textOptions);

            if (pAnakin1 != NULL)
            {
                pAnakin1->setX(20);
                pAnakin1->setY(570);
            }
            if (pObi1 != NULL)
            {
                pObi1->setX(100);
                pObi1->setY(570);
            }
        }
        else
        {
            cout << "Cabou! Jogou bem!" << endl; //continuar caminho voltar menu

            delete pFase;
            pFase = NULL;

            estadoAtual=Estado::Menu;

            if (pAnakin1 != NULL)
            {
                pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
                delete (pAnakin1);
                pAnakin1 = NULL;
            }

            if (pObi1 != NULL)
            {
                pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
                delete (pObi1);
                pObi1 = NULL;
            }

            nomeJog1.clear();
            nomeJog2.clear();
        }
    }
    else if (!(pFase->numJogsVivos()))
    {
        cout << "Cabou! Todos jogadores derrotados" << endl; //continuar caminho voltar menu
        
        delete pFase;
        pFase = NULL;
        estadoAtual=Estado::Menu;
        
        if (pAnakin1 != NULL)
        {
            pMenu->salvarRank(pAnakin1->getPontos(),nomeJog1);
            delete (pAnakin1);
            pAnakin1 = NULL;
        }

        if (pObi1 != NULL)
        {
            pMenu->salvarRank(pObi1->getPontos(),nomeJog2);
            delete (pObi1);
            pObi1 = NULL;
        }

        nomeJog1.clear();
        nomeJog2.clear();
    }
}

string& Jogo::getNome(short int n)
{
    if (n==1)
        return this->nomeJog1;
    return this->nomeJog2;
}

void Jogo::salvarFechamento()
{
    ifstream dataIn("../assets/data.txt", ios::in);

    string estado;
    getline(dataIn,estado,'%');

    if (estado == "jogo")
    {
        cout<<"Tudo necessario ja foi salvo"<<endl;
        return;
    }

    salvar();
}

void Jogo::salvar()
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

        data << nome << ' ' << pontuacao;
        // data << nome << ' ' << to_string(pontuacao);

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

/* ESTADO E RANK */

    //short int plat = pFase->getPlatGeradas();
    //data<<to_string(plat)<<'%';

    int qntdJogsSave = pMenu->getJogsEscolhido();

    data<<pMenu->getFaseEscolhida()<<' '<<qntdJogsSave<<'%';

    // data<<to_string(pMenu->getFaseEscolhida())<<' '<<to_string(qntdJogsSave)<<'%';

/* FASE E JOGADORES */

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

/* NOMES JOGADORES */

    ListaEntidades* allEnts = pFase->getListaEntidades();

    allEnts->salvar(&data);

/* ALL DATA */

    data.close();
}

void Jogo::carregarSaveMenu()
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
            pMenu->salvarRank(paraInt(pts),nome);
        }
    }
}

void Jogo::carregarSave()
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
            pMenu->salvarRank(paraInt(d2),d1);
        }
    }*/

/* ESTADO E RANK */

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

    pMenu->setFaseEscolhida(paraInt(d1),textOptions);
    pMenu->setJogsEscolhido(paraInt(d2),textOptions);

    int fase = paraInt(d1); 
    int jogs = paraInt(d2);

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
    pAnakin1 = new Jogador(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),paraInt(d5),(short)(paraInt(d6)),paraInt(d7));

    if (jogs != 1)
    {
        getline(data,preRead,'%');
        read.clear(); 
        read.str(preRead);
        read>>d1>>d2>>d3>>d4>>d5>>d6>>d7;
        pObi1 = new Jogador(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),paraInt(d5),(short)(paraInt(d6)),paraInt(d7));
    }

    if(!fase)
        pFase = new Mustafar(pAnakin1,pObi1,'s');
    else
        pFase = new Hoth(pAnakin1,pObi1,'s');

/* FASE E JOGADORES */
    
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
                if (pPlat == NULL)
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
                if (pLava == NULL)
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
                if (pGelo == NULL)
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
                Stormtrooper* pStorm = new Stormtrooper(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),paraInt(d5),paraInt(d6));
                if (pStorm == NULL)
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
                K_2SO* pK2 = new K_2SO(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),paraInt(d5),paraInt(d6));
                if (pK2 == NULL)
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
                AT_ST* pAT = new AT_ST(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),paraInt(d5),paraInt(d6));
                if (pAT == NULL)
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

                    Projetil* pProj = new Projetil(paraFloat(d1),paraFloat(d2),paraFloat(d3),paraFloat(d4),(short int)(paraInt(d5)),(bool)(paraInt(d6)));
                    if (pProj == NULL)
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

/* ALL DATA */

    ofstream dataOut("../assets/data.txt", ios::out); 
    dataOut.close();
    estadoAtual=Estado::Jogando;
}

void Jogo::fecharJogo (sf::RenderWindow& janela) 
{
    salvarFechamento();
    janela.close();
}

/*
void Jogo::atalhoSalvarESair(sf::RenderWindow& janela)
{
    salvar();
    janela.close();
}
*/

void Jogo::alternarPause()
{
    if (typingDelay.getElapsedTime().asMilliseconds() < 200)
        return;

    if (estadoAtual == Estado::Jogando)
    {
        estadoAtual = Estado::Pause;
        typingDelay.restart();
        return;
    }

    if (estadoAtual == Estado::Pause)
    {
        estadoAtual = Estado::Jogando;
        typingDelay.restart();
        return;
    }
}

void Jogo::voltarMenuPeloPause()
{
    if (typingDelay.getElapsedTime().asMilliseconds() < 200)
        return;

    if (estadoAtual == Estado::Pause)
    {
        salvar();
        limparFase();
        estadoAtual=Estado::Menu;
        typingDelay.restart();
    }
}

void Jogo::confirmarEntrada() 
{
    if (typingDelay.getElapsedTime().asMilliseconds() < 200)
        return;

    if (estadoAtual == Estado::NomeJog1) 
    {
        short int qntd = pMenu->getJogsEscolhido();
        
        if (qntd == 1)
        {
            inicializarJogo();
            estadoAtual = Estado::Jogando;
        }

        else 
            estadoAtual = Estado::NomeJog2;

        typingDelay.restart();
        return;
    }

    if (estadoAtual == Estado::NomeJog2)
    {
        inicializarJogo();
        estadoAtual = Estado::Jogando;
        typingDelay.restart();
        return;
    }
}

// Voltar para Menu estando em "Ranking" ou em "Como Jogar"
void Jogo::voltarParaMenu()
{
    if (typingDelay.getElapsedTime().asMilliseconds() < 200)
        return;

    if (estadoAtual == Estado::Ranking || estadoAtual == Estado::ComoJogar)
    {
        estadoAtual = Estado::Menu;
        typingDelay.restart();
    }
}
 
