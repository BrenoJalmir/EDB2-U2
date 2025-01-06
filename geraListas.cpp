#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

void generateRandomList(int size, const std::string& filename) {
    // Configura o gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000);

    // Cria e preenche a lista com números aleatórios
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << "!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        int randomNumber = dis(gen);
        file << randomNumber << "\n";
    }

    file.close();
    std::cout << "Lista de tamanho " << size << " salva no arquivo " << filename << std::endl;
}

int main() {
    // Tamanhos das listas
    std::vector<int> sizes = {10000, 100000, 1000000};
    // Nomes dos arquivos
    std::vector<std::string> filenames = {"lista_10000.txt", "lista_100000.txt", "lista_1000000.txt"};

    // Gera as listas e salva em arquivos
    for (size_t i = 0; i < sizes.size(); ++i) {
        generateRandomList(sizes[i], filenames[i]);
    }

    return 0;
}