// src/apresentacao/TelaLogin.cpp
#include "../../include/apresentacao/TelaLogin.hpp"
#include <string>

TelaLogin::TelaLogin(IAutenticacaoService* service) : service(service), janela(nullptr) {}

TelaLogin::~TelaLogin() {
    finalizarCurses();
}

void TelaLogin::inicializarCurses() {
    // Inicializa a tela principal
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    // Configura cores
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    
    // Cria janela centralizada
    int altura = 12;
    int largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;
    
    janela = newwin(altura, largura, startY, startX);
    wbkgd(janela, COLOR_PAIR(1));
}

void TelaLogin::finalizarCurses() {
    if (janela) {
        delwin(janela);
        janela = nullptr;
    }
    // Em vez de endwin(), vamos apenas limpar a tela
    clear();
    refresh();
}

void TelaLogin::exibirMensagem(const char* mensagem) {
    mvwprintw(janela, 8, 2, "%-46s", mensagem); // Limpa linha anterior
    wrefresh(janela);
    napms(2000); // Espera 2 segundos
}

Viajante* TelaLogin::executar() {
    inicializarCurses();
    
    // Desenha a caixa e título
    box(janela, 0, 0);
    mvwprintw(janela, 2, 2, "Sistema de Planejamento de Viagens");
    mvwprintw(janela, 4, 2, "Codigo : ");
    mvwprintw(janela, 6, 2, "Senha  : ");
    wrefresh(janela);
    
    char codigoStr[7] = {0};
    char senhaStr[6] = {0};
    
    // Campo do código
    echo(); // Mostra caracteres digitados
    wmove(janela, 4, 11);
    wrefresh(janela);
    wgetnstr(janela, codigoStr, 6);
    
    // Campo da senha
    noecho(); // Esconde caracteres
    wmove(janela, 6, 11);
    wrefresh(janela);
    
    // Lê senha caractere por caractere
    int i = 0;
    while (i < 5) {
        int ch = wgetch(janela);
        if (ch == '\n' || ch == '\r') {
            break;
        }
        if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
            if (i > 0) {
                i--;
                wmove(janela, 6, 23 + i);
                waddch(janela, ' ');
                wmove(janela, 6, 23 + i);
            }
        } else if (i < 5 && isdigit(ch)) {
            senhaStr[i] = ch;
            waddch(janela, '*');
            i++;
        }
        wrefresh(janela);
    }
    
    Viajante* resultado = nullptr;
    
    try {
        Codigo codigo(codigoStr);
        Senha senha(senhaStr);
        resultado = service->autenticar(codigo, senha);
        
        if (!resultado) {
            exibirMensagem("Credenciais invalidas!");
        } else {
            exibirMensagem("Login realizado com sucesso!");
        }
    }
    catch (const std::invalid_argument& e) {
        exibirMensagem(e.what());
        resultado = nullptr;
    }
    
    finalizarCurses();
    return resultado;
}