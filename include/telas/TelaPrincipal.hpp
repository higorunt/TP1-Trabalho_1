// include/telas/TelaPrincipal.hpp
#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "../entidades/Viajante.hpp"

/**
 * @brief Classe que representa a tela principal do sistema
 * 
 * Esta classe � respons�vel por gerenciar e exibir o menu principal
 * do sistema, permitindo a navega��o entre as diferentes funcionalidades.
 * Herda caracter�sticas b�sicas de TelaBase.
 */
class TelaPrincipal : public TelaBase {
private:
    /** @brief Ponteiro para o objeto Viajante em uso */
    Viajante* viajante;
    
    /** @brief Ponteiro para a janela do menu no ncurses */
    WINDOW* painelMenu;
    
    /**
     * @brief Estrutura que define o layout da tela
     * 
     * Cont�m as dimens�es e posi��es dos elementos na tela
     */
    struct {
        int menuY = 5;     /**< Posi��o Y inicial do menu */
        int altura = 20;   /**< Altura total da janela do menu */
        int largura = 60;  /**< Largura total da janela do menu */
        int centralX;      /**< Posi��o X central calculada */
        int centralY;      /**< Posi��o Y central calculada */
    } layout;

    /**
     * @brief Desenha o menu na tela
     */
    void desenharMenu();

    /**
     * @brief Processa a op��o selecionada pelo usu�rio
     * @param opcao N�mero da op��o selecionada
     */
    void processarOpcao(int opcao);

public:
    /**
     * @brief Construtor da tela principal
     * @param viajante Ponteiro para o objeto Viajante que ser� usado
     */
    TelaPrincipal(Viajante* viajante);

    /**
     * @brief Destrutor da tela principal
     */
    ~TelaPrincipal();

    /**
     * @brief Exibe a tela principal
     * 
     * Implementa��o do m�todo virtual da classe base TelaBase
     */
    void mostrar() override;

    /**
     * @brief Executa o loop principal da tela
     */
    void executar();
};

#endif