import os
import requests
import urllib.parse
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.pagesizes import letter
from reportlab.lib.units import inch

# Função para codificar o conteúdo PlantUML conforme a especificação do PlantUML
def encode_plantuml(text):
    """Codifica o texto PlantUML para a URL do PlantUML."""
    def to_base64(s):
        import base64
        return base64.b64encode(s.encode('utf-8')).decode('utf-8')
    
    def compress(s):
        import zlib
        compressed = zlib.compress(s.encode('utf-8'))
        return compressed[2:-4]
    
    def encode_compact(s):
        import zlib
        compressed = zlib.compress(s.encode('utf-8'))
        compressed = compressed[2:-4]
        return encode_deflate(compressed)
    
    def encode_deflate(data):
        # Encode the compressed data using a custom base64 for PlantUML
        base64_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_"
        res = ""
        buffer = 0
        buffer_length = 0
        for byte in data:
            buffer = (buffer << 8) | byte
            buffer_length += 8
            while buffer_length >= 6:
                buffer_length -= 6
                res += base64_chars[(buffer >> buffer_length) & 0x3F]
        if buffer_length > 0:
            res += base64_chars[(buffer << (6 - buffer_length)) & 0x3F]
        return res
    
    return encode_compact(text)

# Função para gerar o diagrama PlantUML usando a API do PlantUML
def generate_plantuml_diagram(plantuml_code, output_path):
    """Gera um diagrama PlantUML e salva como PNG."""
    try:
        encoded = encode_plantuml(plantuml_code)
        plantuml_url = f'http://www.plantuml.com/plantuml/img/{encoded}'
        
        response = requests.get(plantuml_url)
        if response.status_code == 200:
            with open(output_path, 'wb') as f:
                f.write(response.content)
            print("Diagrama gerado com sucesso!")
            return True
        else:
            print(f"Erro ao gerar diagrama: Status Code {response.status_code}")
            return False
    except Exception as e:
        print(f"Erro ao gerar diagrama: {e}")
        return False

# Função para criar o PDF com o diagrama e a descrição
def create_pdf(diagram_path, pdf_path, description):
    """Cria um PDF contendo o diagrama e a descrição da arquitetura."""
    try:
        # Configurar o documento PDF
        doc = SimpleDocTemplate(
            pdf_path,
            pagesize=letter,
            rightMargin=72,
            leftMargin=72,
            topMargin=72,
            bottomMargin=72
        )
        
        # Estilos
        styles = getSampleStyleSheet()
        styles.add(ParagraphStyle(name='CustomTitle', fontName='Helvetica-Bold', fontSize=24, spaceAfter=30))
        styles.add(ParagraphStyle(name='Heading1', parent=styles['Heading1'], fontName='Helvetica-Bold', fontSize=18, spaceAfter=12))
        styles.add(ParagraphStyle(name='Heading2', parent=styles['Heading2'], fontName='Helvetica-Bold', fontSize=16, spaceAfter=10))
        styles.add(ParagraphStyle(name='Heading3', parent=styles['Heading3'], fontName='Helvetica-Bold', fontSize=14, spaceAfter=8))
        styles.add(ParagraphStyle(name='Normal', parent=styles['Normal'], fontName='Helvetica', fontSize=12, leading=15))
        
        # Lista de elementos para o PDF
        elements = []
        
        # Adicionar título
        elements.append(Paragraph("Modelo de Arquitetura do Sistema de Planejamento de Viagens", styles['CustomTitle']))
        elements.append(Spacer(1, 12))
        
        # Adicionar diagrama
        if os.path.exists(diagram_path):
            try:
                img = Image(diagram_path)
                img.drawHeight = 4 * inch
                img.drawWidth = 6 * inch
                elements.append(img)
                elements.append(Spacer(1, 12))
            except Exception as img_err:
                print(f"Erro ao adicionar imagem ao PDF: {img_err}")
                elements.append(Paragraph("Diagrama de arquitetura não pôde ser inserido.", styles['Normal']))
                elements.append(Spacer(1, 12))
        else:
            elements.append(Paragraph("Diagrama de arquitetura não encontrado.", styles['Normal']))
            elements.append(Spacer(1, 12))
        
        # Adicionar descrição
        for line in description.split('\n'):
            if line.strip():
                if line.startswith('# '):
                    style = styles['Heading1']
                    text = line.replace('# ', '')
                elif line.startswith('## '):
                    style = styles['Heading2']
                    text = line.replace('## ', '')
                elif line.startswith('### '):
                    style = styles['Heading3']
                    text = line.replace('### ', '')
                else:
                    style = styles['Normal']
                    text = line
                elements.append(Paragraph(text, style))
                elements.append(Spacer(1, 12))
        
        # Gerar o PDF
        doc.build(elements)
        print("PDF gerado com sucesso!")
        return True
    
    except Exception as e:
        print(f"Erro ao gerar PDF: {e}")
        return False

