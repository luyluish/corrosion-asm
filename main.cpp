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
    std::ifstream arquivo(argv[1]);
    if (!arquivo) {
        std::cerr << "n da pra abrir \n";
        return 1;
    }

    // Validação do conteúdo (não deve estar vazio)
    if (arquivo.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "arquivo vazio\n";
        return 1;
    }

    // Validação do formato da entrada (deve ser um inteiro contendo só caracteres númericos)
    std::string conteudo;
    arquivo >> conteudo;

    for (char c : conteudo) {
        if (c < '0' || c > '9') {
            std::cerr << "nao e um inteiro\n";
            return 1;
        }
    }

    // Validação do tamanho da entrada (deve conter até 64-bits)
    uint64_t valor;

    if (overflowInt64(conteudo)) {
        std::cerr << "estorou 64-bits\n";
        return 1;
    } else {
        valor = std::stoull(conteudo);
    }
}
