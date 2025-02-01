#include "../../include/repositorios/RepositorioViagem.hpp"
#include <stdexcept>
#include <string>
#include <algorithm>

// Construtor: conecta ao banco e cria a tabela, se necessário
RepositorioViagem::RepositorioViagem(const std::string& caminho) : RepositorioBase(caminho) {
    conectar();
    criarTabela();
}

bool RepositorioViagem::salvar(const Viagem& viagem) {
    const char* sql = "INSERT INTO viagens (codigo, nome, avaliacao, codigo_viajante, custo_total) VALUES (?, ?, ?, ?, ?)";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, viagem.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, viagem.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        // Use o valor inteiro diretamente, pois Avaliacao::getValor() retorna um int
        sqlite3_bind_int(stmt, 3, viagem.getAvaliacao().getValor());
        sqlite3_bind_text(stmt, 4, viagem.getConta().getCodigo().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 5, 0.0); // Custo total inicial é 0

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao salvar viagem: " + std::string(e.what()));
    }
}

Viagem* RepositorioViagem::buscar(const Codigo& codigo) {
    const char* sql = "SELECT * FROM viagens WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return nullptr;

    try {
        sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Recupere as colunas:
            Codigo cod((const char*)sqlite3_column_text(stmt, 0));
            Nome nome((const char*)sqlite3_column_text(stmt, 1));
            // Use o valor inteiro diretamente para criar Avaliacao
            Avaliacao aval(sqlite3_column_int(stmt, 2));
            Codigo codViajante((const char*)sqlite3_column_text(stmt, 3));
            
            // Cria uma Conta com um valor temporário para a senha
            Conta conta(codViajante, Senha("temp"));
            
            finalizar(stmt);
            return new Viagem(nome, cod, aval, conta);
        }
        
        finalizar(stmt);
        return nullptr;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao buscar viagem: " + std::string(e.what()));
    }
}

bool RepositorioViagem::atualizar(const Viagem& viagem) {
    const char* sql = "UPDATE viagens SET nome = ?, avaliacao = ?, custo_total = ? WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, viagem.getNome().getValor().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, viagem.getAvaliacao().getValor());
        sqlite3_bind_double(stmt, 3, 0.0); // Mantém o custo total atual (ou ajuste conforme necessário)
        sqlite3_bind_text(stmt, 4, viagem.getCodigo().getValor().c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao atualizar viagem: " + std::string(e.what()));
    }
}

bool RepositorioViagem::deletar(const Codigo& codigo) {
    const char* sql = "DELETE FROM viagens WHERE codigo = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return false;

    try {
        sqlite3_bind_text(stmt, 1, codigo.getValor().c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        finalizar(stmt);
        return result == SQLITE_DONE;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao deletar viagem: " + std::string(e.what()));
    }
}

std::vector<Viagem> RepositorioViagem::listarPorViajante(const Codigo& codigoViajante) {
    std::vector<Viagem> viagens;
    const char* sql = "SELECT * FROM viagens WHERE codigo_viajante = ?";
    
    sqlite3_stmt* stmt = prepararSQL(sql);
    if (!stmt) return viagens;

    try {
        sqlite3_bind_text(stmt, 1, codigoViajante.getValor().c_str(), -1, SQLITE_STATIC);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Codigo cod((const char*)sqlite3_column_text(stmt, 0));
            Nome nome((const char*)sqlite3_column_text(stmt, 1));
            Avaliacao aval(sqlite3_column_int(stmt, 2));
            Codigo codViajante((const char*)sqlite3_column_text(stmt, 3));
            
            Conta conta(codViajante, Senha("temp"));
            viagens.emplace_back(nome, cod, aval, conta);
        }
        
        finalizar(stmt);
        return viagens;
    }
    catch (const std::exception& e) {
        finalizar(stmt);
        throw std::runtime_error("Erro ao listar viagens: " + std::string(e.what()));
    }
}

double RepositorioViagem::calcularCustoTotal(const Codigo& codigoViagem) {
    // Implemente a lógica de cálculo conforme a regra de negócio.
    // Neste exemplo, retornamos 0.0.
    return 0.0;
}
