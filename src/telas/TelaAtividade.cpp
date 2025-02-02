#include "../../include/telas/TelaAtividade.hpp"
#include <iomanip>
#include <sstream>

// Remover a definição da função livre e adicionar como método da classe
std::string TelaAtividade::formatarData(const std::string& dataStr) {
    if (dataStr.length() != 6) {
        throw std::invalid_argument("Data invalida: informe 6 digitos (ddmmaa)");
    }
    return dataStr.substr(0, 2) + "-" + dataStr.substr(2, 2) + "-" + dataStr.substr(4, 2);
}

void TelaAtividade::mostrar() {
    limparTela();
    desenharMenu();
    
    while (true) {
        int ch = wgetch(janela);
        
        if (ch == '0') break;
        
        if (ch >= '1' && ch <= '4') {
            processarOpcao(ch - '0');
            limparTela();
            desenharMenu();
        }
    }
}

void TelaAtividade::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelAtividade != nullptr) {
        delwin(painelAtividade);
    }
    
    painelAtividade = subwin(janela, layout.altura, layout.largura,
                           layout.centralY + getbegy(janela),
                           layout.centralX + getbegx(janela));
    
    wbkgd(painelAtividade, COLOR_PAIR(COR_PRINCIPAL));
    box(painelAtividade, 0, 0);
    
    mvwprintw(painelAtividade, 1, (layout.largura - 18) / 2, "Gerenciar Atividades");
    
    const char* opcoes[] = {
        "1. Criar nova atividade",
        "2. Listar atividades do destino",
        "3. Editar atividade",
        "4. Excluir atividade",
        "0. Voltar"
    };
    
    for (int i = 0; i < 5; i++) {
        mvwprintw(painelAtividade, i + 3, 3, "%s", opcoes[i]);
    }
    
    mvwprintw(painelAtividade, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelAtividade);
    wrefresh(janela);
}

void TelaAtividade::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            criarAtividade();
            break;
        case 2:
            listarAtividades();
            break;
        case 3:
            editarAtividade();
            break;
        case 4:
            excluirAtividade();
            break;
    }
}

bool TelaAtividade::criarAtividade() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return false;

    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Criar Nova Atividade ===");

    try {
        std::string nome = lerInput("Nome da atividade: ", 3, 2);
        if (nome.empty()) return false;

        std::string data = lerInput("Data (DDMMAA): ", 4, 2);
        if (data.empty()) return false;
        data = formatarData(data);

        std::string horarioStr = lerInput("Horario (HH:MM): ", 5, 2);
        if (horarioStr.empty()) return false;
        Horario horario;
        horario.setValor(horarioStr);

        // Corrigindo a criação e atribuição da duração
        std::string duracaoStr = lerInput("Duracao (minutos): ", 6, 2);
        if (duracaoStr.empty()) return false;
        int duracaoMinutos = std::stoi(duracaoStr);
        Duracao duracao(duracaoMinutos);  // Usando o construtor com int

        std::string precoStr = lerInput("Preco (R$): ", 7, 2);
        if (precoStr.empty()) return false;
        Dinheiro preco(std::stod(precoStr));

        std::string avalStr = lerInput("Avaliacao (1-5): ", 8, 2);
        if (avalStr.empty()) return false;
        int avaliacao = std::stoi(avalStr);

        // Gerar código único para a atividade
        std::string baseCode = codigoDestino.getValor().substr(0, 3);
        time_t now = time(0);
        std::string timestamp = std::to_string(now % 1000);
        while (timestamp.length() < 3) timestamp = "0" + timestamp;
        std::string codigoAtiv = baseCode + timestamp;

        Atividade novaAtividade(
            Nome(nome),
            Codigo(codigoAtiv),
            Avaliacao(avaliacao),
            Data(data),
            horario,
            duracao,  // Usando o objeto Duracao criado corretamente
            preco,
            codigoDestino
        );

        if (servicoAtividade->criarAtividade(novaAtividade)) {
            mostrarAlerta("Atividade criada com sucesso!");
            return true;
        }
        mostrarAlerta("Erro ao criar atividade.");
        return false;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
        return false;
    }
}

