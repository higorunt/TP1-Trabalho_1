#include "../../include/telas/TelaHospedagem.hpp"
#include <iomanip>
#include <sstream>

void TelaHospedagem::mostrar() {
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

void TelaHospedagem::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelHospedagem != nullptr) {
        delwin(painelHospedagem);
    }
    
    painelHospedagem = subwin(janela, layout.altura, layout.largura,
                             layout.centralY + getbegy(janela),
                             layout.centralX + getbegx(janela));
    
    wbkgd(painelHospedagem, COLOR_PAIR(COR_PRINCIPAL));
    box(painelHospedagem, 0, 0);
    
    mvwprintw(painelHospedagem, 1, (layout.largura - 20) / 2, "Gerenciar Hospedagem");
    
    const char* opcoes[] = {
        "1. Definir hospedagem",
        "2. Visualizar hospedagem",
        "3. Editar hospedagem",
        "4. Excluir hospedagem",
        "0. Voltar"
    };
    
    for (int i = 0; i < 5; i++) {
        mvwprintw(painelHospedagem, i + 3, 3, "%s", opcoes[i]);
    }
    
    mvwprintw(painelHospedagem, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelHospedagem);
    wrefresh(janela);
}

void TelaHospedagem::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            criarHospedagem();
            break;
        case 2:
            visualizarHospedagem();
            break;
        case 3:
            editarHospedagem();
            break;
        case 4:
            excluirHospedagem();
            break;
    }
}

bool TelaHospedagem::criarHospedagem() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return false;

    // Verificar se já existe hospedagem para este destino
    if (servicoHospedagem->buscarPorDestino(codigoDestino) != nullptr) {
        mostrarAlerta("Já existe uma hospedagem cadastrada para este destino!");
        return false;
    }

    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Definir Hospedagem ===");

    try {
        std::string nome = lerInput("Nome da hospedagem: ", 3, 2);
        if (nome.empty()) return false;

        std::string diariaStr = lerInput("Valor da diaria (R$): ", 4, 2);
        if (diariaStr.empty()) return false;
        double diaria = std::stod(diariaStr);

        std::string avalStr = lerInput("Avaliacao (1-5): ", 5, 2);
        if (avalStr.empty()) return false;
        int avaliacao = std::stoi(avalStr);

        // Gerar código único para a hospedagem
        std::string baseCode = codigoDestino.getValor().substr(0, 3);
        time_t now = time(0);
        std::string timestamp = std::to_string(now % 1000);
        while (timestamp.length() < 3) timestamp = "0" + timestamp;
        std::string codigoHosp = baseCode + timestamp;

        Hospedagem novaHospedagem(
            Nome(nome),
            Codigo(codigoHosp),
            Avaliacao(avaliacao),
            Dinheiro(diaria),
            codigoDestino
        );

        if (servicoHospedagem->criarHospedagem(novaHospedagem)) {
            mostrarAlerta("Hospedagem definida com sucesso!");
            return true;
        }
        mostrarAlerta("Erro ao definir hospedagem.");
        return false;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
        return false;
    }
}

void TelaHospedagem::visualizarHospedagem() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return;

    try {
        Hospedagem* hospedagem = servicoHospedagem->buscarPorDestino(codigoDestino);
        
        if (!hospedagem) {
            mostrarAlerta("Nenhuma hospedagem encontrada para este destino.");
            return;
        }

        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Detalhes da Hospedagem ===");
        
        std::stringstream ss;
        ss << "Codigo: " << hospedagem->getCodigo().getValor() << "\n"
           << "Nome: " << hospedagem->getNome().getValor() << "\n"
           << "Diaria: R$ " << hospedagem->getDiaria().getValor() << "\n"
           << "Avaliacao: " << hospedagem->getAvaliacao().getValor();

        int linha = 3;
        std::string linha_info;
        while (std::getline(ss, linha_info, '\n')) {
            mvwprintw(janela, linha++, 2, "%s", linha_info.c_str());
        }

        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

        delete hospedagem;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaHospedagem::editarHospedagem() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return;

    try {
        Hospedagem* hospedagem = servicoHospedagem->buscarPorDestino(codigoDestino);
        
        if (!hospedagem) {
            mostrarAlerta("Nenhuma hospedagem encontrada para este destino.");
            return;
        }

        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Editar Hospedagem ===");

        std::string novoNome = lerInput("Novo nome (" + hospedagem->getNome().getValor() + "): ", 3, 2);
        if (novoNome.empty()) novoNome = hospedagem->getNome().getValor();

        std::string novaDiariaStr = lerInput("Nova diaria (R$ " + hospedagem->getDiaria().getValor() + "): ", 4, 2);
        double novaDiaria = novaDiariaStr.empty() ? 
            std::stod(hospedagem->getDiaria().getValor()) : std::stod(novaDiariaStr);

        std::string novaAvalStr = lerInput("Nova avaliacao (" + 
            std::to_string(hospedagem->getAvaliacao().getValor()) + "): ", 5, 2);
        int novaAval = novaAvalStr.empty() ? 
            hospedagem->getAvaliacao().getValor() : std::stoi(novaAvalStr);

        Hospedagem hospedagemAtualizada(
            Nome(novoNome),
            hospedagem->getCodigo(),
            Avaliacao(novaAval),
            Dinheiro(novaDiaria),
            hospedagem->getCodigoDestino()
        );

        if (servicoHospedagem->atualizarHospedagem(hospedagemAtualizada)) {
            mostrarAlerta("Hospedagem atualizada com sucesso!");
        } else {
            mostrarAlerta("Erro ao atualizar hospedagem.");
        }

        delete hospedagem;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaHospedagem::excluirHospedagem() {
    Codigo codigoDestino = selecionarDestino();
    if (codigoDestino.getValor() == "000000") return;

    try {
        Hospedagem* hospedagem = servicoHospedagem->buscarPorDestino(codigoDestino);
        
        if (!hospedagem) {
            mostrarAlerta("Nenhuma hospedagem encontrada para este destino.");
            return;
        }

        std::string confirma = lerInput("Confirma exclusao da hospedagem? (S/N): ", 3, 2);
        if (confirma == "S" || confirma == "s") {
            if (servicoHospedagem->excluirHospedagem(hospedagem->getCodigo())) {
                mostrarAlerta("Hospedagem excluida com sucesso!");
            } else {
                mostrarAlerta("Erro ao excluir hospedagem.");
            }
        }

        delete hospedagem;

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

Codigo TelaHospedagem::selecionarDestino() {
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
