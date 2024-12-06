#ifndef TESTBASE_H
#define TESTBASE_H

#include <iostream>
#include <string>

/**
 * @class TestBase
 * @brief Classe base abstrata para todos os testes.
 */
class TestBase {
protected:
    std::string descricao;

public:
    TestBase(const std::string& descricao) : descricao(descricao) {}
    virtual ~TestBase() {}

    virtual void executar() = 0;

    void mostrarResultado(bool resultado) {
        std::cout << descricao << ": " << (resultado ? "PASSOU" : "FALHOU") << std::endl;
    }
};

#endif // TESTBASE_H