void TelaAtividade::listarAtividades() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return;

    try {
        std::vector<Atividade> atividades = servicoAtividade->listarPorDestino(codigoDestino);
        
        if (atividades.empty()) {
            mostrarAlerta("Nenhuma atividade encontrada para este destino.");
            return;
        }

        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Lista de Atividades ===");
        
        int linha = 3;
        for (const auto& atividade : atividades) {
            std::string info = atividade.getCodigo().getValor() + " | " +
                             atividade.getNome().getValor() + " | " +
                             atividade.getData().getValor() + " " +
                             atividade.getHorario().getValor() + " | R$ " +
                             atividade.getPreco().getValor();
            
            mvwprintw(janela, linha++, 2, "%s", info.c_str());
        }

        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaAtividade::editarAtividade() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Editar Atividade ===");

    std::string codigoStr = lerInput("Codigo da atividade: ", 3, 2);
    if (codigoStr.empty()) return;

    try {
        Codigo codigo(codigoStr);
        Atividade* atividade = servicoAtividade->buscarAtividade(codigo);
        
        if (!atividade) {
            mostrarAlerta("Atividade nao encontrada.");
            return;
        }

        std::string novoNome = lerInput("Novo nome (" + atividade->getNome().getValor() + "): ", 4, 2);
        if (novoNome.empty()) novoNome = atividade->getNome().getValor();

        std::string novaData = lerInput("Nova data (" + atividade->getData().getValor() + "): ", 5, 2);
        if (novaData.empty()) novaData = atividade->getData().getValor();
        else novaData = formatarData(novaData);

        std::string novoHorarioStr = lerInput("Novo horario (" + atividade->getHorario().getValor() + "): ", 6, 2);
        Horario novoHorario = atividade->getHorario();
        if (!novoHorarioStr.empty()) {
            novoHorario.setValor(novoHorarioStr);
        }

        std::string novaDuracaoStr = lerInput("Nova duracao (" + std::to_string(atividade->getDuracao().getValor()) + "): ", 7, 2);
        Duracao novaDuracao(atividade->getDuracao().getValor());  // Inicializa com valor atual
        if (!novaDuracaoStr.empty()) {
            novaDuracao.setValor(std::stoi(novaDuracaoStr));  // Converte string para int
        }

        std::string novoPrecoStr = lerInput("Novo preco (R$ " + atividade->getPreco().getValor() + "): ", 8, 2);
        double novoPreco = novoPrecoStr.empty() ? std::stod(atividade->getPreco().getValor()) : std::stod(novoPrecoStr);

        std::string novaAvalStr = lerInput("Nova avaliacao (" + std::to_string(atividade->getAvaliacao().getValor()) + "): ", 9, 2);
        int novaAval = novaAvalStr.empty() ? atividade->getAvaliacao().getValor() : std::stoi(novaAvalStr);

        Atividade atividadeAtualizada(
            Nome(novoNome),
            atividade->getCodigo(),
            Avaliacao(novaAval),
            Data(novaData),
            novoHorario,
            novaDuracao,
            Dinheiro(novoPreco),
            atividade->getCodigoDestino()
        );

        if (servicoAtividade->atualizarAtividade(atividadeAtualizada)) {
            mostrarAlerta("Atividade atualizada com sucesso!");
        } else {
            mostrarAlerta("Erro ao atualizar atividade.");
        }

        delete atividade;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaAtividade::excluirAtividade() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Excluir Atividade ===");

    std::string codigoStr = lerInput("Codigo da atividade: ", 3, 2);
    if (codigoStr.empty()) return;

    try {
        Codigo codigo(codigoStr);
        
        std::string confirma = lerInput("Confirma exclusao? (S/N): ", 4, 2);
        if (confirma == "S" || confirma == "s") {
            if (servicoAtividade->excluirAtividade(codigo)) {
                mostrarAlerta("Atividade excluida com sucesso!");
            } else {
                mostrarAlerta("Erro ao excluir atividade.");
            }
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

Codigo TelaAtividade::selecionarDestino() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Selecionar Destino ===");

    try {
        std::vector<Destino> destinos = servicoDestino->listarTodos();
        
        if (destinos.empty()) {
            mostrarAlerta("Nenhum destino encontrado.");
            return Codigo("000000");
        }

        int linha = 3;
        for (size_t i = 0; i < destinos.size(); i++) {
            std::string info = std::to_string(i + 1) + ". " + 
                             destinos[i].getCodigo().getValor() + " - " + 
                             destinos[i].getNome().getValor();
            mvwprintw(janela, linha++, 2, "%s", info.c_str());
        }

        std::string escolha = lerInput("Escolha o numero do destino (0 para cancelar): ", linha + 1, 2);
        if (escolha.empty() || escolha == "0") return Codigo("000000");

        size_t idx = std::stoul(escolha) - 1;
        if (idx >= destinos.size()) {
            mostrarAlerta("Opcao invalida.");
            return Codigo("000000");
        }

        return destinos[idx].getCodigo();

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
        return Codigo("000000");
    }
}
