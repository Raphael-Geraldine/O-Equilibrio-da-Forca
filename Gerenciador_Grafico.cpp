#define MENUINICIALPNG "/Users/samurai_Bacon/Downloads/OEquillibrioDaForca/fundos/MenuInicial.png"
//#define MENUINICIALPNG "MenuInicial.png"

#define ANAKINPNG "/Users/samurai_Bacon/Downloads/OEquillibrioDaForca/fundos/Anakin.png"
//#define ANAKINPNG "Anakin.png"

#define FONTE "/Users/samurai_Bacon/Downloads/OEquillibrioDaForca/fontes/PressStart2P.ttf"
//#define FONTE "PressStart2P.ttf"

#include <iostream>
using namespace std;

#include "Menu.h"
using namespace TrabalhoJogo;

#include "Gerenciador_Grafico.h"
#include <SFML/graphics.hpp>

TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico()
{

}
TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{

}

//void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharEnte (Ente* pE)

void TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::desenharMenu (Menu* pM)
{
    sf::RenderWindow janela (sf::VideoMode(1280,720),"O Equilibrio da Forca");

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

    sf::Text textIniciar("Iniciar o jogo", fonteMenu, 30);
    textIniciar.setPosition(400,200);

    sf::Text textRank("Ver o ranking", fonteMenu, 30);
    textRank.setPosition(420,270);

    sf::Text textLoad("Carregar o jogo", fonteMenu, 30);
    textLoad.setPosition(390,340);

    sf::Text textFase("Fase 1: Mustafar", fonteMenu, 30);
    textFase.setPosition(385,410);

    sf::Text textPlayers("1 jogador", fonteMenu, 30);
    textPlayers.setPosition(460,480);

    sf::Text textRules("Como jogar?", fonteMenu, 30);
    textRules.setPosition(440,550);

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
        janela.draw(textIniciar);
        janela.draw(textRank);
        janela.draw(textLoad);
        janela.draw(textFase);
        janela.draw(textPlayers);
        janela.draw(textRules);
        janela.display();

        pM->CliqueNoTexto(janela,textIniciar);
        pM->CliqueNoTexto(janela,textRank);
        pM->CliqueNoTexto(janela,textLoad);
        pM->CliqueNoTexto(janela,textFase);
        pM->CliqueNoTexto(janela,textPlayers);
        pM->CliqueNoTexto(janela,textRules);
    }
}