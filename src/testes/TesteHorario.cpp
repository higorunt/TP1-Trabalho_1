#include "../../include/testes/TesteHorario.hpp"
#include <fstream>
#include <stdexcept>

TesteHorario::TesteHorario(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteHorario::setUp() {
    // Preparação antes dos testes
}

void TesteHorario::tearDown() {
    // Limpeza após os testes
}

void TesteHorario::rodarTestes() {
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Tenta criar um objeto Horario diretamente
            Horario horario;
            horario.setValor(linha); // Define o horário após validação
            registrarTesteSucesso();
        } catch (std::exception &e) {
            registrarTesteFalha("Falha ao validar Horário: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
