# O Equilíbrio da Força — macOS Build (Apple Silicon)

> **Nota:** Este projeto foi desenvolvido exclusivamente para **fins educacionais e sem fins lucrativos**.

Este projeto foi um trabalho prático, em **dupla**, desenvolvido por **Marco Vendramin** [(@marcokvendramin)](https://github.com/marcokvendramin) e **Raphael Geraldine** [(@Raphael-Geraldine)](https://github.com/raphael-geraldine). O objetivo principal desta atividade é consolidar o aprendizado teórico obtido na disciplina de Técnicas de Programação, do prof. Jean Marcelo Simão, por meio da aplicação de conceitos de engenharia de software e desenvolvimento orientado a objetos.

<img src="https://github.com/user-attachments/assets/19fd3fa7-1bf5-41b8-91b1-ef3d5466fa11" width="100%" alt="Fase 2" />

## Escopo desta Branch do Repositório

Como **iniciativa própria**, eu, Raphael Geraldine, resolvi ir além das exigências da disciplina e criar uma distribuição nativa, autônoma e polida para macOS (ARM64). Essa experiência reforçou algo fundamental: engenharia de software de baixo nível e atenção à **experiência do usuário** precisam andar juntas. Cuidar de todo o ciclo, do código C++ até a entrega final, é o que transforma um trabalho acadêmico em uma **aplicação completa** e agradável de usar.

Neste sentido, esta branch contém o aplicativo pré-compilado e empacotado como um **Bundle Nativo do macOS (`.app`)**, configurado especificamente para a arquitetura **Apple Silicon**.
> **Nota:** O executável empacotado está disponível diretamente na aba [**Releases**](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/releases) da página do repositório no GitHub na forma de um arquivo de imagem de disco (**`.dmg`**).
>
> 🔍 **Procurando o código-fonte em C++?**  
> Todo o desenvolvimento do jogo, diagramas UML e código em C++/SFML/pthreads estão mantidos na **[branch master (código-fonte principal)](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/tree/master)** e **foram feitos em dupla**.

<img src="https://github.com/user-attachments/assets/c9d7a13e-1f61-4d91-984b-b8b06e35ec4c" width="100%" alt="Menu Principal" />

## Estrutura do Pacote Aplicativo (`.app`)

A estrutura interna do diretório nesta branch segue rigorosamente o padrão de pacotes de aplicativos do **macOS**:

```text
O Equilíbrio da Força.app/
└── Contents/
    ├── Frameworks/      # Dynamic Libraries da SFML (.dylib)
    ├── MacOS/           # Executável binário compilado para ARM64
    ├── Resources/       # Assets (data.txt, texturas, fontes do jogo)
    ├── _CodeSignature/  # Assinatura de código do pacote
    └── Info.plist       # Propriedades e metadados da aplicação macOS
```

## Sobre o Jogo

**“O Equilíbrio da Força”** é um jogo de plataforma 2D inspirado no universo ficcional de **_Star Wars_**. O objetivo principal dos jogadores é derrotar todos os inimigos da fase escolhida. Adicionalmente, se for inserido o nome do jogador, sua jogada vai para o _ranking_, do contrário a jogada é anônima e não gera pontuação. O jogo pode ser disputado por **um ou dois jogadores** simultaneamente, por meio de comandos distintos no teclado.

Durante a partida, os personagens podem se movimentar, saltar e atacar. Cada jogador possui uma quantidade de pontos de vida, reduzida ao entrar em contato com inimigos, projéteis ou obstáculos. Caso todos os jogadores sejam derrotados, a partida é encerrada.

O jogo possui duas fases: **_Mustafar_ (Fase 1) e _Hoth_ (Fase 2)**, que apresentam cenários distintos. Cada qual tem um inimigo exclusivo, além do inimigo fácil presente nas duas. Em _Hoth_, o inimigo exclusivo realiza ataques com projéteis. 

Por meio do menu principal do jogo, o usuário pode selecionar a fase do jogo, escolher a quantidade de jogadores, consultar as instruções de como jogar e visualizar o **_ranking_**. Todos os botões contam com efeitos de _hover_ implementados em SFML para garantir uma melhor **experiência de usuário (UX)**. Além disso, o progresso e o estado atual daa fase pode ser salvo pelo jogador, o que permite o jogador retomar sua jogada posteriormente. O **salvamento** ocorre com arquivo “.txt”.

<img src="https://github.com/user-attachments/assets/6643850e-9392-4ae4-b45c-77cfdd3b9ade" width="100%" alt="fase1" />

## Download

* **Versão:** `v1.0.0-macOS`;
* **Arquitetura:** Apple Silicon (ARM64);
* **Dependências:** Todas as dependências da SFML já inclusas dentro do pacote do aplicativo (`O Equilíbrio da Força.app/Contents/Frameworks`).

### Requisitos Mínimos

* **Processador:** Apple Silicon (M1 ou superior);
* **Sistema Operacional:** macOS 26.0 (Tahoe) ou superior.

<a href="https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/releases" target="_blank"><img src="https://img.shields.io/badge/Baixar_App_macOS-000000?style=for-the-badge&logo=apple&logoColor=white" alt="Baixar DMG" /></a>

> **Nota:** Todas instruções adicionais estão contidas na página de download.

![DMG](https://github.com/user-attachments/assets/0391b1de-9dce-4bf2-bd85-3ae47e7abc76)
