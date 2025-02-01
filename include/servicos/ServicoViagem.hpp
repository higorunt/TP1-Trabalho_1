#ifndef SERVICO_VIAGEM_HPP
#define SERVICO_VIAGEM_HPP

#include "../repositorios/RepositorioViagem.hpp"
#include "../repositorios/RepositorioDestino.hpp"
#include "../entidades/Viagem.hpp"
#include "../entidades/Destino.hpp"
#include <vector>
#include <memory>

class ServicoViagem {
private:
    RepositorioViagem* repositorioViagem;
    RepositorioDestino* repositorioDestino;

public:
    ServicoViagem(RepositorioViagem* repViagem, RepositorioDestino* repDestino)
        : repositorioViagem(repViagem), repositorioDestino(repDestino) {}

    bool criarViagem(const Viagem& viagem);
    Viagem* buscarViagem(const Codigo& codigo);
    bool atualizarViagem(const Viagem& viagem);
    bool excluirViagem(const Codigo& codigo);
    
    double calcularCustoViagem(const Codigo& codigoViagem);
    std::vector<Viagem> listarViagensPorViajante(const Codigo& codigoViajante);
    std::vector<Destino> listarDestinosPorViagem(const Codigo& codigoViagem);
    
    bool possuiDestinos(const Codigo& codigoViagem);
};

#endif