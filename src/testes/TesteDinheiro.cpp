#include "../../include/testes/TesteDinheiro.hpp"
#include <fstream>
#include <exception>

/**
 * @class TesteDinheiro
 * @brief Classe responsável por testar a validação de objetos do tipo Dinheiro a partir de um arquivo de testes.
 *
 * A classe TesteDinheiro lê um arquivo de texto contendo valores de dinheiro em formato numérico e tenta criar
 * um objeto Dinheiro com os valores extraídos. Se a criação do objeto for bem-sucedida, o teste é registrado
 * como um sucesso. Caso contrário, o teste é registrado como uma falha.
 */
TesteDinheiro::TesteDinheiro(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações antes da execução de cada teste.
 *
 * Este método pode ser utilizado para preparar o ambiente de teste, como a inicialização de variáveis
 * ou configuração de recursos necessários. No momento, não realiza nenhuma configuração adicional.
 */
void TesteDinheiro::setUp() {}

/**
 * @brief Limpeza após a execução de cada teste.
 *
 * Este método pode ser utilizado para limpar o ambiente de teste, como a liberação de recursos ou
 * redefinir variáveis. No momento, não realiza nenhuma limpeza adicional.
 */
void TesteDinheiro::tearDown() {}

/**
 * @brief Método principal que executa os testes de validação de valores monetários.
 *
 * Este método lê o arquivo especificado por `caminhoArquivoTeste`, onde cada linha contém um valor numérico
 * que representa uma quantia de dinheiro. Para cada linha, o método tenta criar um objeto Dinheiro e verificar
 * se o valor é válido.
 *
 * Caso o valor seja válido e o objeto Dinheiro seja criado com sucesso, o teste é considerado um sucesso.
 * Caso contrário, o teste é considerado uma falha e a exceção gerada será registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes não puder ser aberto.
 * @throws std::invalid_argument Se o valor numérico na linha não for válido para o tipo Dinheiro.
 */
void TesteDinheiro::rodarTestes()
{
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    std::string linha;
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tenta criar um objeto Dinheiro a partir do valor numérico presente na linha
            Dinheiro dinheiro(stof(linha)); // Conversão para float
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            registrarTesteFalha("Falha ao validar Dinheiro: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
