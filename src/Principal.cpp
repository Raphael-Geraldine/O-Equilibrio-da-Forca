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
#include "../include/Hoth.h"

using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;
using namespace Fases;

#include "../include/Principal.h"

TrabalhoJogo::Principal::Principal(): 
    pGG(TrabalhoJogo::Gerenciadores::Gerenciador_Grafico::getGerenciadorGrafico()), 
    pMenu(nullptr), 
    pAnakin(nullptr)
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete (pMenu);
    pMenu = nullptr;

    delete (pFases[0]);
    pFases[0] = nullptr;

    delete (pFases[1]);
    pFases[1] = nullptr;

    delete (pAnakin);
    pAnakin = nullptr;

    // Cuidado: Gerenciador_Grafico é singleton, não deleta aqui.
    pGG = nullptr;

    LEntidades.limpar();
}

void TrabalhoJogo::Principal::executar()
{
    pGG = Gerenciador_Grafico::getGerenciadorGrafico();
    
    Ente::staticSetGG(pGG);

    pMenu = new Menu();
    pAnakin = new Jogador();
    Fase* pFase1 = new Mustafar(pAnakin);
    Fase* pFase2 = new Hoth(pAnakin);
    pFases[0] = pFase1;
    pFases[1] = pFase2;

    //pMustafar->incluirEntidade(pAnakin);

    pGG->window(pMenu, pFases);
}