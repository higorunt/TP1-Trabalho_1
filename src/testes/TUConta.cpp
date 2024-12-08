#include "../../include/testes/TUConta.hpp"

/**
 * @class TUConta
 * @brief Classe de teste unitário para a classe Conta.
 *
 * Esta classe realiza testes de unidade para a classe `Conta`, validando os domínios `Codigo` e `Senha`. Ela executa
 * testes para verificar se a classe `Conta` está manipulando corretamente esses atributos.
 */
const std::string TUConta::VALOR_VALIDO_CODIGO = "ABC123";
const std::string TUConta::VALOR_VALIDO_SENHA = "14526";

/**
 * @brief Configura o ambiente de teste, criando um objeto `Conta` com valores válidos.
 *
 * Este método é chamado antes da execução de cada teste. Ele cria um objeto `Conta` com um `Codigo` e uma `Senha`
 * válidos. O estado de execução é inicializado como `SUCESSO`.
 */
void TUConta::setUp()
{
    conta = new Conta(Codigo(VALOR_VALIDO_CODIGO), Senha(VALOR_VALIDO_SENHA));
    estado = SUCESSO;
}

/**
 * @brief Limpa os recursos após o teste, deletando o objeto `Conta`.
 *
 * Este método é chamado após a execução de cada teste para garantir que os recursos alocados sejam liberados.
 */
void TUConta::tearDown()
{
    delete conta;
}

/**
 * @brief Método que executa os testes unitários para os domínios `Codigo` e `Senha`.
 *
 * Este método realiza os testes para os domínios `Codigo` e `Senha` verificando se os valores definidos nos objetos
 * são corretamente atribuídos à instância de `Conta`. Caso contrário, o estado de execução é alterado para `FALHA`.
 */
void TUConta::testarCenario()
{
    // Teste para o domínio Código
    Codigo codigo(VALOR_VALIDO_CODIGO);
    conta->setCodigo(codigo);
    if (conta->getCodigo().getValor() != VALOR_VALIDO_CODIGO)
    {
        estado = FALHA;
    }

    // Teste para o domínio Senha
    Senha senha(VALOR_VALIDO_SENHA);
    conta->setSenha(senha);
    if (conta->getSenha().getValor() != VALOR_VALIDO_SENHA)
    {
        estado = FALHA;
    }
}

/**
 * @brief Executa o teste completo de unidade para a classe `Conta`.
 *
 * Este método chama `setUp`, executa os testes no método `testarCenario` e, em seguida, chama `tearDown` para
 * liberar recursos. Retorna o estado final do teste (SUCESSO ou FALHA).
 *
 * @return Retorna o estado do teste: `SUCESSO` ou `FALHA`.
 */
int TUConta::run()
{
    setUp();
    testarCenario();
    tearDown();
    return estado;
}
