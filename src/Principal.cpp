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
    pFase(nullptr),
    pAnakin1(nullptr),
    pObi1(nullptr)
{
    executar();
}

TrabalhoJogo::Principal::~Principal()
{
    delete (pMenu);
    pMenu = nullptr;

    if (pFase != nullptr)
        delete (pFase);
    pFase = nullptr;

    if (pAnakin1 != nullptr)
        delete (pAnakin1);
    pAnakin1 = nullptr;

    if (pObi1 != nullptr)
        delete (pObi1);
    pObi1 = nullptr;

    // Cuidado: Gerenciador_Grafico é singleton, não deleta aqui.
    pGG = nullptr;

    LEntidades.limpar();
}

void TrabalhoJogo::Principal::executar()
{
    pGG = Gerenciador_Grafico::getGerenciadorGrafico();
    
    Ente::staticSetGG(pGG);

    pMenu = new Menu();
    
    //pMustafar->incluirEntidade(pAnakin);

    pGG->window(pMenu, this);
}

Fase* TrabalhoJogo::Principal::getFase()
{
    if (pAnakin1 == nullptr) //ou seja, início de jogo
    {
        short int qntd = pMenu->getJogsEscolhido();
        short int fase = pMenu->getFaseEscolhida();
        
        pAnakin1 = new Jogador();
        
        if(qntd != 1)
            pObi1 = new Jogador();
        
        if (!fase) //0 é Mustafar
            pFase = new Mustafar(pAnakin1, pObi1);
        else
            pFase = new Hoth(pAnakin1, pObi1);
    }
    if(!(pFase->getVivos())) //ou seja, quando derrotar todos inimigos
    {
        Mustafar* pMustafar = dynamic_cast<Mustafar*>(pFase);
        if (pMustafar != nullptr)
        {
            delete(pFase);
            pFase = new Hoth(pAnakin1, pObi1);
        }
        else
        {
            cout<<"Cabou!"<<endl; //preparar caminho coltar menu
        }
    }
    return pFase;
}