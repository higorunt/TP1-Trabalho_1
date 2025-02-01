// include/telas/TelaPrincipal.hpp
#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "TelaViagem.hpp"
#include "../entidades/Viajante.hpp"
#include "../servicos/ServicoViagem.hpp"

class TelaPrincipal : public TelaBase {
private:
    Viajante* viajante;
    ServicoViagem* servicoViagem;
    TelaViagem* telaViagem;
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
    TelaPrincipal(Viajante* viajante, ServicoViagem* servicoViagem);
    ~TelaPrincipal();

    void mostrar() override;
    void executar();
};

#endif