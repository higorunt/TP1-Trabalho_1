#ifndef REPOSITORIO_ATIVIDADE_HPP
#define REPOSITORIO_ATIVIDADE_HPP

#include "../entidades/Atividade.hpp"
#include "RepositorioBase.hpp"
#include <vector>

class RepositorioAtividade : public RepositorioBase
{
public:
    RepositorioAtividade(const std::string &caminhoBD);

    bool criarAtividade(const Atividade &atividade);
    Atividade *lerAtividade(const Codigo &codigo);
    bool atualizarAtividade(const Atividade &atividade);
    bool excluirAtividade(const Codigo &codigo);
    std::vector<Atividade> listarAtividades(const Codigo &destinoCodigo);

private:
    Atividade mapearParaEntidade(sqlite3_stmt *stmt);
};

#endif // REPOSITORIO_ATIVIDADE_HPP