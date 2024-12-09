# Planejamento de Viagens

## Contexto do Trabalho
Este projeto faz parte da disciplina de Técnicas de Programação e tem como objetivo aplicar conceitos de programação orientada a objetos (POO) em C++. O trabalho envolve o desenvolvimento de um sistema modular e escalável com classes bem definidas, validação de regras de negócio e testes unitários para cada componente.

O sistema será construído com base em domínios e entidades, que representam os elementos fundamentais do software. Além disso, serão implementados testes unitários para validar o funcionamento de cada componente.

## Visão Geral
O software a ser desenvolvido é um sistema de gestão de planejamento de viagens que permitirá aos usuários (viajantes) realizarem operações básicas de manipulação de dados, conhecidas pela sigla CRUD (Create, Read, Update, Delete). O sistema tem como objetivo proporcionar uma experiência prática e intuitiva para organizar e gerenciar viagens, destinos, atividades e hospedagens.

## Estrutura do Trabalho
O projeto será composto por dois principais níveis de abstração:

- **Domínios**: Representam valores básicos do sistema e encapsulam regras de validação.
- **Entidades**: São compostas por um ou mais domínios e modelam conceitos mais complexos.

## 1. Domínios

Os domínios são responsáveis por encapsular um único valor e garantir que ele esteja sempre válido com base em regras específicas. Eles implementam métodos para atribuir (`setValor`) e recuperar (`getValor`) o valor.

Os domínios a serem implementados são:

### Nome
Representa o nome de uma pessoa e deve atender aos seguintes critérios:

- Texto com até 30 caracteres

### Código
Representa um identificador único, como um código de usuário. Deve atender aos seguintes critérios:

- Formato alfanumérico com exatamente 6 caracteres.
- Cada caractere pode ser letra (A-Z ou a-z) ou dígito (0-9).

### Avaliação
Representa uma avaliação numérica. Deve atender aos seguintes critérios:

- Valor inteiro entre 1 e 5.

### Data
- Formato DD-MM-AA
    - DD: 00 a 31
    - MM: 01 a 12
    - AA: 00 a 99
- Levar em consideração anos bissextos

### Senha
Representa uma senha. Deve atender aos seguintes critérios:

- Cinco dígitos (0-9)
- Não há dígito duplicado
- Os cinco dígitos não podem estar em ordem crescente (01234, 12345, 23456 etc.)
- Os cinco dígitos não podem estar em ordem decrescente (43210, 54321, 65432 etc.)

### Dinheiro
- Valor monetário entre 0,00 e 200.000,00.

### Duração
- Tempo em dias, de 0 a 360.

### Horário
- Formato HH:MM (24h)

Cada classe de domínio deve:

- Contar com métodos `set` e `get`.
- Validar os valores no método `set`, lançando exceções em caso de dados inválidos.

## 2. Entidades
As classes de entidade são:

- **Viajante**: Representa o usuário do sistema.
- **Viagem**: Contém informações sobre uma viagem específica.
- **Destino**: Inclui detalhes de um destino dentro de uma viagem.
- **Atividade**: Representa uma tarefa ou evento associado a um destino.
- **Hospedagem**: Detalha locais de estadia associados a um destino.

Cada classe de entidade deve:

- Ter atributos compostos por instâncias das classes de domínio.
- Permitir acesso a esses atributos por meio de métodos `set` e `get`.

## Testes
### Testes de Domínio:
- Cada teste deve validar valores válidos e inválidos para os domínios.
- O teste deve garantir que métodos `set` lançam exceções adequadas.

### Testes de Entidade:
- Devem exercitar todos os métodos públicos das entidades.
- O comportamento esperado deve ser validado para cada método.

## Estrutura:
- As pastas 'Entidades', 'Domínio' e 'Testes' com os arquivos .hpp estão localizadas na pasta include. Já as pastas 'Entidades', 'Domínio' e 'Testes' com os arquivos .cpp estão na pasta src.

## Colaboradores
- Evelyn Caroline 221006404
- Higor Roger 22106440
- João Victor 212007046
