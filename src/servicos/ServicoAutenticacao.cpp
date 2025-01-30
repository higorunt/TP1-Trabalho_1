// src/servicos/ServicoAutenticacao.cpp
#include "../../include/servicos/ServicoAutenticacao.hpp"
#include <stdexcept>
#include <iostream>

ServicoAutenticacao::ServicoAutenticacao(IRepositorio<Viajante, Codigo>* repo) 
    : repositorio(repo) {
    if (!repo) {
        throw std::invalid_argument("Reposit�rio n�o pode ser nulo");
    }
}

ServicoAutenticacao::~ServicoAutenticacao() {
    // O reposit�rio deve ser deletado por quem o criou
}

/**
 * @brief Realiza a autentica��o de um viajante no sistema
 *
 * @details Este m�todo verifica se existe um viajante com o c�digo fornecido
 * e se a senha fornecida corresponde � senha cadastrada para este viajante.
 * O m�todo inclui valida��es de formato da senha atrav�s do construtor da classe Senha.
 *
 * @param codigo C�digo identificador do viajante
 * @param senha Senha fornecida para autentica��o
 *
 * @return Ponteiro para o objeto Viajante em caso de autentica��o bem-sucedida
 *
 * @throws std::runtime_error Se o usu�rio n�o existir no reposit�rio
 * @throws std::runtime_error Se a senha fornecida estiver incorreta
 * @throws std::runtime_error Se ocorrer algum erro inesperado durante o processo
 *
 * @note O m�todo � respons�vel por liberar a mem�ria alocada em caso de falha na autentica��o
 */
Viajante* ServicoAutenticacao::autenticar(const Codigo& codigo, const Senha& senha) {
    try {
        // Buscar viajante pelo c�digo
        Viajante* viajante = repositorio->buscar(codigo);
        
        if (!viajante) {
            std::cout << "Usu�rio n�o existe." << std::endl;
            throw std::runtime_error("Usu�rio n�o existe");
        }
        
        try {
            // Se a senha n�o passar na valida��o dos dom�nios, vai gerar exce��o
            Senha senhaInput(senha.getValor());
            
            // Se passou na valida��o, verifica se est� correta
            if (viajante->getConta().getSenha().getValor() != senha.getValor()) {
                std::cout << "Senha incorreta." << std::endl;
                delete viajante;
                throw std::runtime_error("Senha incorreta");
            }
            
            std::cout << "Autentica��o bem-sucedida." << std::endl;
            return viajante;
            
        } catch (const std::invalid_argument&) {
            // Qualquer erro de valida��o da senha � tratado como "senha incorreta"
            std::cout << "Senha incorreta." << std::endl;
            delete viajante;
            throw std::runtime_error("Senha incorreta");
        }
    }
    catch (const std::runtime_error& e) {
        // Repassa erros espec�ficos de autentica��o
        throw;
    }
    catch (const std::exception&) {
        // Qualquer outro erro inesperado
        std::cerr << "Erro durante autentica��o" << std::endl;
        throw std::runtime_error("Erro no sistema");
    }
}

bool ServicoAutenticacao::cadastrar(const Viajante& viajante) {
    try {
        // Verificar se j� existe um viajante com este c�digo
        Viajante* existente = repositorio->buscar(viajante.getConta().getCodigo());
        
        if (existente) {
            std::cout << "J� existe um viajante com este c�digo." << std::endl;
            delete existente;
            throw std::runtime_error("J� existe um viajante com este c�digo");
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
        // Repassar erros de valida��o dos dom�nios
        std::cerr << e.what() << std::endl;
        throw;
    }
    catch (const std::runtime_error& e) {
        // Repassar erros espec�ficos do cadastro
        throw;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro durante cadastro: " << e.what() << std::endl;
        throw std::runtime_error("Erro no sistema");
    }
}