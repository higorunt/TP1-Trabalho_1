#include "../../include/telas/TelaDestino.hpp"
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>

// Construtor: armazena os ponteiros dos serviços e do usuário
TelaDestino::TelaDestino(ServicoDestino* srvDestino, ServicoViagem* srvViagem, Viajante* v)
    : servicoDestino(srvDestino), servicoViagem(srvViagem), viajante(v), painelDestino(nullptr)
{
    int altura, largura;
    getmaxyx(janela, altura, largura);
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
}

// Destrutor: libera a janela, se criada
TelaDestino::~TelaDestino() {
    if (painelDestino != nullptr) {
        delwin(painelDestino);
        painelDestino = nullptr;
    }
}

// Permite ao usuário selecionar uma viagem real (a partir dos dados do usuário)
Codigo TelaDestino::selecionarViagem() {
    // Obter a lista real de viagens do usuário usando o ServicoViagem
    std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
    
    // Define um código sentinela "000000" para indicar cancelamento
    Codigo codigoSentinela("000000");
    
    if (viagens.empty()) {
        mostrarAlerta("Nenhuma viagem encontrada para afiliacao.");
        return codigoSentinela;
    }
    
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Selecione a Viagem para afiliar o Destino ===");
    int linha = 3;
    for (size_t i = 0; i < viagens.size(); i++) {
        std::stringstream ss;
        ss << (i+1) << ". " << viagens[i].getCodigo().getValor() << " - " << viagens[i].getNome().getValor();
        mvwprintw(janela, linha++, 2, "%s", ss.str().c_str());
    }
    mvwprintw(janela, linha+1, 2, "Digite o numero da viagem ou ESC para cancelar:");
    wrefresh(janela);
    
    int ch = wgetch(janela);
    if (ch == 27) {  // ESC
        return codigoSentinela;
    }
    int escolha = ch - '0';
    if (escolha < 1 || escolha > static_cast<int>(viagens.size())) {
        mostrarAlerta("Selecao invalida.");
        return codigoSentinela;
    }
    return viagens[escolha - 1].getCodigo();
}

// Desenha o formulário para cadastro de destino com informações da viagem selecionada
void TelaDestino::desenharFormulario(const std::string& infoViagem) {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    int modalAltura = 16;
    int modalLargura = 70;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;
    
    if (painelDestino != nullptr) {
        delwin(painelDestino);
    }
    
    painelDestino = newwin(modalAltura, modalLargura,
                           modalY + getbegy(janela),
                           modalX + getbegx(janela));
    
    wbkgd(painelDestino, COLOR_PAIR(COR_INVERSA));
    box(painelDestino, 0, 0);
    
    std::string titulo = "Cadastrar Destino";
    mvwprintw(painelDestino, 1, (modalLargura - titulo.length())/2, "%s", titulo.c_str());
    
    // Exibe informações da viagem selecionada
    mvwprintw(painelDestino, 2, 2, "Viagem: %s", infoViagem.c_str());
    
    // Campo: Nome do Destino
    mvwprintw(painelDestino, 4, 2, "Nome: ");
    mvwaddch(painelDestino, 4, 10, '[');
    mvwhline(painelDestino, 4, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelDestino, 4, 11 + TAM_MAX_NOME, ']');
    
    // Campo: Data de Início
    mvwprintw(painelDestino, 6, 2, "Data Inicio: ");
    mvwaddch(painelDestino, 6, 15, '[');
    mvwhline(painelDestino, 6, 16, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 6, 16 + TAM_MAX_DATA, ']');
    
    // Campo: Data de Fim
    mvwprintw(painelDestino, 8, 2, "Data Fim: ");
    mvwaddch(painelDestino, 8, 12, '[');
    mvwhline(painelDestino, 8, 13, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 8, 13 + TAM_MAX_DATA, ']');
    
    // Campo: Avaliacao
    mvwprintw(painelDestino, 10, 2, "Avaliacao: ");
    mvwaddch(painelDestino, 10, 13, '[');
    mvwhline(painelDestino, 10, 14, ' ', TAM_MAX_AVALIACAO);
    mvwaddch(painelDestino, 10, 14 + TAM_MAX_AVALIACAO, ']');
    
    // Instruções
    mvwprintw(painelDestino, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");
    
    wrefresh(painelDestino);
    wrefresh(janela);
}

// Processa os dados inseridos e cria o destino, utilizando o código da viagem selecionada
bool TelaDestino::processarDestino(const Codigo& codigoViagem) {
    // Gera automaticamente o código do destino: 3 primeiros caracteres do código da viagem + timestamp
    std::string base = codigoViagem.getValor().substr(0, 3);
    time_t now = time(0);
    std::string timestamp = std::to_string(now % 1000);
    while (timestamp.length() < 3) {
        timestamp = "0" + timestamp;
    }
    std::string codigoDestinoStr = base + timestamp;
    
    // Ler os demais campos
    wmove(painelDestino, 4, 11);
    std::string nomeStr = campoTexto(painelDestino, 4, 11, TAM_MAX_NOME);
    if (nomeStr.empty()) return false;
    
    wmove(painelDestino, 6, 16);
    std::string dataInicioStr = campoTexto(painelDestino, 6, 16, TAM_MAX_DATA);
    if (dataInicioStr.empty()) return false;
    
    wmove(painelDestino, 8, 13);
    std::string dataFimStr = campoTexto(painelDestino, 8, 13, TAM_MAX_DATA);
    if (dataFimStr.empty()) return false;
    
    wmove(painelDestino, 10, 14);
    std::string avalStr = campoTexto(painelDestino, 10, 14, TAM_MAX_AVALIACAO);
    if (avalStr.empty()) return false;
    
    try {
        Codigo codigoDestino(codigoDestinoStr);
        Nome nomeDestino(nomeStr);
        Data dataInicio(dataInicioStr);
        Data dataFim(dataFimStr);
        int aval = std::stoi(avalStr);
        Avaliacao avaliacao(aval);
        
        // Cria o objeto Destino com os dados e associa-o à viagem selecionada
        Destino destino(codigoDestino, nomeDestino, dataInicio, dataFim, avaliacao, codigoViagem);
        
        if (servicoDestino->criarDestino(destino)) {
            mostrarAlerta("Destino criado com sucesso!");
            return true;
        } else {
            mostrarAlerta("Erro ao criar destino.");
            return false;
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
        return false;
    }
}

// Exibe a tela de destinos para cadastro
void TelaDestino::mostrar() {
    // Permite ao usuário selecionar uma viagem real usando o serviço de viagens
    Codigo codViagemSelecionada = selecionarViagem();
    if (codViagemSelecionada.getValor() == "000000") {
        mostrarAlerta("Selecao de viagem cancelada.");
        return;
    }
    
    // Exibe informações da viagem selecionada
    std::string infoViagem = "Viagem: " + codViagemSelecionada.getValor();
    limparTela();
    desenharFormulario(infoViagem);
}

// Executa o fluxo de cadastro de destino
bool TelaDestino::executar() {
    Codigo codViagemSelecionada = selecionarViagem();
    if (codViagemSelecionada.getValor() == "000000") {
        mostrarAlerta("Selecao de viagem cancelada.");
        return false;
    }
    desenharFormulario("Viagem: " + codViagemSelecionada.getValor());
    return processarDestino(codViagemSelecionada);
}
