#include "TesteSenha.h"
#include <iostream>

const std::string VALOR_VALIDO = "14253"; // Novo valor v�lido
const std::string VALOR_INVALIDO = "12345"; // Exemplo inv�lido por ordem crescente

void TesteSenha::setUp() {
    senha = new Senha(VALOR_VALIDO);
    estado = SUCESSO;
}

void TesteSenha::tearDown() {
    delete senha;
    senha = nullptr;
}

void TesteSenha::rodarTestes() {
    testarCenarioValorValido();
    testarCenarioValorInvalido();
}

void TesteSenha::testarCenarioValorValido() {
    try {
        senha->setValor(VALOR_VALIDO);
        if (senha->getValor() != VALOR_VALIDO) {
            estado = FALHA;
        }
    } catch (const std::invalid_argument&) {
        estado = FALHA;
    }
}

void TesteSenha::testarCenarioValorInvalido() {
    try {
        senha->setValor(VALOR_INVALIDO);
        estado = FALHA;
    } catch (const std::invalid_argument&) {
        // Exce��o esperada - teste bem-sucedido
    }
}
