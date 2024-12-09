#include "../../include/testes/TUConta.hpp"

/**
 * @class TUConta
 * @brief Classe de teste unit�rio para a classe Conta.
 *
 * Esta classe realiza testes de unidade para a classe `Conta`, validando os dom�nios `Codigo` e `Senha`. Ela executa
 * testes para verificar se a classe `Conta` est� manipulando corretamente esses atributos.
 */
const std::string TUConta::VALOR_VALIDO_CODIGO = "ABC123";
const std::string TUConta::VALOR_VALIDO_SENHA = "14526";

/**
 * @brief Configura o ambiente de teste, criando um objeto `Conta` com valores v�lidos.
 *
 * Este m�todo � chamado antes da execu��o de cada teste. Ele cria um objeto `Conta` com um `Codigo` e uma `Senha`
 * v�lidos. O estado de execu��o � inicializado como `SUCESSO`.
 */
void TUConta::setUp()
{
    conta = new Conta(Codigo(VALOR_VALIDO_CODIGO), Senha(VALOR_VALIDO_SENHA));
    estado = SUCESSO;
}

/**
 * @brief Limpa os recursos ap�s o teste, deletando o objeto `Conta`.
 *
 * Este m�todo � chamado ap�s a execu��o de cada teste para garantir que os recursos alocados sejam liberados.
 */
void TUConta::tearDown()
{
    delete conta;
}

/**
 * @brief M�todo que executa os testes unit�rios para os dom�nios `Codigo` e `Senha`.
 *
 * Este m�todo realiza os testes para os dom�nios `Codigo` e `Senha` verificando se os valores definidos nos objetos
 * s�o corretamente atribu�dos � inst�ncia de `Conta`. Caso contr�rio, o estado de execu��o � alterado para `FALHA`.
 */
void TUConta::testarCenario()
{
    // Teste para o dom�nio C�digo
    Codigo codigo(VALOR_VALIDO_CODIGO);
    conta->setCodigo(codigo);
    if (conta->getCodigo().getValor() != VALOR_VALIDO_CODIGO)
    {
        estado = FALHA;
    }

    // Teste para o dom�nio Senha
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
 * Este m�todo chama `setUp`, executa os testes no m�todo `testarCenario` e, em seguida, chama `tearDown` para
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
