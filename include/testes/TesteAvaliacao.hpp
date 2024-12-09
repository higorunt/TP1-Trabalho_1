//221006440

#ifndef TESTE_AVALIACAO_HPP
#define TESTE_AVALIACAO_HPP

#include "TestBase.hpp"
#include "../dominios/Avaliacao.hpp"
#include <string>

class TesteAvaliacao : public TestBase {
private:
    std::string caminhoArquivoTeste;

protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

public:
    explicit TesteAvaliacao(const std::string &caminhoArquivo);
};

#endif // TESTE_AVALIACAO_HPP
