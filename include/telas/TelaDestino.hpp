#ifndef TELA_DESTINO_HPP
#define TELA_DESTINO_HPP

#include "../servicos/ServicoDestino.hpp"
#ifdef _WIN32
#include <ncurses.h>
#else
#include <ncurses.h>
#endif
#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Data.hpp"

class TelaDestino
{
private:
    ServicoDestino *servico;
    WINDOW *painelDestino;

    void desenharModal();
    bool processarDestino();

public:
    TelaDestino(ServicoDestino *srv);
    ~TelaDestino();

    void mostrar();
    bool executar();
};

#endif // TELA_DESTINO_HPP