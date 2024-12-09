//212007046

#ifndef TUDESTINO_HPP
#define TUDESTINO_HPP

#include "../dominios/Nome.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Avaliacao.hpp"
#include "../dominios/Data.hpp"
#include "../entidades/Destino.hpp"

class TUDestino {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    const static std::string VALOR_VALIDO_DATA_INICIO;
    const static std::string VALOR_VALIDO_DATA_FIM;

    Destino *destino;
    int estado;
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUDESTINO_HPP