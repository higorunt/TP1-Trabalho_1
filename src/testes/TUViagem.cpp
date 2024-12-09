#include "../../include/testes/TUViagem.h"

const int TUViagem::VALOR_VALIDO_AVALIACAO = 5;
const std::string TUViagem::VALOR_VALIDO_NOME = "ENGENHARIA";
const std::string TUViagem::VALOR_VALIDO_CODIGO = "ENE012";

void TUViagem::setUp() {
    viagem = new Viagem(Nome(VALOR_VALIDO_NOME), Codigo(VALOR_VALIDO_CODIGO),
                Avaliacao(VALOR_VALIDO_AVALIACAO));
    estado = SUCESSO;
}

void TUViagem::tearDown() {
    delete viagem;
}

void TUViagem::testarCenario() {

    //Teste para o domínio Avaliação
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    viagem->setAvaliacao(avaliacao);
    if (viagem->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
        estado = FALHA;
    }

    // Teste para o domínio Nome
    Nome nome(VALOR_VALIDO_NOME);
    viagem->setNome(nome);
    if (viagem->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    viagem->setCodigo(codigo);
    if (viagem->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }
}

int TUViagem::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
