#include "../../include/testes/TesteSenha.hpp"
#include <fstream>
#include <exception>

TesteSenha::TesteSenha(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteSenha::setUp() {
    // Prepara��o, se necess�rio
}

void TesteSenha::tearDown() {
    // Limpeza, se necess�rio
}

void TesteSenha::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Senha
            Senha senha(linha);
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Senha: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
