//212007046


#ifndef TUHOSPEDAGEM_HPP
#define TUHOSPEDAGEM_HPP

#include "../dominios/Nome.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Avaliacao.hpp"
#include "../dominios/Dinheiro.hpp"
#include "../entidades/Hospedagem.hpp"

class TUHospedagem {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    const static double VALOR_VALIDO_DIARIA;

    Hospedagem *hospedagem;
    int estado;
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUHOSPEDAGEM_HPP