# PlantUML code orientado a processos
plantuml_code = """
@startuml
skinparam backgroundColor white
skinparam componentStyle uml2
skinparam defaultFontName Arial
skinparam linetype ortho

title Sistema de Planejamento de Viagens - Arquitetura Completa

' Domain Layer
package "Dom�nios" {
    class Avaliacao {
        + setValor(valor: int)
        + getValor(): int
    }
    class Codigo {
        + setCodigo(codigo: string)
        + getCodigo(): string
        + validarCodigo(): bool
    }
    class Data {
        + setData(data: string)
        + getData(): string
        + validarData(): bool
    }
    class Dinheiro {
        + setValor(valor: float)
        + getValor(): float
        + validarValor(): bool
    }
    class Duracao {
        + setDuracao(duracao: int)
        + getDuracao(): int
        + validarDuracao(): bool
    }
    class Horario {
        + setHorario(horario: string)
        + getHorario(): string
        + validarHorario(): bool
    }
    class Nome {
        + setNome(nome: string)
        + getNome(): string
        + validarNome(): bool
    }
    class Senha {
        + setSenha(senha: string)
        + getSenha(): string
        + validarSenha(): bool
    }
}

' Entity Layer  
package "Entidades" {
    class Viajante {
        - nome: Nome
        - conta: Conta
    }
    class Viagem {
        - nome: Nome
        - codigo: Codigo
        - avaliacao: Avaliacao
        - conta: Conta
        - custoTotal: Dinheiro
    }
    class Destino {
        - nome: Nome
        - codigo: Codigo
        - avaliacao: Avaliacao
        - dataInicio: Data
        - dataFim: Data
    }
    class Atividade {
        - nome: Nome
        - codigo: Codigo
        - avaliacao: Avaliacao
        - data: Data
        - horario: Horario
        - duracao: Duracao
        - preco: Dinheiro
    }
    class Hospedagem {
        - nome: Nome
        - codigo: Codigo
        - avaliacao: Avaliacao
        - diaria: Dinheiro
    }
    class Conta {
        - codigo: Codigo
        - senha: Senha
    }
}

' Interface Layer
package "Interfaces" {
    interface IRepositorio<T,K> {
        + {abstract} salvar(entidade: T&): bool
        + {abstract} buscar(id: K&): T*
        + {abstract} atualizar(entidade: T&): bool
        + {abstract} deletar(id: K&): bool
    }
    
    interface IRepositorioViagem {
        + {abstract} listarPorViajante(codigoViajante: Codigo&): vector<Viagem>
        + {abstract} calcularCustoTotal(codigoViagem: Codigo&): double
        + {abstract} possuiDestinos(codigoViagem: Codigo&): bool
    }
}

' Repository Layer
package "Reposit�rios" {
    class RepositorioBase {
        # db: sqlite3*
        + RepositorioBase(caminho: string)
        + ~RepositorioBase()
        # executar(query: string): void
        # executarSelect(query: string): sqlite3_stmt*
        # finalizar(): void
        # inicializar(): void
    }
    class RepositorioAutenticacao {
        + RepositorioAutenticacao(caminho: string)
        + autenticar(codigo: Codigo&, senha: Senha&): bool
        + salvar(viajante: Viajante&): bool
        + buscar(codigo: Codigo&): Viajante*
        + atualizar(viajante: Viajante&): bool
        + deletar(codigo: Codigo&): bool
    }
    class RepositorioViagem {
        + RepositorioViagem(caminho: string)
        + salvar(viagem: Viagem&): bool
        + buscar(codigo: Codigo&): Viagem*
        + atualizar(viagem: Viagem&): bool
        + deletar(codigo: Codigo&): bool
        + listarPorViajante(codigo: Codigo&): vector<Viagem>
        + calcularCustoTotal(codigo: Codigo&): double
        + possuiDestinos(codigo: Codigo&): bool
    }
    class RepositorioDestino {
        + RepositorioDestino(caminho: string)
        + salvar(destino: Destino&): bool
        + buscar(codigo: Codigo&): Destino*
        + atualizar(destino: Destino&): bool
        + deletar(codigo: Codigo&): bool
        + listarPorViagem(codigo: Codigo&): vector<Destino>
    }
    class RepositorioAtividade {
        + RepositorioAtividade(caminho: string)
        + salvar(atividade: Atividade&): bool
        + buscar(codigo: Codigo&): Atividade*
        + atualizar(atividade: Atividade&): bool
        + deletar(codigo: Codigo&): bool
        + listarPorDestino(codigo: Codigo&): vector<Atividade>
    }
    class RepositorioHospedagem {
        + RepositorioHospedagem(caminho: string)
        + salvar(hospedagem: Hospedagem&): bool
        + buscar(codigo: Codigo&): Hospedagem*
        + atualizar(hospedagem: Hospedagem&): bool
        + deletar(codigo: Codigo&): bool
        + listarPorDestino(codigo: Codigo&): vector<Hospedagem>
    }
    class RepositorioViajante {
        + RepositorioViajante(caminho: string)
        + salvar(viajante: Viajante&): bool
        + buscar(codigo: Codigo&): Viajante*
        + atualizar(viajante: Viajante&): bool
        + deletar(codigo: Codigo&): bool
    }
    class RepositorioConta {
        + RepositorioConta(caminho: string)
        + salvar(conta: Conta&): bool
        + buscar(codigo: Codigo&): Conta*
        + atualizar(conta: Conta&): bool
        + deletar(codigo: Codigo&): bool
    }
}

' Service Layer
package "Servi�os" {
    class ServicoAutenticacao {
        - repositorio: IRepositorio<Viajante,Codigo>*
        + ServicoAutenticacao(repo: IRepositorio<Viajante,Codigo>*)
        + ~ServicoAutenticacao()
        + autenticar(codigo: Codigo&, senha: Senha&): Viajante*
        + cadastrar(viajante: Viajante&): bool
    }
    class ServicoViagem {
        - repositorio: RepositorioViagem*
        - repositorioDestino: RepositorioDestino*
        + ServicoViagem(repoViagem: RepositorioViagem*, repoDestino: RepositorioDestino*)
        + criarViagem(viagem: Viagem&): bool
        + buscarViagem(codigo: Codigo&): Viagem*
        + atualizarViagem(viagem: Viagem&): bool
        + excluirViagem(codigo: Codigo&): bool
        + calcularCustoViagem(codigo: Codigo&): double
        + listarViagensPorViajante(codigo: Codigo&): vector<Viagem>
        + listarDestinosPorViagem(codigo: Codigo&): vector<Destino>
        + possuiDestinos(codigo: Codigo&): bool
    }
    class ServicoDestino {
        - repositorio: RepositorioDestino*
        + ServicoDestino(repo: RepositorioDestino*)
        + cadastrarDestino(destino: Destino&): bool
        + buscarDestino(codigo: Codigo&): Destino*
        + atualizarDestino(destino: Destino&): bool
        + excluirDestino(codigo: Codigo&): bool
        + listarPorViagem(codigo: Codigo&): vector<Destino>
        + listarTodos(): vector<Destino>
    }
    class ServicoAtividade {
        - repositorio: RepositorioAtividade*
        + ServicoAtividade(repo: RepositorioAtividade*)
        + cadastrarAtividade(atividade: Atividade&): bool
        + buscarAtividade(codigo: Codigo&): Atividade*
        + atualizarAtividade(atividade: Atividade&): bool
        + excluirAtividade(codigo: Codigo&): bool
        + listarPorDestino(codigo: Codigo&): vector<Atividade>
    }
    class ServicoHospedagem {
        - repositorio: RepositorioHospedagem*
        + ServicoHospedagem(repo: RepositorioHospedagem*)
        + cadastrarHospedagem(hospedagem: Hospedagem&): bool
        + buscarHospedagem(codigo: Codigo&): Hospedagem*
        + atualizarHospedagem(hospedagem: Hospedagem&): bool
        + excluirHospedagem(codigo: Codigo&): bool
        + listarPorDestino(codigo: Codigo&): vector<Hospedagem>
    }
    class ServicoViajante {
        - repositorio: RepositorioViajante*
        + ServicoViajante(repo: RepositorioViajante*)
        + cadastrarViajante(viajante: Viajante&): bool
        + buscarViajante(codigo: Codigo&): Viajante*
        + atualizarViajante(viajante: Viajante&): bool
        + excluirViajante(codigo: Codigo&): bool
    }
    class ServicoConta {
        - repositorio: RepositorioConta*
        + ServicoConta(repo: RepositorioConta*)
        + criarConta(conta: Conta&): bool
        + buscarConta(codigo: Codigo&): Conta*
        + atualizarConta(conta: Conta&): bool
        + excluirConta(codigo: Codigo&): bool
    }
}

' UI Layer
package "Telas" {
    class TelaBase
    class TelaAutenticacao
    class TelaCadastro
    class TelaPrincipal
    class TelaViagem
    class TelaDestino
    class TelaAtividade
    class TelaHospedagem
    class TelaViajante
    class TelaConta
}

' Inheritance
IRepositorio <|-- RepositorioBase
IRepositorioViagem <|-- RepositorioViagem
RepositorioBase <|-- RepositorioAutenticacao
RepositorioBase <|-- RepositorioViagem 
RepositorioBase <|-- RepositorioDestino
RepositorioBase <|-- RepositorioAtividade
RepositorioBase <|-- RepositorioHospedagem
RepositorioBase <|-- RepositorioViajante
RepositorioBase <|-- RepositorioConta

TelaBase <|-- TelaAutenticacao
TelaBase <|-- TelaCadastro
TelaBase <|-- TelaPrincipal
TelaBase <|-- TelaViagem
TelaBase <|-- TelaDestino
TelaBase <|-- TelaAtividade
TelaBase <|-- TelaHospedagem
TelaBase <|-- TelaViajante
TelaBase <|-- TelaConta

' Dependencies - Entities
Viajante --> Nome
Viajante --> Conta
Viagem --> Nome
Viagem --> Codigo
Viagem --> Avaliacao
Viagem --> Conta
Viagem --> Dinheiro
Destino --> Nome
Destino --> Codigo
Destino --> Avaliacao
Destino --> Data
Atividade --> Nome
Atividade --> Codigo
Atividade --> Avaliacao
Atividade --> Data
Atividade --> Horario
Atividade --> Duracao
Atividade --> Dinheiro
Hospedagem --> Nome
Hospedagem --> Codigo
Hospedagem --> Avaliacao
Hospedagem --> Dinheiro
Conta --> Codigo
Conta --> Senha

' Relationships - Entities
Conta "1" -- "0..*" Viagem
Viagem "1" -- "0..*" Destino
Destino "1" -- "0..*" Atividade
Destino "1" -- "0..*" Hospedagem

' Dependencies - Services/Repositories
ServicoAutenticacao --> RepositorioAutenticacao
ServicoViagem --> RepositorioViagem
ServicoDestino --> RepositorioDestino
ServicoAtividade --> RepositorioAtividade
ServicoHospedagem --> RepositorioHospedagem
ServicoViajante --> RepositorioViajante
ServicoConta --> RepositorioConta

' Dependencies - UI/Services
TelaAutenticacao --> ServicoAutenticacao
TelaCadastro --> ServicoAutenticacao
TelaViagem --> ServicoViagem
TelaDestino --> ServicoDestino
TelaAtividade --> ServicoAtividade
TelaHospedagem --> ServicoHospedagem
TelaViajante --> ServicoViajante
TelaConta --> ServicoConta
@enduml
"""

