# Guia de Implementa��o de Dom�nios e Entidades

## Estrutura de C�digo de Dom�nios

### Arquivo dominios.hpp
```cpp

#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

class Dominio {
private:
    Tipo valor; // Atributo para armazenar valor.
    bool validar(Tipo); // M�todo para validar valor.
public:
    bool setValor(Tipo); // M�todo para atribuir valor.
    Tipo getValor() const; // M�todo para recuperar valor.
};

inline Tipo Dominio::getValor() const {
    return valor;
}

#endif // DOMINIOS_HPP_INCLUDED
----------------------------------------------

Arquivo 'dominios.cpp' 

#include "dominios.hpp"

bool Dominio::validar(Tipo valor) {
    // Implementar c�digo de valida��o.
    return true;
}

bool Dominio::setValor(Tipo valor) {
    if (!validar(valor))
        return false;
    this->valor = valor;
    return true;
}

----------------------------------------------

// C�digo de Teste no main.cpp
 
#include <iostream>
#include "dominios.hpp"

using namespace std;

int main() {
    Dominio dominio;

    if (dominio.setValor(VALOR_VALIDO)) // Escolher valor v�lido.
        cout << "Valor = " << dominio.getValor() << endl;
    else
        cout << "Valor invalido" << endl;

    if (dominio.setValor(VALOR_INVALIDO)) // Escolher valor inv�lido.
        cout << "Valor = " << dominio.getValor() << endl;
    else
        cout << "Valor invalido" << endl;

    return 0;
}
----------------------------------------------

// Estrutura de C�digo de Entidades
Arquivo entidades.hpp

using namespace std;

class Entidade {
private:
    Dominio nomeAtributo; // Declarar cada atributo da classe.
public:
    void setNomeAtributo(const Dominio&); // Declarar m�todo set para cada atributo.
    Dominio getNomeAtributo() const; // Declarar m�todo get para cada atributo.
};

// Implementar m�todos set e get para cada atributo.
inline void Entidade::setNomeAtributo(const Dominio &nomeAtributo) {
    this->nomeAtributo = nomeAtributo;
}

inline Dominio Entidade::getNomeAtributo() const {
    return nomeAtributo;
}
----------------------------------------------
C�digo de Teste no main.cpp

#include <iostream>
#include "entidades.hpp"

using namespace std;

int main() {
    Entidade entidade;
    Dominio dominio;

    dominio.setValor(VALOR_VALIDO); // Escolher valor v�lido.
    entidade.setNomeAtributo(dominio);
    cout << entidade.getNomeAtributo().getValor() << endl;

    return 0;
}

----------------------------------------------
Refatora��o para Uso de Exce��es
Arquivo dominios.hpp

#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <stdexcept>
using namespace std;

class Dominio {
private:
    Tipo valor; // Atributo para armazenar valor.
    void validar(Tipo); // M�todo para validar valor.
public:
    void setValor(Tipo); // M�todo para atribuir valor.
    Tipo getValor() const; // M�todo para recuperar valor.
};

inline Tipo Dominio::getValor() const {
    return valor;
}

#endif // DOMINIOS_HPP_INCLUDED
----------------------------------------------
C�digo de Teste no main.cpp

#include <iostream>
#include <stdexcept>
#include "dominios.hpp"

using namespace std;

int main() {
    Dominio dominio;

    try {
        dominio.setValor(VALOR_VALIDO); // Escolher valor v�lido.
    } catch (invalid_argument &exp) {
        cout << "Excecao: " << exp.what() << endl;
    }

    try {
        dominio.setValor(VALOR_INVALIDO); // Escolher valor inv�lido.
    } catch (invalid_argument &exp) {
        cout << "Excecao: " << exp.what() << endl;
    }

    return 0;
}
----------------------------------------------
Testes de Unidade para Dom�nios
Arquivo testes.hpp

#ifndef TESTES_HPP_INCLUDED
#define TESTES_HPP_INCLUDED

#include <stdexcept>
#include "dominios.hpp"
using namespace std;

class TUDominio {
private:
    const static int VALOR_VALIDO = 20; // Defini��o de constante.
    const static int VALOR_INVALIDO = 30; // Defini��o de constante.
    Dominio *dominio; // Refer�ncia para unidade em teste.
    int estado; // Estado do teste.
    void setUp(); // Criar unidade em teste.
    void tearDown(); // Destruir unidade em teste.
    void testarCenarioValorValido(); // Teste com valor v�lido.
    void testarCenarioValorInvalido(); // Teste com valor inv�lido.
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run(); // Executar teste.
};

#endif // TESTES_HPP_INCLUDED

----------------------------------------------
Arquivo testes.cpp
C�digo de Teste no main.cpp


#include <iostream>
#include "testes.hpp"

using namespace std;

int main() {
    TUDominio testeDominio;
    switch (testeDominio.run()) {
        case TUDominio::SUCESSO:
            cout << "SUCESSO" << endl;
            break;
        case TUDominio::FALHA:
            cout << "FALHA" << endl;
            break;
    }
    return 0;
}
## Implementa��o dos M�todos de Teste

### Arquivo testes.cpp


#include "testes.hpp"

void TUDominio::setUp() {
    dominio = new Dominio();
    estado = SUCESSO;
}

void TUDominio::tearDown() {
    delete dominio;
}

void TUDominio::testarCenarioValorValido() {
    try {
        dominio->setValor(VALOR_VALIDO);
        if (dominio->getValor() != VALOR_VALIDO) {
            estado = FALHA;
        }
    } catch (invalid_argument &exp) {
        estado = FALHA;
    }
}

void TUDominio::testarCenarioValorInvalido() {
    try {
        dominio->setValor(VALOR_INVALIDO);
        estado = FALHA;
    } catch (invalid_argument &exp) {
        return;
    }
}

int TUDominio::run() {
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
```