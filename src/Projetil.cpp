/* Para a física e matemática que seguem foram utilizados como referências de ensino superior:
   
   1. Norma de Vetores e arcotangente: Geometria Analítica, Alfredo Steimbruch, Primeira edição
   2. Arrasto e Velocidade Terminal:  Fundamentos de Física, Halliday, Resnick, Walker, Décima Edição, Volume 1 [Mecânica]

   Quanto aos conceitos de ensino médio, advém naturalmente de conhecimento prévio ao ingresso
   na universidade, mas, para todos os efeitos, todos estão contidos nos mesmos livros acima (diretamente ou não).
*/

#define PROJETILPNG "../assets/images/Laser.png"

#include <cmath>
using std::sqrt;
using std::atan2;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using namespace std;

#include "../include/Projetil.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/AT_ST.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

Projetil::Projetil(short int d):
    Entidade(),
    projetilSkin(),
    massa(0.12f),
    coefArrasto(0.25f),
    densidadeAr(1.225f),
    areaSecao(0.006f),
    moduloVelLancamento(800.0f),
    ativo(false),
    dano(d)
{
    x=1700;

    y=800;

    sf::Texture* pTexturaP = pGG->carregarTextura(PROJETILPNG);

    if (pTexturaP == nullptr)
        cerr << "Erro de carregamento do PNG do Projetil" << endl;

    else
        projetilSkin.setTexture(*pTexturaP); 

    sf::FloatRect bounds = projetilSkin.getLocalBounds();
    projetilSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    projetilSkin.setScale(0.15,0.15);

    atualizarPosicaoSprite();
}

Projetil::Projetil(float sx, float sy, float velx, float vely,short int d, bool a):
    Entidade(),
    projetilSkin(),
    massa(0.12f),
    coefArrasto(0.25f),
    densidadeAr(1.225f),
    areaSecao(0.006f),
    moduloVelLancamento(800.0f),
    ativo(a),
    dano(d)
{
    x=sx;
    y=sy;
    velocidade.x=velx;
    velocidade.y=vely;

    sf::Texture* pTexturaP = pGG->carregarTextura(PROJETILPNG);

    if (pTexturaP == nullptr)
        cerr << "Erro de carregamento do PNG do Projetil" << endl;

    else
        projetilSkin.setTexture(*pTexturaP); 

    sf::FloatRect bounds = projetilSkin.getLocalBounds();
    projetilSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    projetilSkin.setScale(0.15,0.15);

    atualizarPosicaoSprite();
}

Projetil::~Projetil()
{
    ativo=false;
}

// 1. Matemática/ Física de Ensino Médio: cálculo de módulo de vetor.
float Projetil::calcularModulo(const sf::Vector2f& vetor) const
{
    return sqrt(vetor.x * vetor.x + vetor.y * vetor.y);
}

// 2. Matemática de Ensino Superior: definição de norma de vetor.
sf::Vector2f Projetil:: normalizar(const sf::Vector2f& vetor) const
{
    const float modulo = calcularModulo(vetor);

    // Evita divisão por zero (Chefão e jogador aproximadamente na mesma posição).
    if (modulo <= 0.0001f)
        return sf::Vector2f(0.0f, 0.0f);

    return sf::Vector2f(vetor.x/ modulo, vetor.y/modulo);
}

// 3. Física de Ensino Superior: Arrasto do ar e velocidade terminal em lançamento com arrasto.
float Projetil::calcularVelTerminal() const
{
    if (massa <= 0.0f || coefArrasto <= 0.0f || densidadeAr <= 0.0f || areaSecao <= 0.0f)
        return 0.0f;

    const float velocidadeTerminalMetros = std::sqrt(
        (2.0f * massa * gravidadeReal) /
        (coefArrasto * densidadeAr * areaSecao)
    );

    return velocidadeTerminalMetros * pixelsPorMetro; // De entidade.
}

