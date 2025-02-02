#include "../../include/repositorios/RepositorioHospedagem.hpp"
#include <stdexcept>
#include <sstream>

RepositorioHospedagem::RepositorioHospedagem(const std::string& caminhoBD)
    : RepositorioBase(caminhoBD)
{
    if (!conectar()) {
        throw std::runtime_error("Nao foi possivel conectar ao banco de dados (Hospedagem)");
    }
    criarTabela();
}

bool RepositorioHospedagem::salvar(const Hospedagem& hospedagem) {
    std::string sql = "INSERT INTO hospedagens (codigo, nome, diaria, avaliacao, codigo_destino) VALUES ('" +
                      hospedagem.getCodigo().getValor() + "', '" +
                      hospedagem.getNome().getValor() + "', " +
                      hospedagem.getDiaria().getValor() + ", " +
                      std::to_string(hospedagem.getAvaliacao().getValor()) + ", '" +
                      hospedagem.getCodigoDestino().getValor() + "');";
    return executarSQL(sql);
}

Hospedagem* RepositorioHospedagem::buscar(const Codigo& codigo) {
    std::string sql = "SELECT * FROM hospedagens WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Hospedagem* hospedagem = new Hospedagem(mapearParaEntidade(stmt));
        finalizar(stmt);
        return hospedagem;
    }
    finalizar(stmt);
    return nullptr;
}

bool RepositorioHospedagem::atualizar(const Hospedagem& hospedagem) {
    std::string sql = "UPDATE hospedagens SET "
                      "nome = '" + hospedagem.getNome().getValor() + "', " +
                      "diaria = " + hospedagem.getDiaria().getValor() + ", " +
                      "avaliacao = " + std::to_string(hospedagem.getAvaliacao().getValor()) +
                      " WHERE codigo = '" + hospedagem.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioHospedagem::deletar(const Codigo& codigo) {
    std::string sql = "DELETE FROM hospedagens WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

Hospedagem* RepositorioHospedagem::buscarPorDestino(const Codigo& codigoDestino) {
    std::string sql = "SELECT * FROM hospedagens WHERE codigo_destino = '" + codigoDestino.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Hospedagem* hospedagem = new Hospedagem(mapearParaEntidade(stmt));
        finalizar(stmt);
        return hospedagem;
    }
    finalizar(stmt);
    return nullptr;
}

Hospedagem RepositorioHospedagem::mapearParaEntidade(sqlite3_stmt* stmt) {
    std::string codigo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::string nome = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    double diaria = sqlite3_column_double(stmt, 2);
    int avaliacao = sqlite3_column_int(stmt, 3);
    std::string codigoDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

    return Hospedagem(
        Nome(nome),
        Codigo(codigo),
        Avaliacao(avaliacao),
        Dinheiro(diaria),
        Codigo(codigoDestino)
    );
}
