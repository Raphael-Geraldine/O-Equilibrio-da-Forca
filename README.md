# O Equilíbrio da Força — macOS Build (Apple Silicon)

> **Nota:** Este projeto foi desenvolvido exclusivamente para **fins educacionais e sem fins lucrativos**.

Esta branch contém o aplicativo pré-compilado e empacotado como um **Bundle Nativo do macOS (`.app`)**, configurado especificamente para a arquitetura **Apple Silicon**.

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

## Download

> **Nota:** O executável empacotado está disponível diretamente na aba [**Releases**](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/releases) da página do repositório no GitHub na forma de um arquivo de imagem de disco (**`.dmg`**).

* **Versão:** `v1.0.0-macOS`
* **Arquitetura:** Apple Silicon (ARM64)
* **Dependências:** Todas as dependências da SFML já inclusas dentro do pacote do aplicativo (`O Equilíbrio da Força.app/Contents/Frameworks`).

## Requisitos Mínimos

* **Processador:** Apple Silicon (M1 ou superior)
* **Sistema Operacional:** macOS 26.0 (Tahoe) ou superior

## Instruções de Instalação e Execução
Como este projeto educacional é distribuído sem um certificado pago de desenvolvedor, o sistema de segurança do macOS (Gatekeeper) aplicará uma quarentena ao arquivo baixado, podendo exibir um aviso de "Aplicativo danificado".

**1. Obtenção do App**

* **Via `.dmg` (Recomendado):** Baixe o `.dmg` na página de [**Releases**](https://github.com/Raphael-Geraldine/O-Equilibrio-da-Forca/releases), todas instruções necessárias estão contidas lá.
* **Via Git Clone:** Clone esta branch e mova o diretório `O Equilíbrio da Força.app` diretamente para a pasta `/Applications`.

**2. Liberação do Gatekeeper** (caso via Git Clone)

Abra o Terminal do macOS e execute os comandos abaixo para autorizar a pasta do app e remover a quarentena do sistema:
```zsh
cd /
chmod -R u+rw /Applications/"O Equilíbrio da Força.app"
xattr -cr /Applications/"O Equilíbrio da Força.app"
codesign --force --deep --sign - /Applications/"O Equilíbrio da Força.app"
```
