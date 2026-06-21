#include "../include/Obstaculo.h"
using namespace OEquilibrioDaForca;
using namespace Obstaculos;

Obstaculo::Obstaculo():Entidade(), largura(1), danoso(false)
{}

Obstaculo::~Obstaculo()
{}

void Obstaculo::salvarDataBuffer()
{
    Entidade::salvarDataBuffer();
}