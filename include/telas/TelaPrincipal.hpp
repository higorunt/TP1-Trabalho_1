// include/telas/TelaPrincipal.hpp
#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "../entidades/Viajante.hpp"

/**
 * @brief Classe que representa a tela principal do sistema
 * 
 * Esta classe é responsável por gerenciar e exibir o menu principal
 * do sistema, permitindo a navegação entre as diferentes funcionalidades.
 * Herda características básicas de TelaBase.
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
     * Contém as dimensões e posições dos elementos na tela
     */
    struct {
        int menuY = 5;     /**< Posição Y inicial do menu */
        int altura = 20;   /**< Altura total da janela do menu */
        int largura = 60;  /**< Largura total da janela do menu */
        int centralX;      /**< Posição X central calculada */
        int centralY;      /**< Posição Y central calculada */
    } layout;

    /**
     * @brief Desenha o menu na tela
     */
    void desenharMenu();

    /**
     * @brief Processa a opção selecionada pelo usuário
     * @param opcao Número da opção selecionada
     */
    void processarOpcao(int opcao);

public:
    /**
     * @brief Construtor da tela principal
     * @param viajante Ponteiro para o objeto Viajante que será usado
     */
    TelaPrincipal(Viajante* viajante);

    /**
     * @brief Destrutor da tela principal
     */
    ~TelaPrincipal();

    /**
     * @brief Exibe a tela principal
     * 
     * Implementação do método virtual da classe base TelaBase
     */
    void mostrar() override;

    /**
     * @brief Executa o loop principal da tela
     */
    void executar();
};

#endif