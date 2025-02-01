#ifndef SERVICO_DESTINO_HPP
#define SERVICO_DESTINO_HPP

#include <string>
#include <vector>
#include "RepositorioDestino.hpp"
#include "Destino.hpp"
#include "Codigo.hpp"

class ServicoDestino
{
private:
    RepositorioDestino repositorio;

public:
    ServicoDestino(const std::string &caminhoBD);

    bool criarDestino(const Destino &destino);
    Destino *lerDestino(const Codigo &codigo);
    bool atualizarDestino(const Destino &destino);
    bool excluirDestino(const Codigo &codigo);
    std::vector<Destino> listarDestinos(const Codigo &viagemCodigo);
};

#endif // SERVICO_DESTINO_HPP