#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Menu.h"
#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Gerenciador_Grafico.h"
#include "../include/Fase.h"
#include "../include/Mustafar.h"

using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;
using namespace Fases;

#include "../include/Principal.h"

TrabalhoJogo::Principal::Principal(): 
    pGG(TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico()), 
    pMenu(), 
    LEntidades(),
    pMustafar()
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete(pMenu);
    delete(pGG);
    delete(pMustafar);
    LEntidades.limpar();
}

void TrabalhoJogo::Principal::executar()
{
    pMenu = new Menu();
    pAnakin = new Jogador();
    pMustafar = new Mustafar();
    pMustafar->incluirEntidade(pAnakin);
    pGG = TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico();
    pGG->window(pMenu,static_cast<Fase*>(pMustafar)); //depois vai precisar passar uma lista de fases e entidades!!!
}