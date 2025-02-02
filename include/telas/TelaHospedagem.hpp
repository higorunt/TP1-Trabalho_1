#ifndef TELA_HOSPEDAGEM_HPP
#define TELA_HOSPEDAGEM_HPP

#include "../servicos/ServicoHospedagem.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Nome.hpp"
#include "../dominios/Dinheiro.hpp"

class TelaHospedagem
{
private:
    ServicoHospedagem *servico;
    WINDOW *painelHospedagem;

    void desenharModal();
    bool processarHospedagem();

public:
    TelaHospedagem(ServicoHospedagem *srv);
    ~TelaHospedagem();

    void mostrar();
    bool executar();
};

#endif // TELA_HOSPEDAGEM_HPP