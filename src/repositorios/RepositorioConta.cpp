#include "../include/repositorios/RepositorioConta.hpp"
#include <stdexcept>

RepositorioConta::RepositorioConta(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    std::string sql = "CREATE TABLE IF NOT EXISTS Conta ("
                      "codigo TEXT PRIMARY KEY, "
                      "senha TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioConta::criarConta(const Conta &conta)
{
    std::string sql = "INSERT INTO Conta (codigo, senha) "
                      "VALUES ('" +
                      conta.getCodigo().getValor() + "', "
                                                     "'" +
                      conta.getSenha().getValor() + "');";
    return executarSQL(sql);
}

Conta *RepositorioConta::lerConta(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Conta WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Conta *conta = new Conta(mapearParaEntidade(stmt));
        finalizar(stmt);
        return conta;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioConta::atualizarConta(const Conta &conta)
{
    std::string sql = "UPDATE Conta SET "
                      "senha = '" +
                      conta.getSenha().getValor() + "' "
                                                    "WHERE codigo = '" +
                      conta.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioConta::excluirConta(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Conta WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Conta> RepositorioConta::listarContas()
{
    std::vector<Conta> contas;
    std::string sql = "SELECT * FROM Conta;";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        contas.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return contas;
}

Conta RepositorioConta::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Senha senha(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));

    return Conta(codigo, senha);
}