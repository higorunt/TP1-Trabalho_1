# Requisitos para a Parte 2 do Projeto

Este documento detalha os requisitos específicos para a segunda etapa do desenvolvimento do sistema de planejamento de viagens, que envolve o desenvolvimento das camadas de apresentação, serviço, interfaces entre módulos, e outras atividades descritas abaixo. 

## 1. Atividades a Serem Realizadas

1. **Construir um modelo de arquitetura do software:**
   - Criar um diagrama de arquitetura que detalhe os módulos do sistema, as interfaces entre eles e seus relacionamentos.
   - Descrever textualmente as responsabilidades de cada módulo.
   - O modelo de arquitetura deve ser fornecido em formato PDF.

2. **Codificar e documentar as interfaces entre módulos:**
   - Declarar as interfaces por meio de classes abstratas contendo métodos virtuais puros.
   - Documentar as classes que representam interfaces usando a ferramenta Doxygen para gerar arquivos em formato HTML.

3. **Projetar e codificar a camada de apresentação:**
   - Implementar e depender de serviços declarados em interfaces.
   - A camada pode ser implementada usando:
     - `cin` e `cout` para entrada e saída no terminal.
     - Biblioteca PDCurses para interface textual.
     - Interface gráfica, se desejado.

4. **Projetar e codificar a camada de serviço:**
   - Implementar os serviços definidos nas interfaces.
   - Armazenar os objetos em:
     - Estruturas de dados em memória (fila, pilha, etc.).
     - Banco de dados relacional usando SQLite.

5. **Criar um vídeo de demonstração:**
   - Demonstrar que o código integrado é executado com sucesso.

## 2. Requisitos Funcionais e Não Funcionais

### Funcionais:
1. Implementar operações CRUD (Create, Read, Update, Delete) para:
   - Viagem
   - Destino
   - Atividade
   - Hospedagem

2. Implementar as seguintes funcionalidades adicionais:
   - Consultar custo de viagem.
   - Listar viagens associadas a um viajante.
   - Listar destinos associados a uma viagem.
   - Listar atividades associadas a um destino.
   - Listar hospedagens associadas a um destino.

3. Respeitar as seguintes regras de negócio:
   - Não pode ser excluído um registro se houver registros associados a ele.
   - A data de uma atividade deve estar dentro do intervalo definido pelas datas de início e término do destino associado.

### Não Funcionais:
1. As interfaces entre módulos devem ser bem definidas e documentadas.
2. O sistema deve seguir um padrão de codificação consistente e profissional.
3. O projeto deve ser entregue sem erros de compilação e preparado para execução na plataforma de correção.
4. Adotar práticas de programação defensiva para garantir robustez e confiabilidade.

## 3. Entregáveis

1. **Código-fonte e executável:**
   - Fornecer o código-fonte completo e o executável no formato especificado.
   - Incluir projeto configurado no formato Code::Blocks para facilitar a avaliação.

2. **Documentação:**
   - Modelo de arquitetura em formato PDF.
   - Documentação das interfaces em HTML gerada pelo Doxygen.
   - Arquivo README com instruções detalhadas de execução e compilação.

3. **Testes:**
   - Criar casos de teste para todas as funcionalidades mencionadas nos requisitos funcionais.
   - Garantir que cada caso de teste contemple ao menos um cenário de sucesso.

4. **Pacote de entrega:**
   - Incluir todos os artefatos construídos em um arquivo ZIP nomeado como `T1-TP1-X-Y-Z.ZIP`, substituindo X, Y e Z pelos números de matrícula dos autores.
   - Garantir que o arquivo ZIP possa ser descompactado sem erros e que não contenha vírus.

## 4. Padrões e Convenções

- **Identificação do Autor:**
  - Identificar em comentários a matrícula do autor responsável pela implementação de cada classe.

- **Padrão de Codificação:**
  - Seguir as práticas adotadas no laboratório para nomenclatura, organização e estilo do código.

- **Ferramentas Utilizadas:**
  - Doxygen para documentação.
  - SQLite para armazenamento de dados, caso necessário.
  - Code::Blocks para configuração do projeto.

## 5. Prazo e Envio

1. Certificar-se de que todos os requisitos foram atendidos.
2. Enviar o arquivo ZIP no prazo estipulado pelo professor.
3. Garantir que o vídeo de demonstração está claro e bem estruturado para avaliação.

---

Este documento deve servir como guia para a conclusão da segunda etapa do projeto, assegurando que todas as exigências sejam cumpridas de maneira organizada e eficiente.