# Descrição da arquitetura
architecture_description = """
# Documentação da Arquitetura do Sistema de Planejamento de Viagens

## 1. Visão Geral
O sistema utiliza uma arquitetura modular que separa as responsabilidades em diferentes componentes:
- **Camada de Apresentação**
- **Camada de Serviço**
- **Camada de Domínio**
- **Aplicação Principal**

Cada módulo possui interfaces bem definidas e interage de forma específica, garantindo a manutenção e escalabilidade do sistema.

## 2. Módulos e Responsabilidades

### 2.1 Camada de Apresentação

**Responsabilidades:**

- **Tela de Login:**
  - Capturar as credenciais do usuário (nome de usuário e senha).
  - Enviar as credenciais para o **Serviço de Autenticação**.
  - Exibir mensagens de erro em caso de falha na autenticação.
  - Navegar para a **Tela Principal** após uma autenticação bem-sucedida.

- **Tela Principal:**
  - Exibir as opções disponíveis para o usuário após o login.
  - Permitir a navegação para as telas de **Gerenciamento de Viagens**, **Destinos**, **Atividades** e **Hospedagens**.
  - Exibir informações resumidas sobre as viagens atuais do usuário.

- **Telas de Gerenciamento:**
  - **Gerenciamento de Viagens:** Permite ao usuário criar, visualizar, atualizar e excluir viagens.
  - **Gerenciamento de Destinos:** Permite ao usuário gerenciar os destinos associados a cada viagem.
  - **Gerenciamento de Atividades:** Permite ao usuário gerenciar as atividades planejadas para cada destino.
  - **Gerenciamento de Hospedagens:** Permite ao usuário gerenciar as opções de hospedagem nos destinos.

### 2.2 Camada de Serviço

**Responsabilidades:**

- **Serviço de Autenticação:**
  - Validar as credenciais do usuário.
  - Gerenciar o estado de autenticação do usuário.
  - Fornecer tokens ou sessões para usuários autenticados.

- **Serviço de Viagens:**
  - Gerenciar operações CRUD para viagens.
  - Calcular custos totais das viagens.
  - Validar datas e durações das viagens conforme regras de negócio.

- **Serviço de Destinos:**
  - Gerenciar operações CRUD para destinos.
  - Associar destinos a viagens específicas.
  - Validar a integridade referencial ao adicionar ou remover destinos.

- **Serviço de Atividades:**
  - Gerenciar operações CRUD para atividades.
  - Agendar atividades em horários específicos.
  - Garantir que as atividades não se sobreponham em um mesmo destino.

- **Serviço de Hospedagens:**
  - Gerenciar operações CRUD para hospedagens.
  - Associar hospedagens a destinos específicos.
  - Permitir avaliações das hospedagens pelos usuários.

### 2.3 Camada de Domínio

**Responsabilidades:**

- **Autenticação:**
  - Encapsular a lógica de validação de credenciais.
  - Gerenciar informações de sessão ou tokens de autenticação.

- **Viagem:**
  - Representar os detalhes de uma viagem, incluindo datas, duração e custos.
  - Associar destinos específicos à viagem.

- **Destino:**
  - Representar um destino dentro de uma viagem.
  - Associar atividades e hospedagens ao destino.

- **Atividade:**
  - Representar uma atividade planejada em um destino.
  - Gerenciar o horário e a duração da atividade.

- **Hospedagem:**
  - Representar uma opção de hospedagem em um destino.
  - Gerenciar avaliações feitas pelos usuários.

### 2.4 Aplicação Principal

**Responsabilidades:**

- **main.cpp:**
  - Ponto de entrada da aplicação.
  - Inicializar a **Tela de Login**.
  - Gerenciar o fluxo geral da aplicação após a autenticação.

## 3. Relacionamentos e Fluxo de Dados

- **Tela de Login** envia as credenciais para o **Serviço de Autenticação**.
- **Serviço de Autenticação** valida as credenciais através do domínio **Autenticação**.
- Após a autenticação bem-sucedida, a **Tela de Login** navega para a **Tela Principal**.
- **Tela Principal** oferece opções para gerenciar **Viagens**, **Destinos**, **Atividades** e **Hospedagens**.
- Cada opção de gerenciamento na **Tela Principal** interage com o respectivo **Serviço** na **Camada de Serviço**.
- Os **Serviços** manipulam os dados através das classes de domínio correspondentes (**Viagem**, **Destino**, etc.).
- A **Aplicação Principal** (`main.cpp`) inicializa a **Tela de Login** e a **Tela Principal**, gerenciando o fluxo geral da aplicação.

## 4. Regras de Negócio Principais

1. **Integridade Referencial:**
   - Não é permitido excluir registros que possuam dependências associadas (e.g., não excluir um Viajante se houver Viagens associadas).

2. **Validações Temporais:**
   - As datas das atividades devem estar dentro do intervalo definido pelas datas de início e término da viagem.
   - Evitar a sobreposição de horários em atividades dentro do mesmo destino.

3. **Validações de Dados:**
   - Formato específico para cada domínio (e.g., senhas devem ter um formato seguro).
   - Regras de negócio por entidade para garantir a validade e consistência dos dados.

## 5. Padrões de Projeto Utilizados

- **Repository Pattern:** Abstração da camada de persistência, facilitando a troca de implementações de armazenamento.
- **Interface Segregation:** Separação das responsabilidades em interfaces específicas para cada serviço.
- **Dependency Injection:** Inversão de controle para facilitar testes e manutenção.
- **Factory Method:** Criação de objetos complexos de forma controlada.
- **Singleton:** Gerenciamento da conexão com o banco de dados para evitar múltiplas instâncias.

## 6. Considerações Finais

A arquitetura proposta reflete de forma precisa os processos reais da aplicação de planejamento de viagens. A separação clara de responsabilidades entre os módulos garante um sistema modular, escalável e de fácil manutenção, atendendo aos requisitos funcionais e não funcionais do projeto.
"""

def main():
    # Definir os caminhos dos arquivos
    puml_file = 'architecture.puml'
    diagram_file = 'architecture_diagram.png'
    pdf_file = 'modelo_arquitetura.pdf'
    
    # Gerar o diagrama PlantUML
    print("Gerando diagrama de arquitetura...")
    success = generate_plantuml_diagram(plantuml_code, diagram_file)
    
    if not success:
        print("Falha ao gerar o diagrama. Abortando a criação do PDF.")
        return
    
    # Gerar o PDF com o diagrama e a descrição
    print("Gerando documento PDF...")
    success = create_pdf(diagram_file, pdf_file, architecture_description)
    
    if success:
        print(f"Documento PDF '{pdf_file}' gerado com sucesso!")
    else:
        print("Falha ao gerar o PDF.")

if __name__ == "__main__":
    main()
