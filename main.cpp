#include "include/telas/TelaBase.hpp"
#include "include/telas/TelaAutenticacao.hpp"
#include "include/telas/TelaPrincipal.hpp"
#include "include/telas/TelaViagem.hpp"
#include "include/telas/TelaDestino.hpp"
#include "include/servicos/ServicoAutenticacao.hpp"
#include "include/servicos/ServicoViagem.hpp"
#include "include/servicos/ServicoDestino.hpp"
#include "include/servicos/ServicoAtividade.hpp"
#include "include/servicos/ServicoHospedagem.hpp"
#include "include/repositorios/RepositorioAutenticacao.hpp"
#include "include/repositorios/RepositorioViagem.hpp"
#include "include/repositorios/RepositorioDestino.hpp"
#include "include/repositorios/RepositorioAtividade.hpp"
#include "include/repositorios/RepositorioHospedagem.hpp"
#include <iostream>
#include <memory>

int main() {
    setlocale(LC_ALL, "");

    try {
        std::unique_ptr<RepositorioAutenticacao> repAuth(new RepositorioAutenticacao("viagens.db"));
        std::unique_ptr<RepositorioViagem> repViagem(new RepositorioViagem("viagens.db"));
        std::unique_ptr<RepositorioDestino> repDestino(new RepositorioDestino("viagens.db"));
        std::unique_ptr<RepositorioAtividade> repAtividade(new RepositorioAtividade("viagens.db"));
        std::unique_ptr<RepositorioHospedagem> repHospedagem(new RepositorioHospedagem("viagens.db"));

        std::unique_ptr<ServicoAutenticacao> servicoAuth(new ServicoAutenticacao(repAuth.get()));
        std::unique_ptr<ServicoViagem> servicoViagem(new ServicoViagem(repViagem.get(), repDestino.get()));
        std::unique_ptr<ServicoDestino> servicoDestino(new ServicoDestino(repDestino.get()));
        std::unique_ptr<ServicoAtividade> servicoAtividade(new ServicoAtividade(repAtividade.get(), servicoDestino.get()));
        std::unique_ptr<ServicoHospedagem> servicoHospedagem(new ServicoHospedagem(repHospedagem.get()));
        
        std::unique_ptr<TelaAutenticacao> telaAutenticacao(new TelaAutenticacao(servicoAuth.get()));

        std::unique_ptr<Viajante> viajante(telaAutenticacao->fazerLogin());

        if (viajante) {
            std::unique_ptr<TelaPrincipal> telaPrincipal(
                new TelaPrincipal(
                    viajante.get(), 
                    servicoViagem.get(), 
                    servicoDestino.get(),
                    servicoAtividade.get(),    // <-- Quarto argumento
                    servicoHospedagem.get()    // <-- Quinto argumento (faltava este)
                )
            );
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
