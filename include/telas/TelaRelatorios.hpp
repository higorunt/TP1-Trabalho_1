#ifndef TELA_RELATORIOS_HPP
#define TELA_RELATORIOS_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../servicos/ServicoDestino.hpp"
#include "../servicos/ServicoAtividade.hpp"
#include "../servicos/ServicoHospedagem.hpp"
#include "../entidades/Viajante.hpp"

class TelaRelatorios : public TelaBase {
public:
    TelaRelatorios(ServicoViagem* srvViagem, 
                   ServicoDestino* srvDestino,
                   ServicoAtividade* srvAtividade,
                   ServicoHospedagem* srvHospedagem,
                   Viajante* v)
        : servicoViagem(srvViagem), servicoDestino(srvDestino),
          servicoAtividade(srvAtividade), servicoHospedagem(srvHospedagem),
          viajante(v), painelRelatorios(nullptr) {}
    
    ~TelaRelatorios() {
        if (painelRelatorios) delwin(painelRelatorios);
    }

    void mostrar() override;

private:
    ServicoViagem* servicoViagem;
    ServicoDestino* servicoDestino;
    ServicoAtividade* servicoAtividade;
    ServicoHospedagem* servicoHospedagem;
    Viajante* viajante;
    WINDOW* painelRelatorios;

    struct {
        int altura = 20;
        int largura = 60;
        int centralX;
        int centralY;
    } layout;

    void desenharMenu();
    void processarOpcao(int opcao);
    void resumoGeralCustos();
    void listarMinhasViagens();
    void detalhesViagem();
    void relatorioDestino();
    void relatorioAtividades();
    void relatorioHospedagens();
    void exibirDetalhesDestino(const Destino& destino);
    int calcularDias(const std::string& dataInicio, const std::string& dataFim);
};

#endif
