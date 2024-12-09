#include "../../include/testes/TUAtividade.h"

const int TUAtividade::VALOR_VALIDO_AVALIACAO = 4;
const std::string TUAtividade::VALOR_VALIDO_NOME = "Jon�o";
const int TUAtividade::VALOR_VALIDO_DATA[3] = {10, 10, 10};
const std::string TUAtividade::VALOR_VALIDO_HORARIO = "11:30";
const int TUAtividade::VALOR_VALIDO_DURACAO = 348;
const double TUAtividade::VALOR_VALIDO_DINHEIRO = 140550.95;
const std::string TUAtividade::VALOR_VALIDO_CODIGO = "1b22kl";

void TUAtividade::setUp() {
    atividade = new Atividade(Nome(VALOR_VALIDO_NOME), Codigo(VALOR_VALIDO_CODIGO),
                Avaliacao(VALOR_VALIDO_AVALIACAO), Data(VALOR_VALIDO_DATA[0], VALOR_VALIDO_DATA[1], VALOR_VALIDO_DATA[2]),
                Horario(VALOR_VALIDO_HORARIO), Duracao(VALOR_VALIDO_DURACAO), Dinheiro(VALOR_VALIDO_DINHEIRO));
    estado = SUCESSO;
}

void TUAtividade::tearDown() {
    delete atividade;
}

void TUAtividade::testarCenario() {

    //Teste para o dom�nio Avalia��o
    Avaliacao avaliacao(VALOR_VALIDO_AVALIACAO);
    atividade->setAvaliacao(avaliacao);
    if (atividade->getAvaliacao().getValor() != VALOR_VALIDO_AVALIACAO) {
        estado = FALHA;
    }

    // Teste para o dom�nio Nome
    Nome nome(VALOR_VALIDO_NOME);
    atividade->setNome(nome);
    if (atividade->getNome().getValor() != VALOR_VALIDO_NOME) {
        estado = FALHA;
    }

    // Teste para o dom�nio Data
    Data data(VALOR_VALIDO_DATA[0], VALOR_VALIDO_DATA[1], VALOR_VALIDO_DATA[2]);
    atividade->setData(data);
    if (atividade->getData().getValor() != data) {
        estado = FALHA;
    }

    // Teste para o dom�nio Hor�rio
    Horario horario(VALOR_VALIDO_HORARIO);
    atividade->setHorario(horario);
    if (atividade->getHorario().getValor() != VALOR_VALIDO_HORARIO) {
        estado = FALHA;
    }

    // Teste para o dom�nio Dura��o
    Duracao duracao(VALOR_VALIDO_DURACAO);
    atividade->setDuracao(duracao);
    if (atividade->getDuracao().getValor() != VALOR_VALIDO_DURACAO) {
        estado = FALHA;
    }

    // Teste para o dom�nio Dinheiro/Pre�o
    Dinheiro dinheiro(VALOR_VALIDO_DINHEIRO);
    atividade->setPreco(dinheiro);
    if (atividade->getPreco().getValor() != VALOR_VALIDO_DINHEIRO) {
        estado = FALHA;
    }

    // Teste para o dom�nio C�digo
    Codigo codigo(VALOR_VALIDO_CODIGO);
    atividade->setCodigo(codigo);
    if (atividade->getCodigo().getValor() != VALOR_VALIDO_CODIGO) {
        estado = FALHA;
    }
}

int TUAtividade::run() {
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
