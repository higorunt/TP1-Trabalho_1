# Planejamento de Viagens

## Pré-requisitos de Instalação
1. Instalar MSYS2 (https://www.msys2.org/)
2. Abrir o terminal MSYS2 e instalar os seguintes pacotes:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-pdcurses
   pacman -S mingw-w64-x86_64-sqlite3
   ```
3. Adicionar o diretório `C:\msys64\mingw64\bin` ao PATH do sistema

## Compilação e Execução
Para compilar o projeto:
```bash
mingw32-make
```

Para executar o programa:
```bash
mingw32-make run
```

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

## Arquitetura do Sistema

### 3. Repositórios
Os repositórios são responsáveis pela persistência dos dados usando SQLite:

- **RepositorioBase**: Classe base com funcionalidades comuns de banco de dados
- **RepositorioViagem**: Gerencia dados de viagens
- **RepositorioDestino**: Gerencia dados de destinos
- **RepositorioAtividade**: Gerencia dados de atividades
- **RepositorioHospedagem**: Gerencia dados de hospedagens
- **RepositorioAutenticacao**: Gerencia dados de autenticação

### 4. Serviços
Camada que implementa as regras de negócio:

- **ServicoViagem**: Lógica de negócio para viagens
- **ServicoDestino**: Lógica de negócio para destinos
- **ServicoAtividade**: Lógica de negócio para atividades
- **ServicoHospedagem**: Lógica de negócio para hospedagens
- **ServicoAutenticacao**: Lógica de autenticação e gestão de usuários

### 5. Interface do Usuário
Interface construída usando PDCurses:

- **TelaBase**: Classe base com funcionalidades comuns de interface
- **TelaAutenticacao**: Login e registro
- **TelaPrincipal**: Menu principal do sistema
- **TelaViagem**: Gestão de viagens
- **TelaDestino**: Gestão de destinos
- **TelaAtividade**: Gestão de atividades
- **TelaHospedagem**: Gestão de hospedagens
- **TelaRelatorios**: Visualização de relatórios

### Estrutura de Pastas
```
projeto/
├── include/
│   ├── dominios/      # Headers dos domínios
│   ├── entidades/     # Headers das entidades
│   ├── interfaces/    # Headers das interfaces
│   ├── repositorios/  # Headers dos repositórios
│   ├── servicos/      # Headers dos serviços
│   ├── telas/         # Headers das telas
│   └── testes/        # Headers dos testes
├── src/
│   ├── dominios/      # Implementação dos domínios
│   ├── entidades/     # Implementação das entidades
│   ├── repositorios/  # Implementação dos repositórios
│   ├── servicos/      # Implementação dos serviços
│   ├── telas/         # Implementação das telas
│   └── testes/        # Implementação dos testes
└── docs/              # Documentação gerada pelo Doxygen
```

### Funcionalidades Principais

1. **Gestão de Viagens**
   - Criar, editar e excluir viagens
   - Associar destinos a viagens
   - Calcular custos totais

2. **Gestão de Destinos**
   - Adicionar/remover destinos em viagens
   - Definir datas de início/fim
   - Associar atividades e hospedagens

3. **Gestão de Atividades**
   - Programar atividades em destinos
   - Controlar horários e durações
   - Gerenciar custos de atividades

4. **Gestão de Hospedagens**
   - Registrar locais de hospedagem
   - Controlar períodos de estadia
   - Gerenciar custos de hospedagem

5. **Relatórios**
   - Resumo geral de custos
   - Listagem de viagens
   - Detalhes de destinos
   - Programação de atividades
   - Informações de hospedagens

### Tecnologias Utilizadas
- **C++17**: Linguagem de programação
- **SQLite3**: Banco de dados
- **PDCurses**: Interface gráfica em modo texto
- **Doxygen**: Documentação do código
- **Make**: Automação de build

### Padrões de Projeto Utilizados
- **Repository Pattern**: Abstração da camada de dados
- **Service Layer**: Encapsulamento da lógica de negócio
- **Factory Method**: Criação de objetos
- **Singleton**: Conexão com banco de dados

### Documentação
O projeto utiliza Doxygen para gerar documentação automática. Para gerar:
```bash
doxygen Doxyfile
```
A documentação será gerada na pasta `docs/`.

## Colaboradores
- Evelyn Caroline 221006404
- Higor Roger 22106440
- João Victor 212007046
