// main.cpp
#include "include/telas/TelaBase.hpp"
#include "include/telas/TelaAutenticacao.hpp"
#include "include/telas/TelaPrincipal.hpp"
#include "include/servicos/ServicoAutenticacao.hpp"
#include "include/repositorios/RepositorioAutenticacao.hpp"
#include <iostream>

int main() {
    setlocale(LC_ALL, "");

    try {
        // Criar instâncias necessárias
        auto* repositorio = new RepositorioAutenticacao("viagens.db");
        auto* servico = new ServicoAutenticacao(repositorio);

        // Criar e executar tela de autenticação
        auto* telaAutenticacao = new TelaAutenticacao(servico);
        Viajante* viajante = telaAutenticacao->fazerLogin();

        if (viajante) {
            // Criar e executar tela principal
            auto* telaPrincipal = new TelaPrincipal(viajante);
            telaPrincipal->executar();
            delete telaPrincipal;
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