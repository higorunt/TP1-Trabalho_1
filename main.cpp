#include "include/apresentacao/TelaLogin.hpp"
#include "include/services/AutenticacaoService.hpp"
#include "include/repositories/MockAutenticacaoRepository.hpp"

int main() {
    // Criar instâncias necessárias
    IAutenticacaoRepository* repo = new MockAutenticacaoRepository();
    IAutenticacaoService* service = new AutenticacaoService(repo);
    
    // Criar e executar tela de login
    TelaLogin* telaLogin = new TelaLogin(service);
    Viajante* viajante = telaLogin->executar();
    
    // Usar o viajante para evitar o warning
    if (viajante) {
        // Exemplo: mostrar o nome do viajante
        Nome nome = viajante->getNome();
        printf("\nBem-vindo, %s!\n", nome.getValor().c_str());
        delete viajante;
    }
    
    // Limpar recursos
    delete telaLogin;
    delete service;
    delete repo;
    
    return 0;
}