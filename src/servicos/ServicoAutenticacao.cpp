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

/**
 * @brief Realiza a autenticação de um viajante no sistema
 *
 * @details Este método verifica se existe um viajante com o código fornecido
 * e se a senha fornecida corresponde à senha cadastrada para este viajante.
 * O método inclui validações de formato da senha através do construtor da classe Senha.
 *
 * @param codigo Código identificador do viajante
 * @param senha Senha fornecida para autenticação
 *
 * @return Ponteiro para o objeto Viajante em caso de autenticação bem-sucedida
 *
 * @throws std::runtime_error Se o usuário não existir no repositório
 * @throws std::runtime_error Se a senha fornecida estiver incorreta
 * @throws std::runtime_error Se ocorrer algum erro inesperado durante o processo
 *
 * @note O método é responsável por liberar a memória alocada em caso de falha na autenticação
 */
Viajante* ServicoAutenticacao::autenticar(const Codigo& codigo, const Senha& senha) {
    try {
        // Buscar viajante pelo código
        Viajante* viajante = repositorio->buscar(codigo);
        
        if (!viajante) {
            std::cout << "Usuário não existe." << std::endl;
            throw std::runtime_error("Usuário não existe");
        }
        
        try {
            // Se a senha não passar na validação dos domínios, vai gerar exceção
            Senha senhaInput(senha.getValor());
            
            // Se passou na validação, verifica se está correta
            if (viajante->getConta().getSenha().getValor() != senha.getValor()) {
                std::cout << "Senha incorreta." << std::endl;
                delete viajante;
                throw std::runtime_error("Senha incorreta");
            }
            
            std::cout << "Autenticação bem-sucedida." << std::endl;
            return viajante;
            
        } catch (const std::invalid_argument&) {
            // Qualquer erro de validação da senha é tratado como "senha incorreta"
            std::cout << "Senha incorreta." << std::endl;
            delete viajante;
            throw std::runtime_error("Senha incorreta");
        }
    }
    catch (const std::runtime_error& e) {
        // Repassa erros específicos de autenticação
        throw;
    }
    catch (const std::exception&) {
        // Qualquer outro erro inesperado
        std::cerr << "Erro durante autenticação" << std::endl;
        throw std::runtime_error("Erro no sistema");
    }
}

bool ServicoAutenticacao::cadastrar(const Viajante& viajante) {
    try {
        // Verificar se já existe um viajante com este código
        Viajante* existente = repositorio->buscar(viajante.getConta().getCodigo());
        
        if (existente) {
            std::cout << "Já existe um viajante com este código." << std::endl;
            delete existente;
            throw std::runtime_error("Já existe um viajante com este código");
        }
        
        // Salvar novo viajante
        if (!repositorio->salvar(viajante)) {
            std::cout << "Erro ao cadastrar viajante." << std::endl;
            throw std::runtime_error("Erro ao cadastrar viajante");
        }
        
        std::cout << "Viajante cadastrado com sucesso." << std::endl;
        return true;
    }
    catch (const std::invalid_argument& e) {
        // Repassar erros de validação dos domínios
        std::cerr << e.what() << std::endl;
        throw;
    }
    catch (const std::runtime_error& e) {
        // Repassar erros específicos do cadastro
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro durante cadastro: " << e.what() << std::endl;
        throw std::runtime_error("Erro no sistema");
    }
}