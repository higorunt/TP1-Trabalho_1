# Requisitos para a Parte 2 do Projeto

Este documento detalha os requisitos espec�ficos para a segunda etapa do desenvolvimento do sistema de planejamento de viagens, que envolve o desenvolvimento das camadas de apresenta��o, servi�o, interfaces entre m�dulos, e outras atividades descritas abaixo. 

## 1. Atividades a Serem Realizadas

1. **Construir um modelo de arquitetura do software:**
   - Criar um diagrama de arquitetura que detalhe os m�dulos do sistema, as interfaces entre eles e seus relacionamentos.
   - Descrever textualmente as responsabilidades de cada m�dulo.
   - O modelo de arquitetura deve ser fornecido em formato PDF.

2. **Codificar e documentar as interfaces entre m�dulos:**
   - Declarar as interfaces por meio de classes abstratas contendo m�todos virtuais puros.
   - Documentar as classes que representam interfaces usando a ferramenta Doxygen para gerar arquivos em formato HTML.

3. **Projetar e codificar a camada de apresenta��o:**
   - Implementar e depender de servi�os declarados em interfaces.
   - A camada pode ser implementada usando:
     - `cin` e `cout` para entrada e sa�da no terminal.
     - Biblioteca PDCurses para interface textual.
     - Interface gr�fica, se desejado.

4. **Projetar e codificar a camada de servi�o:**
   - Implementar os servi�os definidos nas interfaces.
   - Armazenar os objetos em:
     - Estruturas de dados em mem�ria (fila, pilha, etc.).
     - Banco de dados relacional usando SQLite.

5. **Criar um v�deo de demonstra��o:**
   - Demonstrar que o c�digo integrado � executado com sucesso.

## 2. Requisitos Funcionais e N�o Funcionais

### Funcionais:
1. Implementar opera��es CRUD (Create, Read, Update, Delete) para:
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

3. Respeitar as seguintes regras de neg�cio:
   - N�o pode ser exclu�do um registro se houver registros associados a ele.
   - A data de uma atividade deve estar dentro do intervalo definido pelas datas de in�cio e t�rmino do destino associado.

### N�o Funcionais:
1. As interfaces entre m�dulos devem ser bem definidas e documentadas.
2. O sistema deve seguir um padr�o de codifica��o consistente e profissional.
3. O projeto deve ser entregue sem erros de compila��o e preparado para execu��o na plataforma de corre��o.
4. Adotar pr�ticas de programa��o defensiva para garantir robustez e confiabilidade.

## 3. Entreg�veis

1. **C�digo-fonte e execut�vel:**
   - Fornecer o c�digo-fonte completo e o execut�vel no formato especificado.
   - Incluir projeto configurado no formato Code::Blocks para facilitar a avalia��o.

2. **Documenta��o:**
   - Modelo de arquitetura em formato PDF.
   - Documenta��o das interfaces em HTML gerada pelo Doxygen.
   - Arquivo README com instru��es detalhadas de execu��o e compila��o.

3. **Testes:**
   - Criar casos de teste para todas as funcionalidades mencionadas nos requisitos funcionais.
   - Garantir que cada caso de teste contemple ao menos um cen�rio de sucesso.

4. **Pacote de entrega:**
   - Incluir todos os artefatos constru�dos em um arquivo ZIP nomeado como `T1-TP1-X-Y-Z.ZIP`, substituindo X, Y e Z pelos n�meros de matr�cula dos autores.
   - Garantir que o arquivo ZIP possa ser descompactado sem erros e que n�o contenha v�rus.

## 4. Padr�es e Conven��es

- **Identifica��o do Autor:**
  - Identificar em coment�rios a matr�cula do autor respons�vel pela implementa��o de cada classe.

- **Padr�o de Codifica��o:**
  - Seguir as pr�ticas adotadas no laborat�rio para nomenclatura, organiza��o e estilo do c�digo.

- **Ferramentas Utilizadas:**
  - Doxygen para documenta��o.
  - SQLite para armazenamento de dados, caso necess�rio.
  - Code::Blocks para configura��o do projeto.

## 5. Prazo e Envio

1. Certificar-se de que todos os requisitos foram atendidos.
2. Enviar o arquivo ZIP no prazo estipulado pelo professor.
3. Garantir que o v�deo de demonstra��o est� claro e bem estruturado para avalia��o.

---

Este documento deve servir como guia para a conclus�o da segunda etapa do projeto, assegurando que todas as exig�ncias sejam cumpridas de maneira organizada e eficiente.
