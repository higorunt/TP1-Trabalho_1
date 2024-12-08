#include <iostream>
#include "include/testes/TesteNome.hpp"
#include "include/testes/TesteCodigo.hpp"
#include "include/testes/TesteSenha.hpp"
#include "include/testes/TesteAvaliacao.hpp"
#include "include/testes/TesteData.hpp"
#include "include/testes/TesteDinheiro.hpp"
#include "include/testes/TesteDuracao.hpp"
#include "include/testes/TesteHorario.hpp"
#include "include/testes/TUConta.hpp"

using namespace std;

void rodarTestesDominios() {
    // Teste do dom�nio Nome
    TesteNome testeNome("test_data/dominios/inputs_nome.txt");
    int resultadoNome = testeNome.run();
    if (resultadoNome == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Nome." << endl;
    }

    // Teste do dom�nio C�digo
    TesteCodigo testeCodigo("test_data/dominios/inputs_codigo.txt");
    int resultadoCodigo = testeCodigo.run();
    if (resultadoCodigo == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio C�digo." << endl;
    }

    // Teste do dom�nio Senha
    TesteSenha testeSenha("test_data/dominios/inputs_senha.txt");
    int resultadoSenha = testeSenha.run();
    if (resultadoSenha == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Senha." << endl;
    }

    // Teste do dom�nio Avalia��o
    TesteAvaliacao testeAvaliacao("test_data/dominios/inputs_avaliacao.txt");
    int resultadoAvaliacao = testeAvaliacao.run();
    if (resultadoAvaliacao == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Avalia��o." << endl;
    }

    // Teste do dom�nio Data
    TesteData testeData("test_data/dominios/inputs_data.txt");
    int resultadoData = testeData.run();
    if (resultadoData == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Data." << endl;
    }

    // Teste do dom�nio Dinheiro
    TesteDinheiro testeDinheiro("test_data/dominios/inputs_dinheiro.txt");
    int resultadoDinheiro = testeDinheiro.run();
    if (resultadoDinheiro == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Dinheiro." << endl;
    }

    // Teste do dom�nio Dura��o
    TesteDuracao testeDuracao("test_data/dominios/inputs_duracao.txt");
    int resultadoDuracao = testeDuracao.run();
    if (resultadoDuracao == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Dura��o." << endl;
    }

    // Teste do dom�nio Hor�rio
    TesteHorario testeHorario("test_data/dominios/inputs_horario.txt");
    int resultadoHorario = testeHorario.run();
    if (resultadoHorario == TestBase::FALHA) {
        cout << "Alguns testes falharam no dom�nio Hor�rio." << endl;
    }
}

void rodarTestesEntidades() {
    // Teste da entidade Conta
    TUConta testeConta;
    int resultadoConta = testeConta.run();
    if (resultadoConta == TUConta::SUCESSO) {
        cout << "Entidade Conta: SUCESSO ." << endl;
    }
    else{
        cout << "Alguns testes falharam na entidade Conta ." << endl;
    }


    // Adicione aqui os testes para outras entidades conforme necess�rio
}

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)

    cout << "Iniciando testes de dom�nios..." << endl;
    rodarTestesDominios();

    cout << "\nIniciando testes de entidades..." << endl;
    rodarTestesEntidades();

    cout << "\nTestes conclu�dos." << endl;
    return 0;
}
