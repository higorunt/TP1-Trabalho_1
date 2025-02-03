#include "../../include/telas/TelaRelatorios.hpp"
#include <iomanip>
#include <sstream>

void TelaRelatorios::mostrar() {
    limparTela();
    desenharMenu();
    
    while (true) {
        int ch = wgetch(janela);
        if (ch == '0') break;
        if (ch >= '1' && ch <= '6') {
            processarOpcao(ch - '0');
            limparTela();
            desenharMenu();
        }
    }
}

void TelaRelatorios::desenharMenu() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    layout.centralY = (altura - layout.altura) / 2;
    layout.centralX = (largura - layout.largura) / 2;
    
    if (painelRelatorios != nullptr) {
        delwin(painelRelatorios);
    }
    
    painelRelatorios = subwin(janela, layout.altura, layout.largura,
                             layout.centralY + getbegy(janela),
                             layout.centralX + getbegx(janela));
    
    wbkgd(painelRelatorios, COLOR_PAIR(COR_PRINCIPAL));
    box(painelRelatorios, 0, 0);
    
    mvwprintw(painelRelatorios, 1, (layout.largura - 22) / 2, "%s", 
              converterParaCP850("=== Menu de Relatorios ===").c_str());
    
    const char* opcoes[] = {
        "1. Resumo Geral de Custos",
        "2. Minhas Viagens",
        "3. Detalhes de Viagem",
        "4. Relatorio de Destino",
        "5. Relatorio de Atividades",
        "6. Relatorio de Hospedagens",
        "0. Voltar"
    };
    
    for (int i = 0; i < 7; i++) {
        mvwprintw(painelRelatorios, i + 3, 3, "%s", converterParaCP850(opcoes[i]).c_str());
    }
    
    mvwprintw(painelRelatorios, layout.altura - 2, 2, "Digite o numero da opcao desejada");
    
    wrefresh(painelRelatorios);
    wrefresh(janela);
}

