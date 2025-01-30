// main.cpp
#include "include/telas/TelaBase.hpp"
#include "include/telas/TelaAutenticacao.hpp"
#include "include/telas/TelaPrincipal.hpp"
#include "include/servicos/ServicoAutenticacao.hpp"
#include "include/repositorios/RepositorioAutenticacao.hpp"
#include <iostream>
#include <memory> // Para smart pointers

int main() {
    setlocale(LC_ALL, "");

    try {
        // Criar instâncias usando smart pointers
        std::unique_ptr<RepositorioAutenticacao> repositorio(new RepositorioAutenticacao("viagens.db"));
        std::unique_ptr<ServicoAutenticacao> servico(new ServicoAutenticacao(repositorio.get()));
        std::unique_ptr<TelaAutenticacao> telaAutenticacao(new TelaAutenticacao(servico.get()));

        // Fazer login
        std::unique_ptr<Viajante> viajante(telaAutenticacao->fazerLogin());

        if (viajante) {
            // Criar e executar tela principal
            std::unique_ptr<TelaPrincipal> telaPrincipal(new TelaPrincipal(viajante.get()));
            telaPrincipal->executar();
            // Não precisa fazer delete, o unique_ptr cuida disso
        }

        // Não precisa fazer delete, os smart pointers cuidam da limpeza automaticamente
        endwin(); // Garante que o ncurses seja encerrado adequadamente
    }
    catch (const std::exception& e) {
        endwin(); // Garante que o ncurses seja encerrado mesmo em caso de erro
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}