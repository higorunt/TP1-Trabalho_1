#include "../../include/testes/TUViajante.h"

const std::string TUViajante::VALOR_VALIDO_NOME = "São José de Cupertino";
const Conta TUViajante::VALOR_VALIDO_CONTA = {"0lm1kz", "03895"};

void TUViajante::setUp() {
    viajante = new Viajante(Nome(VALOR_VALIDO_NOME), Conta(VALOR_VALIDO_CONTA));
    estado = SUCESSO;
}

void TUViajante::tearDown() {
    delete viajante;
}

void TUViajante::testarCenario() {

    // Teste para o domínio Nome
    Nome nome(VALOR_VALIDO_NOME);
    viajante->setNome(nome);
    if (viajante->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para a sub-entidade Conta
    Conta conta(VALOR_VALIDO_CONTA);
    viajante->setConta(conta);
    if (viajante->getConta().getValor() != VALOR_VALIDO_CONTA) {
        estado = FALHA;
    }
}

int TUViajante::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
