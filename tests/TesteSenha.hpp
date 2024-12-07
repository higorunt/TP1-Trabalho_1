#ifndef TESTE_SENHA_HPP
#define TESTE_SENHA_HPP

#include "TestBase.hpp"
#include "dominios/Senha.hpp"

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