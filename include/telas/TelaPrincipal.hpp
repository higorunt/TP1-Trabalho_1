//221006440
#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "TelaViagem.hpp"
#include "TelaDestino.hpp"  // Inclusão da tela de destinos
#include "TelaAtividade.hpp"
#include "TelaHospedagem.hpp"
#include "TelaRelatorios.hpp"
#include "../entidades/Viajante.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../servicos/ServicoAtividade.hpp"
#include "../servicos/ServicoHospedagem.hpp"

/**
 * @brief Classe que gerencia a interface principal do sistema.
 * 
 * Coordena o acesso às diferentes funcionalidades do sistema.
 */
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
    TelaRelatorios* telaRelatorios;
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
