#include "../../include/testes/TUDestino.h"

const int TUDestino::VALOR_VALIDO_AVALIACAO = 5;
const std::string TUDestino::VALOR_VALIDO_NOME = "Darcy Ribeiro";
const int TUDestino::VALOR_VALIDO_DATA_IN[3] = {10, 10, 10};
const int TUDestino::VALOR_VALIDO_DATA_OUT[3] = {12, 12, 12};
const std::string TUDestino::VALOR_VALIDO_CODIGO = "212abl";

void TUDestino::setUp() {
    destino = new Destino(Nome(VALOR_VALIDO_NOME), Codigo(VALOR_VALIDO_CODIGO), Avaliacao(VALOR_VALIDO_AVALIACAO),
            Data(VALOR_VALIDO_DATA_IN[0], VALOR_VALIDO_DATA_IN[1], VALOR_VALIDO_DATA_IN[2]),
            Data(VALOR_VALIDO_DATA_OUT[0], VALOR_VALIDO_DATA_OUT[1], VALOR_VALIDO_DATA_OUT[2]));
    estado = SUCESSO;
}

void TUDestino::tearDown() {
    delete destino;
}

void TUDestino::testarCenario() {

    //Teste para o domínio Avaliação
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    destino->setAvaliacao(avaliacao);
    if (destino->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
        estado = FALHA;
    }

    // Teste para o domínio Nome
    Nome nome(VALOR_VALIDO_NOME);
    destino->setNome(nome);
    if (destino->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para o domínio Data (inicial)
    Data datain(VALOR_VALIDO_DATA_IN);
    destino->setDataInicio(datain);
    if (destino->getDataInicio().getValor() != datain) {
        estado = FALHA;
    }

    // Teste para o domínio Data (final)
    Data dataout(VALOR_VALIDO_DATA_OUT);
    destino->setDataFim(dataout);
    if (destino->getDataFim().getValor() != dataout) {
        estado = FALHA;
    }

    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    destino->setCodigo(codigo);
    if (destino->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }
}

int TUDestino::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
