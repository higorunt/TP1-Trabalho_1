#ifndef TESTE_NOME_H
#define TESTE_NOME_H

#include "TestBase.h"
#include "dominios/Nome.h" // Incluindo o dom�nio Nome

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
