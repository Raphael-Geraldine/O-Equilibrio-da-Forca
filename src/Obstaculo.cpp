#include "../include/Obstaculo.h"
using namespace OEquilibrioDaForca;
using namespace Obstaculos;

Obstaculo::Obstaculo():Entidade(), danoso(false)
{}

Obstaculo::~Obstaculo()
{}

void Obstaculo::salvarDataBuffer()
{
    Entidade::salvarDataBuffer();
}