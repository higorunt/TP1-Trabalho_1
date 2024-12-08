#include "../../include/testes/TesteNome.hpp"
#include <fstream>
#include <exception>

TesteNome::TesteNome(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteNome::setUp() {
    // Prepara��o se necess�rio antes de rodar os testes (opcional)
}

void TesteNome::tearDown() {
    // Limpeza de recursos ap�s os testes (opcional)
}

void TesteNome::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if(!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while(std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Nome
            Nome nome(linha);
            // Se n�o lan�ou exce��o, � sucesso
            registrarTesteSucesso();
        } catch (std::exception &e) {
            // Em caso de exce��o, registra falha
            registrarTesteFalha("Falha ao validar Nome: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
