#include "../../include/telas/TelaCadastro.hpp"

TelaCadastro::TelaCadastro(ServicoAutenticacao* srv) 
    : servico(srv), modalCadastro(nullptr) {
}

TelaCadastro::~TelaCadastro() {
    if (modalCadastro != nullptr) {
        delwin(modalCadastro);
        modalCadastro = nullptr;
    }
}

void TelaCadastro::desenharModal() {
    int altura, largura;
    getmaxyx(janela, altura, largura);
    
    // Dimensões do modal
    int modalAltura = 12;
    int modalLargura = 60;
    int modalY = (altura - modalAltura) / 2;
    int modalX = (largura - modalLargura) / 2;
    
    // Criar janela do modal
    if (modalCadastro != nullptr) {
        delwin(modalCadastro);
    }
    
    modalCadastro = newwin(modalAltura, modalLargura,
                          modalY + getbegy(janela),
                          modalX + getbegx(janela));
                          
    // Configurar cores e borda
    wbkgd(modalCadastro, COLOR_PAIR(COR_INVERSA));
    box(modalCadastro, 0, 0);
    
    // Título
    std::string titulo = "Criar Nova Conta";
    mvwprintw(modalCadastro, 1, (modalLargura - titulo.length()) / 2, "%s", titulo.c_str());
    
    // Campos
    mvwprintw(modalCadastro, 3, 2, "Nome:   ");
    mvwaddch(modalCadastro, 3, 10, '[');
    mvwhline(modalCadastro, 3, 11, ' ', TAM_MAX_NOME);
    mvwaddch(modalCadastro, 3, 11 + TAM_MAX_NOME, ']');
    
    mvwprintw(modalCadastro, 5, 2, "Codigo: ");
    mvwaddch(modalCadastro, 5, 10, '[');
    mvwhline(modalCadastro, 5, 11, ' ', TAM_MAX_CODIGO);
    mvwaddch(modalCadastro, 5, 11 + TAM_MAX_CODIGO, ']');
    
    mvwprintw(modalCadastro, 7, 2, "Senha:  ");
    mvwaddch(modalCadastro, 7, 10, '[');
    mvwhline(modalCadastro, 7, 11, ' ', TAM_MAX_SENHA);
    mvwaddch(modalCadastro, 7, 11 + TAM_MAX_SENHA, ']');
    
    // Instruções
    mvwprintw(modalCadastro, modalAltura - 2, 2, "ESC = Cancelar | ENTER = Confirmar");
    
    wrefresh(modalCadastro);
}

void TelaCadastro::mostrar() {
    limparTela();
    desenharModal();
}

bool TelaCadastro::processarCadastro() {
    // Ler nome
    wmove(modalCadastro, 3, 11);
    std::string nomeStr = campoTexto(modalCadastro, 3, 11, TAM_MAX_NOME);
    if (nomeStr.empty()) return false;
    
    // Ler código
    wmove(modalCadastro, 5, 11);
    std::string codigoStr = campoTexto(modalCadastro, 5, 11, TAM_MAX_CODIGO);
    if (codigoStr.empty()) return false;
    
    // Ler senha
    wmove(modalCadastro, 7, 11);
    std::string senhaStr = campoTexto(modalCadastro, 7, 11, TAM_MAX_SENHA, true);
    if (senhaStr.empty()) return false;
    
    try {
        Nome nome(nomeStr);
        Codigo codigo(codigoStr);
        Senha senha(senhaStr);
        
        Conta conta(codigo, senha);
        Viajante viajante(nome, conta);
        
        if (servico->cadastrar(viajante)) {
            mostrarAlerta("Conta criada com sucesso!");
            return true;
        } else {
            mostrarAlerta("Erro ao criar conta!");
            return false;
        }
    } catch (const std::exception& e) {
        mostrarAlerta(e.what());
        return false;
    }
}

bool TelaCadastro::executar() {
    mostrar();
    return processarCadastro();
}