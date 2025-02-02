#ifndef REPOSITORIO_VIAJANTE_HPP
#define REPOSITORIO_VIAJANTE_HPP

#include "../entidades/Viajante.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioViajante : public RepositorioBase
{
public:
    RepositorioViajante(const std::string &caminhoBD);

    bool criarViajante(const Viajante &viajante);
    Viajante *lerViajante(const Codigo &codigo);
    bool atualizarViajante(const Viajante &viajante);
    bool excluirViajante(const Codigo &codigo);
    std::vector<Viajante> listarViajantes();

private:
    Viajante mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_VIAJANTE_HPP