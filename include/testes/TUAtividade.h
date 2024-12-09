#ifndef TUATIVIDADE_H
#define TUATIVIDADE_H

#include "../dominios/nome.hpp"
#include "../dominios/codigo.hpp"
#include "../dominios/avaliacao.hpp"
#include "../dominios/data.hpp"
#include "../dominios/Horario.hpp"
#include "../dominios/Duracao.hpp"
#include "../dominios/dinheiro.hpp"
#include "../entidades/Atividade.hpp"

class TUAtividade {
private:
    const static std::string VALOR_VALIDO_NOME;
    const static std::string VALOR_VALIDO_CODIGO;
    const static int VALOR_VALIDO_AVALIACAO;
    const static int VALOR_VALIDO_DATA[3];
    const static std::string VALOR_VALIDO_HORARIO;
    const static int VALOR_VALIDO_DURACAO;
    const static double VALOR_VALIDO_DINHEIRO;
    Atividade *atividade;
    int estado{};
    void setUp();
    void tearDown();
    void testarCenario();

public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};

#endif // TUATIVIDADE_H
