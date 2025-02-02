#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "TelaViagem.hpp"
#include "TelaDestino.hpp"  // Inclus�o da tela de destinos
#include "TelaAtividade.hpp"
#include "TelaHospedagem.hpp"
#include "../entidades/Viajante.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../servicos/ServicoAtividade.hpp"
#include "../servicos/ServicoHospedagem.hpp"

class TelaPrincipal : public TelaBase {
private:
    Viajante* viajante;
    ServicoViagem* servicoViagem;
    ServicoDestino* servicoDestino;
    ServicoAtividade* servicoAtividade;
    ServicoHospedagem* servicoHospedagem;
    TelaViagem* telaViagem;
    TelaDestino* telaDestino;
    TelaAtividade* telaAtividade;
    TelaHospedagem* telaHospedagem;
    WINDOW* painelMenu;
    
    struct {
        int menuY = 5;
        int altura = 20;
        int largura = 60;
        int centralX;
        int centralY;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);

public:
    TelaPrincipal(Viajante* viajante, 
                  ServicoViagem* servicoViagem, 
                  ServicoDestino* servicoDestino,
                  ServicoAtividade* servicoAtividade,
                  ServicoHospedagem* servicoHospedagem);
    ~TelaPrincipal();

    void mostrar() override;
    void executar();
};

#endif
