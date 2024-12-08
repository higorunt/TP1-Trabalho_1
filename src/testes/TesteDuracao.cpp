#include "../../include/testes/TesteDuracao.hpp"
#include <fstream>
#include <exception>

TesteDuracao::TesteDuracao(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteDuracao::setUp() {}

void TesteDuracao::tearDown() {}

void TesteDuracao::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Duracao
            Duracao duracao(stoi(linha)); // Conversão para inteiro
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Duracao: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
