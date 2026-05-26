#define MENUINICIALPNG "../assets/images/MenuInicial.png"
#define ANAKINPNG "../assets/images/Anakin.png"
#define FONTE "../assets/fonts/PressStart2P.ttf"

/*
#define MENUINICIALPNG "MenuInicial.png"
#define ANAKINPNG "Anakin.png"
#define FONTE "PressStart2P.ttf"
*/

#include <iostream>
#include <string>
#include <list>
using namespace std;

#include "../include/Menu.h"
#include "../include/Ente.h"
using namespace TrabalhoJogo;

#include "../include/Fase.h"
#include "../include/Mustafar.h"
using namespace TrabalhoJogo;
using namespace Fases;

#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include "../include/Gerenciador_Grafico.h"

#include <SFML/Graphics.hpp>
#include <stdlib.h>

short int TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::optionSelected(-1);

TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico()
{
    textOptions.clear();
    menuOptions = {"Iniciar o jogo", "Ver o ranking", "Carregar o jogo", "Fase 1: Mustafar", "1 jogador", "Como jogar?"};
}

TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{
    textOptions.clear();
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::menuTextPlacement()
{
    list<string>::iterator it = menuOptions.begin();
    int i = 0, posY = 200;
    while (it != menuOptions.end())
    {
        sf::Text text(*it, fonteMenu, 30);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        text.setPosition(640,posY);
        textOptions.push_back(text);
        i++;
        posY+=70;
        it++;
    }
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharTextoMenu (sf::RenderWindow & janela)
{
    for (int i=0; i<textOptions.size();i++)
    {
        janela.draw(textOptions[i]);

        sf::Vector2f mousePosition = janela.mapPixelToCoords(sf::Mouse::getPosition(janela));
        if (textOptions[i].getGlobalBounds().contains(mousePosition))
        {
            sf::Color hover(255,255,255,170);
            textOptions[i].setFillColor(hover);
        }
        else
        {
            textOptions[i].setFillColor(sf::Color::White);
        }
    }
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::loadMenu (Menu* pM)
{
    if (!texturaFundo.loadFromFile(MENUINICIALPNG))
    {
        cerr << "Erro de carregamento do Plano de Fundo do Menu Inicial" << endl;
    }
    else
    {
        fundo.setTexture(texturaFundo); 
    }

    if (!texturaAnakin.loadFromFile(ANAKINPNG))
    {
        cerr << "Erro de carregamento do Personagem de exemplo" << endl;
    }
    else
    {
        anakin.setTexture(texturaAnakin); 
    }
    anakin.setScale(0.5,0.5);
    anakin.setPosition(50,170);

    if (!fonteMenu.loadFromFile(FONTE))
    {
        cerr << "Erro de carregamento da Fonte no Menu" << endl;
    }
    else
    {
        //cout<<"tudo ok com a fonte"<<endl;
    }

    menuTextPlacement();
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharMenu (Menu* pM, sf::RenderWindow & janela)
{
    janela.draw(fundo);
    janela.draw(anakin);

    desenharTextoMenu (janela);
        
    janela.display();

    if (pM->CliqueDeRedirecionamento(janela,textOptions[0]))
        optionSelected=0;
    if (pM->CliqueDeRedirecionamento(janela,textOptions[1]))
        optionSelected=1;
    if (pM->CliqueDeRedirecionamento(janela,textOptions[2]))
        optionSelected=2;
    if (pM->CliqueDeRedirecionamento(janela,textOptions[3]))
        optionSelected=3; //falta implementar o clique específico
    if (pM->CliqueDeRedirecionamento(janela,textOptions[4]))
        optionSelected=4; //falta implementar o clique específico
    if (pM->CliqueDeRedirecionamento(janela,textOptions[5]))
        optionSelected=5;
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::window(Menu* pM, Fase* pF, Entidade* pEnt /*, classes que serão desenhadas imagino*/)
{
    sf::RenderWindow janela (sf::VideoMode(1280,720),"O Equilibrio da Forca");
    janela.setFramerateLimit (120);

    loadMenu(pM);

    while (janela.isOpen())
    {
        sf::Event event;
        while (janela.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela.close();
        }

        janela.clear(sf::Color::Black);
        
        if (optionSelected == -1)
            desenharMenu (pM,janela);
        if (optionSelected == 0)
        {
            desenharFase(pF,janela,pEnt);
        }
        if (optionSelected == 1)
        {
            cout<<"Rank page"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 2)
        {
            cout<<"load atribute"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 3)
        {
            cout<<"change text, level"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 4)
        {
            cout<<"change text player"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 5)
        {
            cout<<"How to play, page"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
    }
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharEnte (Ente* pE)
{

}
void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::posicionarEnte (Ente* pE)
{

}
void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharFase (Fase* pF, sf::RenderWindow & janela, Entidade* pEnt)
{
    //janela.setMouseCursorVisible(false);

    janela.draw(pF->getFundo());
    janela.draw(pF->getGround());
    janela.draw(pF->getPlataforma());
    janela.draw(pEnt->getDrawData());
    

    
    //debug hitbox plataforma
    sf::RectangleShape hitboxVisual(sf::Vector2f(11.0f, 6.0f));
    hitboxVisual.setPosition(270.0f, 270.0f);
    hitboxVisual.setFillColor(sf::Color::Transparent);
    hitboxVisual.setOutlineColor(sf::Color::Red);
    hitboxVisual.setOutlineThickness(1.0f);
    janela.draw(hitboxVisual);




    janela.display();
}