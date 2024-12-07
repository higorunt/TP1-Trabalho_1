#include "TesteNome.hpp"
#include <iostream>

const std::string VALOR_VALIDO = "João";  // Valor válido
const std::string VALOR_INVALIDO = "";    // Valor inválido (vazio)

void TesteNome::setUp() {
    nome = new Nome(VALOR_VALIDO); 
    estado = SUCESSO;              
}

void TesteNome::tearDown() {
    delete nome; // Libera a memória alocada para o objeto Nome
    nome = nullptr;
}

void TesteNome::rodarTestes() {
    testarCenarioValorValido();    
    testarCenarioValorInvalido(); 
}

void TesteNome::testarCenarioValorValido() {
    try {
        nome->setValor(VALOR_VALIDO); 
        if (nome->getValor() != VALOR_VALIDO) { 
            estado = FALHA;
        }
    } catch (const std::invalid_argument& e) {
        estado = FALHA; 
    }
}

void TesteNome::testarCenarioValorInvalido() {
    try {
        nome->setValor(VALOR_INVALIDO); 
        estado = FALHA;                  
    } catch (const std::invalid_argument&) {
        // Exceção esperada - teste bem sucedido
    }
}
