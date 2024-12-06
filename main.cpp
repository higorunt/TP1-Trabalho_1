#include <iostream>
#include "tests/TesteNome.h" // Inclui o arquivo de testes para o dom�nio Nome

int main() {
    TesteNome testeNome;  // Cria uma inst�ncia do teste para o dom�nio Nome

    // Executa os testes e verifica o resultado
    switch (testeNome.run()) {
        case TesteNome::SUCESSO:
            std::cout << "SUCESSO: Todos os testes do Dominio Nome passaram!" << std::endl;
            break;
        case TesteNome::FALHA:
            std::cout << "FALHA: Alguns testes falharam!" << std::endl;
            break;
        default:
            std::cout << "Erro desconhecido!" << std::endl;
    }

    return 0;
}
