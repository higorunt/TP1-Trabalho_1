// src/telas/TelaAutenticacao.cpp
#include "../../include/telas/TelaAutenticacao.hpp"
#include <string>

TelaAutenticacao::TelaAutenticacao(ServicoAutenticacao* srv) 
    : servico(srv) {}

void TelaAutenticacao::mostrar() {
    wclear(janela);
    box(janela, 0, 0);
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Desenhar bordas mais elegantes
    mvwaddch(janela, 0, 0, ACS_ULCORNER);
    mvwhline(janela, 0, 1, ACS_HLINE, largura-2);
    mvwaddch(janela, 0, largura-1, ACS_URCORNER);
    mvwvline(janela, 1, 0, ACS_VLINE, altura-2);
    mvwvline(janela, 1, largura-1, ACS_VLINE, altura-2);
    mvwaddch(janela, altura-1, 0, ACS_LLCORNER);
    mvwhline(janela, altura-1, 1, ACS_HLINE, largura-2);
    mvwaddch(janela, altura-1, largura-1, ACS_LRCORNER);
    
    // Título centralizado
    std::string titulo = "Sistema de Planejamento de Viagens";
    int posX = (largura - titulo.length()) / 2;
    mvwprintw(janela, 2, posX, "%s", titulo.c_str());
    
    // Linha decorativa sob o título
    mvwhline(janela, 3, posX, ACS_HLINE, titulo.length());
    
    // Campos de entrada centralizados
    int colunaCampos = (largura - 30) / 2;
    
    // Campo Código - usando caracteres ASCII normais para garantir exibição
    mvwprintw(janela, 6, colunaCampos, "Codigo:");
    mvwaddch(janela, 6, colunaCampos + 7, '[');
    mvwhline(janela, 6, colunaCampos + 8, ' ', 6);
    mvwaddch(janela, 6, colunaCampos + 14, ']');
    
    // Campo Senha
    mvwprintw(janela, 9, colunaCampos, "Senha: ");
    mvwaddch(janela, 9, colunaCampos + 7, '[');
    mvwhline(janela, 9, colunaCampos + 8, ' ', 5);
    mvwaddch(janela, 9, colunaCampos + 13, ']');
    
    // Instruções na parte inferior - garantindo que cabe na tela
    std::string instrucao = "Pressione Enter apos digitar";
    mvwprintw(janela, altura-2, (largura - instrucao.length()) / 2, "%s", instrucao.c_str());
    
    wrefresh(janela);
}

Viajante* TelaAutenticacao::fazerLogin() {
    mostrar();
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    int colunaCampos = (largura - 30) / 2;
    
    while (true) {
        // Ler código na posição correta dentro dos colchetes
        wmove(janela, 6, colunaCampos + 8);
        std::string codigoStr = lerEntrada(6, colunaCampos + 8, 6, true);
        
        // Ler senha com máscara na posição correta
        wmove(janela, 9, colunaCampos + 8);
        std::string senhaStr;
        noecho(); // Desliga o eco dos caracteres
        for (int i = 0; i < 5; i++) {
            char c = wgetch(janela);
            if (c == '\n' || c == KEY_ENTER) break;
            if (c == KEY_BACKSPACE || c == 127) {
                if (i > 0) {
                    i -= 2;
                    wmove(janela, 9, colunaCampos + 8 + i + 1);
                    waddch(janela, ' ');
                    wmove(janela, 9, colunaCampos + 8 + i + 1);
                    if (!senhaStr.empty()) {
                        senhaStr.pop_back();
                    }
                }
                continue;
            }
            senhaStr += c;
            mvwaddch(janela, 9, colunaCampos + 8 + i, '*');
            wrefresh(janela);
        }
        echo(); // Religa o eco dos caracteres
        
        try {
            Codigo codigo(codigoStr);
            Senha senha(senhaStr);
            
            // Limpar mensagens anteriores
            for(int i = 12; i < altura-2; i++) {
                limparLinha(i);
            }
            
            Viajante* viajante = servico->autenticar(codigo, senha);
            
            if (!viajante) {
                std::string erro = "Credenciais inválidas. Tente novamente.";
                exibirMensagem(erro, 12, (largura - erro.length()) / 2);
                wrefresh(janela);
                napms(2000);
                mostrar(); // Redesenha a tela
                continue;
            }
            
            return viajante;
        }
        catch (const std::invalid_argument& e) {
            std::string erro = e.what();
            exibirMensagem(erro, 12, (largura - erro.length()) / 2);
            wrefresh(janela);
            napms(2000);
            mostrar(); // Redesenha a tela
        }
    }
}