#include <iostream>
#include <string>
#include <fstream>

#include "DeterministicFiniteAutomaton.h"
#include "FiniteAutomaton.h"
#include "UsefulMethods.h"

int main() {
    std::fstream f("/home/istra/CLionProjects/lfc-tema2/tema2-lfc-REGEX-AFD/expresii_regulate.txt");

    std::string regex;
    f >> regex;

    f.close();

    if(!UsefulMethods::isValidRegex(regex)){
        std::cout << "Regex from file was not correct, try again!\n";
        return 0;
    }

    DeterministicFiniteAutomaton b;
    FiniteAutomaton a = b.ConvertFromRegex(regex);

    std::string word;
    int options = 0;
    do {
        std::cout
                << "1 - Afisarea automatului M \n2 - Afisarea inteligibil  a expresiei regulte r din fisier \n3 - Verificarea unui cuvânt în automat.\n0 - EXIT\n";
        std::cout << "Alegeti optiunea: ";
        std::cin >> options;
        switch (options) {
            case 1:
                a.PrintAutomaton();
                break;
            case 2:
                std::cout << regex << '\n';
                break;
            case 3:
                std::cout << "Cititi un cuvant: ";
                std::cin >> word;
                if (a.CheckWord(word))
                    std::cout << "Cuvantul este acceptat de automatul obtinut.\n";
                else
                    std::cout << "Cuvantul NU este acceptat de automatul obtinut.\n";
                std::cout << '\n';
                break;
            default:
                break;
        }
    } while (options != 0);

    return 0;
}