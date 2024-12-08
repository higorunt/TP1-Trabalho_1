#include "../../include/testes/TesteData.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @class TesteData
 * @brief Classe responsável por testar a validação de objetos do tipo Data a partir de um arquivo de testes.
 *
 * A classe TesteData lê um arquivo de texto contendo datas no formato "DD-MM-AAAA", tenta criar um
 * objeto Data com os valores extraídos e valida se o formato está correto. Se a criação do objeto for
 * bem-sucedida, o teste é registrado como um sucesso. Caso contrário, é registrado como uma falha.
 */
TesteData::TesteData(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações antes da execução de cada teste.
 *
 * Este método pode ser utilizado para preparar o ambiente de teste, como a inicialização de variáveis
 * ou configuração de recursos necessários. No momento, não realiza nenhuma configuração adicional.
 */
void TesteData::setUp()
{
    // Preparação antes dos testes
}

/**
 * @brief Limpeza após a execução de cada teste.
 *
 * Este método pode ser utilizado para limpar o ambiente de teste, como a liberação de recursos ou
 * redefinir variáveis. No momento, não realiza nenhuma limpeza adicional.
 */
void TesteData::tearDown()
{
    // Limpeza após os testes
}

/**
 * @brief Método principal que executa os testes de validação de datas.
 *
 * Este método lê o arquivo especificado por `caminhoArquivoTeste`, onde cada linha contém uma data
 * no formato "DD-MM-AAAA". Para cada linha, o método tenta criar um objeto Data e verificar se o
 * formato é válido.
 *
 * Caso o formato da data esteja correto, o teste é considerado um sucesso. Caso contrário, o teste
 * é considerado uma falha e a exceção gerada será registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes não puder ser aberto.
 * @throws std::invalid_argument Se o formato da data na linha não for válido.
 */
void TesteData::rodarTestes()
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
            // Divide a string no formato DD-MM-AA
            std::istringstream ss(linha);
            int dia, mes, ano;
            char separador1, separador2;

            ss >> dia >> separador1 >> mes >> separador2 >> ano;

            if (ss.fail() || separador1 != '-' || separador2 != '-')
            {
                throw std::invalid_argument("Formato inválido para Data: " + linha);
            }

            // Tenta criar um objeto Data
            Data data(dia, mes, ano);
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            registrarTesteFalha("Falha ao validar Data: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
