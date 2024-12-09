#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Classe base para testes unitários.
 */
class TestBase {
protected:
    int estado; ///< Estado atual do teste.
    int testesExecutados; ///< Número de testes executados.
    int testesComSucesso; ///< Número de testes com sucesso.
    int testesComFalha; ///< Número de testes com falha.

    std::vector<std::string> mensagensFalha; ///< Mensagens de falha dos testes.

    /**
     * @brief Configura o ambiente para os testes.
     */
    virtual void setUp() = 0;    

    /**
     * @brief Limpa o ambiente após os testes.
     */
    virtual void tearDown() = 0; 

    /**
     * @brief Executa os testes.
     */
    virtual void rodarTestes() = 0; 

public:
    const static int SUCESSO = 0; ///< Constante para indicar sucesso.
    const static int FALHA = -1; ///< Constante para indicar falha.

    /**
     * @brief Construtor da classe TestBase.
     */
    TestBase() : estado(FALHA), testesExecutados(0), testesComSucesso(0), testesComFalha(0) {}

    /**
     * @brief Executa o conjunto de testes.
     * @return Estado final dos testes.
     */
    int run() {
        setUp();                
        try {
            rodarTestes();      
            estado = SUCESSO;   
        } catch (std::exception& e) {
            std::cerr << "Erro inesperado: " << e.what() << std::endl;
            estado = FALHA;     
        }
        tearDown();             

        imprimirRelatorio();

        return estado;          
    }

protected:
    /**
     * @brief Registra um teste com sucesso.
     */
    void registrarTesteSucesso() {
        testesExecutados++;
        testesComSucesso++;
    }

    /**
     * @brief Registra um teste com falha.
     * @param mensagem Mensagem de falha do teste.
     */
    void registrarTesteFalha(const std::string &mensagem) {
        testesExecutados++;
        testesComFalha++;
        mensagensFalha.push_back(mensagem);
    }

    /**
     * @brief Imprime o relatório dos testes.
     */
    void imprimirRelatorio() {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Relatório de Testes" << std::endl;
        std::cout << "Executados: " << testesExecutados << std::endl;
        std::cout << "Sucessos:   " << testesComSucesso << std::endl;
        std::cout << "Falhas:     " << testesComFalha << std::endl;

        if(!mensagensFalha.empty()) {
            std::cout << "\nDetalhes das Falhas:" << std::endl;
            for (const auto &msg : mensagensFalha) {
                std::cout << " - " << msg << std::endl;
            }
        }

        std::cout << "-----------------------------------" << std::endl;
    }
};

#endif // TEST_BASE_HPP