sf::Vector2f Projetil::calcularAcelArrasto() const 
{
    const sf::Vector2f velocidadeMetros (
        velocidade.x / pixelsPorMetro,
        velocidade.y / pixelsPorMetro
    );

    const float rapidez = calcularModulo(velocidadeMetros);

    if (rapidez <= 0.0001f || massa <= 0.0f)
        return sf::Vector2f(0.0f, 0.0f);

    const float k = 0.5f * coefArrasto * densidadeAr * areaSecao;

    const sf::Vector2f forcaArrasto(
        -k * rapidez * velocidadeMetros.x,
        -k * rapidez * velocidadeMetros.y
    );

    const sf::Vector2f aceleracaoMetros(
        forcaArrasto.x / massa,
        forcaArrasto.y / massa
    );

    return sf::Vector2f(
        aceleracaoMetros.x * pixelsPorMetro,
        aceleracaoMetros.y * pixelsPorMetro
    );
}

void Projetil::aplicarFisica()
{
    const sf::Vector2f acelArrasto = calcularAcelArrasto();

    gravitar();

    velocidade.x += acelArrasto.x * dt;
    velocidade.y += acelArrasto.y * dt;

    limitarVelTerminal(calcularVelTerminal());
}

void Projetil::desativar() 
{
    ativo=false;
    x=1700.0f;
    y=800.0f;
    velocidade = sf::Vector2f(0.0f, 0.0f);
    atualizarPosicaoSprite();
}

// Matemática de Ensino Médio: Conversão graus <-> radianos.
// Matemática de Ensino Superior: Arcotangente.
void Projetil::atualizarRotacaoSprite()
{
    if (calcularModulo(velocidade) <= 0.0001f)
        return;

    const float anguloRad = atan2(velocidade.y, velocidade.x);   
    const float anguloGraus = anguloRad * 180.0f / 3.14159265f; // Aproximadamente 180.0f / PI

    projetilSkin.setRotation(anguloGraus);
}

void Projetil::executar()
{
    if (ativo)
    {
        aplicarFisica();
        atualizarRotacaoSprite();
        mover();
    }
}

void Projetil::salvar()
{
    Entidade::salvarDataBuffer();
    if (buffer != nullptr)
    {
        *buffer<<to_string(dano)<<' '<<to_string(ativo)<<' '<< "Projetil" <<'%';
    }
}

// Física de Ensino Médio: Movimento Retilínio Uniforme
void Projetil::mover()
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    if((x+(getBounds().width/2.0f))<0 || (x-(getBounds().width/2.0f))>1280 
        || (y+(getBounds().height/2.0f))<0 || (y-(getBounds().height/2.0f))>720)
    {
        desativar();
        return;
    }

    atualizarPosicaoSprite();
}

void Projetil::danificar(Jogador* p)
{
    if (ativo && p != nullptr)
    {
        p->sofrerAtaque(dano);
        desativar();
    }
}

void Projetil::perseguir(Jogador* pJog, AT_ST* pAT)
{
    if (pJog == nullptr || pAT == nullptr)
        return;

    ativo = true;

    const sf::Vector2f origem = pAT->calcularPontoAtirador();
    const sf::Vector2f alvo = pAT->calcularLancamento(pJog, moduloVelLancamento);
    
    x = origem.x;
    y = origem.y;

    const sf::Vector2f direcao (alvo.x - x, alvo.y - y);

    /*
    sf::Vector2f posJog = pJog->getPosicaoAnterior();
    sf::Vector2f posAT = pAT->getPosicaoAnterior();

    x = posAT.x;
    y = posAT.y;

    const sf::Vector2f direcao (posJog.x - x, posJog.y - y);
    */

    const sf::Vector2f direcaoNormalizada = normalizar(direcao);

    // Evitar novamente divisão por zero no cálculo do ângulo.
    if (calcularModulo(direcaoNormalizada) <= 0.0001f)
    {
        desativar();
        return;
    }

    velocidade.x = direcaoNormalizada.x * moduloVelLancamento;
    velocidade.y = direcaoNormalizada.y * moduloVelLancamento;
    


    ativo = true;

    atualizarPosicaoSprite();
}

void Projetil::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    projetilSkin.setPosition(x,y);
}

sf::Sprite Projetil::getDrawData() const 
{
    return projetilSkin;
}

sf::FloatRect Projetil::getBounds() const
{
    return projetilSkin.getGlobalBounds();
}

bool Projetil::getAtivo() const
{
    return ativo;
}

