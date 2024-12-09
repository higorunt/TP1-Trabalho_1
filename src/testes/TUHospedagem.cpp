#include "../../include/testes/TUHospedagem.h"

const int TUHospedagem::VALOR_VALIDO_AVALIACAO = 3;
const std::string TUHospedagem::VALOR_VALIDO_NOME = "SUBSOLO ICC";
const double TUHospedagem::VALOR_VALIDO_DINHEIRO = 6.10;
const std::string TUHospedagem::VALOR_VALIDO_CODIGO = "vish09";

void TUHospedagem::setUp() {
    hospedagem = new Hospedagem(Nome(VALOR_VALIDO_NOME), Codigo(VALOR_VALIDO_CODIGO),
                Avaliacao(VALOR_VALIDO_AVALIACAO), Dinheiro(VALOR_VALIDO_DINHEIRO));
    estado = SUCESSO;
}

void TUHospedagem::tearDown() {
    delete hospedagem;
}

void TUHospedagem::testarCenario() {

    //Teste para o domínio Avaliação
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    hospedagem->setAvaliacao(avaliacao);
    if (hospedagem->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
        estado = FALHA;
    }

    // Teste para o domínio Nome
    Nome nome(VALOR_VALIDO_NOME);
    hospedagem->setNome(nome);
    if (hospedagem->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para o domínio Dinheiro/Preço
    Dinheiro dinheiro(VALOR_VALIDO_DINHEIRO);
    hospedagem->setPreco(dinheiro);
    if (hospedagem->getPreco().getValor() != VALOR_VALIDO_DINHEIRO) {
        estado = FALHA;
    }

    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    hospedagem->setCodigo(codigo);
    if (hospedagem->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }
}

int TUHospedagem::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
