#include "TesteNome.h"
#include <iostream>

TesteNome::TesteNome() : TestBase("Teste do dom�nio Nome") {
    // Montamos uma lista de testes detalhada.
    // Cada teste inclui:
    // - O valor de entrada
    // - Se deve ou n�o ser v�lido
    // - Uma breve descri��o do que est� sendo testado

    casos.push_back({"Joao", true, "Valor v�lido b�sico"});
    casos.push_back({"", false, "Valor vazio - deve ser inv�lido"});
    casos.push_back({std::string(31, 'A'), false, "Valor com 31 caracteres - excede limite"});
    casos.push_back({"A", true, "Valor no limite inferior (1 caractere)"});
    casos.push_back({std::string(30, 'B'), true, "Valor no limite superior (30 caracteres)"});
}

bool TesteNome::rodarCasoTeste(const CasoTeste &caso) {
    std::cout << "Testando valor: \"" << caso.valor << "\" (" << caso.descricao << ")\n";

    bool resultado;
    try {
        Nome nome(caso.valor);
        // Se chegar aqui sem exce��o, o valor foi aceito
        resultado = true;
    } catch (const std::invalid_argument &) {
        // Foi lan�ado std::invalid_argument, ent�o o valor � inv�lido
        resultado = false;
    } catch (...) {
        // Qualquer outra exce��o n�o esperada
        std::cout << "Erro inesperado!\n";
        return false;
    }

    // Mostrar o resultado esperado e o obtido
    std::cout << "  Esperado: " << (caso.deveSerValido ? "V�lido" : "Inv�lido")
              << " | Obtido: " << (resultado ? "V�lido" : "Inv�lido") << "\n\n";

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
