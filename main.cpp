#include "include/apresentacao/TelaLogin.hpp"
#include "include/services/AutenticacaoService.hpp"
#include "include/repositories/SQLiteAutenticacaoRepository.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "\n=== Sistema de Planejamento de Viagens ===\n" << std::endl;

        // Criar instâncias necessárias
        SQLiteAutenticacaoRepository* repo = new SQLiteAutenticacaoRepository("viagens.db");
        IAutenticacaoService* service = new AutenticacaoService(repo);

        // Criar um usuário de teste
        std::cout << "\nConfigurando usuário de teste..." << std::endl;

        try {
            Codigo codigo("ADM123");
            Senha senha("14785");
            Nome nome("Administrador");
            Conta conta(codigo, senha);
            Viajante viajante(nome, conta);

            bool salvou = repo->salvar(viajante);
            if (salvou) {
                std::cout << "Usuário de teste configurado com sucesso!" << std::endl;
            }

            // Listar viajantes cadastrados
            repo->listarViajantes();

        }
        catch (const std::exception& e) {
            std::cout << "Erro ao configurar usuário de teste: " << e.what() << std::endl;
        }

        // Criar e executar tela de login
        std::cout << "\nIniciando sistema de login..." << std::endl;
        TelaLogin* telaLogin = new TelaLogin(service);
        Viajante* viajante = telaLogin->executar();

        if (viajante) {
            std::cout << "\nBem-vindo, " << viajante->getNome().getValor() << "!" << std::endl;
            delete viajante;
        }

        // Limpar recursos
        delete telaLogin;
        delete service;
        delete repo;

    }
    catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nPrograma finalizado.\n" << std::endl;
    return 0;
}
