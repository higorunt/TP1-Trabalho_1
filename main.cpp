#include <iostream>
#include "tests/TesteNome.h"

int main() {
    // Configurar o locale para UTF-8 (em sistemas Linux/Unix normalmente "pt_BR.UTF-8")
    // Em Windows, tente "Portuguese_Brazil.1252" ou outra localidade compatível:
    setlocale(LC_ALL, "");

    std::cout << "Executando testes do Trabalho 1\n";
    std::cout << "--------------------------------\n";

    executarTesteNome();

    std::cout << "--------------------------------\n";
    std::cout << "Todos os testes foram executados.\n";

    return 0;
}
