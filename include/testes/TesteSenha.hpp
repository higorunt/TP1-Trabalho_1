#ifndef TESTE_SENHA_HPP
#define TESTE_SENHA_HPP

#include "TestBase.hpp"
#include "../dominios/senha.hpp"
#include <string>

class TesteSenha : public TestBase {
private:
    std::string caminhoArquivoTeste;
protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;
public:
    explicit TesteSenha(const std::string &caminhoArquivo);
};

#endif // TESTE_SENHA_HPP
