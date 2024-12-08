#include "../../include/testes/TesteNome.hpp"
#include <fstream>
#include <exception>

/**
 * @class TesteNome
 * @brief Classe responsável por testar a validação de objetos do tipo Nome a partir de um arquivo de testes.
 *
 * A classe TesteNome lê um arquivo de texto contendo valores de nome e tenta criar um objeto Nome com os valores extraídos.
 * Se a criação do objeto for bem-sucedida, o teste é registrado como um sucesso. Caso contrário, o teste é registrado como uma falha.
 */
TesteNome::TesteNome(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações antes da execução de cada teste.
 *
 * Este método pode ser utilizado para preparar o ambiente de teste, como a inicialização de variáveis
 * ou configuração de recursos necessários. No momento, não realiza nenhuma configuração adicional.
 */
void TesteNome::setUp() {}

/**
 * @brief Limpeza após a execução de cada teste.
 *
 * Este método pode ser utilizado para limpar o ambiente de teste, como a liberação de recursos ou
 * redefinir variáveis. No momento, não realiza nenhuma limpeza adicional.
 */
void TesteNome::tearDown() {}

/**
 * @brief Método principal que executa os testes de validação de nomes.
 *
 * Este método lê o arquivo especificado por `caminhoArquivoTeste`, onde cada linha contém um valor de nome
 * (em formato de texto). Para cada linha, o método tenta criar um objeto Nome e verificar se o valor é válido.
 *
 * Caso o valor seja válido e o objeto Nome seja criado com sucesso, o teste é considerado um sucesso.
 * Caso contrário, o teste é considerado uma falha e a exceção gerada será registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes não puder ser aberto.
 * @throws std::invalid_argument Se o valor do nome for inválido para o tipo Nome.
 */
void TesteNome::rodarTestes()
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
            // Tenta criar um objeto Nome e valida o valor
            Nome nome(linha);
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Em caso de exceção, registra falha
            registrarTesteFalha("Falha ao validar Nome: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
