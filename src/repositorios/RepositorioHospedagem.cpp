#include "../include/repositorios/RepositorioHospedagem.hpp"
#include <stdexcept>

RepositorioHospedagem::RepositorioHospedagem(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    std::string sql = "CREATE TABLE IF NOT EXISTS Hospedagem ("
                      "codigo TEXT PRIMARY KEY, "
                      "nome TEXT NOT NULL, "
                      "avaliacao INTEGER NOT NULL, "
                      "diaria REAL NOT NULL, "
                      "destinoCodigo TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioHospedagem::criarHospedagem(const Hospedagem &hospedagem)
{
    std::string sql = "INSERT INTO Hospedagem (codigo, nome, avaliacao, diaria, destinoCodigo) "
                      "VALUES ('" +
                      hospedagem.getCodigo().getValor() + "', "
                                                          "'" +
                      hospedagem.getNome().getValor() + "', " +
                      std::to_string(hospedagem.getAvaliacao().getValor()) + ", " +
                      std::to_string(std::stod(hospedagem.getDiaria().getValor())) + ", "
                                                                                     "'" +
                      hospedagem.getDestinoCodigo().getValor() + "');";
    return executarSQL(sql);
}

Hospedagem *RepositorioHospedagem::lerHospedagem(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Hospedagem WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Hospedagem *hospedagem = new Hospedagem(mapearParaEntidade(stmt));
        finalizar(stmt);
        return hospedagem;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioHospedagem::atualizarHospedagem(const Hospedagem &hospedagem)
{
    std::string sql = "UPDATE Hospedagem SET "
                      "nome = '" +
                      hospedagem.getNome().getValor() + "', "
                                                        "avaliacao = " +
                      std::to_string(hospedagem.getAvaliacao().getValor()) + ", "
                                                                             "diaria = " +
                      std::to_string(std::stod(hospedagem.getDiaria().getValor())) + ", "
                                                                                     "destinoCodigo = '" +
                      hospedagem.getDestinoCodigo().getValor() + "' "
                                                                 "WHERE codigo = '" +
                      hospedagem.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioHospedagem::excluirHospedagem(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Hospedagem WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Hospedagem> RepositorioHospedagem::listarHospedagens(const Codigo &destinoCodigo)
{
    std::vector<Hospedagem> hospedagens;
    std::string sql = "SELECT * FROM Hospedagem WHERE destinoCodigo = '" + destinoCodigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        hospedagens.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return hospedagens;
}

Hospedagem RepositorioHospedagem::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Nome nome(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    Avaliacao avaliacao(sqlite3_column_int(stmt, 2));
    Dinheiro diaria(std::to_string(sqlite3_column_double(stmt, 3)));
    Codigo destinoCodigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));

    return Hospedagem(nome, codigo, avaliacao, diaria, destinoCodigo);
}