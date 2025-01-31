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
            throw std::runtime_error("Usuario nao encontrado");
        }
        
        // Verificar senha
        if (viajante->getConta().getSenha().getValor() != senha.getValor()) {
            std::string mensagem = "Senha incorreta";
            delete viajante;  // Libera a memória antes de lançar a exceção
            throw std::runtime_error(mensagem);
        }
        
        // Se chegou aqui, a autenticação foi bem-sucedida
        return viajante;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro durante autenticação: " << e.what() << std::endl;
        throw; // Relança a exceção para ser tratada na TelaAutenticacao
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