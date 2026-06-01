#include <iostream>
using namespace std;

#include "../include/Menu.h"
using namespace TrabalhoJogo;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include "../include/Fase.h"
#include "../include/Mustafar.h"
//#include "../include/Hoth.h"
using namespace TrabalhoJogo;
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