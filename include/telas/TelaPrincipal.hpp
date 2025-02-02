#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "TelaViagem.hpp"
#include "TelaDestino.hpp"  // Inclusão da nova tela de destinos
#include "../entidades/Viajante.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../servicos/ServicoDestino.hpp"

class TelaPrincipal : public TelaBase {
private:
    Viajante* viajante;
    ServicoViagem* servicoViagem;
    ServicoDestino* servicoDestino;
    TelaViagem* telaViagem;
    TelaDestino* telaDestino;
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
    TelaPrincipal(Viajante* viajante, ServicoViagem* servicoViagem, ServicoDestino* servicoDestino);
    ~TelaPrincipal();

    void mostrar() override;
    void executar();
};

#endif
