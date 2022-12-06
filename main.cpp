#include <iostream>
#include "DeterministicFiniteAutomaton.h"
#include <vector>
#include <string>
#include <unordered_map>

int main() {
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

    return 0;
}
