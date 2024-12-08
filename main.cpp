#include <iostream>
#include "include/testes/TesteNome.hpp"
#include "include/testes/TesteCodigo.hpp"
#include "include/testes/TesteSenha.hpp"
#include "include/testes/TesteAvaliacao.hpp"
#include "include/testes/TesteData.hpp"
#include "include/testes/TesteDinheiro.hpp"
#include "include/testes/TesteDuracao.hpp"
#include "include/testes/TesteHorario.hpp"

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)
    std::cout << "Iniciando testes...\n";

    // Teste do domínio Nome
    TesteNome testeNome("test_data/dominios/inputs_nome.txt");
    int resultadoNome = testeNome.run();

    // Teste do domínio Código
    TesteCodigo testeCodigo("test_data/dominios/inputs_codigo.txt");
    int resultadoCodigo = testeCodigo.run();

    // Teste do domínio Senha
    TesteSenha testeSenha("test_data/dominios/inputs_senha.txt");
    int resultadoSenha = testeSenha.run();

    // Teste do domínio Avaliação
    TesteAvaliacao testeAvaliacao("test_data/dominios/inputs_avaliacao.txt");
    int resultadoAvaliacao = testeAvaliacao.run();

    // Teste do domínio Data
    TesteData testeData("test_data/dominios/inputs_data.txt");
    int resultadoData = testeData.run();

    // Teste do domínio Dinheiro
    TesteDinheiro testeDinheiro("test_data/dominios/inputs_dinheiro.txt");
    int resultadoDinheiro = testeDinheiro.run();

    // Teste do domínio Duração
    TesteDuracao testeDuracao("test_data/dominios/inputs_duracao.txt");
    int resultadoDuracao = testeDuracao.run();

    // Teste do domínio Horário
    TesteHorario testeHorario("test_data/dominios/inputs_horario.txt");
    int resultadoHorario = testeHorario.run();

    // Resumo geral
    std::cout << "\nResumo Geral dos Testes:\n";
    if (resultadoNome == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Nome.\n";
    }
    if (resultadoCodigo == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Código.\n";
    }
    if (resultadoSenha == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Senha.\n";
    }
    if (resultadoAvaliacao == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Avaliação.\n";
    }
    if (resultadoData == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Data.\n";
    }
    if (resultadoDinheiro == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Dinheiro.\n";
    }
    if (resultadoDuracao == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Duração.\n";
    }
    if (resultadoHorario == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Horário.\n";
    }

    std::cout << "Testes concluídos.\n";
    return 0;
}
