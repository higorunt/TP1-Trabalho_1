#ifndef TELA_VIAGEM_HPP
#define TELA_VIAGEM_HPP

#include "TelaBase.hpp"
#include "../servicos/ServicoViagem.hpp"
#include "../entidades/Viajante.hpp"
#include <vector>

class TelaViagem : public TelaBase {
private:
    ServicoViagem* servico;
    Viajante* viajante;

    void mostrarFormularioCriar();
    void mostrarFormularioEditar(const Viagem& viagem);
    void mostrarDetalhesViagem(const Viagem& viagem);
    void mostrarListaViagens(const std::vector<Viagem>& viagens);

public:
    TelaViagem(ServicoViagem* srv, Viajante* vjt) : servico(srv), viajante(vjt) {}
    
    void mostrar() override;
    void mostrarMenuViagens();
    void criarViagem();
    void listarViagens();
    void editarViagem();
    void excluirViagem();
    void calcularCustoViagem();
};

#endif