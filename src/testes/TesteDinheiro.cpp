#include "../../include/testes/TesteDinheiro.hpp"
#include <fstream>
#include <exception>

/**
 * @class TesteDinheiro
 * @brief Classe respons�vel por testar a valida��o de objetos do tipo Dinheiro a partir de um arquivo de testes.
 *
 * A classe TesteDinheiro l� um arquivo de texto contendo valores de dinheiro em formato num�rico e tenta criar
 * um objeto Dinheiro com os valores extra�dos. Se a cria��o do objeto for bem-sucedida, o teste � registrado
 * como um sucesso. Caso contr�rio, o teste � registrado como uma falha.
 */
TesteDinheiro::TesteDinheiro(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configura��es antes da execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para preparar o ambiente de teste, como a inicializa��o de vari�veis
 * ou configura��o de recursos necess�rios. No momento, n�o realiza nenhuma configura��o adicional.
 */
void TesteDinheiro::setUp() {}

/**
 * @brief Limpeza ap�s a execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para limpar o ambiente de teste, como a libera��o de recursos ou
 * redefinir vari�veis. No momento, n�o realiza nenhuma limpeza adicional.
 */
void TesteDinheiro::tearDown() {}

/**
 * @brief M�todo principal que executa os testes de valida��o de valores monet�rios.
 *
 * Este m�todo l� o arquivo especificado por `caminhoArquivoTeste`, onde cada linha cont�m um valor num�rico
 * que representa uma quantia de dinheiro. Para cada linha, o m�todo tenta criar um objeto Dinheiro e verificar
 * se o valor � v�lido.
 *
 * Caso o valor seja v�lido e o objeto Dinheiro seja criado com sucesso, o teste � considerado um sucesso.
 * Caso contr�rio, o teste � considerado uma falha e a exce��o gerada ser� registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes n�o puder ser aberto.
 * @throws std::invalid_argument Se o valor num�rico na linha n�o for v�lido para o tipo Dinheiro.
 */
void TesteDinheiro::rodarTestes()
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
            // Tenta criar um objeto Dinheiro a partir do valor num�rico presente na linha
            Dinheiro dinheiro(stof(linha)); // Convers�o para float
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            registrarTesteFalha("Falha ao validar Dinheiro: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
