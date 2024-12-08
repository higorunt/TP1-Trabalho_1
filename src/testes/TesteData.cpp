#include "../../include/testes/TesteData.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

TesteData::TesteData(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteData::setUp() {
    // Preparação antes dos testes
}

void TesteData::tearDown() {
    // Limpeza após os testes
}

void TesteData::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Divide a string no formato DD-MM-AA
            std::istringstream ss(linha);
            int dia, mes, ano;
            char separador1, separador2;

            ss >> dia >> separador1 >> mes >> separador2 >> ano;

            if (ss.fail() || separador1 != '-' || separador2 != '-') {
                throw std::invalid_argument("Formato inválido para Data: " + linha);
            }

            // Tenta criar um objeto Data
            Data data(dia, mes, ano);
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Data: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
