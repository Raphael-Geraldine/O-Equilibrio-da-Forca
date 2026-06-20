/* Para a física e matemática que seguem foram utilizados como referências de ensino superior:
   
   1. Colisões e coeficiente de Restituição:  Fundamentos de Física, Halliday, Resnick, Walker, Oitava Edição, Volume 2

   Quanto aos conceitos de ensino médio, advém naturalmente de conhecimento prévio ao ingresso
   na universidade, mas, para todos os efeitos, todos estão contidos nos mesmos livros acima (diretamente ou não).
*/

#include "../include/Gerenciador_Colisoes.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

const float Gerenciador_Colisoes::lim_esq = 0.0f;
const float Gerenciador_Colisoes::lim_dir = 1280.0f;
const float Gerenciador_Colisoes::lim_cima = 0.0f;
const float Gerenciador_Colisoes::lim_baixo = 720.0f;

const float Gerenciador_Colisoes::epsilonJanela = 0.5f;
const float Gerenciador_Colisoes::coefRestTeto = 0.15f;

Gerenciador_Colisoes::Gerenciador_Colisoes():
    LIs(),
    LOs(),
    pJog1(nullptr),
    pJog2(nullptr),
    pChao(nullptr)
{}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
    LIs.clear();
    LOs.clear();

    pJog1 = nullptr;
    pJog2 = nullptr;
    pChao = nullptr;
}

bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == nullptr || pe2 == nullptr)
        return false;

    return (pe1->getBounds()).intersects(pe2->getBounds());
}

