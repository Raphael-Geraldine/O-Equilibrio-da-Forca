#define FONTE "../assets/fonts/PressStart2P.ttf"

#include "../include/Jogo.h"
#include "../include/Personagem.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

#include <string>
using namespace std;
#include <stdlib.h>
#include <SFML/Graphics.hpp>

float Gerenciador_Grafico::dt = 0;

Gerenciador_Grafico* Gerenciador_Grafico::pGrafico = nullptr;

void Gerenciador_Grafico::destruirGGrafico() 
{
    if (pGrafico != nullptr) 
    {
        delete pGrafico;
        pGrafico = nullptr;
    }
}

/*
void Gerenciador_Grafico::destruirGGrafico() 
{
    if (Gerenciador_Grafico::getGerenciadorGrafico() != nullptr) 
    {
        delete (Gerenciador_Grafico::getGerenciadorGrafico());
    }
}
*/

Gerenciador_Grafico::Gerenciador_Grafico()
{
    janela.create (sf::VideoMode(1280,720),"O Equilibrio da Forca");
    janela.setFramerateLimit(120);

    if (!fonteName.loadFromFile(FONTE))
        cerr << "Erro de carregamento da Fonte no Menu" << endl;
    nameType.setFont(fonteName);

    //textOptions.clear();
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
    map<const char*, sf::Texture*>::iterator it;

    for (it = mapaTexturas.begin(); it != mapaTexturas.end(); ++it) 
    {
        if((*it).second)    
            delete ((*it).second);

        ((*it).second) = nullptr;
    }

    mapaTexturas.clear();
    //textOptions.clear();
}

sf::RenderWindow* Gerenciador_Grafico::getJanela()
{
    return &janela;
}

Gerenciador_Grafico* Gerenciador_Grafico::getGerenciadorGrafico()
{
    if (pGrafico == nullptr) 
    {
        pGrafico = new Gerenciador_Grafico();
        std::atexit(destruirGGrafico);
    }

    return pGrafico;
}
void Gerenciador_Grafico::desenharEnte (Ente* pE)
{
    if (pE == NULL)
    {
        cerr << "Erro: ponteiro para Ente nulo." << endl;
        return;
    }

    //sf::Sprite spriteEntidade = pE->getDrawData();
    //janela.draw(spriteEntidade);
    //desenharOrigem(janela, spriteEntidade);
    pE->desenhar();

    Inimigo* pI = dynamic_cast<Inimigo*>(pE);
    if (pI != nullptr)
        janela.draw(pI->getBarraVida());
}

void Gerenciador_Grafico::desenharFase(Fase* pF) 
{
    if (pF == NULL) 
    {
        cerr << "Erro: Ponteiro para fase nulo." << endl;
        return;
    }

    pF->desenhar();
    janela.draw(pF->getChao());
    
    const Listas::ListaEntidades* lEntidades = pF->getListaEntidades();
    
    if (lEntidades == NULL)
    {
        std::cerr << "Lista de entidades nula." << std::endl;
        return;
    }

    int tamanho = static_cast<int> (lEntidades->getTamanho());

    for (int i = 0; i < tamanho; i++) 
    {
        if ((*lEntidades)[i] == NULL) 
        {
            cerr << "Entidade nula no indice " << i << "." << endl;
            continue;
        }
        
        Ente* pE = (*lEntidades)[i];
        Personagem* pP = dynamic_cast<Personagem*>(pE);
        if ((pP != nullptr && pP->getVida() > 0) || pP==nullptr)
        {
            desenharEnte (pE);
            //desenharOrigem(janela,pE->getDrawData());
        }
            
    }

    //janela.display(); o display é dado após desenhar a vida
}

void Gerenciador_Grafico::desenharOrigem(const sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::RectangleShape hitbox(sf::Vector2f(bounds.width, bounds.height));
    
    hitbox.setPosition(bounds.left, bounds.top);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
    
    float raio = 4.f;
    sf::CircleShape ponto(raio);
    ponto.setFillColor(sf::Color::Red);
    ponto.setOrigin(raio, raio);
    ponto.setPosition(sprite.getPosition());
    
    janela.draw(hitbox);
    janela.draw(ponto);
}

void Gerenciador_Grafico::posicionarEnte (Ente* pE)
{

}

void Gerenciador_Grafico::desenharMenu (Menu* pM, vector<sf::Text>& text)
{
    janela.draw(pM->getFundo());
    pM->desenhar();

    desenharTextoMenu(text);
        
    janela.display();
}

void Gerenciador_Grafico::desenharTextoMenu (vector<sf::Text>& textOptions)
{
    // Chamada fora do loop.
    sf::Vector2f mousePosition = janela.mapPixelToCoords(sf::Mouse::getPosition(janela)); 

    for (int i=0; i<textOptions.size();i++)
    {   
        if (textOptions[i].getGlobalBounds().contains(mousePosition))
        {
            sf::Color hover(255,255,255,170);
            textOptions[i].setFillColor(hover);
        }
        else
        {
            textOptions[i].setFillColor(sf::Color::White);
        }

        janela.draw(textOptions[i]); // Após ajuste de cores.
    }
} 

