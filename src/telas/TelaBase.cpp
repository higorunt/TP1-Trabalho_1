#include "../../include/telas/TelaBase.hpp"
#include <cstring>
#include <algorithm>

TelaBase::TelaBase() : janela(nullptr) {
    // Inicialização do ncurses
    initscr();
    start_color();
    cbreak();             // Desabilita buffering de linha
    noecho();            // Não mostra caracteres digitados
    keypad(stdscr, TRUE); // Habilita teclas especiais (F1, arrows, etc)
    curs_set(1);         // Mostra o cursor
    
    // Inicializar esquema de cores
    inicializarCores();
    
    // Configurar tamanho padrão (1280x720 aproximado em caracteres)
    configurarTamanho();
    
    // Ativar suporte a mouse
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    
    refresh();
}

TelaBase::~TelaBase() {
    if (janela != nullptr) {
        delwin(janela);
        janela = nullptr;
    }
}

void TelaBase::inicializarCores() {
    // Definição dos pares de cores
    init_pair(COR_PRINCIPAL, COLOR_WHITE, COLOR_BLUE);   // Tema principal
    init_pair(COR_INVERSA, COLOR_BLUE, COLOR_WHITE);     // Campos de entrada
    init_pair(COR_ERRO, COLOR_WHITE, COLOR_RED);         // Mensagens de erro
    init_pair(COR_ALERTA, COLOR_YELLOW, COLOR_BLUE);     // Alertas
    init_pair(COR_DESTAQUE, COLOR_WHITE, COLOR_RED);     // Destaque especial
}

void TelaBase::configurarTamanho(int altura, int largura) {
    resize_term(altura, largura);
    
    // Criar janela principal centralizada
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;
    
    if (janela != nullptr) {
        delwin(janela);
    }
    
    janela = newwin(altura, largura, startY, startX);
    wbkgd(janela, COLOR_PAIR(COR_PRINCIPAL));
    box(janela, 0, 0);
    
    refresh();
    wrefresh(janela);
}

void TelaBase::mostrarAlerta(const std::string& mensagem) {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Calcular dimensões do alerta
    int maxMsgWidth = largura - 20;  // Margem de 10 em cada lado
    int numLinhas = (mensagem.length() + maxMsgWidth - 1) / maxMsgWidth + 2; // +2 para título e instruções
    
    int alertaAltura = numLinhas + 4;  // +4 para bordas e espaços
    int alertaLargura = std::min(std::max(60, static_cast<int>(mensagem.length() + 10)), largura - 10);
    
    // Centralizar o alerta
    int alertaY = (altura - alertaAltura) / 2;
    int alertaX = (largura - alertaLargura) / 2;
    
    // Criar janela do alerta
    WINDOW* alertaWin = newwin(alertaAltura, alertaLargura, 
                              alertaY + getbegy(janela), 
                              alertaX + getbegx(janela));
    
    // Configurar cores e borda
    wbkgd(alertaWin, COLOR_PAIR(COR_ERRO));
    box(alertaWin, 0, 0);
    
    // Título centralizado
    std::string titulo = "AVISO";
    mvwprintw(alertaWin, 1, (alertaLargura - titulo.length()) / 2, "%s", titulo.c_str());
    
    // Quebrar e centralizar a mensagem
    std::string msg = mensagem;
    int linha = 2;
    while (!msg.empty() && linha < alertaAltura - 2) {
        std::string parte;
        if (msg.length() > maxMsgWidth) {
            size_t pos = msg.rfind(' ', maxMsgWidth);
            if (pos == std::string::npos) pos = maxMsgWidth;
            parte = msg.substr(0, pos);
            msg = msg.substr(pos + 1);
        } else {
            parte = msg;
            msg.clear();
        }
        
        mvwprintw(alertaWin, linha++, (alertaLargura - parte.length()) / 2, "%s", parte.c_str());
    }
    
    // Instruções
    mvwprintw(alertaWin, alertaAltura - 2, 2, "Pressione qualquer tecla para continuar...");
    
    // Atualizar e aguardar
    wrefresh(alertaWin);
    wgetch(alertaWin);
    
    // Limpar
    delwin(alertaWin);
    touchwin(janela);
    wrefresh(janela);
}

std::string TelaBase::campoTexto(WINDOW* win, int y, int x, int max_len, bool senha) {
    std::string texto;
    int ch;
    int pos = 0;
    
    wmove(win, y, x);
    wrefresh(win);
    
    while (true) {
        ch = wgetch(win);
        
        if (ch == 27) { // ESC
            texto.clear();
            break;
        }
        
        if (ch == '\n' || ch == KEY_ENTER) {
            break;
        }
        
        if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
            if (!texto.empty()) {
                texto.pop_back();
                pos--;
                mvwaddch(win, y, x + pos, ' ');
                wmove(win, y, x + pos);
                wrefresh(win);
            }
            continue;
        }
        
        if (texto.length() < max_len && isprint(ch)) {
            texto += ch;
            mvwaddch(win, y, x + pos, senha ? '*' : ch);
            pos++;
            wrefresh(win);
        }
    }
    
    return texto;
}

void TelaBase::centralizar() {
    int altura, largura;
    getmaxyx(stdscr, altura, largura);
    
    int winAltura, winLargura;
    getmaxyx(janela, winAltura, winLargura);
    
    int startY = (altura - winAltura) / 2;
    int startX = (largura - winLargura) / 2;
    
    mvwin(janela, startY, startX);
    wrefresh(janela);
}

void TelaBase::limparTela() {
    wclear(janela);
    box(janela, 0, 0);
    wrefresh(janela);
}

void TelaBase::limparLinha(int linha) {
    wmove(janela, linha, 1);
    whline(janela, ' ', getmaxx(janela) - 2);
    wrefresh(janela);
}

void TelaBase::exibirMensagem(const std::string& msg, int linha, int coluna) {
    limparLinha(linha);
    mvwprintw(janela, linha, coluna, "%s", msg.c_str());
    wrefresh(janela);
}

std::string TelaBase::lerEntrada(int linha, int coluna, int maxChars, bool echo) {
    std::string entrada;
    int ch;
    int pos = 0;
    
    wmove(janela, linha, coluna);
    wrefresh(janela);
    
    while (true) {
        ch = wgetch(janela);
        
        if (ch == 27) { // ESC
            entrada.clear();
            break;
        }
        
        if (ch == '\n' || ch == KEY_ENTER) {
            break;
        }
        
        if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
            if (!entrada.empty()) {
                entrada.pop_back();
                pos--;
                mvwaddch(janela, linha, coluna + pos, ' ');
                wmove(janela, linha, coluna + pos);
                wrefresh(janela);
            }
            continue;
        }
        
        if (entrada.length() < maxChars && isprint(ch)) {
            entrada += ch;
            mvwaddch(janela, linha, coluna + pos, echo ? ch : '*');
            pos++;
            wrefresh(janela);
        }
    }
    
    return entrada;
}

void TelaBase::esconder() {
    if (janela != nullptr) {
        delwin(janela);
        janela = nullptr;
    }
}