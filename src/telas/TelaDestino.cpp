#include "../../include/telas/TelaDestino.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// =================== Construtor e Destrutor ===================

TelaDestino::TelaDestino(ServicoDestino* srvDestino, ServicoViagem* srvViagem, Viajante* v)
    : servicoDestino(srvDestino), servicoViagem(srvViagem), viajante(v), painelDestino(nullptr)
{
    // Inicializa o layout com base na janela principal (herdada de TelaBase)
    int altura, largura;
    getmaxyx(janela, altura, largura);
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
}

TelaDestino::~TelaDestino() {
    if (painelDestino != nullptr) {
        delwin(painelDestino);
        painelDestino = nullptr;
    }
}

// =================== Métodos Auxiliares ===================

// Converte uma data digitada sem separadores (ex.: "050722") para o formato "dd-mm-aa"
std::string TelaDestino::formatarData(const std::string& dataStr) {
    if (dataStr.length() != TAM_MAX_DATA) {
        throw std::invalid_argument("Data invalida: informe 6 digitos (ddmmaa).");
    }
    return dataStr.substr(0, 2) + "-" + dataStr.substr(2, 2) + "-" + dataStr.substr(4, 2);
}

// Converte um objeto Data (formato "dd-mm-aa") para time_t para comparação
time_t TelaDestino::dataToTime(const Data& d) {
    std::string s = d.getValor(); // Exemplo: "05-07-22"
    int dia = std::stoi(s.substr(0,2));
    int mes = std::stoi(s.substr(3,2));
    int ano = std::stoi(s.substr(6,2));
    tm t = {0};
    t.tm_mday = dia;
    t.tm_mon = mes - 1;
    t.tm_year = 100 + ano; // 2000+ano - 1900
    return mktime(&t);
}

// =================== Seleção de Viagem ===================

