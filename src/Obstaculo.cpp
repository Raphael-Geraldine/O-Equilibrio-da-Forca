#include "../include/Obstaculo.h"
using namespace TrabalhoJogo;
using namespace Obstaculos;

Obstaculo::Obstaculo():Entidade(ID::obstaculo), danoso(false)
{}

Obstaculo::~Obstaculo()
{}

void Obstaculo::salvarDataBuffer()
{}