#include <iostream>
using namespace std;

#include "../include/Menu.h"
using namespace TrabalhoJogo;

//#include "../include/Jogador.h"
//using namespace TrabalhoJogo;
//using namespace Entidades;
//using namespace Personagens;

#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

/* #include "../include/Mustafar.h"
#include "../include/Hoth.h"
using namespace TrabalhoJogo;
using namespace Fase; */

#include "../include/Principal.h"

TrabalhoJogo::Principal::Principal(): gG(), menu()
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete(menu);
}

void TrabalhoJogo::Principal::executar()
{
    menu=new Menu();
}