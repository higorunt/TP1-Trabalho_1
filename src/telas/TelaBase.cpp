// src/telas/TelaBase.cpp
#include "../../include/telas/TelaBase.hpp"

TelaBase::TelaBase() : janela(nullptr) {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    // Configurar cores
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    
    centralizar();
}

TelaBase::~TelaBase() {
    esconder();
}

void TelaBase::centralizar() {
    int altura = 15;
    int largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;
    
    if (janela) delwin(janela);
    janela = newwin(altura, largura, startY, startX);
    
    wbkgd(janela, COLOR_PAIR(1));
    box(janela, 0, 0);
    refresh();
    wrefresh(janela);
}

void TelaBase::exibirMensagem(const std::string& msg, int linha, int coluna) {
    limparLinha(linha);
    mvwprintw(janela, linha, coluna, msg.c_str());
    wrefresh(janela);
}

std::string TelaBase::lerEntrada(int linha, int coluna, int maxChars, bool echo) {
    char buffer[256] = {0};
    
    if (echo) ::echo(); else noecho();
    wmove(janela, linha, coluna);
    wgetnstr(janela, buffer, maxChars);
    
    return std::string(buffer);
}

void TelaBase::limparLinha(int linha) {
    wmove(janela, linha, 1);
    wclrtoeol(janela);
    box(janela, 0, 0);
    wrefresh(janela);
}

void TelaBase::esconder() {
    if (janela) {
        delwin(janela);
        janela = nullptr;
    }
}