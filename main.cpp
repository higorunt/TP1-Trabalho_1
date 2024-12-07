#include <iostream>
#include "tests/TesteNome.hpp"
#include "tests/TesteSenha.hpp" // Inclui o arquivo de testes para o domínio Senha

int main() {
    TesteNome testeNome;
    TesteSenha testeSenha; // Cria uma instância do teste para o domínio Senha

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

    switch (testeSenha.run()) {
        case TesteSenha::SUCESSO:
            std::cout << "SUCESSO: Todos os testes do Dominio Senha passaram!" << std::endl;
            break;
        case TesteSenha::FALHA:
            std::cout << "FALHA: Alguns testes falharam!" << std::endl;
            break;
        default:
            std::cout << "Erro desconhecido!" << std::endl;
    }

    //Pensar em outra logica para fazer os testes!

    return 0;
}
