#include "../../include/testes/TesteAvaliacao.hpp"
#include <fstream>
#include <exception>

/**
 * @brief Construtor da classe TesteAvaliacao.
 *
 * Este construtor inicializa o caminho do arquivo de teste, onde cada linha do arquivo ser� utilizada para testar
 * a cria��o de um objeto da classe Avaliacao.
 *
 * @param caminhoArquivo Caminho do arquivo que cont�m os dados de teste para a classe Avaliacao.
 */
TesteAvaliacao::TesteAvaliacao(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configura��es adicionais antes da execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para configurar o ambiente ou objetos necess�rios antes de cada teste. No momento,
 * n�o h� configura��o adicional definida, mas o m�todo est� dispon�vel para extens�es futuras.
 */
void TesteAvaliacao::setUp()
{
    // Configura��es adicionais antes do teste (opcional)
}

/**
 * @brief Limpeza de recursos ap�s a execu��o de cada teste.
 *
 * Este m�todo pode ser utilizado para liberar recursos ou realizar a��es de limpeza ap�s cada teste. No momento,
 * n�o h� limpeza definida, mas o m�todo est� dispon�vel para extens�es futuras.
 */
void TesteAvaliacao::tearDown()
{
    // Limpeza de recursos ap�s os testes (opcional)
}

/**
 * @brief Executa os testes definidos no arquivo de teste.
 *
 * O arquivo de teste � lido linha por linha, e cada linha � tratada como um valor a ser convertido para inteiro e utilizado
 * para criar um objeto da classe Avaliacao. Se a cria��o for bem-sucedida, o teste � registrado como sucesso; se falhar, �
 * registrado como falha. As falhas podem ser causadas por erros de convers�o de dados ou exce��es imprevistas.
 *
 * @throws std::runtime_error Se o arquivo de teste n�o puder ser aberto.
 */
void TesteAvaliacao::rodarTestes()
{
    // Abre o arquivo de testes
    std::ifstream arquivo(caminhoArquivoTeste);
    if (!arquivo.is_open())
    {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo de testes: " + caminhoArquivoTeste);
    }

    // L� cada linha do arquivo
    std::string linha;
    while (std::getline(arquivo, linha))
    {
        try
        {
            // Tenta criar um objeto Avaliacao a partir da linha lida
            Avaliacao avaliacao(stoi(linha)); // Converte a linha para inteiro e cria a Avaliacao

            // Se a cria��o for bem-sucedida, registra o teste como sucesso
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            // Se ocorrer uma exce��o, registra o teste como falha
            // O erro pode ser uma falha de convers�o (stoi) ou qualquer outro erro inesperado
            registrarTesteFalha("Falha ao validar Avaliacao: '" + linha + "'. Erro: " + e.what());
        }
    }

    // Fecha o arquivo ap�s ler todas as linhas
    arquivo.close();
}
