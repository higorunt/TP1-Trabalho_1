#ifndef TELA_VIAJANTE_HPP
#define TELA_VIAJANTE_HPP

#include "../servicos/ServicoViajante.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"

class TelaViajante
{
private:
    ServicoViajante *servico;
    WINDOW *painelViajante;

    void desenharModal();
    bool processarViajante();

public:
    TelaViajante(ServicoViajante *srv);
    ~TelaViajante();

    void mostrar();
    bool executar();
};

#endif // TELA_VIAJANTE_HPP