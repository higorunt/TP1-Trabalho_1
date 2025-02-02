#include "../../include/repositorios/RepositorioAtividade.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

RepositorioAtividade::RepositorioAtividade(const std::string& caminhoBD)
    : RepositorioBase(caminhoBD)
{
    if (!conectar()) {
        throw std::runtime_error("Nao foi possivel conectar ao banco de dados (Atividade)");
    }
    criarTabela();
}

bool RepositorioAtividade::salvar(const Atividade& atividade) {
    std::string sql = "INSERT INTO atividades (codigo, nome, data, horario, duracao, preco, avaliacao, codigo_destino) VALUES ('" +
                      atividade.getCodigo().getValor() + "', '" +
                      atividade.getNome().getValor() + "', '" +
                      atividade.getData().getValor() + "', '" +
                      atividade.getHorario().getValor() + "', '" +
                      std::to_string(atividade.getDuracao().getValor()) + "', " +
                      atividade.getPreco().getValor() + ", " +
                      std::to_string(atividade.getAvaliacao().getValor()) + ", '" +
                      atividade.getCodigoDestino().getValor() + "');";
    return executarSQL(sql);
}

Atividade* RepositorioAtividade::buscar(const Codigo& codigo) {
    std::string sql = "SELECT * FROM atividades WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Atividade* atividade = new Atividade(mapearParaEntidade(stmt));
        finalizar(stmt);
        return atividade;
    }
    finalizar(stmt);
    return nullptr;
}

bool RepositorioAtividade::atualizar(const Atividade& atividade) {
    std::string sql = "UPDATE atividades SET "
                      "nome = '" + atividade.getNome().getValor() + "', " +
                      "data = '" + atividade.getData().getValor() + "', " +
                      "horario = '" + atividade.getHorario().getValor() + "', " +
                      "duracao = '" + std::to_string(atividade.getDuracao().getValor()) + "', " +
                      "preco = " + atividade.getPreco().getValor() + ", " +
                      "avaliacao = " + std::to_string(atividade.getAvaliacao().getValor()) +
                      " WHERE codigo = '" + atividade.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioAtividade::deletar(const Codigo& codigo) {
    std::string sql = "DELETE FROM atividades WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Atividade> RepositorioAtividade::listarPorDestino(const Codigo& codigoDestino) {
    std::vector<Atividade> atividades;
    std::string sql = "SELECT * FROM atividades WHERE codigo_destino = '" + codigoDestino.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        atividades.push_back(mapearParaEntidade(stmt));
    }
    finalizar(stmt);
    return atividades;
}

Atividade RepositorioAtividade::mapearParaEntidade(sqlite3_stmt* stmt) {
    std::string codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::string data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    std::string horarioStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    std::string duracaoStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    double preco = sqlite3_column_double(stmt, 5);
    int avaliacao = sqlite3_column_int(stmt, 6);
    std::string codigoDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

    // Criar objetos com setValor
    Horario horario;
    horario.setValor(horarioStr);

    // Converter string para int para Duracao
    int duracaoMinutos = std::stoi(duracaoStr);
    Duracao duracao(duracaoMinutos);

    return Atividade(
        Nome(nome),
        Codigo(codigo),
        Avaliacao(avaliacao),
        Data(data),
        horario,
        duracao,
        Dinheiro(preco),
        Codigo(codigoDestino)
    );
}