void TelaRelatorios::detalhesViagem() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio de Custos por Viagem ===");

    try {
        std::string codigo = lerInput("Digite o codigo da viagem: ", 3, 2);
        if (codigo.empty()) return;

        Codigo codigoViagem(codigo);
        Viagem* viagem = servicoViagem->buscarViagem(codigoViagem);
        
        if (!viagem) {
            mostrarAlerta("Viagem nao encontrada.");
            return;
        }

        std::vector<Destino> destinos = servicoDestino->listarPorViagem(codigoViagem);
        double custoTotal = servicoViagem->calcularCustoViagem(codigoViagem);

        int linha = 3;
        mvwprintw(janela, linha++, 2, "Viagem: %s", viagem->getNome().getValor().c_str());
        mvwprintw(janela, linha++, 2, "Codigo: %s", viagem->getCodigo().getValor().c_str());
        linha++;

        mvwprintw(janela, linha++, 2, "=== Destinos ===");
        for (const auto& destino : destinos) {
            exibirDetalhesDestino(destino);
            linha += 3;
        }

        mvwprintw(janela, linha + 2, 2, "Custo Total da Viagem: R$ %.2f", custoTotal);
        
        delete viagem;
        
        mvwprintw(janela, linha + 4, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::exibirDetalhesDestino(const Destino& destino) {
    int linha = 3;
    mvwprintw(janela, linha++, 2, "Destino: %s", destino.getNome().getValor().c_str());
    mvwprintw(janela, linha++, 2, "Codigo: %s", destino.getCodigo().getValor().c_str());
    mvwprintw(janela, linha++, 2, "Periodo: %s a %s", 
             destino.getDataInicio().getValor().c_str(),
             destino.getDataFim().getValor().c_str());
    linha++;

    // Listar atividades
    std::vector<Atividade> atividades = servicoAtividade->listarPorDestino(destino.getCodigo());
    if (!atividades.empty()) {
        mvwprintw(janela, linha++, 2, "Atividades:");
        double custoAtividades = 0.0;
        
        for (const auto& ativ : atividades) {
            mvwprintw(janela, linha++, 4, "- %s: R$ %s", 
                     ativ.getNome().getValor().c_str(),
                     ativ.getPreco().getValor().c_str());
            custoAtividades += std::stod(ativ.getPreco().getValor());
        }
        
        mvwprintw(janela, linha++, 4, "Total Atividades: R$ %.2f", custoAtividades);
    }
    linha++;

    // Buscar hospedagem
    Hospedagem* hosp = servicoHospedagem->buscarPorDestino(destino.getCodigo());
    if (hosp) {
        mvwprintw(janela, linha++, 2, "Hospedagem:");
        mvwprintw(janela, linha++, 4, "- %s: R$ %s/dia", 
                 hosp->getNome().getValor().c_str(),
                 hosp->getDiaria().getValor().c_str());
        
        // Calcular total de dias
        tm tmInicio = {}, tmFim = {};
        std::string dataInicio = destino.getDataInicio().getValor();
        std::string dataFim = destino.getDataFim().getValor();
        
        tmInicio.tm_mday = std::stoi(dataInicio.substr(0, 2));
        tmInicio.tm_mon = std::stoi(dataInicio.substr(3, 2)) - 1;
        tmInicio.tm_year = std::stoi(dataInicio.substr(6, 2)) + 2000 - 1900;
        
        tmFim.tm_mday = std::stoi(dataFim.substr(0, 2));
        tmFim.tm_mon = std::stoi(dataFim.substr(3, 2)) - 1;
        tmFim.tm_year = std::stoi(dataFim.substr(6, 2)) + 2000 - 1900;
        
        time_t t1 = mktime(&tmInicio);
        time_t t2 = mktime(&tmFim);
        
        int dias = (int)((difftime(t2, t1) / (60 * 60 * 24)) + 1);
        double custoHospedagem = std::stod(hosp->getDiaria().getValor()) * dias;
        
        mvwprintw(janela, linha++, 4, "Total Hospedagem (%d dias): R$ %.2f", 
                 dias, custoHospedagem);
        
        delete hosp;
    }
}

void TelaRelatorios::processarOpcao(int opcao) {
    switch (opcao) {
        case 1:
            resumoGeralCustos();
            break;
        case 2:
            listarMinhasViagens();
            break;
        case 3:
            detalhesViagem();
            break;
        case 4:
            relatorioDestino();
            break;
        case 5:
            relatorioAtividades();
            break;
        case 6:
            relatorioHospedagens();
            break;
    }
}

void TelaRelatorios::resumoGeralCustos() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Resumo Geral de Custos ===");

    try {
        std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
        if (viagens.empty()) {
            mostrarAlerta("Nenhuma viagem encontrada.");
            return;
        }

        double custoTotalGeral = 0.0;
        int linha = 3;

        mvwprintw(janela, linha++, 2, "Viajante: %s", viajante->getNome().getValor().c_str());
        linha++;

        for (const auto& viagem : viagens) {
            double custoViagem = servicoViagem->calcularCustoViagem(viagem.getCodigo());
            custoTotalGeral += custoViagem;

            // Substituindo caracteres especiais por ASCII
            mvwprintw(janela, linha++, 2, "----------------------------------------------");
            mvwprintw(janela, linha++, 2, "| Viagem: %s", converterParaCP850(viagem.getNome().getValor()).c_str());
            mvwprintw(janela, linha++, 2, "| Codigo: %s", viagem.getCodigo().getValor().c_str());
            mvwprintw(janela, linha++, 2, "| Custo Total: R$ %.2f", custoViagem);
            mvwprintw(janela, linha++, 2, "----------------------------------------------");
            linha++;
        }

        mvwprintw(janela, linha++, 2, "----------------------------------------------");
        mvwprintw(janela, linha++, 2, "TOTAL GERAL: R$ %.2f", custoTotalGeral);
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::relatorioDestino() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio por Destino ===");

    try {
        std::string codigoStr = lerInput("Digite o codigo do destino: ", 3, 2);
        if (codigoStr.empty()) return;

        Codigo codigoDestino(codigoStr);
        Destino* destino = servicoDestino->buscarDestino(codigoDestino);
        
        if (!destino) {
            mostrarAlerta("Destino nao encontrado.");
            return;
        }

        int linha = 3;
        exibirDetalhesDestino(*destino);
        
        delete destino;
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::listarMinhasViagens() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Minhas Viagens ===");

    try {
        std::vector<Viagem> viagens = servicoViagem->listarViagensPorViajante(viajante->getConta().getCodigo());
        if (viagens.empty()) {
            mostrarAlerta("Nenhuma viagem encontrada.");
            return;
        }

        int linha = 3;
        for (const auto& viagem : viagens) {
            mvwprintw(janela, linha++, 2, "-------------------------------");
            mvwprintw(janela, linha++, 2, "| Nome: %s", viagem.getNome().getValor().c_str());
            mvwprintw(janela, linha++, 2, "| Codigo: %s", viagem.getCodigo().getValor().c_str());
            mvwprintw(janela, linha++, 2, "| Avaliacao: %d", viagem.getAvaliacao().getValor());
            
            double custoViagem = servicoViagem->calcularCustoViagem(viagem.getCodigo());
            mvwprintw(janela, linha++, 2, "| Custo Total: R$ %.2f", custoViagem);
            mvwprintw(janela, linha++, 2, "-------------------------------");
            linha++;
        }

        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::relatorioAtividades() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio de Atividades ===");

    try {
        std::string codigoStr = lerInput("Digite o codigo do destino: ", 3, 2);
        if (codigoStr.empty()) return;

        Codigo codigoDestino(codigoStr);
        Destino* destino = servicoDestino->buscarDestino(codigoDestino);
        
        if (!destino) {
            mostrarAlerta("Destino nao encontrado.");
            return;
        }

        std::vector<Atividade> atividades = servicoAtividade->listarPorDestino(codigoDestino);
        if (atividades.empty()) {
            mostrarAlerta("Nenhuma atividade encontrada para este destino.");
            return;
        }

        int linha = 5;
        double custoTotal = 0.0;

        mvwprintw(janela, linha++, 2, "Destino: %s", destino->getNome().getValor().c_str());
        mvwprintw(janela, linha++, 2, "Periodo: %s a %s", 
                 destino->getDataInicio().getValor().c_str(),
                 destino->getDataFim().getValor().c_str());
        linha++;

        // Usando ASCII puro para separadores
        mvwprintw(janela, linha++, 2, "----------------------------------------------");
        for (const auto& ativ : atividades) {
            mvwprintw(janela, linha++, 2, "| %s", ativ.getNome().getValor().c_str());
            mvwprintw(janela, linha++, 2, "|   Data: %s as %s", 
                     ativ.getData().getValor().c_str(),
                     ativ.getHorario().getValor().c_str());
            mvwprintw(janela, linha++, 2, "|   Duracao: %d minutos", 
                     ativ.getDuracao().getValor());
            mvwprintw(janela, linha++, 2, "|   Preco: R$ %s", 
                     ativ.getPreco().getValor().c_str());
            mvwprintw(janela, linha++, 2, "|   Avaliacao: %d/5", 
                     ativ.getAvaliacao().getValor());
            mvwprintw(janela, linha++, 2, "----------------------------------------------");

            custoTotal += std::stod(ativ.getPreco().getValor());
        }
        mvwprintw(janela, linha++, 2, "| Custo Total das Atividades: R$ %.2f", custoTotal);
        mvwprintw(janela, linha++, 2, "----------------------------------------------");

        delete destino;
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

void TelaRelatorios::relatorioHospedagens() {
    limparTela();
    box(janela, 0, 0);
    mvwprintw(janela, 1, 2, "=== Relatorio de Hospedagens ===");

    try {
        std::string codigoStr = lerInput("Digite o codigo do destino: ", 3, 2);
        if (codigoStr.empty()) return;

        Codigo codigoDestino(codigoStr);
        Destino* destino = servicoDestino->buscarDestino(codigoDestino);
        
        if (!destino) {
            mostrarAlerta("Destino nao encontrado.");
            return;
        }

        Hospedagem* hosp = servicoHospedagem->buscarPorDestino(codigoDestino);
        if (!hosp) {
            mostrarAlerta("Nenhuma hospedagem encontrada para este destino.");
            return;
        }

        int linha = 5;
        mvwprintw(janela, linha++, 2, "Destino: %s", destino->getNome().getValor().c_str());
        mvwprintw(janela, linha++, 2, "Periodo: %s a %s", 
                 destino->getDataInicio().getValor().c_str(),
                 destino->getDataFim().getValor().c_str());
        linha++;

        int dias = calcularDias(destino->getDataInicio().getValor(), destino->getDataFim().getValor());
        double custoTotal = std::stod(hosp->getDiaria().getValor()) * dias;

        mvwprintw(janela, linha++, 2, "----------------------------------------------");
        mvwprintw(janela, linha++, 2, "| Hospedagem: %s", hosp->getNome().getValor().c_str());
        mvwprintw(janela, linha++, 2, "| Diaria: R$ %s", hosp->getDiaria().getValor().c_str());
        mvwprintw(janela, linha++, 2, "| Avaliacao: %d/5", hosp->getAvaliacao().getValor());
        mvwprintw(janela, linha++, 2, "|");
        mvwprintw(janela, linha++, 2, "| Periodo total: %d dias", dias);
        mvwprintw(janela, linha++, 2, "| Custo total: R$ %.2f", custoTotal);
        mvwprintw(janela, linha++, 2, "----------------------------------------------");

        delete destino;
        delete hosp;
        
        mvwprintw(janela, linha + 2, 2, "Pressione qualquer tecla para continuar...");
        wrefresh(janela);
        wgetch(janela);

    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
    }
}

// Metodo auxiliar para calcular dias entre datas
int TelaRelatorios::calcularDias(const std::string& dataInicio, const std::string& dataFim) {
    tm tmInicio = {}, tmFim = {};
    
    tmInicio.tm_mday = std::stoi(dataInicio.substr(0, 2));
    tmInicio.tm_mon = std::stoi(dataInicio.substr(3, 2)) - 1;
    tmInicio.tm_year = std::stoi(dataInicio.substr(6, 2)) + 2000 - 1900;
    
    tmFim.tm_mday = std::stoi(dataFim.substr(0, 2));
    tmFim.tm_mon = std::stoi(dataFim.substr(3, 2)) - 1;
    tmFim.tm_year = std::stoi(dataFim.substr(6, 2)) + 2000 - 1900;
    
    time_t t1 = mktime(&tmInicio);
    time_t t2 = mktime(&tmFim);
    
    return (int)((difftime(t2, t1) / (60 * 60 * 24)) + 1);
}
