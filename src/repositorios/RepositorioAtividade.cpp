#include "../include/repositorios/RepositorioAtividade.hpp"
#include <stdexcept>

RepositorioAtividade::RepositorioAtividade(const std::string &caminhoBD)
    : RepositorioBase(caminhoBD)
{
    std::string sql = "CREATE TABLE IF NOT EXISTS Atividade ("
                      "codigo TEXT PRIMARY KEY, "
                      "nome TEXT NOT NULL, "
                      "avaliacao INTEGER NOT NULL, "
                      "data TEXT NOT NULL, "
                      "horario TEXT NOT NULL, "
                      "duracao INTEGER NOT NULL, "
                      "preco REAL NOT NULL, "
                      "destinoCodigo TEXT NOT NULL);";
    executarSQL(sql);
}

bool RepositorioAtividade::criarAtividade(const Atividade &atividade)
{
    std::string sql = "INSERT INTO Atividade (codigo, nome, avaliacao, data, horario, duracao, preco, destinoCodigo) "
                      "VALUES ('" +
                      atividade.getCodigo().getValor() + "', "
                                                         "'" +
                      atividade.getNome().getValor() + "', " +
                      std::to_string(atividade.getAvaliacao().getValor()) + ", "
                                                                            "'" +
                      atividade.getData().getValor() + "', "
                                                       "'" +
                      atividade.getHorario().getValor() + "', " +
                      std::to_string(atividade.getDuracao().getValor()) + ", " +
                      std::to_string(std::stod(atividade.getPreco().getValor())) + ", "
                                                                                   "'" +
                      atividade.getDestinoCodigo().getValor() + "');";
    return executarSQL(sql);
}

Atividade *RepositorioAtividade::lerAtividade(const Codigo &codigo)
{
    std::string sql = "SELECT * FROM Atividade WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Atividade *atividade = new Atividade(mapearParaEntidade(stmt));
        finalizar(stmt);
        return atividade;
    }

    finalizar(stmt);
    return nullptr;
}

bool RepositorioAtividade::atualizarAtividade(const Atividade &atividade)
{
    std::string sql = "UPDATE Atividade SET "
                      "nome = '" +
                      atividade.getNome().getValor() + "', "
                                                       "avaliacao = " +
                      std::to_string(atividade.getAvaliacao().getValor()) + ", "
                                                                            "data = '" +
                      atividade.getData().getValor() + "', "
                                                       "horario = '" +
                      atividade.getHorario().getValor() + "', "
                                                          "duracao = " +
                      std::to_string(atividade.getDuracao().getValor()) + ", "
                                                                          "preco = " +
                      std::to_string(std::stod(atividade.getPreco().getValor())) + ", "
                                                                                   "destinoCodigo = '" +
                      atividade.getDestinoCodigo().getValor() + "' "
                                                                "WHERE codigo = '" +
                      atividade.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioAtividade::excluirAtividade(const Codigo &codigo)
{
    std::string sql = "DELETE FROM Atividade WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Atividade> RepositorioAtividade::listarAtividades(const Codigo &destinoCodigo)
{
    std::vector<Atividade> atividades;
    std::string sql = "SELECT * FROM Atividade WHERE destinoCodigo = '" + destinoCodigo.getValor() + "';";
    sqlite3_stmt *stmt = prepararSQL(sql);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        atividades.push_back(mapearParaEntidade(stmt));
    }

    finalizar(stmt);
    return atividades;
}

Atividade RepositorioAtividade::mapearParaEntidade(sqlite3_stmt *stmt)
{
    Codigo codigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    Nome nome(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    Avaliacao avaliacao(sqlite3_column_int(stmt, 2));
    Data data(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
    Horario horario(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
    Duracao duracao(sqlite3_column_int(stmt, 5));
    Dinheiro preco(std::to_string(sqlite3_column_double(stmt, 6)));
    Codigo destinoCodigo(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));

    return Atividade(nome, codigo, avaliacao, data, horario, duracao, preco, destinoCodigo);
}