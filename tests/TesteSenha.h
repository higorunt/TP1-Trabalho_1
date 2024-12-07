#ifndef TESTE_SENHA_H
#define TESTE_SENHA_H

#include "TestBase.h"
#include "dominios/Senha.h"

class TesteSenha : public TestBase {
private:
    Senha* senha;

    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

    void testarCenarioValorValido();
    void testarCenarioValorInvalido();

public:
    TesteSenha() : senha(nullptr) {}
};

#endif // TESTE_SENHA_H