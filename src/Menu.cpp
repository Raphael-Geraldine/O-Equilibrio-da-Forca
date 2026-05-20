#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../include/Menu.h"
#include <SFML/graphics.hpp>

#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

TrabalhoJogo::Menu::Menu(): gGraf(), qntdJogadores(1)
{
    fases.clear();
    fases.push_back("Mustafar");
    fases.push_back("Hoth");

    faseEscolhida=fases.begin();
    executar();
}

TrabalhoJogo::Menu::~Menu()
{
    fases.clear();
    faseEscolhida=fases.end();
    qntdJogadores=-1;
    delete(gGraf);
}

void TrabalhoJogo::Menu::executar()
{
    //gGraf=new Gerenciador_Grafico();
    
    //gGraf->window(this);
}

bool TrabalhoJogo::Menu::CliqueDeRedirecionamento(sf::RenderWindow& janela, sf::Text& text)
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