#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

// Função auxiliar para checar se a entrada estoura o limite de 64-bits
bool overflowInt64(const std::string& s){
    const std::string max = "18446744073709551615";

    if (s.length() > max.length()) {
        return true;
    }
    if (s.length() < max.length()) {
        return false;
    }

    return s > max;
}

int main(int argc, char* argv[]) {
    // Abertura do arquivo CI de entrada
    std::string argumentoEntrada = argv[1];
    if (argumentoEntrada.empty()) {
        std::cerr << "Erro de execucao. Formato: ./main.cpp [numero]";
    }

    std::ifstream arquivo(argumentoEntrada);
    if (!arquivo) {
        std::cerr << "Nao foi possivel abrir o arquivo especificado.\n";
        return 1;
    }

    // Validação do conteúdo (não deve estar vazio)
    if (arquivo.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "\n";
        return 1;
    }

    // Validação do formato da entrada (deve ser um inteiro contendo só caracteres númericos)
    std::string conteudo;
    arquivo >> conteudo;

    for (char c : conteudo) {
        if (c < '0' || c > '9') {
            std::cerr << "O arquivo de entrada nao eh um literal inteiro.\n";
            return 1;
        }
    }

    // Validação do tamanho da entrada (deve conter até 64-bits)
    uint64_t valor;

    if (overflowInt64(conteudo)) {
        std::cerr << "O literal inteiro estorou o limite de 64-bits.\n";
        return 1;
    } else {
        valor = std::stoull(conteudo);
    }

    // Criação do arquivo de saída
    argumentoEntrada.erase(argumentoEntrada.length() - 3);

    // Saida
    std::ofstream saida(argumentoEntrada + ".s");
    saida << " .section .text\n";
    saida << " .globl _start\n";
    saida << "_start:\n";
    saida << " mov $" << valor << ", %rax\n";
    saida << "\n";
    saida << " call imprime_num\n";
    saida << " call sair\n";
    saida << "\n";
    saida << " .include \"runtime.s\"";

    saida.close();

    std::cout << "Compilacao finalizada.\n";

}