void Gerenciador_Colisoes::tratarColisoesJogsObstaculos()
{
    std::list<Obstaculo*>::iterator it; 
    
    for (it = LOs.begin(); it != LOs.end(); ++it)
    {
        if ((*it) == nullptr)
            continue; // Deve ser tolerado de fato?

        Obstaculo* pObs = (*it);

        if (pJog1 != nullptr && verificarColisao (pJog1, pObs))
            tratarColisaoJogObstaculo(pJog1, pObs);

        if (pJog2 != nullptr && verificarColisao (pJog2, pObs))
            tratarColisaoJogObstaculo(pJog2, pObs);
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigos()
{
    int tamanhoInim = static_cast<int>(LIs.size());

    for (int i = 0; i < tamanhoInim; i++)
    {
        Inimigo* pInim = LIs[i];

        if (LIs[i] == nullptr)
            continue; // Deve-se tolerar de fato?
    
        if (pJog1 != nullptr && verificarColisao(pJog1, pInim))
            tratarColisaoJogInimigo(pJog1, pInim);

        if (pJog2 != nullptr && verificarColisao(pJog2, pInim))
            tratarColisaoJogInimigo(pJog2, pInim);
    }
}

void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    //int tamanhoProj = static_cast<int>(LPjs.size());

    set<Projetil*>::iterator it;

    //for (int i = 0; i < tamanhoProj; i++)
    for (it = LPjs.begin(); it != LPjs.end(); ++it)
    {
        //Projetil* pProj = LPjs[i];
        Projetil* pProj = *it;

        //if (LPjs[i] == nullptr)
        if (pProj == nullptr)
            continue; // Deve-se tolerar de fato?
    
        if (pJog1 != nullptr && verificarColisao(pJog1, pProj))
            tratarColisaoJogProjetil(pJog1, pProj);

        if (pJog2 != nullptr && verificarColisao(pJog2, pProj))
            tratarColisaoJogProjetil(pJog2, pProj);
    }
}

void Gerenciador_Colisoes::tratarColisaoJogProjetil(Jogador* pJog, Projetil* pProj)
{
    pProj->danificar(pJog);
}

void Gerenciador_Colisoes::tratarColisoesChaoJogadores()
{
    if (pChao == nullptr)
        return;

    if (pJog1 != nullptr)
        tratarColisaoPersonagemChao(pJog1);

    if (pJog2 != nullptr)
        tratarColisaoPersonagemChao(pJog2);
}

void Gerenciador_Colisoes::tratarColisoesInimObstaculos()
{
    int tamanhoInim = static_cast<int>(LIs.size());

    for (int i = 0; i < tamanhoInim; i++)
    {
        Inimigo* pInim = LIs[i];

        if (LIs[i] == nullptr)
            continue; // Deve-se tolerar de fato?
    
        std::list<Obstaculo*>::iterator it; 

        for (it = LOs.begin(); it != LOs.end(); ++it)
        {
            if ((*it) == nullptr)
                continue; // Deve ser tolerado de fato?

            Obstaculo* pObs = (*it);

            if (verificarColisao(pInim, pObs))
                tratarColisaoInimObstaculo(pInim, pObs);
        }
    }
}

void Gerenciador_Colisoes::tratarColisoesChaoInimigos()
{
    if (pChao == nullptr)
        return;

    int tamanhoInim = static_cast<int>(LIs.size());
    
    for (int i = 0; i < tamanhoInim; i++)
    {
        Inimigo* pInim = LIs[i];

        if (LIs[i] == nullptr)
            continue; // Deve-se tolerar de fato?

        if (pInim != nullptr) 
            tratarColisaoPersonagemChao(pInim);
    }
}

void Gerenciador_Colisoes::tratarColisaoJogObstaculo(Jogador* pJog, Obstaculo* pObs)
{
    if (pJog == nullptr || pObs == nullptr)
        return;

    pObs->obstaculizar(pJog);
}

void Gerenciador_Colisoes::tratarColisaoJogInimigo(Jogador* pJog, Inimigo* pInim)
{
    if (pJog == nullptr || pInim == nullptr)
        return;

    pInim->tentarDanificar(pJog);
    pJog->colidirInimigo(pInim);
}

void Gerenciador_Colisoes::tratarColisaoInimObstaculo(Inimigo* pInim, Obstaculo* pObs)
{
    if (pInim == nullptr || pObs == nullptr)
        return;

    sf::Vector2f velAntes = pInim->getVelocidade();

    pObs->obstaculizarInim(pInim);

    K_2SO* pK2 = dynamic_cast<K_2SO*>(pInim);

    if (pK2 != nullptr && velAntes.y > 0.0f && personagemSobreObstaculo(pK2, pObs))
        pK2->ativarImpacto();
}

void Gerenciador_Colisoes::tratarColisaoPersonagemChao(Personagem* pP)
{
    if (pP == nullptr || pChao == nullptr)
        return;

    sf::FloatRect pBounds = pP->getBounds();
    sf::FloatRect chaoBounds = pChao->getGlobalBounds();
    sf::FloatRect intersecao;

    if (!pBounds.intersects(chaoBounds, intersecao))
        return;

    const float EPSILON = 0.5f;
    const float COEF_REST_PISO = 0.07f;

    sf::Vector2f vel = pP->getVelocidade();
    sf::Vector2f posAnt = pP->getPosicaoAnterior();

    // Como a origem do personagem está no centro:
    sf::FloatRect boundsAnterior(
        posAnt.x - pBounds.width / 2.0f,
        posAnt.y - pBounds.height / 2.0f,
        pBounds.width,
        pBounds.height
    );

    float anteriorBaixo = boundsAnterior.top + boundsAnterior.height;
    float chaoCima = chaoBounds.top;

    // Só faz sentido o caso do personagem vindo de cima.
    if (anteriorBaixo <= chaoCima)
    {
        pP->setY(pP->getY() - intersecao.height - EPSILON);
        float novaVelY = (-1.0f) * vel.y * COEF_REST_PISO;

        // Evita ficar quicando "ad aeternum" no chão.
        if (novaVelY > -20.0f)
            novaVelY = 0.0f;

        pP->setVelocidadeY(novaVelY);

        float personagemBaixo = pP->getY()+(pBounds.height/2.0f); 
        float chaoCima = pChao->getPosition().y;

        if (abs(personagemBaixo - chaoCima) < 2.0f)
        {
            pP->setNoChao(true);

            K_2SO* pK2 = dynamic_cast<K_2SO*>(pP);

            if (pK2 != nullptr && vel.y > 0.0f)
                pK2->ativarImpacto();
        }

        else
            pP->setNoChao(false);

        pP->atualizarPosicaoSprite();
    }
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pI)
{
    if (pI == nullptr) 
        cerr << "Erro: Tentativa de incluir inimigo com ponteiro nulo." << endl;
    else
        LIs.push_back(pI);
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO)
{
    if (pO == nullptr) 
        cerr << "Erro: Tentativa de incluir obstáculo com ponteiro nulo." << endl;
    else
        LOs.push_back(pO);
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pJ)
{
    if (pJ == nullptr) 
        cerr << "Erro: Tentativa de incluir projétil com ponteiro nulo." << endl;
    else
        LPjs.insert(pJ);
}

void Gerenciador_Colisoes::incluirChao(sf::RectangleShape* pC)
{
    if (pC == nullptr) 
        cerr << "Erro: Tentativa de incluir chão com ponteiro nulo." << endl;
    else
        pChao=pC;
}

void Gerenciador_Colisoes::setJog1(Jogador* pJ1)
{
    if (pJ1 == nullptr) 
    {
        cerr << "Erro: Tentativa de incluir Jogador1 com ponteiro nulo." << endl;
        return;
    }

    else
        pJog1 = pJ1;
}

void Gerenciador_Colisoes::setJog2(Jogador* pJ2)
{
    if (pJ2 == nullptr) 
    {
        cerr << "Erro: Tentativa de incluir Jogador2 com ponteiro nulo." << endl;
        return;
    }

    else
        pJog2 = pJ2;
}

void Gerenciador_Colisoes::executar()
{
    // Para cada jogador e inimigo, resetar estado com relação ao chão
    // antes de recalcular colisões no frame e ver se está dentro dos limites.

    if (pJog1 == nullptr && pJog2 == nullptr)
    {
        cerr << "Erro: nenhum jogador cadastrado no Gerenciador de Colisoes." << endl;
        return;
    }

    if (pJog1 != nullptr)
    {
        pJog1->setNoChao(false);
        caracterOutOfBounds(pJog1);
    }

    if (pJog2 != nullptr)
    {
        pJog2->setNoChao(false);
        caracterOutOfBounds(pJog2);
    }
    
    int tamanhoInim = static_cast<int>(LIs.size());

    for (int i = 0; i < tamanhoInim; i++)
    {
        Inimigo* pInim = LIs[i];

        if (LIs[i] == nullptr)
            continue; // Deve-se tolerar de fato?

        if (pInim != nullptr) 
        {
            pInim->setNoChao(false);
            caracterOutOfBounds(pInim);
        }
    }
    
    tratarColisoesChaoJogadores();
    tratarColisoesChaoInimigos();

    tratarColisoesJogsObstaculos();
    tratarColisoesInimObstaculos();

    verificarImpactoK2SO();

    tratarColisoesJogsInimigos();
    tratarColisoesJogsProjeteis();
}

void Gerenciador_Colisoes::caracterOutOfBounds(Entidade* pe)
{
    if (pe == nullptr) 
        return;

    sf::FloatRect bounds = pe->getBounds();
    Jogador* pJog = dynamic_cast<Jogador*>(pe);
    
    bool corrigiu = false;

    // Saiu pela esquerda
    if (bounds.left < lim_esq)
    {
        pe->setX(lim_esq + (bounds.width/2.0f));
        corrigiu = true;
    }

    // Saiu pela direita
    else if (bounds.left + bounds.width > lim_dir)
    {
        pe->setX(lim_dir - (bounds.width/2.0f));
        corrigiu = true;
    }

    bounds = pe->getBounds();

    // Saiu por cima
    if (bounds.top < lim_cima)
    {
        pe->setY(pe->getY() + (lim_cima - bounds.top));
        corrigiu = true;

        if (pJog != nullptr)
        {
            sf::Vector2f vel = pJog->getVelocidade();

            if (vel.y < 0.0f)
            {
                float novaVelY = (-1.0f) * vel.y * coefRestTeto;

                // Garante um pequeno recuo para baixo.
                if (novaVelY < 60.0f)
                    novaVelY = 60.0f;

                pJog->setVelocidadeY(novaVelY);
                pJog->setNoChao(false);
            }
        }
    }

    // Saiu por baixo
    else if (bounds.top + bounds.height > lim_baixo)
    {
        pe->setY(pe->getY() - ((bounds.top + bounds.height) - lim_baixo));
        corrigiu = true;
    }

    if (corrigiu && pJog != nullptr)
    {
        pJog->atualizarPosicaoSprite();

        sf::Vector2f vel = pJog->getVelocidade();

        if (pJog->getBounds().top <= lim_cima && vel.y < 0.0f)
            pJog->setVelocidadeY(0.0f);

        if (pJog->getBounds().left <= lim_esq && vel.x < 0.0f)
            pJog->setVelocidadeX(0.0f);

        if (pJog->getBounds().left + pJog->getBounds().width >= lim_dir && vel.x > 0.0f)
            pJog->setVelocidadeX(0.0f);
    }
}

void Gerenciador_Colisoes::removerInimigo(Inimigo* pI)
{
    if (pI == nullptr)
        return;

    int tamanhoInim = static_cast<int>(LIs.size());

    for (int i = 0; i < tamanhoInim; i++)
    {
        if (LIs[i] == pI)
        {
            LIs.erase(LIs.begin() + i);
            return;
        }
    }
}

void Gerenciador_Colisoes::verificarImpactoK2SO()
{
    int tamanhoInim = static_cast<int>(LIs.size());

    for (int i = 0; i < tamanhoInim; i++)
    {
        if (LIs[i] == nullptr)
            continue;

        Inimigo* pInim = LIs[i];
        
        K_2SO* pK2 = dynamic_cast<K_2SO*>(pInim);

        if (pK2 == nullptr)
            continue;

        if (!pK2->getImpactoAtivo())
            continue;

        bool aplicouEmPlataforma = false;
        bool impactoReconhecido = false;

        std::list<Obstaculo*>::iterator it;
        
        for (it = LOs.begin(); it != LOs.end(); ++it)
        {
            Obstaculo* pObs = *it;

            if (pObs == nullptr)
                continue;

            if (personagemSobreObstaculo(pK2, pObs))
            {
                aplicarImpactoK2EmPlataforma(pK2, pObs);
                aplicouEmPlataforma = true;
                impactoReconhecido = true;
                break;
            }
        }

        if (!aplicouEmPlataforma && personagemSobreChao(pK2))
        {
            if (jogadorNoImpactoChaoK2(pJog1, pK2))
                pJog1->sofrerAtaque(pK2->getDanoImpacto());

            if (jogadorNoImpactoChaoK2(pJog2, pK2))
                pJog2->sofrerAtaque(pK2->getDanoImpacto());
        }

        if (impactoReconhecido)
            pK2->consumirImpacto();
    }
}

bool Gerenciador_Colisoes::personagemSobreObstaculo (Personagem* pP, Obstaculo* pObs)
{
    if (pP == nullptr || pObs == nullptr)
        return false;

    sf::FloatRect pBounds = pP->getBounds();
    sf::FloatRect oBounds = pObs->getBounds();

    float baixoPersonagem = pBounds.top + pBounds.height;
    float topoObstaculo = oBounds.top;

    bool emIntervaloObs = 
        pBounds.left + pBounds.width > oBounds.left &&
        pBounds.left < oBounds.left + oBounds.width;

    bool pertoDoTopo =
        baixoPersonagem >= topoObstaculo - 5.0f &&
        baixoPersonagem <= topoObstaculo + 10.0f;
        
    return (emIntervaloObs && pertoDoTopo);   
}

void Gerenciador_Colisoes::aplicarImpactoK2EmPlataforma(K_2SO* pK2, Obstaculo* pObs)
{
    if (pK2 == nullptr || pObs == nullptr)
        return;

    if (personagemSobreObstaculo(pJog1, pObs))
        pJog1->sofrerAtaque(pK2->getDanoImpacto());

    if (personagemSobreObstaculo(pJog2, pObs))
        pJog2->sofrerAtaque(pK2->getDanoImpacto());
}

bool Gerenciador_Colisoes::jogadorNoImpactoChaoK2 (Jogador* pJog, K_2SO* pK2)
{
    if (pJog == nullptr || pK2 == nullptr)
        return false;

    if (!personagemSobreChao(pJog))
        return false;

    float dx = pJog->getX() - pK2->getX();

    if (dx < 0.0f)
        dx = -dx;

    return dx <= pK2->getRaioImpacto();
}

/*
bool Gerenciador_Colisoes::jogadorNoImpactoChaoK2(Jogador* pJog, K_2SO* pK2)
{
    if (pJog == nullptr || pK2 == nullptr)
        return false;

    if (!pJog->getNoChao())
        return false;

    sf::FloatRect boundsJog = pJog->getBounds();
    float centroJogX = boundsJog.left + boundsJog.width / 2.0f;
    float centroJogY = boundsJog.top + boundsJog.height / 2.0f;


    sf::FloatRect boundsK2 = pK2->getBounds();
    float centroK2X = boundsK2.left + boundsK2.width / 2.0f;
    float centroK2Y = boundsK2.top + boundsK2.height / 2.0f;

    float dx = centroJogX - centroK2X;
    float dy = centroJogY - centroK2Y;

    float distanciaQuadrada = dx * dx + dy * dy;
    float raio = pK2->getRaioImpacto();

    return distanciaQuadrada <= raio * raio; // Para evitar usar sqrt.
}               
*/

bool Gerenciador_Colisoes::personagemSobreChao(Personagem* pP)
{
    if (pP == nullptr || pChao == nullptr)
        return false;

    sf::FloatRect pBounds = pP->getBounds();
    sf::FloatRect chaoBounds = pChao->getGlobalBounds();

    float baixoPersonagem = pBounds.top + pBounds.height;
    float topoChao = chaoBounds.top;

    bool emIntervaloChao =
        pBounds.left + pBounds.width > chaoBounds.left &&
        pBounds.left < chaoBounds.left + chaoBounds.width;

    bool pertoDoTopo =
        baixoPersonagem >= topoChao - 5.0f &&
        baixoPersonagem <= topoChao + 10.0f;

    return emIntervaloChao && pertoDoTopo;
}