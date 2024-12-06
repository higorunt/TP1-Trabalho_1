#ifndef TESTENOME_H
#define TESTENOME_H

#include "TestBase.h"
#include "../include/dominios/Nome.h"
#include <vector>

/**
 * @class TesteNome
 * @brief Classe de teste para o dom�nio Nome, com sa�da detalhada.
 */
class TesteNome : public TestBase {
private:
    // Estrutura para armazenar informa��es de cada teste
    struct CasoTeste {
        std::string valor;
        bool deveSerValido;
        std::string descricao;
    };

    // Lista de casos de teste
    std::vector<CasoTeste> casos;

    // M�todo auxiliar para rodar um caso de teste
    bool rodarCasoTeste(const CasoTeste &caso);

public:
    TesteNome();
    void executar() override;
};

/**
 * @brief Fun��o para executar os testes do dom�nio Nome.
 */
void executarTesteNome();

#endif // TESTENOME_H
