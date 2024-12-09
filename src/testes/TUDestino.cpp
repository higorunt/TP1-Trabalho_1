#include "../../include/testes/TUDestino.hpp"

const std::string TUDestino::VALOR_VALIDO_NOME = "Destino Teste";
const std::string TUDestino::VALOR_VALIDO_CODIGO = "DST123";
const int TUDestino::VALOR_VALIDO_AVALIACAO = 5;
const std::string TUDestino::VALOR_VALIDO_DATA_INICIO = "01-01-23";
const std::string TUDestino::VALOR_VALIDO_DATA_FIM = "10-01-23";

void TUDestino::setUp() {
    try {
        Nome nome(VALOR_VALIDO_NOME);
        Codigo codigo(VALOR_VALIDO_CODIGO);
        Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
        Data dataInicio(1, 1, 23);
        Data dataFim(10, 1, 23);

        destino = new Destino(nome, codigo, avaliacao, dataInicio, dataFim);
        estado = SUCESSO;
    } catch (const std::exception &e) {
        estado = FALHA;
    }
}

void TUDestino::tearDown() {
    delete destino;
}

void TUDestino::testarCenario() {
    try {
        // Teste para o domínio Nome
        Nome nome(VALOR_VALIDO_NOME);
        destino->setNome(nome);
        if (destino->getNome().getValor() != VALOR_VALIDO_NOME) {
            estado = FALHA;
        }

        // Teste para o domínio Código
        Codigo codigo(VALOR_VALIDO_CODIGO);
        destino->setCodigo(codigo);
        if (destino->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
            estado = FALHA;
        }

        // Teste para o domínio Avaliação
        Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
        destino->setAvaliacao(avaliacao);
        if (destino->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
            estado = FALHA;
        }

        // Teste para o domínio Data de Início
        Data dataInicio(1, 1, 23);
        destino->setDataInicio(dataInicio);
        if (destino->getDataInicio().getValor() != VALOR_VALIDO_DATA_INICIO) {
            estado = FALHA;
        }

        // Teste para o domínio Data de Fim
        Data dataFim(10, 1, 23);
        destino->setDataFim(dataFim);
        if (destino->getDataFim().getValor() != VALOR_VALIDO_DATA_FIM) {
            estado = FALHA;
        }
    } catch (const std::exception &e) {
        estado = FALHA;
    }
}

int TUDestino::run() {
    setUp();
    if (estado == SUCESSO) {
        testarCenario();
    }
    tearDown();
    return estado;
}