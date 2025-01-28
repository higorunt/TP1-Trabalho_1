// src/services/AutenticacaoService.cpp
#include "../../include/services/AutenticacaoService.hpp"

AutenticacaoService::AutenticacaoService(IAutenticacaoRepository* repository) 
    : repository(repository) {}

AutenticacaoService::~AutenticacaoService() = default;

Viajante* AutenticacaoService::autenticar(const Codigo& codigo, const Senha& senha) {
    Viajante* viajante = repository->buscarPorCodigo(codigo);
    if (viajante && viajante->getConta().getSenha().getValor() == senha.getValor()) {
        return viajante;
    }
    return nullptr;
}

bool AutenticacaoService::cadastrar(const Viajante& viajante) {
    return repository->salvar(viajante);
}