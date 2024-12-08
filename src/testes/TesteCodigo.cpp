#include "../../include/testes/TesteCodigo.hpp"
#include <fstream>
#include <exception>

TesteCodigo::TesteCodigo(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

void TesteCodigo::setUp()
{
    // Preparação, se necessário
}

void TesteCodigo::tearDown()
{
    // Limpeza, se necessário
}

/**
 * @brief Executa os testes de código baseados nas linhas do arquivo de teste.
 *
 * O método percorre o arquivo linha por linha, tentando criar um objeto Codigo a partir de cada linha.
 * Caso a criação do objeto Codigo seja bem-sucedida, o teste é registrado como bem-sucedido. Caso contrário,
 * uma mensagem de falha é registrada com o erro ocorrido.
 *
 * @throws std::runtime_error Se não for possível abrir o arquivo de teste.
 */
void TesteCodigo::rodarTestes()
{
    // Abrindo o arquivo de testes.
    std::ifstream arquivo(caminhoArquivoTeste);

    // Verificando se o arquivo foi aberto corretamente.
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    // Lendo linha por linha do arquivo de teste.
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tentando criar o objeto Codigo a partir da linha lida.
            Codigo codigo(linha);

            // Caso a criação seja bem-sucedida, registra o teste como sucesso.
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Caso ocorra um erro, registra o teste como falha e mostra o erro ocorrido.
            registrarTesteFalha("Falha ao validar Codigo: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close(); // Fechando o arquivo após terminar a leitura.
}
