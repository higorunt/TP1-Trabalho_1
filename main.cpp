// main.cpp
#include "include/telas/TelaBase.hpp"
#include "include/telas/TelaAutenticacao.hpp"
#include "include/telas/TelaPrincipal.hpp"
#include "include/telas/TelaViagem.hpp"
#include "include/servicos/ServicoAutenticacao.hpp"
#include "include/servicos/ServicoViagem.hpp"
#include "include/repositorios/RepositorioAutenticacao.hpp"
#include "include/repositorios/RepositorioViagem.hpp"
#include "include/repositorios/RepositorioDestino.hpp"
#include <iostream>
#include <memory>

int main() {
    setlocale(LC_ALL, "");

    try {
        // Criar instâncias usando smart pointers
        std::unique_ptr<RepositorioAutenticacao> repAuth(new RepositorioAutenticacao("viagens.db"));
        std::unique_ptr<RepositorioViagem> repViagem(new RepositorioViagem("viagens.db"));
        std::unique_ptr<RepositorioDestino> repDestino(new RepositorioDestino("viagens.db"));

        std::unique_ptr<ServicoAutenticacao> servicoAuth(new ServicoAutenticacao(repAuth.get()));
        std::unique_ptr<ServicoViagem> servicoViagem(new ServicoViagem(repViagem.get(), repDestino.get()));
        
        std::unique_ptr<TelaAutenticacao> telaAutenticacao(new TelaAutenticacao(servicoAuth.get()));

        // Fazer login
        std::unique_ptr<Viajante> viajante(telaAutenticacao->fazerLogin());

        if (viajante) {
            // Criar telas
            std::unique_ptr<TelaViagem> telaViagem(new TelaViagem(servicoViagem.get(), viajante.get()));
            std::unique_ptr<TelaPrincipal> telaPrincipal(new TelaPrincipal(viajante.get(), servicoViagem.get()));
            
            // Executar tela principal
            telaPrincipal->executar();
        }

        endwin();
    }
    catch (const std::exception& e) {
        endwin();
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}