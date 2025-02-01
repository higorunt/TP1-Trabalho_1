#include "RepositorioViagem.hpp"
#include <stdexcept>

RepositorioViagem::RepositorioViagem(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    // Cria a tabela de viagens se não existir
    std::string sql = "CREATE TABLE IF NOT EXISTS Viagem ("
                      "codigo TEXT PRIMARY KEY, "
                      "nome TEXT NOT NULL, "
                      "avaliacao INTEGER NOT NULL, "
                      "contaCodigo TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioViagem::criarViagem(const Viagem &viagem)
{
    std::string sql = "INSERT INTO Viagem (codigo, nome, avaliacao, contaCodigo) "
                      "VALUES ('" +
                      viagem.getCodigo().getValor() + "', "
                                                      "'" +
                      viagem.getNome().getValor() + "', " + std::to_string(viagem.getAvaliacao().getValor()) + ", "
                                                                                                               "'" +
                      viagem.getConta().getCodigo().getValor() + "');";
    return executarSQL(sql);
}

Viagem *RepositorioViagem::lerViagem(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Viagem WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Viagem *viagem = new Viagem(mapearParaEntidade(stmt));
        finalizar(stmt);
        return viagem;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioViagem::atualizarViagem(const Viagem &viagem)
{
    std::string sql = "UPDATE Viagem SET "
                      "nome = '" +
                      viagem.getNome().getValor() + "', "
                                                    "avaliacao = " +
                      std::to_string(viagem.getAvaliacao().getValor()) + ", "
                                                                         "contaCodigo = '" +
                      viagem.getConta().getCodigo().getValor() + "' "
                                                                 "WHERE codigo = '" +
                      viagem.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioViagem::excluirViagem(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Viagem WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Viagem> RepositorioViagem::listarViagens(const Codigo &viajanteCodigo)
{
    std::vector<Viagem> viagens;
    std::string sql = "SELECT * FROM Viagem WHERE contaCodigo = '" + viajanteCodigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        viagens.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return viagens;
}

Viagem RepositorioViagem::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Nome nome(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    Avaliacao avaliacao(sqlite3_column_int(stmt, 2));
    Codigo contaCodigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));

    // Supondo que a entidade Conta já esteja carregada
    Conta conta(contaCodigo, Senha("00000")); // Senha fictícia, pois não é armazenada aqui
    return Viagem(nome, codigo, avaliacao, conta);
}