#ifndef TELA_HOSPEDAGEM_HPP
#define TELA_HOSPEDAGEM_HPP
//221006440
#include "TelaBase.hpp"
#include "../servicos/ServicoHospedagem.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../entidades/Viajante.hpp"

/**
 * @brief Classe que gerencia a interface de hospedagens.
 * 
 * Permite gerenciar hospedagens associadas a destinos.
 */
class TelaHospedagem : public TelaBase {
public:
    TelaHospedagem(ServicoHospedagem* srvHospedagem, ServicoDestino* srvDestino, Viajante* v)
        : servicoHospedagem(srvHospedagem), servicoDestino(srvDestino), 
          viajante(v), painelHospedagem(nullptr) {}
    
    ~TelaHospedagem() {
        if (painelHospedagem != nullptr) {
            delwin(painelHospedagem);
        }
    }

    void mostrar() override;

private:
    ServicoHospedagem* servicoHospedagem;
    ServicoDestino* servicoDestino;
    Viajante* viajante;
    WINDOW* painelHospedagem;
    
    struct {
        int altura = 12;
        int largura = 40;
        int centralY;
        int centralX;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);
    bool criarHospedagem();
    void visualizarHospedagem();
    void editarHospedagem();
    void excluirHospedagem();
    Codigo selecionarDestino();
};

#endif
