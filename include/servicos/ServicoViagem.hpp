#ifndef SERVICO_VIAGEM_HPP
#define SERVICO_VIAGEM_HPP

#include "../entidades/Viagem.hpp"
#include "../repositorios/RepositorioViagem.hpp"

class ServicoViagem
{
private:
    RepositorioViagem repositorio;

public:
    ServicoViagem(const std::string &caminhoBD);

    bool criarViagem(const Viagem &viagem);
    Viagem *lerViagem(const Codigo &codigo);
    bool atualizarViagem(const Viagem &viagem);
    bool excluirViagem(const Codigo &codigo);
    std::vector<Viagem> listarViagens(const Codigo &viajanteCodigo);
};

#endif // SERVICO_VIAGEM_HPP