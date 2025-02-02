#ifndef REPOSITORIO_ATIVIDADE_HPP
#define REPOSITORIO_ATIVIDADE_HPP

#include <string>
#include <vector>
#include "../entidades/Atividade.hpp"
#include "../dominios/Codigo.hpp"
#include "../dominios/Dinheiro.hpp"

class RepositorioAtividade
{
public:
    explicit RepositorioAtividade(const std::string &caminhoBD);
    bool criarAtividade(const Atividade &atividade);
    Atividade *lerAtividade(const Codigo &codigo);
    bool atualizarAtividade(const Atividade &atividade);
    bool excluirAtividade(const Codigo &codigo);
    std::vector<Atividade> listarAtividades(const Codigo &destinoCodigo);
};

#endif // REPOSITORIO_ATIVIDADE_HPP