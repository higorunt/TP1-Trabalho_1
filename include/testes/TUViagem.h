#ifndef TUVIAGEM_H
#define TUVIAGEM_H

#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/avaliacao.hpp"
#include "../entidades/Viagem.hpp"

class TUViagem {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    Viagem *viagem;
    int estado{};
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUVIAGEM_H
