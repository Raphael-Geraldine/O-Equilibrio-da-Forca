#define LAVAPNG "../assets/images/Lava.png" 

#include "../include/Lava.h"
#include "../include/Jogador.h"
#include "../include/Obstaculo.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;

#include "SFML/Graphics.hpp"

Lava::Lava(): Obstaculo(), largura(1), danosidade(5)
{
    danoso=true;
}
Lava::~Lava()
{

}
void Lava::executar()
{

}
void Lava::salvar()
{

}
void Lava::obstaculizar (Jogador* p)
{

}
void Lava::mover()
{
    //não faz nada, mas precisa ter pois a classe pai tem virtual void mover()
}
sf::Sprite Lava::getDrawData()
{
    return lavaSkin;
}
sf::FloatRect Lava::getBounds() const
{
    return lavaSkin.getGlobalBounds();
}