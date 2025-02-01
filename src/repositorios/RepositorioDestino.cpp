#include "../../include/repositorios/RepositorioDestino.hpp"
#include <stdexcept>

RepositorioDestino::RepositorioDestino(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    // Cria a tabela de destinos se não existir
    std::string sql = "CREATE TABLE IF NOT EXISTS Destino ("
                      "codigo TEXT PRIMARY KEY, "
                      "nome TEXT NOT NULL, "
                      "avaliacao INTEGER NOT NULL, "
                      "dataInicio TEXT NOT NULL, "
                      "dataFim TEXT NOT NULL, "
                      "viagemCodigo TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioDestino::criarDestino(const Destino &destino)
{
    std::string sql = "INSERT INTO Destino (codigo, nome, avaliacao, dataInicio, dataFim, viagemCodigo) "
                      "VALUES ('" +
                      destino.getCodigo().getValor() + "', "
                                                       "'" +
                      destino.getNome().getValor() + "', " +
                      std::to_string(destino.getAvaliacao().getValor()) + ", "
                                                                          "'" +
                      destino.getDataInicio().getValor() + "', "
                                                           "'" +
                      destino.getDataFim().getValor() + "', "
                                                        "'" +
                      destino.getCodigoViagem().getValor() + "');";
    return executarSQL(sql);
}

Destino *RepositorioDestino::lerDestino(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Destino WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Destino *destino = new Destino(mapearParaEntidade(stmt));
        finalizar(stmt);
        return destino;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioDestino::atualizarDestino(const Destino &destino)
{
    std::string sql = "UPDATE Destino SET "
                      "nome = '" +
                      destino.getNome().getValor() + "', "
                                                     "avaliacao = " +
                      std::to_string(destino.getAvaliacao().getValor()) + ", "
                                                                          "dataInicio = '" +
                      destino.getDataInicio().getValor() + "', "
                                                           "dataFim = '" +
                      destino.getDataFim().getValor() + "' "
                                                        "WHERE codigo = '" +
                      destino.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioDestino::excluirDestino(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Destino WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Destino> RepositorioDestino::listarDestinos(const Codigo &viagemCodigo)
{
    std::vector<Destino> destinos;
    std::string sql = "SELECT * FROM Destino WHERE viagemCodigo = '" + viagemCodigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        destinos.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return destinos;
}

Destino RepositorioDestino::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Nome nome(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    Avaliacao avaliacao(sqlite3_column_int(stmt, 2));
    Data dataInicio(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
    Data dataFim(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
    Codigo viagemCodigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)));

    return Destino(nome, codigo, avaliacao, dataInicio, dataFim, viagemCodigo);
}