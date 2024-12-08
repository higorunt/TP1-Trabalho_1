#include "../../include/testes/TesteDinheiro.hpp"
#include <fstream>
#include <exception>

TesteDinheiro::TesteDinheiro(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteDinheiro::setUp() {}

void TesteDinheiro::tearDown() {}

void TesteDinheiro::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Dinheiro
            Dinheiro dinheiro(stof(linha)); // Conversão para float
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Dinheiro: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
