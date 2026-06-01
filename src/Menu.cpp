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

Menu::Menu(): gGraf(), qntdJogadores(1), pJogo()
{
    fases.clear();
    fases.push_back("Mustafar");
    fases.push_back("Hoth");

    faseEscolhida=fases.begin();
    executar();
}

Menu::~Menu()
{
    fases.clear();
    faseEscolhida=fases.end();
    qntdJogadores=-1;
    delete(gGraf);
}

void Menu::executar()
{
    //gGraf=new Gerenciador_Grafico();
    
    //gGraf->window(this);
}

bool Menu::CliqueDeRedirecionamento(sf::RenderWindow& janela, sf::Text& text)
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