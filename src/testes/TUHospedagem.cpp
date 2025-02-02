#include <iostream>
#include "testes/TUHospedagem.hpp"
#include "dominios/Codigo.hpp"
#include "dominios/Dinheiro.hpp"

void TUHospedagem::testarCenario()
{
    try
    {
        Codigo codigo("123456");
        Dinheiro dinheiro(100.0);
        // Adicione os testes necessários aqui
    }
    catch (const std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}