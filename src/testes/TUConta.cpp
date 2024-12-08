#include "../../include/testes/TUConta.hpp"

const std::string TUConta::VALOR_VALIDO_CODIGO = "ABC123";
const std::string TUConta::VALOR_VALIDO_SENHA = "14526";

void TUConta::setUp() {
    conta = new Conta(Codigo(VALOR_VALIDO_CODIGO), Senha(VALOR_VALIDO_SENHA));
    estado = SUCESSO;
}

void TUConta::tearDown() {
    delete conta;
}

void TUConta::testarCenario() {
    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    conta->setCodigo(codigo);
    if (conta->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }

    // Teste para o domínio Senha
    Senha senha(VALOR_VALIDO_SENHA);
    conta->setSenha(senha);
    if (conta->getSenha().getValor() != VALOR_VALIDO_SENHA) {
        estado = FALHA;
    }
}

int TUConta::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}