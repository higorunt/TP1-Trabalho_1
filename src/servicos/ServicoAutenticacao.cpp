// src/servicos/ServicoAutenticacao.cpp
#include "../../include/servicos/ServicoAutenticacao.hpp"
#include <stdexcept>
#include <iostream>

ServicoAutenticacao::ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo) 
    : repositorio(repo) {
    if (!repo) {
        throw std::invalid_argument("Repositório não pode ser nulo");
    }
}

ServicoAutenticacao::~ServicoAutenticacao() {
    // O repositório deve ser deletado por quem o criou
}

Viajante* ServicoAutenticacao::autenticar(const Codigo& codigo, const Senha& senha) {
    try {
        // Buscar viajante pelo código
        Viajante* viajante = repositorio->buscar(codigo);
        
        if (!viajante) {
            std::cout << "Viajante não encontrado." << std::endl;
            return nullptr;
        }
        
        // Verificar senha
        if (viajante->getConta().getSenha().getValor() == senha.getValor()) {
            std::cout << "Autenticação bem-sucedida." << std::endl;
            return viajante;
        }
        
        std::cout << "Senha incorreta." << std::endl;
        delete viajante;
        return nullptr;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro durante autenticação: " << e.what() << std::endl;
        return nullptr;
    }
}

bool ServicoAutenticacao::cadastrar(const Viajante& viajante) {
    try {
        // Verificar se já existe um viajante com este código
        Viajante* existente = repositorio->buscar(viajante.getConta().getCodigo());
        
        if (existente) {
            std::cout << "Já existe um viajante com este código." << std::endl;
            delete existente;
            return false;
        }
        
        // Salvar novo viajante
        bool sucesso = repositorio->salvar(viajante);
        
        if (sucesso) {
            std::cout << "Viajante cadastrado com sucesso." << std::endl;
        } else {
            std::cout << "Erro ao cadastrar viajante." << std::endl;
        }
        
        return sucesso;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro durante cadastro: " << e.what() << std::endl;
        return false;
    }
}