#include "../../include/testes/TesteNome.hpp"
#include <fstream>
#include <exception>

TesteNome::TesteNome(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteNome::setUp() {
    // Preparação se necessário antes de rodar os testes (opcional)
}

void TesteNome::tearDown() {
    // Limpeza de recursos após os testes (opcional)
}

void TesteNome::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if(!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while(std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Nome
            Nome nome(linha);
            // Se não lançou exceção, é sucesso
            registrarTesteSucesso();
        } catch (std::exception &e) {
            // Em caso de exceção, registra falha
            registrarTesteFalha("Falha ao validar Nome: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
