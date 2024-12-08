
#include "../../include/testes/TesteCodigo.hpp"
#include <fstream>
#include <exception>

TesteCodigo::TesteCodigo(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteCodigo::setUp() {
    // Prepara��o, se necess�rio
}

void TesteCodigo::tearDown() {
    // Limpeza, se necess�rio
}

void TesteCodigo::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
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
