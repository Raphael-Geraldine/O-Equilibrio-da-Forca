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
using namespace TrabalhoJogo;

#include "../include/Gerenciador_Grafico.h"

#include <SFML/graphics.hpp>
#include <stdlib.h>

TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico()
{
    textOptions.clear();
    menuOptions = {"Iniciar o jogo", "Ver o ranking", "Carregar o jogo", "Fase 1: Mustafar", "1 jogador", "Como jogar?"};
}
TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{
    textOptions.clear();
}

//void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharEnte (Ente* pE)

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::menuTextPlacement(sf::Font& fonteMenu)
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
        janela.draw(textOptions[i]);
}

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharMenu (Menu* pM)
{
    sf::RenderWindow janela (sf::VideoMode(1280,720),"O Equilibrio da Forca");
    janela.setFramerateLimit (120);

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

    sf::Font fonteMenu;
    if (!fonteMenu.loadFromFile(FONTE))
    {
        cerr << "Erro de carregamento da Fonte no Menu" << endl;
    }
    else
    {
        //cout<<"tudo ok com a fonte"<<endl;
    }

    menuTextPlacement(fonteMenu);

    while (janela.isOpen())
    {
        sf::Event event;
        while (janela.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela.close();
        }

        janela.clear(sf::Color::Black);
        janela.draw(fundo);
        janela.draw(anakin);

        desenharTextoMenu (janela);
        
        janela.display();

        pM->CliqueDeRedirecionamento(janela,textOptions[0]);
        pM->CliqueDeRedirecionamento(janela,textOptions[1]);
        pM->CliqueDeRedirecionamento(janela,textOptions[2]);
        pM->CliqueDeRedirecionamento(janela,textOptions[3]); //falta implementar o clique específico
        pM->CliqueDeRedirecionamento(janela,textOptions[4]); //falta implementar o clique específico
        pM->CliqueDeRedirecionamento(janela,textOptions[5]);
    }
}
