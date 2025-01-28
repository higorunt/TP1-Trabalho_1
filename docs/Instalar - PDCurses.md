# Instruções para Configuração e Execução do Projeto TP1-Trabalho

## Pré-requisitos

Antes de começar, certifique-se de ter as seguintes ferramentas instaladas:

- [MSYS2](https://www.msys2.org/): Um ambiente de desenvolvimento para Windows.
- [Code::Blocks](https://www.codeblocks.org/): IDE para C/C++.

### Passo 1: Clonar o Repositório

Clone o repositório do projeto para o seu computador. No terminal ou prompt de comando, execute:

```bash
git clone <url_do_repositorio>
```

### Passo 2: Instalar as Dependências

Abra o terminal do MSYS2 e execute os seguintes comandos para instalar o MinGW e o PDCurses:

#### Instalar o MinGW (GCC)
```bash
pacman -S mingw-w64-x86_64-gcc
```

#### Instalar o PDCurses
```bash
pacman -S mingw-w64-x86_64-pdcurses
```

### Passo 3: Abrir o Projeto no Code::Blocks

1. Abra o Code::Blocks.
2. No menu do Code::Blocks, clique em File > Open e selecione o arquivo de projeto .hbp dentro do diretório clonado do repositório.

O arquivo de projeto está localizado em:
```
<diretório_do_repositorio>/project.hbp
```

### Passo 4: Compilar o Projeto

1. No Code::Blocks, com o projeto aberto, clique em Build na barra de ferramentas ou pressione F9 para compilar o projeto.
2. Caso tudo esteja configurado corretamente, a compilação será realizada sem erros.

### Passo 5: Executar o Projeto

Após a compilação bem-sucedida, clique em Run ou pressione Ctrl + F10 para executar o projeto.