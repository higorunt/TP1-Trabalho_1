#include "../../include/testes/TesteAvaliacao.hpp"
#include <fstream>
#include <exception>

/**
 * @brief Construtor da classe TesteAvaliacao.
 *
 * Este construtor inicializa o caminho do arquivo de teste, onde cada linha do arquivo será utilizada para testar
 * a criação de um objeto da classe Avaliacao.
 *
 * @param caminhoArquivo Caminho do arquivo que contém os dados de teste para a classe Avaliacao.
 */
TesteAvaliacao::TesteAvaliacao(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações adicionais antes da execução de cada teste.
 *
 * Este método pode ser utilizado para configurar o ambiente ou objetos necessários antes de cada teste. No momento,
 * não há configuração adicional definida, mas o método está disponível para extensões futuras.
 */
void TesteAvaliacao::setUp()
{
    // Configurações adicionais antes do teste (opcional)
}

/**
 * @brief Limpeza de recursos após a execução de cada teste.
 *
 * Este método pode ser utilizado para liberar recursos ou realizar ações de limpeza após cada teste. No momento,
 * não há limpeza definida, mas o método está disponível para extensões futuras.
 */
void TesteAvaliacao::tearDown()
{
    // Limpeza de recursos após os testes (opcional)
}

/**
 * @brief Executa os testes definidos no arquivo de teste.
 *
 * O arquivo de teste é lido linha por linha, e cada linha é tratada como um valor a ser convertido para inteiro e utilizado
 * para criar um objeto da classe Avaliacao. Se a criação for bem-sucedida, o teste é registrado como sucesso; se falhar, é
 * registrado como falha. As falhas podem ser causadas por erros de conversão de dados ou exceções imprevistas.
 *
 * @throws std::runtime_error Se o arquivo de teste não puder ser aberto.
 */
void TesteAvaliacao::rodarTestes()
{
    // Abre o arquivo de testes
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open())
    {
        throw std::runtime_error("Não foi possível abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    // Lê cada linha do arquivo
    std::string linha;
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tenta criar um objeto Avaliacao a partir da linha lida
            Avaliacao avaliacao(stoi(linha)); // Converte a linha para inteiro e cria a Avaliacao

            // Se a criação for bem-sucedida, registra o teste como sucesso
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Se ocorrer uma exceção, registra o teste como falha
            // O erro pode ser uma falha de conversão (stoi) ou qualquer outro erro inesperado
            registrarTesteFalha("Falha ao validar Avaliacao: '" + linha + "'. Erro: " + e.what());
        }
    }

    // Fecha o arquivo após ler todas as linhas
    arquivo.close();
}
