//221006404

#ifndef TELA_BASE_HPP
#define TELA_BASE_HPP

#include <pdcurses.h>
#include <string>

/**
 * @brief Classe base para todas as telas do sistema.
 * 
 * Fornece funcionalidades básicas de interface gráfica usando PDCurses.
 */
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
    /**
     * @brief Mostra uma mensagem de alerta na tela.
     * @param mensagem Texto a ser exibido.
     */
    void mostrarAlerta(const std::string& mensagem);
    std::string campoTexto(WINDOW* win, int y, int x, int max_len, bool senha = false);
    void centralizar();
    void limparTela();
    void limparLinha(int linha);
    
    /**
     * @brief Exibe uma mensagem na tela.
     * @param msg Mensagem a ser exibida.
     * @param linha Linha onde a mensagem será exibida.
     * @param coluna Coluna onde a mensagem será exibida.
     */
    void exibirMensagem(const std::string& msg, int linha, int coluna);
    
    std::string mostrarInput(const std::string& prompt);  // Nova função
    std::string lerEntrada(int linha, int coluna, int maxChars, bool echo = true);
    std::string lerInput(const std::string& prompt, int y, int x);

public:
    TelaBase();
    virtual ~TelaBase();
    
    virtual void mostrar() = 0;
    virtual void esconder();

    // Configurações da tela
    void inicializarCores();
    void configurarTamanho(int altura = 30, int largura = 80);
    std::string converterParaCP850(const std::string& text);
};

#endif