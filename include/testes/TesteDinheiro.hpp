#ifndef TESTE_DINHEIRO_HPP
#define TESTE_DINHEIRO_HPP

#include "TestBase.hpp"
#include "../dominios/Dinheiro.hpp"
#include <string>

class TesteDinheiro : public TestBase {
private:
    std::string caminhoArquivoTeste;

protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

public:
    explicit TesteDinheiro(const std::string &caminhoArquivo);
};

#endif // TESTE_DINHEIRO_HPP
