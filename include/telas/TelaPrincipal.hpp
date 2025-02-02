#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include "TelaBase.hpp"
#include "TelaViagem.hpp"
#include "TelaDestino.hpp"
#include "TelaAtividade.hpp"
#include "TelaHospedagem.hpp"
#include "TelaViajante.hpp"
#include "TelaConta.hpp"
#include "../entidades/Viajante.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../servicos/ServicoAtividade.hpp"
#include "../servicos/ServicoHospedagem.hpp"
#include "../servicos/ServicoViajante.hpp"
#include "../servicos/ServicoConta.hpp"

class TelaPrincipal : public TelaBase
{
private:
    Viajante *viajante;
    ServicoViagem *servicoViagem;
    ServicoDestino *servicoDestino;
    ServicoAtividade *servicoAtividade;
    ServicoHospedagem *servicoHospedagem;
    ServicoViajante *servicoViajante;
    ServicoConta *servicoConta;

    TelaViagem *telaViagem;
    TelaDestino *telaDestino;
    TelaAtividade *telaAtividade;
    TelaHospedagem *telaHospedagem;
    TelaViajante *telaViajante;
    TelaConta *telaConta;

    WINDOW *painelMenu;

    struct
    {
        int menuY = 5;
        int altura = 20;
        int largura = 60;
        int centralX;
        int centralY;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);

public:
    TelaPrincipal(Viajante *viajante,
                  ServicoViagem *servicoViagem,
                  ServicoDestino *servicoDestino,
                  ServicoAtividade *servicoAtividade,
                  ServicoHospedagem *servicoHospedagem,
                  ServicoViajante *servicoViajante,
                  ServicoConta *servicoConta);
    ~TelaPrincipal();

    void mostrar() override;
    void executar();
};

#endif