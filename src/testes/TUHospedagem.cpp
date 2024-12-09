#include "../../include/testes/TUHospedagem.hpp"

const std::string TUHospedagem::VALOR_VALIDO_NOME = "Hospedagem Teste";
const std::string TUHospedagem::VALOR_VALIDO_CODIGO = "HOS123";
const int TUHospedagem::VALOR_VALIDO_AVALIACAO = 5;
const double TUHospedagem::VALOR_VALIDO_DIARIA = 150.00;

void TUHospedagem::setUp() {
    Nome nome(VALOR_VALIDO_NOME);
    Codigo codigo(VALOR_VALIDO_CODIGO);
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    Dinheiro diaria(VALOR_VALIDO_DIARIA);

    hospedagem = new Hospedagem(nome, codigo, avaliacao, diaria);
    estado = SUCESSO;
}

void TUHospedagem::tearDown() {
    delete hospedagem;
}

void TUHospedagem::testarCenario() {
    // Teste para o domínio Nome
    Nome nome(VALOR_VALIDO_NOME);
    hospedagem->setNome(nome);
    if (hospedagem->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    hospedagem->setCodigo(codigo);
    if (hospedagem->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }

    // Teste para o domínio Avaliação
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    hospedagem->setAvaliacao(avaliacao);
    if (hospedagem->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
        estado = FALHA;
    }

    // Teste para o domínio Dinheiro (Diária)
    Dinheiro diaria(VALOR_VALIDO_DIARIA);
    hospedagem->setDiaria(diaria);
    if (hospedagem->getDiaria().getValor() != std::to_string(VALOR_VALIDO_DIARIA)) {
        estado = FALHA;
    }
}

int TUHospedagem::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}