void Gerenciador_Grafico::desenharSolicitar1Nome(sf::Event& event, const sf::Sprite& fundo, string& nome)
{
    janela.draw(fundo);
    nameType.setString(nome);

    if (event.type == sf::Event::TextEntered && typingDelay.getElapsedTime().asMilliseconds()>=200) 
    {       
        if (event.text.unicode == '\b') 
        {
            if (!nome.empty())
                nome.pop_back();
        }
        else if ((event.text.unicode > 64 && event.text.unicode < 91 ||
                  event.text.unicode > 96 && event.text.unicode < 123)
                  && nome.size()<15)
            nome += static_cast<char>(event.text.unicode);
 
        nameType.setString(nome);
        nameType.setFillColor(sf::Color::White);
        sf::FloatRect bounds = nameType.getLocalBounds();
        nameType.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
        nameType.setPosition(640,315);

        typingDelay.restart();
    }

    janela.draw(nameType);

    //cout<<nome<<endl;

    janela.display();
}

float Gerenciador_Grafico::getDeltaTempo()
{
    return dt;
}

void Gerenciador_Grafico::atualizarTempoPercorrido() 
{
    dt = relogio.getElapsedTime().asSeconds();
    relogio.restart();
}

sf::Texture* Gerenciador_Grafico::carregarTextura (const char* path)
{
    if (path == nullptr) {
        cerr << "Erro: Caminho para textura nulo!" << endl;
        return nullptr;
    }

    map<const char*, sf::Texture*>::iterator it;
    
    for (it = mapaTexturas.begin(); it != mapaTexturas.end(); ++it)
    {
        if (strcmp((*it).first, path) == 0)
            return ((*it).second);
    }

    sf::Texture* textura = new sf::Texture();
    
    if (!(*textura).loadFromFile(path)) 
    {
        cerr << "Erro: Nao foi possivel carregar textura!" << endl;

        delete (textura);
        textura = nullptr;

        return nullptr;
    }


    mapaTexturas.insert(pair<const char*, sf::Texture*>(path, textura));

    return textura;
}

void Gerenciador_Grafico::desenharRank(const vector<string>& linhasRank, sf::Sprite& fundo)
{
    janela.draw(fundo);

    // vector<ElemRank*>::iterator it;
    vector<string>::const_iterator it;
    int i=1;

    for (it = linhasRank.begin(); it != linhasRank.end(); it++)
    {
        sf::Text textToDisplay(*it,fonteName);
        textToDisplay.setFillColor(sf::Color::White);
        
        sf::FloatRect bounds = textToDisplay.getLocalBounds();
        textToDisplay.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
        
        float y = 130 + (70*i);
        textToDisplay.setPosition(640,y);

        i++;
        
        janela.draw(textToDisplay);
    }
    /*
    for(it=jogsRank.begin();it!=jogsRank.end();++it)
    {
        string jogador = to_string(i) + "o lugar: " + (*it)->getNome() + " - " + to_string((*it)->getPontos()) + " pontos";
        sf::Text textToDisplay(jogador,fonteName);
        textToDisplay.setFillColor(sf::Color::White);
        sf::FloatRect bounds = textToDisplay.getLocalBounds();
        textToDisplay.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
        float y = 130 + (70*i);
        textToDisplay.setPosition(640,y);
        i++;
        janela.draw(textToDisplay);
    }
    */

    janela.display();
}

void Gerenciador_Grafico::desenharVida(Jogador* pJ1, Jogador* pJ2)
{
    if(pJ1 != nullptr)
    {
        string vida = "VIDA JOG1: " + to_string(pJ1->getVida()) + "%";
        sf::Text textToDisplay(vida,fonteName,16);
        textToDisplay.setFillColor(sf::Color::Yellow);
        textToDisplay.setPosition(20,20);
        janela.draw(textToDisplay);
    }
    if(pJ2 != nullptr)
    {
        string vida = "VIDA JOG2: " + to_string(pJ2->getVida()) + "%";
        sf::Text textToDisplay(vida,fonteName,16);
        textToDisplay.setFillColor(sf::Color::Yellow);
        sf::FloatRect bounds = textToDisplay.getLocalBounds();
        textToDisplay.setOrigin(bounds.left + bounds.width, bounds.top); 
        textToDisplay.setPosition(1260,20);
        janela.draw(textToDisplay);
    }
    //janela.display();
}

void Gerenciador_Grafico::mostrar()
{
    janela.display();
}

void Gerenciador_Grafico::desenharComoJogar(sf::Sprite& fundo)
{
    janela.draw(fundo);
    janela.display();
}

void Gerenciador_Grafico::desenharMenuPause(sf::Sprite& pause)
{
    sf::RectangleShape fundo(sf::Vector2f(1280, 720));
    sf::Color cor(160,160,160,100);
    fundo.setFillColor(cor);
    janela.draw(fundo);
    janela.draw(pause);
}







/*
void Gerenciador_Grafico::desenharFase (Fase* pF)
{
    //janela.setMouseCursorVisible(false);

    janela.draw(pF->getFundo());
    janela.draw(pF->getGround());
    janela.draw(pF->getPlataforma());

    desenharOrigem(janela, pF->getPlataforma());
    
    OEquilibrioDaForca::Listas::ListaEntidades* lEntidades = pF->getListaEntidades();
    int tamanho = static_cast<int>(lEntidades->getTamanho());
    for (int i = 0; i < tamanho; i++) 
    {
        Entidade* pEnt = (*lEntidades)[i];

        if (pEnt == NULL) 
            cerr << "Ponteiro nulo em lista de Entidades." << endl;
        
        else 
            janela.draw(pEnt->getDrawData());
            desenharOrigem(janela, pEnt->getDrawData());
    }

    janela.display();
}
*/

