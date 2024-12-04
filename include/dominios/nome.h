#ifndef NOME_H
#define NOME_H

#include <string>
#include <stdexcept>

class Nome {
private:
    std::string valor;                     // Atributo que armazena o valor do nome
    static const int TAMANHO_MAXIMO = 30; // Tamanho máximo permitido para o nome

    void validar(const std::string& valor); // Método privado para validação do nome

public:
    // Método para definir o valor do nome (validação incluída)
    void setValor(const std::string& valor);

    // Método para obter o valor do nome
    std::string getValor() const;
};

#endif // NOME_H
