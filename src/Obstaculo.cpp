#include "../include/Obstaculo.h"
using namespace TrabalhoJogo;
using namespace Obstaculos;

Obstaculo::Obstaculo(ID identificador):Entidade(identificador), danoso(false)
{}

Obstaculo::~Obstaculo()
{}

void Obstaculo::salvarDataBuffer()
{}