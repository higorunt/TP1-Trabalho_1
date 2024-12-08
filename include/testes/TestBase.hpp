#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <iostream>
#include <stdexcept>

class TestBase {
protected:
    int estado;
    virtual void setUp() = 0;    
    virtual void tearDown() = 0; 
    virtual void rodarTestes() = 0; 

public:
    const static int SUCESSO = 0; 
    const static int FALHA = -1;  

    int run() {
        setUp();                
        try {
            rodarTestes();      
            estado = SUCESSO;   
        } catch (std::exception& e) {
            std::cerr << "Erro: " << e.what() << std::endl;
            estado = FALHA;     
        }
        tearDown();             
        return estado;          
    }
};

#endif // TEST_BASE_H
