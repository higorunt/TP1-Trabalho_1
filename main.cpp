#include <iostream>
#include "dominios/Nome.h"

int main() {
    try {
        Nome nome;

        // Teste v�lido
        nome.setValor("Joao Silva");
        std::cout << "Teste valido passou: " << nome.getValor() << std::endl;

        // Teste inv�lido: vazio
        nome.setValor("");
    } catch (const std::invalid_argument& e) {
        std::cout << "Teste invalido passou: " << e.what() << std::endl;
    }

    try {
        Nome nome;

        // Teste inv�lido: mais de 30 caracteres
        nome.setValor("Este nome � muito longo para ser valido");
    } catch (const std::invalid_argument& e) {
        std::cout << "Teste invalido passou: " << e.what() << std::endl;
    }

    return 0;
}
