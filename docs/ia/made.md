# Contexto do Projeto

## Introdu��o

O sistema em desenvolvimento tem como objetivo facilitar o planejamento de viagens por meio de uma aplica��o que possibilite a realiza��o de opera��es CRUD (Create, Read, Update, Delete). Este sistema deve proporcionar uma interface intuitiva para gerenciamento de viagens, destinos, atividades e hospedagens, al�m de garantir a consist�ncia dos dados por meio da aplica��o de regras de neg�cio espec�ficas.

---

## Objetivo do Sistema

O sistema a ser desenvolvido permitir�:

### Opera��es CRUD

- **Viajante**: 
  - Criar conta.
  - Autenticar-se no sistema.

- **Viagem, Destino, Atividade, Hospedagem**:
  - Criar.
  - Consultar (ler).
  - Atualizar (com restri��es na chave prim�ria).
  - Excluir.

### Funcionalidades Adicionais

- Consultar o custo total de uma viagem.
- Listar:
  - Viagens associadas a um viajante.
  - Destinos associados a uma viagem.
  - Atividades associadas a um destino.
  - Hospedagens associadas a um destino.
- Apresentar listagens com os c�digos e nomes dos registros.

### Regras de Neg�cio

- N�o � permitido excluir um registro que possua depend�ncias associadas (por exemplo, excluir uma viagem que possui destinos).
- A data de uma atividade deve estar contida no intervalo definido pelas datas de in�cio e t�rmino do destino associado.

---

## O que J� Foi Realizado

### Estrutura Atual do Projeto

```
project/
??? include/                    # Arquivos de cabe�alho (.hpp)
?   ??? dominios/              # Dom�nios
?   ?   ??? Nome.hpp
?   ?   ??? Codigo.hpp
?   ?   ??? Senha.hpp
?   ?   ??? Avaliacao.hpp
?   ?   ??? Data.hpp
?   ?   ??? Dinheiro.hpp
?   ?   ??? Duracao.hpp
?   ?   ??? Horario.hpp
?   ??? entidades/             # Entidades
?   ?   ??? Conta.hpp
?   ?   ??? Destino.hpp 
?   ?   ??? Hospedagem.hpp
?   ?   ??? Viagem.hpp
?   ?   ??? Atividade.hpp
?   ?   ??? Viajante.hpp
?   ??? testes/                # Testes
?       ??? TestBase.hpp
?       ??? TesteNome.hpp
?       ??? TesteCodigo.hpp
?       ??? TesteSenha.hpp
?       ??? TesteAvaliacao.hpp
?       ??? TesteData.hpp
?       ??? TesteDinheiro.hpp
?       ??? TesteDuracao.hpp
?       ??? TesteHorario.hpp
??? src/                       # Implementa��es (.cpp)
?   ??? dominios/
?   ??? entidades/
?   ??? testes/
??? test_data/                # Dados de teste
??? main.cpp                  # Ponto de entrada principal
??? README.md                 # Documenta��o geral
??? project.cbp               # Arquivo do projeto Code::Blocks
```

### Funcionalidades Conclu�das

- Implementa��o completa das classes de **dom�nios** e **entidades**.
- Testes unit�rios desenvolvidos para cada classe de dom�nio e entidade.
- Estrutura modular do c�digo organizada em pastas.
- Estrutura para dados de teste com arquivos externos.

---

## Boas Pr�ticas Adotadas

- Segrega��o de c�digo por funcionalidade (dom�nios, entidades, testes).
- Organiza��o de arquivos com nomenclatura clara e padr�es consistentes.
- Uso de testes unit�rios para valida��o de cada classe e funcionalidade.
- Estrutura preparada para extens�o (facilitando futuras implementa��es de camadas adicionais).

---

## Pr�ximos Passos

- Implementar modelo de arquitetura e documenta��o correspondente.
- Codificar e documentar interfaces entre m�dulos.
- Desenvolver as camadas de apresenta��o e servi�o.
- Criar v�deo demonstrativo da execu��o do sistema integrado.
- Testar integra��o do sistema com foco nos requisitos funcionais e n�o funcionais.

---
