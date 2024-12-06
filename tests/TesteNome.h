#ifndef TESTE_NOME_H
#define TESTE_NOME_H

#include "TestBase.h"
#include "dominios/Nome.h" // Incluindo o domínio Nome

class TesteNome : public TestBase {
private:
    Nome* nome;    // Ponteiro para a unidade de teste

    void setUp() override;        // Configuração do ambiente de teste
    void tearDown() override;     // Limpeza do ambiente de teste
    void rodarTestes() override;  // Execução dos cenários de teste

    // Cenários específicos de teste para Nome
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    TesteNome() : nome(nullptr) {} // Construtor inicializando o ponteiro como nullptr
};

#endif // TESTE_NOME_H
