#include <iostream>
#include "include/testes/TesteNome.hpp"

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)

    std::cout << "Iniciando testes de Domínios e Entidades...\n";

    TesteNome testeNome("test_data/dominios/inputs_nome.txt");
    int resultadoNome = testeNome.run();

    if (resultadoNome == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no domínio Nome." << std::endl;
    } else {
        std::cout << "Todos os testes do domínio Nome passaram com sucesso." << std::endl;
    }

    return 0;
}
