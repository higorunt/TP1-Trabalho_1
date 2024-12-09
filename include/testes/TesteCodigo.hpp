//221006440

#ifndef TESTE_CODIGO_HPP
#define TESTE_CODIGO_HPP

#include "TestBase.hpp"
#include "../dominios/codigo.hpp"
#include <string>

class TesteCodigo : public TestBase {
private:
    std::string caminhoArquivoTeste;
protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;
public:
    explicit TesteCodigo(const std::string &caminhoArquivo);
};

#endif // TESTE_CODIGO_HPP
