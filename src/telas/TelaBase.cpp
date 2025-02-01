#include "../../include/telas/TelaBase.hpp"
#include <cstring>
#include <algorithm>
#include <map>

using std::map;

// Forward declaration of helper function
std::string removerAcentos(const std::string& texto);

TelaBase::TelaBase() : janela(nullptr) {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    
    // Inicializar esquema de cores
    inicializarCores();
    
    // Configurar tamanho padrão
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
    
    // Tratar a mensagem removendo acentos
    std::string msgTratada = removerAcentos(mensagem);
    
    // Aumentar largura mínima para garantir que a mensagem caiba
    int alertaLargura = std::max(80, static_cast<int>(msgTratada.length()) + 10);
    if (alertaLargura > largura - 4) alertaLargura = largura - 4;
    
    int alertaAltura = 7;  // Altura fixa para começar
    int alertaY = (altura - alertaAltura) / 2;
    int alertaX = (largura - alertaLargura) / 2;
    
    // Criar janela do alerta
    WINDOW* alertaWin = newwin(alertaAltura, alertaLargura, 
                              alertaY + getbegy(janela), 
                              alertaX + getbegx(janela));
    
    // Configurar a janela do alerta
    keypad(alertaWin, TRUE);
    wattron(alertaWin, A_NORMAL);
    wbkgd(alertaWin, COLOR_PAIR(COR_ERRO));
    box(alertaWin, 0, 0);
    
    // Título centralizado
    std::string titulo = "AVISO";
    mvwprintw(alertaWin, 1, (alertaLargura - titulo.length()) / 2, "%s", titulo.c_str());
    
    // Processar e exibir a mensagem
    std::string msg = msgTratada;
    int maxChars = alertaLargura - 4; // -4 para margens
    int linha = 2;
    
    while (!msg.empty()) {
        std::string parte;
        if (msg.length() > maxChars) {
            size_t pos = msg.rfind(' ', maxChars);
            if (pos == std::string::npos) pos = maxChars;
            parte = msg.substr(0, pos);
            msg = msg.substr(pos + 1);
        } else {
            parte = msg;
            msg.clear();
        }
        
        // Centralizar cada linha
        int espacos = (alertaLargura - parte.length()) / 2;
        mvwprintw(alertaWin, linha++, espacos, "%s", parte.c_str());
        
        // Se precisar de mais linhas, redimensionar a janela
        if (!msg.empty() && linha >= alertaAltura - 2) {
            alertaAltura++;
            wresize(alertaWin, alertaAltura, alertaLargura);
            box(alertaWin, 0, 0);
        }
    }
    
    // Adicionar instrução na última linha centralizada
    std::string instrucao = "Pressione qualquer tecla para continuar...";
    mvwprintw(alertaWin, alertaAltura - 2, 
              (alertaLargura - instrucao.length()) / 2, 
              "%s", instrucao.c_str());
    
    // Atualizar a janela
    wrefresh(alertaWin);
    
    // Aguardar tecla
    wgetch(alertaWin);
    
    // Limpar
    delwin(alertaWin);
    touchwin(janela);
    wrefresh(janela);
}

std::string removerAcentos(const std::string& texto) {
    static const std::map<char, char> substituicoes = {
        {'á', 'a'}, {'à', 'a'}, {'ã', 'a'}, {'â', 'a'},
        {'é', 'e'}, {'ê', 'e'},
        {'í', 'i'},
        {'ó', 'o'}, {'ô', 'o'}, {'õ', 'o'},
        {'ú', 'u'},
        {'ç', 'c'},
        {'Á', 'A'}, {'À', 'A'}, {'Ã', 'A'}, {'Â', 'A'},
        {'É', 'E'}, {'Ê', 'E'},
        {'Í', 'I'},
        {'Ó', 'O'}, {'Ô', 'O'}, {'Õ', 'O'},
        {'Ú', 'U'},
        {'Ç', 'C'}
    };

    std::string resultado;
    for (char c : texto) {
        auto it = substituicoes.find(c);
        resultado += (it != substituicoes.end()) ? it->second : c;
    }
    return resultado;
}
std::string TelaBase::campoTexto(WINDOW* win, int y, int x, int max_len, bool senha) {
    std::string texto;
    int ch;
    int pos = 0;
    
    wmove(win, y, x);
    wrefresh(win);
    
    while (true) {
        ch = wgetch(win);

        // Verifica se houve erro na leitura
        if (ch == ERR) {
            continue;
        }
        
        // Se for uma tecla de seta (ou outra tecla especial que você queira ignorar), pula-a
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
            continue;
        }
        
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
        
        // Em vez de isprint, verificamos se ch está no intervalo de caracteres imprimíveis
        if (texto.length() < max_len && ch >= 32 && ch <= 126) {
            texto += static_cast<char>(ch);
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