#include "../include/Principal.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include <stdlib.h>
#include <SFML/Graphics.hpp>

short int Gerenciador_Grafico::optionSelected(-1);
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

    textOptions.clear();
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
    textOptions.clear();
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
void Gerenciador_Grafico::desenharEnte (const Ente* pE)
{
    if (pE == NULL)
    {
        cerr << "Erro: ponteiro para Ente nulo." << endl;
        return;
    }

    sf::Sprite spriteEntidade = pE->getDrawData();
    janela.draw(spriteEntidade);
    //desenharOrigem(janela, spriteEntidade);
}

void Gerenciador_Grafico::desenharFase(Fase* pF, sf::RenderWindow& janela) 
{
    if (pF == NULL) 
    {
        cerr << "Erro: Ponteiro para fase nulo." << endl;
        return;
    }

    pF->executar();

    janela.draw(pF->getDrawData());
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
        
        const Ente* pE = (*lEntidades)[i];

        desenharEnte (pE);
    }

    janela.display();
}

void Gerenciador_Grafico::desenharOrigem(sf::RenderWindow& window, const sf::Sprite& sprite) {
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
    
    window.draw(hitbox);
    window.draw(ponto);
}

void Gerenciador_Grafico::posicionarEnte (Ente* pE)
{

}

void Gerenciador_Grafico::desenharMenu (Menu* pM, sf::RenderWindow & janela)
{
    janela.draw(pM->getFundo());
    janela.draw(pM->getDrawData());

    desenharTextoMenu(janela);
        
    janela.display();

    optionSelected = pM->manager(janela,textOptions);
}

void Gerenciador_Grafico::desenharTextoMenu (sf::RenderWindow & janela)
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

void Gerenciador_Grafico::window(Menu* pM, Principal* pP)
{
    pM->loadMenu(textOptions);

    while (janela.isOpen())
    {
        atualizarTempoPercorrido();

        sf::Event event;
        while (janela.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela.close();
        }

        janela.clear(sf::Color::Black);
        
        if (optionSelected == -1)
        {
            desenharMenu(pM,janela);
        }
        if (optionSelected == 0)
        {
            pP->inicializarJogo();
            pP->atualizarFase();

            if (pP->getFase() != nullptr)
                desenharFase(pP->getFase(), janela);
        }
        if (optionSelected == 1)
        {
            cout<<"Rank page"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 2)
        {
            cout<<"load atribute"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 3)
        {
            cout<<"change text, level"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 4)
        {
            cout<<"change text player"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
        if (optionSelected == 5)
        {
            cout<<"How to play, page"<<endl;
            optionSelected = -1; //temp, just to make it works
        }
    }
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
    map<const char*, sf::Texture*>::iterator it;
    for (it = mapaTexturas.begin(); it != mapaTexturas.end(); ++it)
    {
        if (strcmp((*it).first, path) == 0)
            return ((*it).second);
    }

    sf::Texture* textura = new sf::Texture();
    
    if ((*textura).loadFromFile(path) == false) 
    {
        cerr << "Erro: Nao foi possivel carregar textura!" << endl;

        delete (textura);
        textura = nullptr;

        return nullptr;
    }


    mapaTexturas.insert(pair<const char*, sf::Texture*>(path, textura));

    return textura;
}















/*
void Gerenciador_Grafico::desenharFase (Fase* pF, sf::RenderWindow& janela)
{
    //janela.setMouseCursorVisible(false);

    janela.draw(pF->getFundo());
    janela.draw(pF->getGround());
    janela.draw(pF->getPlataforma());

    desenharOrigem(janela, pF->getPlataforma());
    
    TrabalhoJogo::Listas::ListaEntidades* lEntidades = pF->getListaEntidades();
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

