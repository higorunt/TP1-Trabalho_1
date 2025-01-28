# Instru��es para Configura��o e Execu��o do Projeto TP1-Trabalho

## Pr�-requisitos

Antes de come�ar, certifique-se de ter as seguintes ferramentas instaladas:

- [MSYS2](https://www.msys2.org/): Um ambiente de desenvolvimento para Windows.
- [Code::Blocks](https://www.codeblocks.org/): IDE para C/C++.

### Passo 1: Clonar o Reposit�rio

Clone o reposit�rio do projeto para o seu computador. No terminal ou prompt de comando, execute:

```bash
git clone <url_do_repositorio>
```

### Passo 2: Instalar as Depend�ncias

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
2. No menu do Code::Blocks, clique em File > Open e selecione o arquivo de projeto .hbp dentro do diret�rio clonado do reposit�rio.

O arquivo de projeto est� localizado em:
```
<diret�rio_do_repositorio>/project.hbp
```

### Passo 4: Compilar o Projeto

1. No Code::Blocks, com o projeto aberto, clique em Build na barra de ferramentas ou pressione F9 para compilar o projeto.
2. Caso tudo esteja configurado corretamente, a compila��o ser� realizada sem erros.

### Passo 5: Executar o Projeto

Ap�s a compila��o bem-sucedida, clique em Run ou pressione Ctrl + F10 para executar o projeto.