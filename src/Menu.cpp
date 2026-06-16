#define MENUINICIALPNG "../assets/images/MenuInicial.png"
#define RANKPNG "../assets/images/Ranking.png"
#define HOWPNG "../assets/images/ComoJogarDEMO.png"
#define ANAKINPNG "../assets/images/Anakin.png"
#define NOME1JOG "../assets/images/EnterNameP1.png"
#define NOME2JOG "../assets/images/EnterNameP2.png"
#define PAUSEPNG "../assets/images/Pause.png"

#define FONTE "../assets/fonts/PressStart2P.ttf"

#include <vector>
#include <string>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Principal.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Menu.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>

Menu::Menu(): 
    qntdJogs(1),
    faseEscolhida(0),
    pJogo()
{
    rank.clear();

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

    try
    {
        sf::Texture* pTextPause = pGG->carregarTextura(PAUSEPNG);
        pauseSprite.setTexture(*pTextPause);
    }
    catch(const exception &e)
    {
        cerr << "Erro de carregamento do Plano de Fundo de 'Como jogar?' " << endl;
    }
    
    executar();
}

Menu::~Menu()
{
    faseEscolhida = -1;
    qntdJogs = -1;

    vector<ElemRank*>::iterator it;
    for(it = rank.begin(); it != rank.end(); ++it)
    {
        delete(*it);
    }
    
    rank.clear();
}

void Menu::executar()
{
    menuOptions = {"Iniciar novo jogo", "Ver o ranking", "Retomar jogo anterior", "Fase 1: Mustafar", "1 jogador", "Como jogar?"};
    
    faseString= "Fase 2: Hoth";
    jogsString= "2 Jogadores";
}

OEquilibrioDaForca::Estado Menu::manager(sf::RenderWindow& janela, vector<sf::Text>& text)
{
    if (cliqueEmOpcao(janela,text[0]))
    {
        pTexturaNome1 = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(NOME1JOG);
        if (pTexturaNome1 == nullptr)
            cerr << "Erro de carregamento do fundo solicitando nome 1 jogador" << endl;
        
        if (qntdJogs != 1)
        {
            pTexturaNome2 = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(NOME2JOG);
            if (pTexturaNome2 == nullptr)
                cerr << "Erro de carregamento do fundo solicitando nome 2 jogador" << endl;
        }
        
        fundoNome.setTexture(*pTexturaNome1);

        return Estado::Nomejog1;
    }    

    if (cliqueEmOpcao(janela,text[1]))
        return Estado::Ranking;

    if (cliqueEmOpcao(janela,text[2]))
        return Estado::Carregar;

    if (cliqueEmOpcao(janela,text[3]))
    {
        list<string>::iterator it = menuOptions.begin();
        for (int i = 0; i < 3; i++)
            ++it;

        faseEscolhida == 0 ? faseEscolhida = 1 : faseEscolhida = 0;

        faseEscolhida == 0 ? *it = "Fase 1: Mustafar" : *it = "Fase 2: Hoth";
        
        loadMenu(text);
        
        return Estado::Menu;   
    }

    if (cliqueEmOpcao(janela,text[4]))
    {
        list<string>::iterator it = menuOptions.begin();
        for (int i=0; i<4; i++)
            ++it;

        qntdJogs == 1 ? *it="1 jogador" : *it="2 Jogadores";
        
        loadMenu(text);

        return Estado::Menu;
    }

    if (cliqueEmOpcao(janela,text[5]))
        return Estado::Comojogar;

    return Estado::Menu;
}

void Menu::loadMenu(vector<sf::Text>& text)
{
    pTexturaFundo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(MENUINICIALPNG);
    pTexturaAnakin = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINPNG);
    fundo.setTexture(*pTexturaFundo);
    anakin.setTexture(*pTexturaAnakin);

    anakin.setScale(0.5,0.5);
    anakin.setPosition(50,170);

    if (!fonteMenu.loadFromFile(FONTE))
        cerr << "Erro de carregamento da Fonte no Menu" << endl;

    menuTextPlacement(text);
}

void Menu::menuTextPlacement(vector<sf::Text>& textToDisplay)
{
    textToDisplay.clear();
    list<string>::iterator it = menuOptions.begin();
    int posX = 640, posY = 200;
    while (it != menuOptions.end())
    {
        sf::Text text(*it, fonteMenu, 30);
        sf::FloatRect bounds = text.getLocalBounds();
        // Ponto de referência do meio do objeto texto.
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
        // Coloca o ponto de referência na posição a seguir.
        text.setPosition(posX, posY);
        textToDisplay.push_back(text);
        posY += 70;
        it++;
    }
}

bool Menu::cliqueEmOpcao(sf::RenderWindow& janela, sf::Text& text)
{
    sf::Vector2f mousePosition = janela.mapPixelToCoords(sf::Mouse::getPosition(janela));
    if (text.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Time timer = sf::milliseconds(300);
        sf::sleep(timer);
        cout<<"Redirecionando para: "<<static_cast<string>(text.getString())<<endl;
        return 1;
    }
    return 0;
}

