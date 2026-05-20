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

#include "../include/Fase.h"
#include "../include/Mustafar.h"
//#include "../include/Hoth.h"
using namespace TrabalhoJogo;
using namespace Fases;

#include "../include/Principal.h"

TrabalhoJogo::Principal::Principal(): gG(), menu(), pF()
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete(menu);
    delete(gG);
    delete(pF);
}

void TrabalhoJogo::Principal::executar()
{
    menu=new Menu();
    gG=new Gerenciador_Grafico();
    pF = new Mustafar();

    gG->window(menu,pF);
    /*
    while (!(menu->CliqueDeRedirecionamento()))
    {
        cout<<"algo"<<endl;
    }
    cout<<"ei"<<endl;*/
}