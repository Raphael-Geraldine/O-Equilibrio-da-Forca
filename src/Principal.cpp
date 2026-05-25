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

#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include "../include/Principal.h"

TrabalhoJogo::Principal::Principal(): pGG(), pMenu(), pAnakin(), pObiWan(), pMustafar(), pPlat()
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete(pMenu);
    delete(pGG);
    delete(pMustafar);
    delete(pPlat);
}

void TrabalhoJogo::Principal::executar()
{
    pMenu=new Menu();
    pGG=new Gerenciador_Grafico();
    
    pAnakin = new Jogador();
    pMustafar = new Mustafar(pAnakin);
    pPlat = new Plataforma();
    pGG->window(pMenu,static_cast<Fase*>(pMustafar),static_cast<Entidade*>(pAnakin),pPlat); //depois vai precisar passar uma lista de fases e entidades!!!
}