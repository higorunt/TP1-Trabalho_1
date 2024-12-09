//221006440

#ifndef TESTE_DATA_HPP
#define TESTE_DATA_HPP

#include "TestBase.hpp"
#include "../dominios/Data.hpp"
#include <string>

class TesteData : public TestBase {
private:
    std::string caminhoArquivoTeste;

protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

public:
    explicit TesteData(const std::string &caminhoArquivo);
};

#endif // TESTE_DATA_HPP
