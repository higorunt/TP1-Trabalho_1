#include <iostream>
#include "include/testes/TesteNome.hpp"

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)

    std::cout << "Iniciando testes de Dom�nios e Entidades...\n";

    TesteNome testeNome("test_data/dominios/inputs_nome.txt");
    int resultadoNome = testeNome.run();

    if (resultadoNome == TestBase::FALHA) {
        std::cout << "Alguns testes falharam no dom�nio Nome." << std::endl;
    } else {
        std::cout << "Todos os testes do dom�nio Nome passaram com sucesso." << std::endl;
    }

    return 0;
}
