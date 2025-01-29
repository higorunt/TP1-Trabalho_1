// include/telas/TelaBase.hpp
#ifndef TELA_BASE_HPP
#define TELA_BASE_HPP

#include <pdcurses.h>
#include <string>

class TelaBase {
protected:
    WINDOW* janela;

    // Métodos úteis para todas as telas
    void exibirMensagem(const std::string& msg, int linha, int coluna);
    std::string lerEntrada(int linha, int coluna, int maxChars, bool echo = true);
    void limparLinha(int linha);
    void centralizar();

 void desenharCaixaEntrada(int linha, int coluna, int largura) {
        mvwhline(janela, linha, coluna, '_', largura);
    }
    
    void centralizarTexto(const std::string& texto, int linha) {
        int altura, largura;
        getmaxyx(janela, altura, largura);
        int posX = (largura - texto.length()) / 2;
        exibirMensagem(texto, linha, posX);
    }
    
    void desenharBordasElegantes() {
        int altura, largura;
        getmaxyx(janela, altura, largura);
        
        // Cantos
        mvwaddch(janela, 0, 0, ACS_ULCORNER);
        mvwaddch(janela, altura-1, 0, ACS_LLCORNER);
        mvwaddch(janela, 0, largura-1, ACS_URCORNER);
        mvwaddch(janela, altura-1, largura-1, ACS_LRCORNER);
        
        // Bordas horizontais e verticais
        for(int i = 1; i < largura-1; i++) {
            mvwaddch(janela, 0, i, ACS_HLINE);
            mvwaddch(janela, altura-1, i, ACS_HLINE);
        }
        
        for(int i = 1; i < altura-1; i++) {
            mvwaddch(janela, i, 0, ACS_VLINE);
            mvwaddch(janela, i, largura-1, ACS_VLINE);
        }
    }
    
public:
    TelaBase();
    virtual ~TelaBase();
    
    virtual void mostrar() = 0;
    virtual void esconder();
};

#endif