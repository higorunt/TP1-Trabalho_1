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
    std::cout << "\n=== DEBUG: Iniciando mapeamento ===\n";
    
    // Coluna 0: código do destino
    std::string codigoStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::cout << "DEBUG: Codigo lido: " << codigoStr << std::endl;
    Codigo codigo(codigoStr);
    
    // Coluna 1: nome
    std::string nomeStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::cout << "DEBUG: Nome lido: " << nomeStr << std::endl;
    Nome nome(nomeStr);
    
    // Coluna 2: avaliacao (CORREÇÃO: mudou de posição)
    int aval = sqlite3_column_int(stmt, 2);
    std::cout << "DEBUG: Avaliacao: " << aval << std::endl;
    Avaliacao avaliacao(aval);
    
    // Coluna 3: data_inicio (CORREÇÃO: mudou de posição)
    std::string dataInicioStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    std::cout << "DEBUG: Data inicio (raw): " << dataInicioStr << std::endl;
    Data dataInicio(dataInicioStr); // A data já vem formatada do banco
    
    // Coluna 4: data_fim (CORREÇÃO: mudou de posição)
    std::string dataFimStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
    std::cout << "DEBUG: Data fim (raw): " << dataFimStr << std::endl;
    Data dataFim(dataFimStr); // A data já vem formatada do banco
    
    // Coluna 5: código da viagem
    std::string codigoViagemStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    std::cout << "DEBUG: Codigo viagem: " << codigoViagemStr << std::endl;
    Codigo codigoViagem(codigoViagemStr);
    
    std::cout << "=== DEBUG: Mapeamento concluído ===\n";
    
    return Destino(codigo, nome, dataInicio, dataFim, avaliacao, codigoViagem);
}
