#ifndef REPOSITORIO_DESTINO_HPP
#define REPOSITORIO_DESTINO_HPP

#include "../entidades/Destino.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioDestino : public RepositorioBase
{
public:
    RepositorioDestino(const std::string &caminhoBD);

    bool criarDestino(const Destino &destino);
    Destino *lerDestino(const Codigo &codigo);
    bool atualizarDestino(const Destino &destino);
    bool excluirDestino(const Codigo &codigo);
    std::vector<Destino> listarDestinos(const Codigo &viagemCodigo);

private:
    Destino mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_DESTINO_HPP