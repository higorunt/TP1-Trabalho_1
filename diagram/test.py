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
skinparam defaultFontName "Helvetica"

title Arquitetura Orientada a Processos do Sistema de Planejamento de Viagens

' Definição dos módulos principais
package "Camada de Apresentação" {
    [Tela de Login] as Login
    [Tela Principal] as MainScreen
    [Gerenciamento de Viagens] as ManageTrips
    [Gerenciamento de Destinos] as ManageDestinations
    [Gerenciamento de Atividades] as ManageActivities
    [Gerenciamento de Hospedagens] as ManageAccommodations
}

package "Camada de Serviço" {
    [Serviço de Autenticação] as AuthService
    [Serviço de Viagens] as TripsService
    [Serviço de Destinos] as DestinationsService
    [Serviço de Atividades] as ActivitiesService
    [Serviço de Hospedagens] as AccommodationsService
}

package "Camada de Domínio" {
    [Autenticação]
    [Viagem]
    [Destino]
    [Atividade]
    [Hospedagem]
}

package "Aplicação Principal" {
    [main.cpp]
}

' Relacionamentos entre módulos
Login --> AuthService : Envia Credenciais
AuthService --> Autenticação : Valida Credenciais
Autenticação --> AuthService : Retorna Status
AuthService --> Login : Retorna Status
Login --> MainScreen : Navega após Sucesso

MainScreen --> TripsService : Solicita Gerenciamento de Viagens
MainScreen --> DestinationsService : Solicita Gerenciamento de Destinos
MainScreen --> ActivitiesService : Solicita Gerenciamento de Atividades
MainScreen --> AccommodationsService : Solicita Gerenciamento de Hospedagens

TripsService --> Viagem : Manipula Dados de Viagem
DestinationsService --> Destino : Manipula Dados de Destino
ActivitiesService --> Atividade : Manipula Dados de Atividade
AccommodationsService --> Hospedagem : Manipula Dados de Hospedagem

Viagem --> Data : Define
Viagem --> Dinheiro : Calcula
Viagem --> Duracao : Define
Viagem --> Destino : Contém

Destino --> Nome : Possui
Destino --> Atividade : Contém
Destino --> Hospedagem : Contém

Atividade --> Horario : Agendada em
Hospedagem --> Avaliacao : Recebe

Viajante --> Senha : Possui

main.cpp --> Login : Inicializa Tela de Login
main.cpp --> MainScreen : Inicializa Tela Principal

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
