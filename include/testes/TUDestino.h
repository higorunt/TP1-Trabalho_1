#ifndef TUDESTINO_H
#define TUDESTINO_H

#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/avaliacao.hpp"
#include "../dominios/data.hpp"
#include "../entidades/Destino.hpp"

class TUDestino {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    const static int VALOR_VALIDO_DATA_IN;
    const static int VALOR_VALIDO_DATA_OUT;
    Destino *destino;
    int estado{};
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUDESTINO_H
