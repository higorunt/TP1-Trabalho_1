#ifndef TELA_BASE_HPP
#define TELA_BASE_HPP

#include <pdcurses.h>
#include <string>

class TelaBase {
protected:
    WINDOW* janela;
    
    // Cores padrão do sistema
    static const int COR_PRINCIPAL = 1;      // Azul/Branco
    static const int COR_INVERSA = 2;        // Branco/Azul
    static const int COR_ERRO = 3;           // Vermelho/Branco
    static const int COR_ALERTA = 4;         // Amarelo/Azul
    static const int COR_DESTAQUE = 5;       // Branco/Vermelho

    // Métodos utilitários para interface
    void mostrarAlerta(const std::string& mensagem);
    std::string campoTexto(WINDOW* win, int y, int x, int max_len, bool senha = false);
    void centralizar();
    void limparTela();
    void limparLinha(int linha);
    void exibirMensagem(const std::string& msg, int linha, int coluna);
    std::string mostrarInput(const std::string& prompt);  // Nova função
    std::string lerEntrada(int linha, int coluna, int maxChars, bool echo = true);

public:
    TelaBase();
    virtual ~TelaBase();
    
    virtual void mostrar() = 0;
    virtual void esconder();

    // Configurações da tela
    void inicializarCores();
    void configurarTamanho(int altura = 30, int largura = 80);
};

#endif