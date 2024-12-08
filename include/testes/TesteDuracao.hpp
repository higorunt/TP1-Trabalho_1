#ifndef TESTE_DURACAO_HPP
#define TESTE_DURACAO_HPP

#include "TestBase.hpp"
#include "../dominios/Duracao.hpp"
#include <string>

class TesteDuracao : public TestBase {
private:
    std::string caminhoArquivoTeste;

protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

public:
    explicit TesteDuracao(const std::string &caminhoArquivo);
};

#endif // TESTE_DURACAO_HPP
