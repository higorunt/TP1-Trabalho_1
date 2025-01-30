// include/telas/TelaPrincipal.hpp
#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "../entidades/Viajante.hpp"

class TelaPrincipal : public TelaBase {
private:
    Viajante* viajante;
    WINDOW* painelMenu;
    
    struct {
        int menuY = 5;
        int altura = 20;  // Aumentei para comportar mais opções
        int largura = 60; // Aumentei para textos mais longos
        int centralX;
        int centralY;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);

public:
    TelaPrincipal(Viajante* viajante);
    ~TelaPrincipal();

    void mostrar() override;
    void executar();
};

#endif