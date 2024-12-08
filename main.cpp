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
    // Teste do domínio Nome
    TesteNome testeNome("test_data/dominios/inputs_nome.txt");
    int resultadoNome = testeNome.run();
    if (resultadoNome == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Nome." << endl;
    }

    // Teste do domínio Código
    TesteCodigo testeCodigo("test_data/dominios/inputs_codigo.txt");
    int resultadoCodigo = testeCodigo.run();
    if (resultadoCodigo == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Código." << endl;
    }

    // Teste do domínio Senha
    TesteSenha testeSenha("test_data/dominios/inputs_senha.txt");
    int resultadoSenha = testeSenha.run();
    if (resultadoSenha == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Senha." << endl;
    }

    // Teste do domínio Avaliação
    TesteAvaliacao testeAvaliacao("test_data/dominios/inputs_avaliacao.txt");
    int resultadoAvaliacao = testeAvaliacao.run();
    if (resultadoAvaliacao == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Avaliação." << endl;
    }

    // Teste do domínio Data
    TesteData testeData("test_data/dominios/inputs_data.txt");
    int resultadoData = testeData.run();
    if (resultadoData == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Data." << endl;
    }

    // Teste do domínio Dinheiro
    TesteDinheiro testeDinheiro("test_data/dominios/inputs_dinheiro.txt");
    int resultadoDinheiro = testeDinheiro.run();
    if (resultadoDinheiro == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Dinheiro." << endl;
    }

    // Teste do domínio Duração
    TesteDuracao testeDuracao("test_data/dominios/inputs_duracao.txt");
    int resultadoDuracao = testeDuracao.run();
    if (resultadoDuracao == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Duração." << endl;
    }

    // Teste do domínio Horário
    TesteHorario testeHorario("test_data/dominios/inputs_horario.txt");
    int resultadoHorario = testeHorario.run();
    if (resultadoHorario == TestBase::FALHA) {
        cout << "Alguns testes falharam no domínio Horário." << endl;
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


    // Adicione aqui os testes para outras entidades conforme necessário
}

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)

    cout << "Iniciando testes de domínios..." << endl;
    rodarTestesDominios();

    cout << "\nIniciando testes de entidades..." << endl;
    rodarTestesEntidades();

    cout << "\nTestes concluídos." << endl;
    return 0;
}
