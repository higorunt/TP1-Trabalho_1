#include "../../include/repositorios/RepositorioDestino.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

RepositorioDestino::RepositorioDestino(const std::string& caminhoBD)
    : RepositorioBase(caminhoBD)
{
    if (!conectar()) {
        throw std::runtime_error("Nao foi possivel conectar ao banco de dados (Destino)");
    }
    criarTabela();
}

bool RepositorioDestino::salvar(const Destino& destino) {
    std::string sql = "INSERT INTO destinos (codigo, nome, data_inicio, data_fim, avaliacao, codigo_viagem) VALUES ('" +
                      destino.getCodigo().getValor() + "', '" +
                      destino.getNome().getValor() + "', '" +
                      destino.getDataInicio().getValor() + "', '" +
                      destino.getDataFim().getValor() + "', " +
                      std::to_string(destino.getAvaliacao().getValor()) + ", '" +
                      destino.getCodigoViagem().getValor() + "');";
    return executarSQL(sql);
}

Destino* RepositorioDestino::buscar(const Codigo& codigo) {
    std::string sql = "SELECT * FROM destinos WHERE codigo = '" + codigo.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Destino* destino = new Destino(mapearParaEntidade(stmt));
        finalizar(stmt);
        return destino;
    }
    finalizar(stmt);
    return nullptr;
}

bool RepositorioDestino::atualizar(const Destino& destino) {
    std::string sql = "UPDATE destinos SET "
                      "nome = '" + destino.getNome().getValor() + "', " +
                      "data_inicio = '" + destino.getDataInicio().getValor() + "', " +
                      "data_fim = '" + destino.getDataFim().getValor() + "', " +
                      "avaliacao = " + std::to_string(destino.getAvaliacao().getValor()) +
                      " WHERE codigo = '" + destino.getCodigo().getValor() + "';";
    return executarSQL(sql);
}

bool RepositorioDestino::deletar(const Codigo& codigo) {
    std::string sql = "DELETE FROM destinos WHERE codigo = '" + codigo.getValor() + "';";
    return executarSQL(sql);
}

std::vector<Destino> RepositorioDestino::listarPorViagem(const Codigo& codigoViagem) {
    std::vector<Destino> destinos;
    std::string sql = "SELECT * FROM destinos WHERE codigo_viagem = '" + codigoViagem.getValor() + "';";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        destinos.push_back(mapearParaEntidade(stmt));
    }
    finalizar(stmt);
    return destinos;
}
std::vector<Destino> RepositorioDestino::listarTodos() {
    std::vector<Destino> destinos;
    std::string sql = "SELECT * FROM destinos;";
    sqlite3_stmt* stmt = prepararSQL(sql);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        destinos.push_back(mapearParaEntidade(stmt));
    }
    finalizar(stmt);
    return destinos;
}
Destino RepositorioDestino::mapearParaEntidade(sqlite3_stmt* stmt) {
    // Coluna 0: codigo do destino
    Codigo codigo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    // Coluna 1: nome
    Nome nome(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    // Coluna 2: data_inicio
    std::string dataInicioStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    Data dataInicio(dataInicioStr);
    // Coluna 3: data_fim
    std::string dataFimStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    Data dataFim(dataFimStr);
    // Coluna 4: avaliacao
    int aval = sqlite3_column_int(stmt, 4);
    Avaliacao avaliacao(aval);
    // Coluna 5: codigo_viagem
    Codigo codigoViagem(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    
    return Destino(codigo, nome, dataInicio, dataFim, avaliacao, codigoViagem);
}
