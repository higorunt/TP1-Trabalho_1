// include/telas/TelaViagem.hpp
#ifndef TELA_VIAGEM_HPP
#define TELA_VIAGEM_HPP
//221006404
#include "TelaBase.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../entidades/Viajante.hpp"
#include <PDcurses.h>
#include <vector>

/**
 * @brief Classe que gerencia a interface de viagens.
 * 
 * Permite criar, editar, excluir e visualizar viagens do usuário.
 */
class TelaViagem : public TelaBase {
private:
    ServicoViagem* servico;
    Viajante* viajante;
    WINDOW* painelViagem;

    struct {
        int menuY = 5;
        int altura = 20;
        int largura = 60;
        int centralX;
        int centralY;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);
    void criarViagem();
    void listarViagens();
    void editarViagem();
    void excluirViagem();
    void calcularCustoViagem();
    void mostrarDetalhesViagem(const Viagem& viagem);
    void mostrarFormularioEditar(const Viagem& viagem);

public:
    TelaViagem(ServicoViagem* srv, Viajante* vjt) 
        : servico(srv), viajante(vjt), painelViagem(nullptr) {
        layout.centralX = 0;
        layout.centralY = 0;
    }

    ~TelaViagem() {
        if (painelViagem != nullptr) {
            delwin(painelViagem);
            painelViagem = nullptr;
        }
    }

    void mostrar() override;
};

#endif