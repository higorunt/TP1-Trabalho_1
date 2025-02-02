#ifndef SERVICO_VIAJANTE_HPP
#define SERVICO_VIAJANTE_HPP

#include "../entidades/Viajante.hpp"
#include "../repositorios/RepositorioViajante.hpp"

class ServicoViajante
{
private:
    RepositorioViajante repositorio;

public:
    ServicoViajante(const std::string &caminhoBD);

    bool criarViajante(const Viajante &viajante);
    Viajante *lerViajante(const Codigo &codigo);
    bool atualizarViajante(const Viajante &viajante);
    bool excluirViajante(const Codigo &codigo);
    std::vector<Viajante> listarViajantes();
};

#endif // SERVICO_VIAJANTE_HPP