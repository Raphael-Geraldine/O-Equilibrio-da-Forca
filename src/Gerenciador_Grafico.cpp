#define MENUINICIALPNG "../assets/images/MenuInicial.png"
#define ANAKINPNG "../assets/images/Anakin.png"
#define FONTE "../assets/fonts/PressStart2P.ttf"

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
    menuOptions = {"Iniciar o jogo", "Ver o ranking", "Carregar o jogo", "Fase 1: Mustafar", "1 jogador", "Como jogar?"};
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
void Gerenciador_Grafico::desenharEnte (Ente* pE)
{
    if (pE == NULL)
    {
        cerr << "Erro: ponteiro para Ente nulo." << endl;
        return;
    }

    sf::Sprite spriteEntidade = pE->getDrawData();
    janela.draw(spriteEntidade);
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

void Gerenciador_Grafico::desenharMenu (Menu* pM, sf::RenderWindow & janela)
{
    janela.draw(fundo);
    janela.draw(anakin);

    desenharTextoMenu (janela);
        
    janela.display();

    if (pM->CliqueDeRedirecionamento(janela,textOptions[0]))
        optionSelected=0;

    if (pM->CliqueDeRedirecionamento(janela,textOptions[1]))
        optionSelected=1;

    if (pM->CliqueDeRedirecionamento(janela,textOptions[2]))
        optionSelected=2;

    if (pM->CliqueDeRedirecionamento(janela,textOptions[3]))
        optionSelected=3; //falta implementar o clique específico

    if (pM->CliqueDeRedirecionamento(janela,textOptions[4]))
        optionSelected=4; //falta implementar o clique específico

    if (pM->CliqueDeRedirecionamento(janela,textOptions[5]))
        optionSelected=5;
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
    janela.draw(pF->getGround());
    
    ListaEntidades* lEntidades = pF->getListaEntidades();
    
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

void Gerenciador_Grafico::window(Menu* pM, Fase* pF)
{
    loadMenu(pM);

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
            desenharMenu (pM,janela);
        }
        if (optionSelected == 0)
        {
            desenharFase(pF,janela);
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

void Gerenciador_Grafico::loadMenu(Menu* pM)
{
    fundo.setTexture(*carregarTextura(MENUINICIALPNG));
    anakin.setTexture(*carregarTextura(ANAKINPNG));

    anakin.setScale(0.5,0.5);
    anakin.setPosition(50,170);

    if (!fonteMenu.loadFromFile(FONTE))
    {
        cerr << "Erro de carregamento da Fonte no Menu" << endl;
    }

    else
    {
        //cout<<"tudo ok com a fonte"<<endl;
    }

    menuTextPlacement();
}

void Gerenciador_Grafico::menuTextPlacement()
{
    textOptions.clear();
    list<string>::iterator it = menuOptions.begin();
    int posX = 640, posY = 200;
    while (it != menuOptions.end())
    {
        sf::Text text(*it, fonteMenu, 30);
        sf::FloatRect bounds = text.getLocalBounds();
        // Ponto de referência do meio do objeto texto.
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f); 
        // Coloca o ponto de referência na posição a seguir.
        text.setPosition(posX,posY);
        textOptions.push_back(text);
        posY+=70;
        it++;
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

