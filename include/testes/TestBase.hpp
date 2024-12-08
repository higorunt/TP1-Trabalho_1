#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class TestBase {
protected:
    int estado;
    int testesExecutados;
    int testesComSucesso;
    int testesComFalha;

    std::vector<std::string> mensagensFalha; 

    virtual void setUp() = 0;    
    virtual void tearDown() = 0; 
    virtual void rodarTestes() = 0; 

public:
    const static int SUCESSO = 0; 
    const static int FALHA = -1;  

    TestBase() : estado(FALHA), testesExecutados(0), testesComSucesso(0), testesComFalha(0) {}

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
    void registrarTesteSucesso() {
        testesExecutados++;
        testesComSucesso++;
    }

    void registrarTesteFalha(const std::string &mensagem) {
        testesExecutados++;
        testesComFalha++;
        mensagensFalha.push_back(mensagem);
    }

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
