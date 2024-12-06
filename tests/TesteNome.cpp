#include "TesteNome.h"
#include <iostream>

TesteNome::TesteNome() : TestBase("Teste do domínio Nome") {
    // Montamos uma lista de testes detalhada.
    // Cada teste inclui:
    // - O valor de entrada
    // - Se deve ou não ser válido
    // - Uma breve descrição do que está sendo testado

    casos.push_back({"Joao", true, "Valor válido básico"});
    casos.push_back({"", false, "Valor vazio - deve ser inválido"});
    casos.push_back({std::string(31, 'A'), false, "Valor com 31 caracteres - excede limite"});
    casos.push_back({"A", true, "Valor no limite inferior (1 caractere)"});
    casos.push_back({std::string(30, 'B'), true, "Valor no limite superior (30 caracteres)"});
}

bool TesteNome::rodarCasoTeste(const CasoTeste &caso) {
    std::cout << "Testando valor: \"" << caso.valor << "\" (" << caso.descricao << ")\n";

    bool resultado;
    try {
        Nome nome(caso.valor);
        // Se chegar aqui sem exceção, o valor foi aceito
        resultado = true;
    } catch (const std::invalid_argument &) {
        // Foi lançado std::invalid_argument, então o valor é inválido
        resultado = false;
    } catch (...) {
        // Qualquer outra exceção não esperada
        std::cout << "Erro inesperado!\n";
        return false;
    }

    // Mostrar o resultado esperado e o obtido
    std::cout << "  Esperado: " << (caso.deveSerValido ? "Válido" : "Inválido")
              << " | Obtido: " << (resultado ? "Válido" : "Inválido") << "\n\n";

    // Retornar se o resultado atende ao esperado
    return (resultado == caso.deveSerValido);
}

void TesteNome::executar() {
    bool resultadoGeral = true;
    for (auto &caso : casos) {
        if (!rodarCasoTeste(caso)) {
            resultadoGeral = false;
        }
    }
    mostrarResultado(resultadoGeral);
}

void executarTesteNome() {
    TesteNome teste;
    teste.executar();
}
