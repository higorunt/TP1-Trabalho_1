#include "../../include/testes/TesteCodigo.hpp"
#include <fstream>
#include <exception>

TesteCodigo::TesteCodigo(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteCodigo::setUp()
{
    // Prepara��o, se necess�rio
}

void TesteCodigo::tearDown()
{
    // Limpeza, se necess�rio
}

/**
 * @brief Executa os testes de c�digo baseados nas linhas do arquivo de teste.
 *
 * O m�todo percorre o arquivo linha por linha, tentando criar um objeto Codigo a partir de cada linha.
 * Caso a cria��o do objeto Codigo seja bem-sucedida, o teste � registrado como bem-sucedido. Caso contr�rio,
 * uma mensagem de falha � registrada com o erro ocorrido.
 *
 * @throws std::runtime_error Se n�o for poss�vel abrir o arquivo de teste.
 */
void TesteCodigo::rodarTestes()
{
    // Abrindo o arquivo de testes.
    std::ifstream arquivo(caminhoArquivoTeste);

    // Verificando se o arquivo foi aberto corretamente.
    if (!arquivo.is_open())
    {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    // Lendo linha por linha do arquivo de teste.
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tentando criar o objeto Codigo a partir da linha lida.
            Codigo codigo(linha);

            // Caso a cria��o seja bem-sucedida, registra o teste como sucesso.
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Caso ocorra um erro, registra o teste como falha e mostra o erro ocorrido.
            registrarTesteFalha("Falha ao validar Codigo: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close(); // Fechando o arquivo ap�s terminar a leitura.
}
