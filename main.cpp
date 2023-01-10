#include <iostream>
#include "DeterministicFiniteAutomaton.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

int main() {
    /*std::fstream f("expresii_regulate.txt");
    std::vector<std::string> states({"q1", "q2", "q3"}), finalStates({"q3"});
    std::vector<std::string> symbols({"a", "b"});
    std::string startState = "q1";
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_delta;
    std::unordered_map<std::string, std::string> aux;
    aux.insert({"a", "q2"});
    aux.insert({"b", "q1"});
    m_delta.insert({"q1", aux});

    aux.clear();
    aux.insert({"a", "q3"});
    aux.insert({"b", "q1"});
    m_delta.insert({"q2", aux});

    aux.clear();
    aux.insert({"a", "q3"});
    aux.insert({"b", "q3"});
    m_delta.insert({"q3", aux});

    DeterministicFiniteAutomaton a(states, symbols, m_delta, startState, finalStates);
    std::cout << a.VerifyAutomaton() << "\n";
    std::cout << a.CheckWord("aabb") << "\n";
    std::cout << a;
    std::string word;
    int options = 0;
    do {
        std::cout
                << "1- Afisarea automatului M \n 2-Afisarea inteligibil  a expresiei regulte r din fisier \n 3- verificarea unui cuvânt în automat. 0- EXIT\n";
        std::cout << "Alegeti optiunea: ";
        std::cin >> options;
        switch (options) {
            case 1:
                a.PrintAutomaton();
                break;
            case 2:
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
     */
    DeterministicFiniteAutomaton a;
    a.ConvertFromRegex("a.b");
    return 0;
}