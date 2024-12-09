//212007046


#ifndef TUCONTA_HPP
#define TUCONTA_HPP

#include "../dominios/Codigo.hpp"
#include "../dominios/Senha.hpp"
#include "../entidades/Conta.hpp"

class TUConta {
private:
    const static std::string VALOR_VALIDO_CODIGO;
    const static std::string VALOR_VALIDO_SENHA;
    Conta *conta;
    int estado;
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUCONTA_HPP