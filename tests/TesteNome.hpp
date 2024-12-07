#ifndef TESTE_NOME_HPP
#define TESTE_NOME_HPP

#include "TestBase.hpp"
#include "dominios/Nome.hpp" // Incluindo o dom�nio Nome

class TesteNome : public TestBase {
private:
    Nome* nome;    // Ponteiro para a unidade de teste

    void setUp() override;        // Configura��o do ambiente de teste
    void tearDown() override;     // Limpeza do ambiente de teste
    void rodarTestes() override;  // Execu��o dos cen�rios de teste

    // Cen�rios espec�ficos de teste para Nome
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    TesteNome() : nome(nullptr) {} // Construtor inicializando o ponteiro como nullptr
};

#endif // TESTE_NOME_H
