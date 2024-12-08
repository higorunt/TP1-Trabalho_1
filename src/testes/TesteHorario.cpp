#include "../../include/testes/TesteHorario.hpp"
#include <fstream>
#include <stdexcept>

/**
 * @class TesteHorario
 * @brief Classe responsável por testar a validação de objetos do tipo Horario a partir de um arquivo de testes.
 *
 * A classe TesteHorario lê um arquivo de texto contendo valores de horário e tenta criar um objeto Horario com os valores extraídos.
 * Se a criação do objeto for bem-sucedida, o teste é registrado como um sucesso. Caso contrário, o teste é registrado como uma falha.
 */
TesteHorario::TesteHorario(const std::string &caminhoArquivo) : caminhoArquivoTeste(caminhoArquivo) {}

/**
 * @brief Configurações antes da execução de cada teste.
 *
 * Este método pode ser utilizado para preparar o ambiente de teste, como a inicialização de variáveis
 * ou configuração de recursos necessários. No momento, não realiza nenhuma configuração adicional.
 */
void TesteHorario::setUp() {}

/**
 * @brief Limpeza após a execução de cada teste.
 *
 * Este método pode ser utilizado para limpar o ambiente de teste, como a liberação de recursos ou
 * redefinir variáveis. No momento, não realiza nenhuma limpeza adicional.
 */
void TesteHorario::tearDown() {}

/**
 * @brief Método principal que executa os testes de validação de horários.
 *
 * Este método lê o arquivo especificado por `caminhoArquivoTeste`, onde cada linha contém um valor de horário
 * (em formato de texto). Para cada linha, o método tenta criar um objeto Horario e verificar se o valor é válido.
 *
 * Caso o valor seja válido e o objeto Horario seja criado com sucesso, o teste é considerado um sucesso.
 * Caso contrário, o teste é considerado uma falha e a exceção gerada será registrada.
 *
 * @throws std::runtime_error Se o arquivo de testes não puder ser aberto.
 * @throws std::invalid_argument Se o formato do valor na linha for inválido para o tipo Horario.
 */
void TesteHorario::rodarTestes()
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
            // Tenta criar um objeto Horario e valida o valor de hora
            Horario horario;
            horario.setValor(linha); // Define o horário após validação
            registrarTesteSucesso();
        }
        catch (std::exception &e)
        {
            registrarTesteFalha("Falha ao validar Horário: '" + linha + "'. Erro: " + e.what());
        }
    }

    arquivo.close();
}
