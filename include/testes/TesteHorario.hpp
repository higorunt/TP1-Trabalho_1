#ifndef TESTE_HORARIO_HPP
#define TESTE_HORARIO_HPP

#include "TestBase.hpp"
#include "../dominios/Horario.hpp"
#include <string>

class TesteHorario : public TestBase {
private:
    std::string caminhoArquivoTeste;

protected:
    void setUp() override;
    void tearDown() override;
    void rodarTestes() override;

public:
    explicit TesteHorario(const std::string &caminhoArquivo);
};

#endif // TESTE_HORARIO_HPP
