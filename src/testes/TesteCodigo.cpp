
#include "../../include/testes/TesteCodigo.hpp"
#include <fstream>
#include <exception>

TesteCodigo::TesteCodigo(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteCodigo::setUp() {
    // Preparação, se necessário
}

void TesteCodigo::tearDown() {
    // Limpeza, se necessário
}

void TesteCodigo::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Codigo
            Codigo codigo(linha);
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Codigo: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
