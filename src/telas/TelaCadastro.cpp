// src/telas/TelaCadastro.cpp
#include "../../include/telas/TelaCadastro.hpp"
#include <string>

TelaCadastro::TelaCadastro(ServicoAutenticacao* srv) 
    : servico(srv) {}

void TelaCadastro::mostrar() {
    wclear(janela);
    box(janela, 0, 0);
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Desenhar bordas mais elegantes (mesmo estilo da TelaAutenticacao)
    mvwaddch(janela, 0, 0, ACS_ULCORNER);
    mvwhline(janela, 0, 1, ACS_HLINE, largura-2);
    mvwaddch(janela, 0, largura-1, ACS_URCORNER);
    mvwvline(janela, 1, 0, ACS_VLINE, altura-2);
    mvwvline(janela, 1, largura-1, ACS_VLINE, altura-2);
    mvwaddch(janela, altura-1, 0, ACS_LLCORNER);
    mvwhline(janela, altura-1, 1, ACS_HLINE, largura-2);
    mvwaddch(janela, altura-1, largura-1, ACS_LRCORNER);
    
    // Título
    std::string titulo = "Cadastro de Nova Conta";
    int posX = (largura - titulo.length()) / 2;
    mvwprintw(janela, 2, posX, "%s", titulo.c_str());
    mvwhline(janela, 3, posX, ACS_HLINE, titulo.length());
    
    // Campos de entrada
    int colunaCampos = (largura - 30) / 2;
    
    // Nome
    mvwprintw(janela, 5, colunaCampos, "Nome:  ");
    mvwaddch(janela, 5, colunaCampos + 7, '[');
    mvwhline(janela, 5, colunaCampos + 8, ' ', 20);
    mvwaddch(janela, 5, colunaCampos + 28, ']');
    
    // Código
    mvwprintw(janela, 7, colunaCampos, "Codigo:");
    mvwaddch(janela, 7, colunaCampos + 7, '[');
    mvwhline(janela, 7, colunaCampos + 8, ' ', 6);
    mvwaddch(janela, 7, colunaCampos + 14, ']');
    
    // Senha
    mvwprintw(janela, 9, colunaCampos, "Senha: ");
    mvwaddch(janela, 9, colunaCampos + 7, '[');
    mvwhline(janela, 9, colunaCampos + 8, ' ', 5);
    mvwaddch(janela, 9, colunaCampos + 13, ']');
    
    // Instruções
    std::string instrucao = "Pressione Enter apos digitar ou ESC para cancelar";
    mvwprintw(janela, altura-2, (largura - instrucao.length()) / 2, "%s", instrucao.c_str());
    
    wrefresh(janela);
}

Viajante* TelaCadastro::executar() {
    mostrar();
    
    int altura, largura;
    getmaxyx(janela, altura, largura);
    int colunaCampos = (largura - 30) / 2;
    
    while (true) {
        // Ler nome
        wmove(janela, 5, colunaCampos + 8);
        std::string nomeStr = lerEntrada(5, colunaCampos + 8, 20, true);
        
        // Verificar ESC
        if (nomeStr.empty()) return nullptr;
        
        // Ler código
        wmove(janela, 7, colunaCampos + 8);
        std::string codigoStr = lerEntrada(7, colunaCampos + 8, 6, true);
        
        if (codigoStr.empty()) return nullptr;
        
        // Ler senha
        wmove(janela, 9, colunaCampos + 8);
        std::string senhaStr;
        noecho();
        for (int i = 0; i < 5; i++) {
            char c = wgetch(janela);
            if (c == '\n' || c == KEY_ENTER) break;
            if (c == 27) { // ESC
                echo();
                return nullptr;
            }
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
        echo();
        
        try {
            Nome nome(nomeStr);
            Codigo codigo(codigoStr);
            Senha senha(senhaStr);
            
            Conta conta(codigo, senha);
            Viajante viajante(nome, conta);
            
            if (servico->cadastrar(viajante)) {
                std::string sucesso = "Conta criada com sucesso!";
                exibirMensagem(sucesso, 12, (largura - sucesso.length()) / 2);
                wrefresh(janela);
                napms(2000);
                return servico->autenticar(codigo, senha);
            } else {
                std::string erro = "Erro ao criar conta. Tente novamente.";
                exibirMensagem(erro, 12, (largura - erro.length()) / 2);
                wrefresh(janela);
                napms(2000);
                mostrar();
            }
        }
        catch (const std::invalid_argument& e) {
            std::string erro = e.what();
            exibirMensagem(erro, 12, (largura - erro.length()) / 2);
            wrefresh(janela);
            napms(2000);
            mostrar();
        }
    }
}