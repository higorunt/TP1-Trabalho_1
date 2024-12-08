#include "../../include/testes/TesteAvaliacao.hpp"
#include <fstream>
#include <exception>

TesteAvaliacao::TesteAvaliacao(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteAvaliacao::setUp() {
    // Configurações adicionais antes do teste (opcional)
}

void TesteAvaliacao::tearDown() {
    // Limpeza de recursos após os testes (opcional)
}

void TesteAvaliacao::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Avaliacao
            Avaliacao avaliacao(stoi(linha)); // Conversão para inteiro
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Avaliacao: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
