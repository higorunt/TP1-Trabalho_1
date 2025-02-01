#include "../../include/telas/TelaViagem.hpp"
#include <iomanip>
#include <sstream>



void TelaViagem::mostrar() {
    limparTela();
    desenharMenu();
    
    while (true) {
        int ch = wgetch(janela);
        
        if (ch == '0') break;
        
        if (ch >= '1' && ch <= '5') {
            processarOpcao(ch - '0');
            limparTela();
            desenharMenu();
        }
    }
}

void TelaViagem::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Calcular posições
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelViagem != nullptr) {
        delwin(painelViagem);
    }
    
    painelViagem = subwin(janela, layout.altura, layout.largura,
                         layout.centralY + getbegy(janela),
                         layout.centralX + getbegx(janela));
    
    wbkgd(painelViagem, COLOR_PAIR(COR_PRINCIPAL));
    box(painelViagem, 0, 0);
    
    mvwprintw(painelViagem, 1, (layout.largura - 16) / 2, "Gerenciar Viagens");
    
    const char* opcoes[] = {
        "1. Criar nova viagem",
        "2. Listar minhas viagens",
        "3. Editar viagem",
        "4. Excluir viagem",
        "5. Calcular custo da viagem",
        "0. Voltar"
    };
    
    for (int i = 0; i < 6; i++) {
        mvwprintw(painelViagem, i + 3, 3, "%s", opcoes[i]);
    }
    
    mvwprintw(painelViagem, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelViagem);
    wrefresh(janela);
}

void TelaViagem::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            criarViagem();
            break;
        case 2:
            listarViagens();
            break;
        case 3:
            editarViagem();
            break;
        case 4:
            excluirViagem();
            break;
        case 5:
            calcularCustoViagem();
            break;
    }
}

void TelaViagem::criarViagem() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    keypad(janela, TRUE);
    noecho();
    
    while (true) {
        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Criar Nova Viagem ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string nome = lerInput("Nome da viagem: ", 3, 2);
        if (nome.empty()) return;

        std::string codigoBase = viajante->getConta().getCodigo().getValor();
        time_t now = time(0);
        std::string timestamp = std::to_string(now % 1000);
        while (timestamp.length() < 3) timestamp = "0" + timestamp;
        std::string codigoViagem = codigoBase.substr(0, 3) + timestamp;

        werase(janela);
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Criar Nova Viagem ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string avalStr = lerInput("Avaliacao (1-5): ", 3, 2);
        if (avalStr.empty()) return;

        try {
            int avaliacao = std::stoi(avalStr);
            Nome nomeViagem(nome);
            Codigo codViagem(codigoViagem);
            Avaliacao avaliacaoViagem(avaliacao);

            Viagem novaViagem(nomeViagem, codViagem, avaliacaoViagem, viajante->getConta());
            
            if (servico->criarViagem(novaViagem)) {
                mostrarAlerta("Viagem criada com sucesso!");
                return;
            } else {
                mostrarAlerta("Erro ao criar viagem.");
            }
        } catch (const std::invalid_argument& e) {
            mostrarAlerta(e.what());
        }
    }
}

void TelaViagem::listarViagens() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Minhas Viagens ===");
    wrefresh(janela);

    try {
        Codigo codigoViajante = viajante->getConta().getCodigo();
        std::vector<Viagem> viagens = servico->listarViagensPorViajante(codigoViajante);

        if (viagens.empty()) {
            mostrarAlerta("Nenhuma viagem encontrada.");
            return;
        }

        int linha = 4;
        for (const auto& viagem : viagens) {
            std::string infoStr = "Viagem: " + viagem.getNome().getValor() + 
                                " | Codigo: " + viagem.getCodigo().getValor() +
                                " | Avaliacao: " + std::to_string(viagem.getAvaliacao().getValor());
            
            mvwprintw(janela, linha++, 2, "%s", infoStr.c_str());
        }

        mvwprintw(janela, linha + 1, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaViagem::editarViagem() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    keypad(janela, TRUE);
    noecho();
    
    while (true) {
        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Editar Viagem ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string codigo = lerInput("Digite o codigo da viagem: ", 3, 2);
        if (codigo.empty()) return;

        try {
            Codigo codigoViagem(codigo);
            Viagem* viagem = servico->buscarViagem(codigoViagem);
            
            if (!viagem) {
                mostrarAlerta("Viagem nao encontrada.");
                continue;
            }

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Viagem ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            std::string prompt = "Novo nome (" + viagem->getNome().getValor() + "): ";
            std::string novoNome = lerInput(prompt, 3, 2);
            if (novoNome.empty()) novoNome = viagem->getNome().getValor();

            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Editar Viagem ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            prompt = "Nova avaliacao (" + std::to_string(viagem->getAvaliacao().getValor()) + "): ";
            std::string novaAvalStr = lerInput(prompt, 3, 2);
            if (novaAvalStr.empty()) novaAvalStr = std::to_string(viagem->getAvaliacao().getValor());

            try {
                Nome nome(novoNome);
                Avaliacao avaliacao(std::stoi(novaAvalStr));

                Viagem viagemAtualizada = *viagem;
                viagemAtualizada.setNome(nome);
                viagemAtualizada.setAvaliacao(avaliacao);

                if (servico->atualizarViagem(viagemAtualizada)) {
                    mostrarAlerta("Viagem atualizada com sucesso!");
                    delete viagem;
                    return;
                } else {
                    mostrarAlerta("Erro ao atualizar viagem.");
                }
            } catch (const std::invalid_argument& e) {
                mostrarAlerta(e.what());
            }

            delete viagem;
        } catch (const std::exception& e) {
            mostrarAlerta(e.what());
        }
    }
}

void TelaViagem::excluirViagem() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    keypad(janela, TRUE);
    noecho();
    
    while (true) {
        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Excluir Viagem ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string codigo = lerInput("Digite o codigo da viagem: ", 3, 2);
        if (codigo.empty()) return;

        try {
            Codigo codigoViagem(codigo);
            
            werase(janela);
            box(janela, 0, 0);
            mvwprintw(janela, 1, 2, "=== Excluir Viagem ===");
            mvwprintw(janela, altura - 2, 2, "ESC para voltar");
            wrefresh(janela);

            std::string confirma = lerInput("Tem certeza? (S/N): ", 3, 2);
            if (confirma.empty()) return;

            if (confirma == "S" || confirma == "s") {
                if (servico->excluirViagem(codigoViagem)) {
                    mostrarAlerta("Viagem excluida com sucesso!");
                    return;
                } else {
                    mostrarAlerta("Erro ao excluir viagem.");
                }
            }
            return;
        } catch (const std::exception& e) {
            mostrarAlerta(e.what());
        }
    }
}

void TelaViagem::calcularCustoViagem() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    keypad(janela, TRUE);
    noecho();
    
    while (true) {
        limparTela();
        box(janela, 0, 0);
        mvwprintw(janela, 1, 2, "=== Calcular Custo da Viagem ===");
        mvwprintw(janela, altura - 2, 2, "ESC para voltar");
        wrefresh(janela);

        std::string codigo = lerInput("Digite o codigo da viagem: ", 3, 2);
        if (codigo.empty()) return;

        try {
            Codigo codigoViagem(codigo);
            double custoTotal = servico->calcularCustoViagem(codigoViagem);
            
            std::stringstream ss;
            ss << "Custo total: R$ " << std::fixed << std::setprecision(2) << custoTotal;
            mostrarAlerta(ss.str());
            return;
        } catch (const std::exception& e) {
            mostrarAlerta(e.what());
        }
    }
}