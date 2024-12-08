#include "../../include/testes/TesteSenha.hpp"
#include <fstream>
#include <exception>

/**
 * @class TesteSenha
 * @brief Classe responsável por testar a validação de objetos do tipo Senha a partir de um arquivo de testes.
 *
 * A classe TesteSenha lê um arquivo de texto contendo valores de senha e tenta criar um objeto Senha com os valores extraídos.
 * Se a criação do objeto for bem-sucedida, o teste é registrado como um sucesso. Caso contrário, o teste é registrado como uma falha.
 */
TesteSenha::TesteSenha(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações antes da execução de cada teste.
 *
 * Este método pode ser utilizado para preparar o ambiente de teste, como a inicialização de variáveis
 * ou configuração de recursos necessários. No momento, não realiza nenhuma configuração adicional.
 */
void TesteSenha::setUp() {}

/**
 * @brief Limpeza após a execução de cada teste.
 *
 * Este método pode ser utilizado para limpar o ambiente de teste, como a liberação de recursos ou
 * redefinir variáveis. No momento, não realiza nenhuma limpeza adicional.
 */
void TesteSenha::tearDown() {}

/**
 * @brief Método principal que executa os testes de validação de senhas.
 *
 * Este método lê o arquivo especificado por `caminhoArquivoTeste`, onde cada linha contém um valor de senha
 * (em formato de texto). Para cada linha, o método tenta criar um objeto Senha e verificar se o valor é válido.
 *
 * Caso o valor seja válido e o objeto Senha seja criado com sucesso, o teste é considerado um sucesso.
 * Caso contrário, o teste é considerado uma falha e a exceção gerada será registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes não puder ser aberto.
 * @throws std::invalid_argument Se o valor da senha for inválido para o tipo Senha.
 */
void TesteSenha::rodarTestes()
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
            // Tenta criar um objeto Senha e valida o valor
            Senha senha(linha);
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Em caso de exceção, registra falha
            registrarTesteFalha("Falha ao validar Senha: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
