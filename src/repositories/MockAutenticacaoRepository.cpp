// src/repositories/MockAutenticacaoRepository.cpp
#include "../../include/repositories/MockAutenticacaoRepository.hpp"

Viajante* MockAutenticacaoRepository::buscarPorCodigo(const Codigo& codigo) {
    // Mock: retorna um usuário de teste se o código for "ADM123"
    if (codigo.getValor() == "ADM123") {
        Codigo cod("ADM123");
        Senha senha("12345");
        Nome nome("Administrador");
        
        Conta* conta = new Conta(cod, senha);
        return new Viajante(nome, *conta);
    }
    return nullptr;
}

bool MockAutenticacaoRepository::salvar(const Viajante& viajante) {
    // Mock: sempre retorna true
    return true;
}