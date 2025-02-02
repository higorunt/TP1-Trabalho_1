#include "../../include/repositorios/RepositorioAtividade.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

RepositorioAtividade::RepositorioAtividade(const std::string &caminhoBD) : caminhoBD(caminhoBD)
{
    // Implementação do construtor
    std::ifstream dbFile(caminhoBD);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
    }
}

bool RepositorioAtividade::criarAtividade(const Atividade &atividade)
{
    std::ofstream dbFile(caminhoBD, std::ios::app);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return false;
    }
    dbFile << atividade.toString() << std::endl;
    return true;
}

Atividade *RepositorioAtividade::lerAtividade(const Codigo &codigo)
{
    std::ifstream dbFile(caminhoBD);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return nullptr;
    }
    std::string line;
    while (std::getline(dbFile, line))
    {
        Atividade atividade = Atividade::fromString(line);
        if (atividade.getCodigo() == codigo)
        {
            return new Atividade(atividade);
        }
    }
    return nullptr;
}

bool RepositorioAtividade::atualizarAtividade(const Atividade &atividade)
{
    std::ifstream dbFile(caminhoBD);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return false;
    }
    std::vector<Atividade> atividades;
    std::string line;
    while (std::getline(dbFile, line))
    {
        Atividade a = Atividade::fromString(line);
        if (a.getCodigo() == atividade.getCodigo())
        {
            atividades.push_back(atividade);
        }
        else
        {
            atividades.push_back(a);
        }
    }
    dbFile.close();

    std::ofstream outFile(caminhoBD);
    if (!outFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return false;
    }
    for (const auto &a : atividades)
    {
        outFile << a.toString() << std::endl;
    }
    return true;
}

bool RepositorioAtividade::excluirAtividade(const Codigo &codigo)
{
    std::ifstream dbFile(caminhoBD);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return false;
    }
    std::vector<Atividade> atividades;
    std::string line;
    while (std::getline(dbFile, line))
    {
        Atividade a = Atividade::fromString(line);
        if (a.getCodigo() != codigo)
        {
            atividades.push_back(a);
        }
    }
    dbFile.close();

    std::ofstream outFile(caminhoBD);
    if (!outFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return false;
    }
    for (const auto &a : atividades)
    {
        outFile << a.toString() << std::endl;
    }
    return true;
}

std::vector<Atividade> RepositorioAtividade::listarAtividades(const Codigo &destinoCodigo)
{
    std::ifstream dbFile(caminhoBD);
    if (!dbFile)
    {
        std::cerr << "Erro ao abrir o arquivo do banco de dados: " << caminhoBD << std::endl;
        return std::vector<Atividade>();
    }
    std::vector<Atividade> atividades;
    std::string line;
    while (std::getline(dbFile, line))
    {
        Atividade atividade = Atividade::fromString(line);
        if (atividade.getDestinoCodigo() == destinoCodigo)
        {
            atividades.push_back(atividade);
        }
    }
    return atividades;
}