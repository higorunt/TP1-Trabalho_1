#include <iostream>
#include <locale> // Adicionada para reconhecer caracteres especiais
#include "dominios/Nome.hpp"
#include "entidades/Conta.hpp"
#include "entidades/Viajante.hpp"

int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a UTF-8 (dependente do sistema)
    
    try {
        Codigo codigo("USR123");
        Senha senha("14523");
        Conta conta(codigo, senha);

        Nome nome("João da Silva");
        Viajante viajante(nome, conta);

        std::cout << "Viajante criado com sucesso!" << std::endl;
        std::cout << "Nome: " << viajante.getNome().getValor() << std::endl;
        std::cout << "Código da conta: " << viajante.getConta().getCodigo().getValor() << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
