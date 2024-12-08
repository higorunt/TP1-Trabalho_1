#include "../../include/testes/TesteHorario.hpp"
#include <fstream>
#include <stdexcept>

TesteHorario::TesteHorario(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteHorario::setUp() {
    // Prepara��o antes dos testes
}

void TesteHorario::tearDown() {
    // Limpeza ap�s os testes
}

void TesteHorario::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Horario diretamente
            Horario horario;
            horario.setValor(linha); // Define o hor�rio ap�s valida��o
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Hor�rio: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
