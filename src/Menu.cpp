#define MENUINICIALPNG "../assets/images/MenuInicial.png"
#define ANAKINPNG "../assets/images/Anakin.png"

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
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>

Menu::Menu(): 
    pGGraf(nullptr),
    qntdJogs(1),
    faseEscolhida(0),
    pJogo()
{
    executar();
}

Menu::~Menu()
{
    faseEscolhida=-1;
    qntdJogs=-1;

    // O Menu não deve deletá-lo, pois Gerenciador_Gráfico é singleton
    pGGraf = nullptr; 
}

void Menu::executar()
{
    menuOptions = {"Iniciar o jogo", "Ver o ranking", "Carregar o jogo", "Fase 1: Mustafar", "1 jogador", "Como jogar?"};
    
    faseString= "Fase 2: Hoth";
    jogsString= "2 Jogadores";
}

short int Menu::manager(sf::RenderWindow& janela, vector<sf::Text>& text)
{
    if (cliqueEmOpcao(janela,text[0]))
        return 0;

    if (cliqueEmOpcao(janela,text[1]))
        return 1;

    if (cliqueEmOpcao(janela,text[2]))
        return 2;

    if (cliqueEmOpcao(janela,text[3]))
    {
        list<string>::iterator it = menuOptions.begin();
        for (int i=0; i<3; i++)
            ++it;

        string tempString = *it;
        *it=faseString;
        faseString=tempString;

        faseEscolhida == 0 ? faseEscolhida = 1 : faseEscolhida = 0;
        
        loadMenu(text);
        
        return 3;   
    }
    if (cliqueEmOpcao(janela,text[4]))
    {
        list<string>::iterator it = menuOptions.begin();
        for (int i=0; i<4; i++)
            ++it;

        string tempString = *it;
        *it=jogsString;
        jogsString=tempString;

        qntdJogs == 1 ? qntdJogs = 2 : qntdJogs = 1;
        
        loadMenu(text);

        return 4;
    }

    if (cliqueEmOpcao(janela,text[5]))
        return 5;

    return -1;
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
        text.setPosition(posX,posY);
        textToDisplay.push_back(text);
        posY+=70;
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

sf::Sprite Menu::getFundo()
{
    return fundo; 
}

sf::Sprite Menu::getDrawData()
{
    return anakin; 
}