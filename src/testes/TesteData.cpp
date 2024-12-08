#include "../../include/testes/TesteData.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @class TesteData
 * @brief Classe respons�vel por testar a valida��o de objetos do tipo Data a partir de um arquivo de testes.
 *
 * A classe TesteData l� um arquivo de texto contendo datas no formato "DD-MM-AAAA", tenta criar um
 * objeto Data com os valores extra�dos e valida se o formato est� correto. Se a cria��o do objeto for
 * bem-sucedida, o teste � registrado como um sucesso. Caso contr�rio, � registrado como uma falha.
 */
TesteData::TesteData(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configura��es antes da execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para preparar o ambiente de teste, como a inicializa��o de vari�veis
 * ou configura��o de recursos necess�rios. No momento, n�o realiza nenhuma configura��o adicional.
 */
void TesteData::setUp()
{
    // Prepara��o antes dos testes
}

/**
 * @brief Limpeza ap�s a execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para limpar o ambiente de teste, como a libera��o de recursos ou
 * redefinir vari�veis. No momento, n�o realiza nenhuma limpeza adicional.
 */
void TesteData::tearDown()
{
    // Limpeza ap�s os testes
}

/**
 * @brief M�todo principal que executa os testes de valida��o de datas.
 *
 * Este m�todo l� o arquivo especificado por `caminhoArquivoTeste`, onde cada linha cont�m uma data
 * no formato "DD-MM-AAAA". Para cada linha, o m�todo tenta criar um objeto Data e verificar se o
 * formato � v�lido.
 *
 * Caso o formato da data esteja correto, o teste � considerado um sucesso. Caso contr�rio, o teste
 * � considerado uma falha e a exce��o gerada ser� registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes n�o puder ser aberto.
 * @throws std::invalid_argument Se o formato da data na linha n�o for v�lido.
 */
void TesteData::rodarTestes()
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
            // Divide a string no formato DD-MM-AA
            std::istringstream ss(linha);
            int dia, mes, ano;
            char separador1, separador2;

            ss >> dia >> separador1 >> mes >> separador2 >> ano;

            if (ss.fail() || separador1 != '-' || separador2 != '-')
            {
                throw std::invalid_argument("Formato inv�lido para Data: " + linha);
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
