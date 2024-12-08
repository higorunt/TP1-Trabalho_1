#ifndef TESTE_NOME_HPP
#define TESTE_NOME_HPP

#include "TestBase.hpp"
#include "../dominios/nome.hpp"
#include <string>

class TesteNome : public TestBase {
private:
    std::string caminhoArquivoTeste;
protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;
public:
    explicit TesteNome(const std::string &caminhoArquivo);
};

#endif // TESTE_NOME_HPP
