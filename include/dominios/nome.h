#ifndef NOME_H
#define NOME_H

#include <string>
#include <stdexcept>

class Nome {
private:
    std::string valor;                     // Atributo que armazena o valor do nome
    static const int TAMANHO_MAXIMO = 30; // Tamanho m�ximo permitido para o nome

    void validar(const std::string& valor); // M�todo privado para valida��o do nome

public:
    // M�todo para definir o valor do nome (valida��o inclu�da)
    void setValor(const std::string& valor);

    // M�todo para obter o valor do nome
    std::string getValor() const;
};

#endif // NOME_H
