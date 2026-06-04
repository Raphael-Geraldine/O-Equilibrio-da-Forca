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
    pMenu(nullptr), 
    pAnakin(nullptr),
    pFase(nullptr)
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete (pMenu);
    pMenu = nullptr;

    delete (pFase);
    pFase = nullptr;

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
    pFase = new Mustafar(pAnakin);
    //pMustafar->incluirEntidade(pAnakin);

    pGG->window(pMenu, pFase);
    //pGG->window(pMenu,static_cast<Fase*>(pMustafar)); //depois vai precisar passar uma lista de fases e entidades!!!
}