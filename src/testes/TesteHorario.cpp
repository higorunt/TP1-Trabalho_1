#include "testes/TesteHorario.hpp"
#include "dominios/Horario.hpp"

void TesteHorario::rodarTestes()
{
    try
    {
        // Exemplo de uso do construtor que aceita um argumento
        Horario horario("12:00");
        // Adicione os testes necessários aqui
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}