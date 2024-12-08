#include "../../include/testes/TesteAvaliacao.hpp"
#include <fstream>
#include <exception>

TesteAvaliacao::TesteAvaliacao(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteAvaliacao::setUp() {
    // Configura��es adicionais antes do teste (opcional)
}

void TesteAvaliacao::tearDown() {
    // Limpeza de recursos ap�s os testes (opcional)
}

void TesteAvaliacao::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Avaliacao
            Avaliacao avaliacao(stoi(linha)); // Convers�o para inteiro
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Avaliacao: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
