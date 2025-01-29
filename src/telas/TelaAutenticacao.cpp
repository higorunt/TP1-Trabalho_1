// src/telas/TelaAutenticacao.cpp
#include "../../include/telas/TelaAutenticacao.hpp"
#include "../../include/telas/TelaCadastro.hpp"
#include <string>
#include <curses.h>

TelaAutenticacao::TelaAutenticacao(ServicoAutenticacao* srv) 
    : servico(srv) {}

Viajante* TelaAutenticacao::fazerLogin() {
    mostrar();
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    int colunaCampos = (largura - 30) / 2; // Centralizado
    int linhaCampos = altura - 10;
    
    while (true) {
        // Campo Código
        std::string codigoStr;
        noecho();
        keypad(janela, TRUE);
        wmove(janela, linhaCampos, colunaCampos + 8);
        wrefresh(janela);

        int ch;
        while ((ch = wgetch(janela)) != KEY_ENTER && ch != '\n') {
            if (ch == KEY_F(1)) { // Tecla F1
                TelaCadastro telaCadastro(servico);
                Viajante* novoViajante = telaCadastro.executar();
                if (novoViajante) return novoViajante;
                mostrar();
                continue;
            }
            if (ch == 27) return nullptr; // ESC

            if (ch == KEY_BACKSPACE || ch == 127) {
                if (!codigoStr.empty()) {
                    codigoStr.pop_back();
                    mvwaddch(janela, linhaCampos, colunaCampos + 8 + codigoStr.length(), ' ');
                }
            } else if (codigoStr.length() < 6 && isprint(ch)) {
                codigoStr += ch;
                mvwaddch(janela, linhaCampos, colunaCampos + 8 + codigoStr.length() - 1, ch);
            }
            wrefresh(janela);
        }

        // Campo Senha
        std::string senhaStr;
        wmove(janela, linhaCampos + 2, colunaCampos + 8);
        wrefresh(janela);

        while ((ch = wgetch(janela)) != KEY_ENTER && ch != '\n') {
            if (ch == 27) return nullptr; // ESC

            if (ch == KEY_BACKSPACE || ch == 127) {
                if (!senhaStr.empty()) {
                    senhaStr.pop_back();
                    mvwaddch(janela, linhaCampos + 2, colunaCampos + 8 + senhaStr.length(), ' ');
                }
            } else if (senhaStr.length() < 5 && isprint(ch)) {
                senhaStr += ch;
                mvwaddch(janela, linhaCampos + 2, colunaCampos + 8 + senhaStr.length() - 1, '*');
            }
            wrefresh(janela);
        }

        // Validação
        try {
            Codigo codigo(codigoStr);
            Senha senha(senhaStr);
            Viajante* viajante = servico->autenticar(codigo, senha);
            
            if (!viajante) {
                mostrarErro("Credenciais inválidas. Tente novamente.");
                continue;
            }
            return viajante;
        } catch (const std::invalid_argument& e) {
            mostrarErro(e.what());
        }
    }
}

void TelaAutenticacao::mostrar() {
    wclear(janela);
    box(janela, 0, 0);
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
     // Logo da UnB (canto inferior esquerdo)
    const char* logo[] = {
        "@@@@@@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@@@@@@",
        " =@@@@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@@@@- ",
        "*-  #@@@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@@@#  -*",
        "***+  -@@@@@@@@@@@@@@@@% %@@@@@@@@@@@@@@@@:  +***",
        "******-  =@@@@@@@@@@@@@% %@@@@@@@@@@@@@=  -******",
        "********+:  =%@@@@@@@@@% %@@@@@@@@@%=  :+********",
        "************-   -%@@@@@% %@@@@@%-   -************",
        "***************=.               .=***************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************",
        "***********************= =***********************"
    };
    
    // Posicionar logo
    int logoY = altura - 15; // 2 linhas acima do fundo
    int logoX = 2; // 2 colunas da borda esquerda
    
    for(int i = 0; i < 13; i++) {
        mvwprintw(janela, logoY + i, logoX, "%s", logo[i]);
    }

    // Campos centralizados
    int colunaCampos = (largura - 30) / 2;
    int linhaCampos = altura - 10;

    mvwprintw(janela, linhaCampos, colunaCampos, "Codigo: ");
    mvwaddch(janela, linhaCampos, colunaCampos + 7, '[');
    mvwhline(janela, linhaCampos, colunaCampos + 8, ' ', 6);
    mvwaddch(janela, linhaCampos, colunaCampos + 14, ']');

    mvwprintw(janela, linhaCampos + 2, colunaCampos, "Senha:  ");
    mvwaddch(janela, linhaCampos + 2, colunaCampos + 7, '[');
    mvwhline(janela, linhaCampos + 2, colunaCampos + 8, ' ', 5);
    mvwaddch(janela, linhaCampos + 2, colunaCampos + 13, ']');

    // Mensagem F1 atualizada
    std::string cadastroOpcao = "Pressione F1 para criar nova conta";
    mvwprintw(janela, linhaCampos + 4, colunaCampos, "%s", cadastroOpcao.c_str());

    wrefresh(janela);
}

void TelaAutenticacao::mostrarErro(const std::string& erro) {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    int caixaAltura = 5;
    int caixaLargura = erro.length() + 8;
    int caixaY = (altura - caixaAltura) / 2;
    int caixaX = (largura - caixaLargura) / 2;

    // Preencher fundo com vermelho
    wattron(janela, COLOR_PAIR(2));
    for (int y = caixaY; y < caixaY + caixaAltura; y++) {
        mvwhline(janela, y, caixaX, ' ', caixaLargura);
    }

    // Bordas
    mvwaddch(janela, caixaY, caixaX, ACS_ULCORNER);
    mvwaddch(janela, caixaY, caixaX + caixaLargura - 1, ACS_URCORNER);
    mvwhline(janela, caixaY, caixaX + 1, ACS_HLINE, caixaLargura - 2);
    mvwhline(janela, caixaY + caixaAltura - 1, caixaX + 1, ACS_HLINE, caixaLargura - 2);
    mvwaddch(janela, caixaY + caixaAltura - 1, caixaX, ACS_LLCORNER);
    mvwaddch(janela, caixaY + caixaAltura - 1, caixaX + caixaLargura - 1, ACS_LRCORNER);

    for (int i = 1; i < caixaAltura - 1; i++) {
        mvwaddch(janela, caixaY + i, caixaX, ACS_VLINE);
        mvwaddch(janela, caixaY + i, caixaX + caixaLargura - 1, ACS_VLINE);
    }

    // Mensagem centralizada
    mvwprintw(janela, caixaY + 2, caixaX + (caixaLargura - erro.length()) / 2, "%s", erro.c_str());
    wattroff(janela, COLOR_PAIR(2));
    
    wrefresh(janela);
    napms(2000);
    mostrar();
}