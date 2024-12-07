#include "TesteNome.hpp"
#include <iostream>

const std::string VALOR_VALIDO = "Jo�o";  // Valor v�lido
const std::string VALOR_INVALIDO = "";    // Valor inv�lido (vazio)

void TesteNome::setUp() {
    nome = new Nome(VALOR_VALIDO); 
    estado = SUCESSO;              
}

void TesteNome::tearDown() {
    delete nome; // Libera a mem�ria alocada para o objeto Nome
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
        // Exce��o esperada - teste bem sucedido
    }
}
