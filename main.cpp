// main.cpp
#include "include/telas/TelaBase.hpp"
#include "include/telas/TelaAutenticacao.hpp"
#include "include/servicos/ServicoAutenticacao.hpp"
#include "include/repositorios/RepositorioBase.hpp"
#include "include/repositorios/RepositorioAutenticacao.hpp"
#include <iostream>

int main() {
    try {
        // Criar instâncias necessárias
        auto* repositorio = new RepositorioAutenticacao("viagens.db");
        auto* servico = new ServicoAutenticacao(repositorio);

        // Criar usuário de teste
        try {
            Codigo codigo("ADM123");
            Senha senha("14785");
            Nome nome("Administrador");
            Conta conta(codigo, senha);
            Viajante viajante(nome, conta);

            if (repositorio->salvar(viajante)) {
                std::cout << "Usuário de teste criado com sucesso!" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Nota: " << e.what() << std::endl;
        }

        // Criar e executar tela de autenticação
        auto* telaAutenticacao = new TelaAutenticacao(servico);
        Viajante* viajante = telaAutenticacao->fazerLogin();

        if (viajante) {
            std::cout << "\nBem-vindo, " << viajante->getNome().getValor() << "!" << std::endl;
            delete viajante;
        }

        // Limpar recursos
        delete telaAutenticacao;
        delete servico;
        delete repositorio;

    }
    catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
