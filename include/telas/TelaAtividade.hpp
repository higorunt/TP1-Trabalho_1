#ifndef TELA_ATIVIDADE_HPP
#define TELA_ATIVIDADE_HPP

#include "../servicos/ServicoAtividade.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Data.hpp"
#include "../dominios/Horario.hpp"
#include "../dominios/Duracao.hpp"
#include "../dominios/Dinheiro.hpp"

class TelaAtividade
{
private:
    ServicoAtividade *servico;
    WINDOW *painelAtividade;

    void desenharModal();
    bool processarAtividade();

public:
    TelaAtividade(ServicoAtividade *srv);
    ~TelaAtividade();

    void mostrar();
    bool executar();
};

#endif // TELA_ATIVIDADE_HPP