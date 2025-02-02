#ifndef TELA_ATIVIDADE_HPP
#define TELA_ATIVIDADE_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoAtividade.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../entidades/Viajante.hpp"

class TelaAtividade : public TelaBase {
public:
    TelaAtividade(ServicoAtividade* srvAtividade, ServicoDestino* srvDestino, Viajante* v)
        : servicoAtividade(srvAtividade), servicoDestino(srvDestino), viajante(v), painelAtividade(nullptr) {}
    
    ~TelaAtividade() {
        if (painelAtividade != nullptr) {
            delwin(painelAtividade);
        }
    }

    void mostrar() override;

private:
    ServicoAtividade* servicoAtividade;
    ServicoDestino* servicoDestino;
    Viajante* viajante;
    WINDOW* painelAtividade;
    
    struct {
        int altura = 12;
        int largura = 40;
        int centralY;
        int centralX;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);
    bool criarAtividade();
    void listarAtividades();
    void editarAtividade();
    void excluirAtividade();
    Codigo selecionarDestino();
    std::string formatarData(const std::string& dataStr);  // Adicionar declaração do método
};

#endif
