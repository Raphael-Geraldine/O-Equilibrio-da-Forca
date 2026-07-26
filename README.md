# O Equilíbrio da Força
> **Nota:** Este projeto foi desenvolvido exclusivamente para **fins educacionais e sem fins lucrativos**.

Este projeto foi um trabalho prático desenvolvido no âmbito da disciplina de Técnicas de Programação, ofertada pelo Departamento Acadêmico de Informática (DAINF) da Universidade Tecnológica Federal do Paraná (UTFPR). O objetivo principal desta atividade é consolidar o aprendizado teórico obtido em sala de aula por meio da aplicação de conceitos de engenharia de software e desenvolvimento orientado a objetos. 

O método utilizado para a concepção deste trabalho digital seguiu um ciclo simplificado de Engenharia de _Software_, através da rigorosa compreensão e levantamento dos requisitos funcionais pré-estabelecidos, que foram revisitados naturalmente e extensivamente no decorrer do projeto. Subsequentemente, realizou-se a modelagem de análise e projeto em Linguagem de Modelagem Unificada (UML, do inglês _Unified Modeling Language_), estendendo e derivando o diagrama de classes padrão arquitetural fornecido pelo professor Jean Marcelo Simão. A fase de implementação foi concretizada na **linguagem C++**, adotando-se os paradigmas clássicos e avançados de **Programação Orientada a Objetos (POO)**, com o suporte da biblioteca gráfica **_Simple and Fast Multimedia Library_ (SFML)** e concorrência via **POSIX Threads (pthreads)**.

<img width="1920" height="1080" alt="fase2" src="https://github.com/user-attachments/assets/19fd3fa7-1bf5-41b8-91b1-ef3d5466fa11" />

## Sobre o jogo

**“O Equilíbrio da Força”** é um jogo de plataforma 2D inspirado no universo ficcional de **_Star Wars_**. O objetivo principal dos jogadores é derrotar todos os inimigos da fase escolhida. Adicionalmente, se for inserido o nome do jogador, sua jogada vai para o _ranking_, do contrário a jogada é anônima e não gera pontuação. O jogo pode ser disputado por **um ou dois jogadores** simultaneamente, por meio de comandos distintos no teclado.

Durante a partida, os personagens podem se movimentar, saltar e atacar. Cada jogador possui uma quantidade de pontos de vida, reduzida ao entrar em contato com inimigos, projéteis ou obstáculos. Caso todos os jogadores sejam derrotados, a partida é encerrada.

O jogo possui duas fases: **_Mustafar_ (Fase 1) e _Hoth_ (Fase 2)**, que apresentam cenários distintos. Cada qual tem um inimigo exclusivo, além do inimigo fácil presente nas duas. Em _Hoth_, o inimigo exclusivo realiza ataques com projéteis. 

Por meio do menu principal do jogo, o usuário pode selecionar a fase do jogo, escolher a quantidade de jogadores, consultar as instruções de como jogar e visualizar o **_ranking_**. Esse juntamente com o progresso na fase pode ser salvo pelo jogador, o que permite retomar a jogada anterior. O **salvamento** ocorre com arquivo “.txt”.

<img width="1920" height="1080" alt="• O Equilibrio da Força" src="https://github.com/user-attachments/assets/c9d7a13e-1f61-4d91-984b-b8b06e35ec4c" />

## Diagrama de Classes (UML)

O projeto foi modelado estendendo e derivando a arquitetura orientada a objetos proposta para a disciplina. Abaixo está a representação estrutural das classes, relacionamentos e heranças implementadas no jogo:

<img width="7015" height="4960" alt="OEquilibrioDaForca" src="https://github.com/user-attachments/assets/5a8c8690-73f9-4775-8e8c-e870a84d0bea" />

## Estrutura do Repositório

O projeto está organizado da seguinte forma:

```text
.
├── assets/          # Fontes, imagens e arquivos de dados
│   ├── fonts/
│   ├── images/
│   └── data.txt
├── include/         # Arquivos de cabeçalho (.h)
└── src/             # Código-fonte (.cpp)
```
## Pré-requisitos e Compilação
Para compilar e executar o projeto a partir do código-fonte, você precisará de:
* **Compilador C/C++** (como GCC, Clang ou MinGW para Windows).
* **Biblioteca SFML** (versão 2.6.2 instalada em seu sistema).

<img width="1920" height="1080" alt="fase1" src="https://github.com/user-attachments/assets/f1e7bafc-23cc-4067-8181-c71cbb9abd63" />

## Download do Executável

🍎 macOS:

* **Instalador (`.dmg`):** O arquivo ".dmg" compilado para instalação direta no macOS está disponível na seção de [`Releases`](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/releases) do repositório.
* **App nativo (`.app`):** Você pode baixar a aplicação pronta na branch [`build-macos`](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/tree/build-macos).

💻 Windows & Linux:

Para rodar no Windows ou Linux, clone a branch master e compile o código em seu compilador favorito.

## Desenvolvedores
Projeto desenvolvido por:
* Marco Antônio Kochem Vendramin [(@marcokvendramin)](https://github.com/marcokvendramin)
* Raphael Bassil Costa Geraldine [(@Raphael-Geraldine)](https://github.com/raphael-geraldine)
