#ifndef TUHOSPEDAGEM_H
#define TUHOSPEDAGEM_H

#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/avaliacao.hpp"
#include "../dominios/dinheiro.hpp"
#include "../entidades/Hospedagem.hpp"

class TUHospedagem {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    const static double VALOR_VALIDO_DINHEIRO;
    Hospedagem *hospedagem;
    int estado{};
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUHOSPEDAGEM_H