// Lista as viagens do viajante e permite a seleção.
// Retorna o código da viagem selecionada ou "000000" se cancelado.
Codigo TelaDestino::selecionarViagem() {
    std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
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
        ss << (i+1) << ". " << viagens[i].getCodigo().getValor() << " - " 
           << viagens[i].getNome().getValor();
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

// =================== Menu de Gerenciamento de Destinos ===================

// Exibe um menu com as opções: cadastrar, listar, editar e excluir destinos.
void TelaDestino::desenharMenuDestino() {
    limparTela();  // Limpa a tela anterior
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    int menuAltura = 14;
    int menuLargura = 60;
    int menuY = (altura - menuAltura) / 2;
    int menuX = (largura - menuLargura) / 2;
    
    if (painelDestino != nullptr) {
        delwin(painelDestino);
    }
    
    painelDestino = newwin(menuAltura, menuLargura,
                           menuY + getbegy(janela),
                           menuX + getbegx(janela));
    wbkgd(painelDestino, COLOR_PAIR(COR_PRINCIPAL));
    box(painelDestino, 0, 0);
    
    mvwprintw(painelDestino, 1, (menuLargura - 23) / 2, "Gerenciar Destinos");
    
    const char* opcoes[] = {
        "1. Cadastrar Destino",
        "2. Listar Destinos",
        "3. Editar Destino",
        "4. Excluir Destino",
        "0. Voltar"
    };
    for (int i = 0; i < 5; i++) {
        mvwprintw(painelDestino, i + 3, 3, "%s", opcoes[i]);
    }
    mvwprintw(painelDestino, menuAltura - 2, 2, "Digite o numero da opcao desejada");
    wrefresh(painelDestino);
    wrefresh(janela);
}

// Processa a opção escolhida no menu de destinos.
void TelaDestino::processarOpcaoDestino(int opcao) {
    switch (opcao) {
        case 1:
            if (cadastrarDestino())
                mostrarAlerta("Destino cadastrado com sucesso!");
            else
                mostrarAlerta("Falha no cadastro de destino.");
            break;
        case 2:
            listarDestinos();
            break;
        case 3:
            editarDestino();
            break;
        case 4:
            excluirDestino();
            break;
        default:
            break;
    }
}

// =================== Fluxo de Cadastro de Destino ===================

bool TelaDestino::cadastrarDestino() {
    // Seleciona a viagem para afiliar o destino
    Codigo codigoViagem = selecionarViagem();
    if (codigoViagem.getValor() == "000000") {
        return false;
    }

    // Busca informações da viagem selecionada
    Viagem* viagem = servicoViagem->buscarViagem(codigoViagem);
    if (viagem == nullptr) {
        mostrarAlerta("Erro ao buscar informacoes da viagem.");
        return false;
    }

    // Prepara string com informações da viagem
    std::string infoViagem = viagem->getCodigo().getValor() + " - " + viagem->getNome().getValor();
    delete viagem;

    // Mostra formulário e processa dados
    desenharFormulario(infoViagem);
    return processarDestino(codigoViagem);
}

// Desenha o formulário para cadastro de destino, exibindo informações da viagem selecionada.
void TelaDestino::desenharFormulario(const std::string& infoViagem) {
    limparTela(); // Limpa a tela antes de mostrar o formulário
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
    mvwprintw(painelDestino, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());
    
    // Exibe informações da viagem selecionada
    mvwprintw(painelDestino, 2, 2, "Viagem: %s", infoViagem.c_str());
    
    // Campo: Nome do Destino
    mvwprintw(painelDestino, 4, 2, "Nome: ");
    mvwaddch(painelDestino, 4, 10, '[');
    mvwhline(painelDestino, 4, 11, ' ', TAM_MAX_NOME);
    mvwaddch(painelDestino, 4, 11 + TAM_MAX_NOME, ']');
    
    // Campo: Data de Início (6 dígitos, ex.: "050722")
    mvwprintw(painelDestino, 6, 2, "Data Inicio (ddmmaa): ");
    mvwaddch(painelDestino, 6, 26, '[');
    mvwhline(painelDestino, 6, 27, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 6, 27 + TAM_MAX_DATA, ']');
    
    // Campo: Data de Fim (6 dígitos)
    mvwprintw(painelDestino, 8, 2, "Data Fim (ddmmaa): ");
    mvwaddch(painelDestino, 8, 24, '[');
    mvwhline(painelDestino, 8, 25, ' ', TAM_MAX_DATA);
    mvwaddch(painelDestino, 8, 25 + TAM_MAX_DATA, ']');
    
    // Campo: Avaliacao (1-5)
    mvwprintw(painelDestino, 10, 2, "Avaliacao (1-5): ");
    mvwaddch(painelDestino, 10, 20, '[');
    mvwhline(painelDestino, 10, 21, ' ', TAM_MAX_AVALIACAO);
    mvwaddch(painelDestino, 10, 21 + TAM_MAX_AVALIACAO, ']');
    
    // Instruções
    mvwprintw(painelDestino, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");
    wrefresh(painelDestino);
    wrefresh(janela);
}

// Processa os dados do formulário e cria o destino, validando as datas.
bool TelaDestino::processarDestino(const Codigo& codigoViagem) {
    // Gera o código do destino: 3 primeiros caracteres do código da viagem + timestamp
    std::string base = codigoViagem.getValor().substr(0, 3);
    time_t now = time(0);
    std::string timestamp = std::to_string(now % 1000);
    while (timestamp.length() < 3)
        timestamp = "0" + timestamp;
    std::string codigoDestinoStr = base + timestamp;
    
    // Ler os campos do formulário
    wmove(painelDestino, 4, 11);
    std::string nomeStr = campoTexto(painelDestino, 4, 11, TAM_MAX_NOME);
    if (nomeStr.empty()) return false;
    
    wmove(painelDestino, 6, 27);
    std::string dataInicioInput = campoTexto(painelDestino, 6, 27, TAM_MAX_DATA);
    if (dataInicioInput.empty()) return false;
    std::string dataInicioStr = formatarData(dataInicioInput);
    
    wmove(painelDestino, 8, 25);
    std::string dataFimInput = campoTexto(painelDestino, 8, 25, TAM_MAX_DATA);
    if (dataFimInput.empty()) return false;
    std::string dataFimStr = formatarData(dataFimInput);
    
    wmove(painelDestino, 10, 21);
    std::string avalStr = campoTexto(painelDestino, 10, 21, TAM_MAX_AVALIACAO);
    if (avalStr.empty()) return false;
    
    try {
        Codigo codigoDestino(codigoDestinoStr);
        Nome nomeDestino(nomeStr);
        Data dataInicio(dataInicioStr);
        Data dataFim(dataFimStr);
        int aval = std::stoi(avalStr);
        Avaliacao avaliacao(aval);
        
        // Valida as datas: a data de início deve ser futura e a data de fim posterior à data de início
        time_t agora = time(NULL);
        time_t inicioTime = dataToTime(dataInicio);
        time_t fimTime = dataToTime(dataFim);
        if (inicioTime <= agora) {
            mostrarAlerta("Data de inicio deve ser futura.");
            return false;
        }
        if (fimTime <= inicioTime) {
            mostrarAlerta("Data de fim deve ser posterior a data de inicio.");
            return false;
        }
        
        Destino destino(codigoDestino, nomeDestino, dataInicio, dataFim, avaliacao, codigoViagem);
        if (servicoDestino->criarDestino(destino)) {
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

// =================== Fluxo para Listar, Editar e Excluir ===================

void TelaDestino::listarDestinos() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Lista de Destinos ===");
    wrefresh(janela);

    try {
        std::vector<Destino> destinos = servicoDestino->listarTodos();
        if (destinos.empty()) {
            mostrarAlerta("Nenhum destino encontrado.");
            return;
        }

        int linha = 4;
        mvwprintw(janela, 2, 2, "%-6s %-20s %-12s %-12s %-5s %-6s", 
                  "Codigo", "Nome", "Data Inicio", "Data Fim", "Aval", "Viagem");
        mvwprintw(janela, 3, 2, std::string(70, '-').c_str());

        for (const auto& d : destinos) {
            std::string nome = d.getNome().getValor();
            if (nome.length() > 20) {
                nome = nome.substr(0, 17) + "...";
            }

            mvwprintw(janela, linha++, 2, "%-6s %-20s %-12s %-12s %-5d %-6s",
                     d.getCodigo().getValor().c_str(),
                     nome.c_str(),
                     d.getDataInicio().getValor().c_str(),
                     d.getDataFim().getValor().c_str(),
                     d.getAvaliacao().getValor(),
                     d.getCodigoViagem().getValor().c_str());

            if (linha >= getmaxy(janela) - 3) {
                mvwprintw(janela, getmaxy(janela) - 2, 2, "Pressione qualquer tecla para continuar...");
                wrefresh(janela);
                wgetch(janela);
                linha = 4;
                limparTela();
                box(janela, 0, 0);
                mvwprintw(janela, 1, 2, "=== Lista de Destinos ===");
                mvwprintw(janela, 2, 2, "%-6s %-20s %-12s %-12s %-5s %-6s", 
                         "Codigo", "Nome", "Data Inicio", "Data Fim", "Aval", "Viagem");
                mvwprintw(janela, 3, 2, std::string(70, '-').c_str());
            }
        }

        mvwprintw(janela, linha + 1, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaDestino::editarDestino() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    keypad(janela, TRUE);
    noecho();
    
    while (true) {
        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Editar Destino ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string codigo = lerInput("Digite o codigo do destino: ", 3, 2);
        if (codigo.empty()) return;

        try {
            Codigo codigoDestino(codigo);
            Destino* destino = servicoDestino->buscarDestino(codigoDestino);
            
            if (!destino) {
                mostrarAlerta("Destino nao encontrado.");
                continue;
            }

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Destino ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            std::string prompt = "Novo nome (" + destino->getNome().getValor() + "): ";
            std::string novoNome = lerInput(prompt, 3, 2);
            if (novoNome.empty()) novoNome = destino->getNome().getValor();

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Destino ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            prompt = "Nova data inicio (" + destino->getDataInicio().getValor() + ") [ddmmaa]: ";
            std::string novaDataInicio = lerInput(prompt, 3, 2);
            if (novaDataInicio.empty()) {
                novaDataInicio = destino->getDataInicio().getValor();
            } else {
                novaDataInicio = formatarData(novaDataInicio);
            }

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Destino ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            prompt = "Nova data fim (" + destino->getDataFim().getValor() + ") [ddmmaa]: ";
            std::string novaDataFim = lerInput(prompt, 3, 2);
            if (novaDataFim.empty()) {
                novaDataFim = destino->getDataFim().getValor();
            } else {
                novaDataFim = formatarData(novaDataFim);
            }

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Destino ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            prompt = "Nova avaliacao (" + std::to_string(destino->getAvaliacao().getValor()) + "): ";
            std::string novaAvalStr = lerInput(prompt, 3, 2);
            if (novaAvalStr.empty()) novaAvalStr = std::to_string(destino->getAvaliacao().getValor());

            try {
                Nome nome(novoNome);
                Data dataInicio(novaDataInicio);
                Data dataFim(novaDataFim);
                Avaliacao avaliacao(std::stoi(novaAvalStr));

                Destino destinoAtualizado(destino->getCodigo(), nome, dataInicio, dataFim, 
                                        avaliacao, destino->getCodigoViagem());

                if (servicoDestino->atualizarDestino(destinoAtualizado)) {
                    mostrarAlerta("Destino atualizado com sucesso!");
                    delete destino;
                    return;
                } else {
                    mostrarAlerta("Erro ao atualizar destino.");
                }
            } catch (const std::invalid_argument& e) {
                mostrarAlerta(e.what());
            }

            delete destino;
        } catch (const std::exception& e) {
            mostrarAlerta(e.what());
        }
    }
}

// Fluxo para excluir destino
void TelaDestino::excluirDestino() {
    limparTela();
    box(janela, 0, 0);
    std::string codigoInput = mostrarInput("Digite o codigo do destino a excluir:");
    if (codigoInput.empty()) {
        mostrarAlerta("Operacao cancelada.");
        return;
    }
    try {
        Codigo codigoDestino(codigoInput);
        if (servicoDestino->excluirDestino(codigoDestino)) {
            mostrarAlerta("Destino excluido com sucesso!");
        } else {
            mostrarAlerta("Falha ao excluir destino.");
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

// =================== Fluxo Principal da TelaDestino ===================

// Exibe o menu principal da TelaDestino.
void TelaDestino::mostrar() {
    desenharMenuDestino();
}

// Executa o fluxo completo de gerenciamento de destinos.
bool TelaDestino::executar() {
    while (true) {
        desenharMenuDestino();
        int ch = wgetch(janela);
        if (ch == '0') break;
        if (ch >= '1' && ch <= '4') {
            processarOpcaoDestino(ch - '0');
        }
    }
    return true;
}
