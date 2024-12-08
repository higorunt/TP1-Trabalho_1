#include "../../include/testes/TesteSenha.hpp"
#include <fstream>
#include <exception>

/**
 * @class TesteSenha
 * @brief Classe respons�vel por testar a valida��o de objetos do tipo Senha a partir de um arquivo de testes.
 *
 * A classe TesteSenha l� um arquivo de texto contendo valores de senha e tenta criar um objeto Senha com os valores extra�dos.
 * Se a cria��o do objeto for bem-sucedida, o teste � registrado como um sucesso. Caso contr�rio, o teste � registrado como uma falha.
 */
TesteSenha::TesteSenha(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configura��es antes da execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para preparar o ambiente de teste, como a inicializa��o de vari�veis
 * ou configura��o de recursos necess�rios. No momento, n�o realiza nenhuma configura��o adicional.
 */
void TesteSenha::setUp() {}

/**
 * @brief Limpeza ap�s a execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para limpar o ambiente de teste, como a libera��o de recursos ou
 * redefinir vari�veis. No momento, n�o realiza nenhuma limpeza adicional.
 */
void TesteSenha::tearDown() {}

/**
 * @brief M�todo principal que executa os testes de valida��o de senhas.
 *
 * Este m�todo l� o arquivo especificado por `caminhoArquivoTeste`, onde cada linha cont�m um valor de senha
 * (em formato de texto). Para cada linha, o m�todo tenta criar um objeto Senha e verificar se o valor � v�lido.
 *
 * Caso o valor seja v�lido e o objeto Senha seja criado com sucesso, o teste � considerado um sucesso.
 * Caso contr�rio, o teste � considerado uma falha e a exce��o gerada ser� registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes n�o puder ser aberto.
 * @throws std::invalid_argument Se o valor da senha for inv�lido para o tipo Senha.
 */
void TesteSenha::rodarTestes()
{
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open())
    {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tenta criar um objeto Senha e valida o valor
            Senha senha(linha);
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Em caso de exce��o, registra falha
            registrarTesteFalha("Falha ao validar Senha: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
