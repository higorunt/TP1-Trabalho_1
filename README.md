# Planejamento de Viagens

## Contexto do Trabalho
Este projeto faz parte da disciplina de T�cnicas de Programa��o e tem como objetivo aplicar conceitos de programa��o orientada a objetos (POO) em C++. O trabalho envolve o desenvolvimento de um sistema modular e escal�vel com classes bem definidas, valida��o de regras de neg�cio e testes unit�rios para cada componente.

O sistema ser� constru�do com base em dom�nios e entidades, que representam os elementos fundamentais do software. Al�m disso, ser�o implementados testes unit�rios para validar o funcionamento de cada componente.

## Vis�o Geral
O software a ser desenvolvido � um sistema de gest�o de planejamento de viagens que permitir� aos usu�rios (viajantes) realizarem opera��es b�sicas de manipula��o de dados, conhecidas pela sigla CRUD (Create, Read, Update, Delete). O sistema tem como objetivo proporcionar uma experi�ncia pr�tica e intuitiva para organizar e gerenciar viagens, destinos, atividades e hospedagens.

## Estrutura do Trabalho
O projeto ser� composto por dois principais n�veis de abstra��o:

- **Dom�nios**: Representam valores b�sicos do sistema e encapsulam regras de valida��o.
- **Entidades**: S�o compostas por um ou mais dom�nios e modelam conceitos mais complexos.

## 1. Dom�nios

Os dom�nios s�o respons�veis por encapsular um �nico valor e garantir que ele esteja sempre v�lido com base em regras espec�ficas. Eles implementam m�todos para atribuir (`setValor`) e recuperar (`getValor`) o valor.

Os dom�nios a serem implementados s�o:

### Nome
Representa o nome de uma pessoa e deve atender aos seguintes crit�rios:

- Texto com at� 30 caracteres

### C�digo
Representa um identificador �nico, como um c�digo de usu�rio. Deve atender aos seguintes crit�rios:

- Formato alfanum�rico com exatamente 6 caracteres.
- Cada caractere pode ser letra (A-Z ou a-z) ou d�gito (0-9).

### Avalia��o
Representa uma avalia��o num�rica. Deve atender aos seguintes crit�rios:

- Valor inteiro entre 1 e 5.

### Data
- Formato DD-MM-AA
    - DD: 00 a 31
    - MM: 01 a 12
    - AA: 00 a 99
- Levar em considera��o anos bissextos

### Senha
Representa uma senha. Deve atender aos seguintes crit�rios:

- Cinco d�gitos (0-9)
- N�o h� d�gito duplicado
- Os cinco d�gitos n�o podem estar em ordem crescente (01234, 12345, 23456 etc.)
- Os cinco d�gitos n�o podem estar em ordem decrescente (43210, 54321, 65432 etc.)

### Dinheiro
- Valor monet�rio entre 0,00 e 200.000,00.

### Dura��o
- Tempo em dias, de 0 a 360.

### Hor�rio
- Formato HH:MM (24h)

Cada classe de dom�nio deve:

- Contar com m�todos `set` e `get`.
- Validar os valores no m�todo `set`, lan�ando exce��es em caso de dados inv�lidos.

## 2. Entidades
As classes de entidade s�o:

- **Viajante**: Representa o usu�rio do sistema.
- **Viagem**: Cont�m informa��es sobre uma viagem espec�fica.
- **Destino**: Inclui detalhes de um destino dentro de uma viagem.
- **Atividade**: Representa uma tarefa ou evento associado a um destino.
- **Hospedagem**: Detalha locais de estadia associados a um destino.

Cada classe de entidade deve:

- Ter atributos compostos por inst�ncias das classes de dom�nio.
- Permitir acesso a esses atributos por meio de m�todos `set` e `get`.

## Testes
### Testes de Dom�nio:
- Cada teste deve validar valores v�lidos e inv�lidos para os dom�nios.
- O teste deve garantir que m�todos `set` lan�am exce��es adequadas.

### Testes de Entidade:
- Devem exercitar todos os m�todos p�blicos das entidades.
- O comportamento esperado deve ser validado para cada m�todo.

## Colaboradores
- Evelyn Caroline 221006404
- Higor Roger 22106440
