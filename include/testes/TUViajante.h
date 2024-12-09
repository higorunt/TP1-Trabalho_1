#ifndef TUVIAJANTE_H
#define TUVIAJANTE_H

#include "../dominios/nome.hpp"
#include "../entidades/viajante.hpp"
#include "../entidades/Conta.hpp"

class TUViajante {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static Conta VALOR_VALIDO_CONTA;
    Viajante *viajante;
    int estado{};
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUVIAJANTE_H
