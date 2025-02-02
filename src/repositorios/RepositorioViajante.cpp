#include "../include/repositorios/RepositorioViajante.hpp"
#include <stdexcept>

RepositorioViajante::RepositorioViajante(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    std::string sql = "CREATE TABLE IF NOT EXISTS Viajante ("
                      "codigo TEXT PRIMARY KEY, "
                      "nome TEXT NOT NULL, "
                      "contaCodigo TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioViajante::criarViajante(const Viajante &viajante)
{
    std::string sql = "INSERT INTO Viajante (codigo, nome, contaCodigo) "
                      "VALUES ('" +
                      viajante.getCodigo().getValor() + "', "
                                                        "'" +
                      viajante.getNome().getValor() + "', "
                                                      "'" +
                      viajante.getConta().getCodigo().getValor() + "');";
    return executarSQL(sql);
}

Viajante *RepositorioViajante::lerViajante(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Viajante WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Viajante *viajante = new Viajante(mapearParaEntidade(stmt));
        finalizar(stmt);
        return viajante;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioViajante::atualizarViajante(const Viajante &viajante)
{
    std::string sql = "UPDATE Viajante SET "
                      "nome = '" +
                      viajante.getNome().getValor() + "', "
                                                      "contaCodigo = '" +
                      viajante.getConta().getCodigo().getValor() + "' "
                                                                   "WHERE codigo = '" +
                      viajante.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioViajante::excluirViajante(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Viajante WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Viajante> RepositorioViajante::listarViajantes()
{
    std::vector<Viajante> viajantes;
    std::string sql = "SELECT * FROM Viajante;";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        viajantes.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return viajantes;
}

Viajante RepositorioViajante::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Nome nome(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    Codigo contaCodigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));

    // Supondo que a entidade Conta já esteja carregada
    Conta conta(contaCodigo, Senha("00000")); // Senha fictícia, pois não é armazenada aqui
    return Viajante(nome, codigo, conta);
}