short int Menu::getFaseEscolhida() const 
{
    return faseEscolhida;
}

short int Menu::getJogsEscolhido() const 
{
    return qntdJogs;
}

void Menu::setFaseEscolhida(short int f, vector<sf::Text>& text)
{
    faseEscolhida = f;

    list<string>::iterator it = menuOptions.begin();
    for (int i=0; i<3; i++)
        ++it;

    faseEscolhida == 0 ? *it="Fase 1: Mustafar" : *it="Fase 2: Hoth";
    
    loadMenu(text);
}

void Menu::setJogsEscolhido(short int j, vector<sf::Text>& text) 
{
    qntdJogs = j;

    list<string>::iterator it = menuOptions.begin();
    for (int i=0; i<4; i++)
        ++it;

    qntdJogs == 1 ? *it="1 jogador" : *it="2 Jogadores";

    loadMenu(text);
}

sf::Sprite Menu::getFundo() const 
{
    return fundo; 
}

sf::Sprite Menu::getDrawData() const 
{
    return anakin; 
}

sf::Sprite Menu::getNomeBack(short int n)
{
    if (n == 1)
        return fundoNome;

    fundoNome.setTexture(*pTexturaNome2);
    return fundoNome;
}
// vector<ElemRank*> Menu::getRank()
// {
//     return rank;
// }

void Menu::salvarRank(int pontos, string nome)
{
    if (nome.empty())
        return;

    vector<ElemRank*>::iterator it;

    for (it = rank.begin(); it != rank.end(); ++it)
    {
        if (pontos > (*it)->getPontos())
        {
            // Insere antes do elemento na posição especificada.
            ElemRank* novo = new ElemRank(nome,pontos);
            rank.insert(it, novo);

            if (rank.size() > 5)
            {
                delete(rank.back());
                rank.pop_back();
            }

            return;
        }
    }

    ElemRank* novo = new ElemRank(nome,pontos);
    rank.push_back(novo);

    if (rank.size() > 5)
    {
        delete rank.back();
        rank.pop_back();
    }
}

/*
void Menu::salvarRank(int pontos, string nome)
{
    if (nome.empty())
        return;

    rank.push_back(new ElemRank(nome,pontos));
    if(!(rank.empty()))
    {
        vector<ElemRank*>::iterator it;

        for (it=rank.begin(); *it != rank.back(); ++it)
        {
            if(pontos > (*it)->getPontos())
            {
                delete(rank.back());
                rank.pop_back();
                rank.insert(it,new ElemRank(nome,pontos));
                break;
            }
        }

        if (rank.size()>5)
        {
            delete(rank.back());
            rank.pop_back();
        }
    }

    for (int i = 0; i < rank.size(); ++i) 
    {
        if (rank[i] != NULL) 
        {
            cout << i + 1 << "o Lugar: " << rank[i]->getNome() << " - " << rank[i]->getPontos() << " pts"<<endl;
        }
    }
}

*/

void Menu::limparRank()
{
    vector<ElemRank*>::iterator it;
    for (it=rank.begin(); it != rank.end(); ++it)
    {
        delete(*it);
    }
    rank.clear();
}

size_t Menu::getTamanhoRank() const 
{
    return rank.size();
}

string Menu::getNomeRank (int indice) const
{
    if (indice < 0 || indice >= static_cast<int> (rank.size()))
    {
        cerr << "Indice fora do ranking." << endl;
        return "";
    }

    return rank[indice]->getNome();
}

int Menu::getPontosRank (int indice) const
{
    if (indice < 0 || indice >= static_cast<int> (rank.size()))
    {
        cerr << "Indice fora do ranking." << endl;
        return 0;
    }

    return rank[indice]->getPontos();
}

vector<string> Menu::getLinhasRank() const
{
    vector<string> linhasRank;
    int tamanhoRank = static_cast<int>(rank.size());

    for (int i = 0; i < tamanhoRank; i++)
    {
        int pts = rank[i]->getPontos();
        string jogador = to_string (i + 1) + "o lugar: " + rank[i]->getNome() + " - " + to_string(pts);
        if (pts == 1)
            jogador += " ponto";
        else
            jogador += " pontos";
        linhasRank.push_back(jogador);
    }

    return linhasRank;
}

sf::Sprite& Menu::getRankSprite()
{
    return rankSprite;
}

sf::Sprite& Menu::getHowSprite()
{
    return howSprite;
}
sf::Sprite& Menu::getMenuPause()
{
    return pauseSprite;
}

Menu::ElemRank::ElemRank(): pontos(0)
{
    nome.clear();
}
Menu::ElemRank::ElemRank(string n, int p): 
    nome(n),
    pontos(p)
{}

Menu::ElemRank::~ElemRank()
{
    nome.clear();
}

void Menu::ElemRank::setNome(string n)
{
    nome = n;
}
void Menu::ElemRank::setPontos(int p)
{
    pontos = p;
}
string Menu::ElemRank::getNome() const
{
    return nome;
}
int Menu::ElemRank::getPontos() const
{
    return pontos;
}