#ifndef TELA_ATIVIDADE_HPP
#define TELA_ATIVIDADE_HPP

#include <curses.h>
#include <string>
#include <vector>
#include "servicos/ServicoAtividade.hpp"

class TelaAtividade
{
private:
    ServicoAtividade *servico;
    WINDOW *painelAtividade;

public:
    TelaAtividade(ServicoAtividade *srv);
    ~TelaAtividade();
    void desenharModal();
    void mostrar();
    bool processarAtividade();
};

#endif // TELA_ATIVIDADE_HPP