#include <iostream>
#include "DeterministicFiniteAutomaton.h"
#include "FiniteAutomaton.h"
#include <vector>
#include <string>
#include <unordered_map>

#define lambda "λ"

int main() {
    /*std::vector<std::string> states({"q1", "q2", "q3"}), finalStates({"q3"});
    std::vector<std::string> symbols({"a", "b", lambda});
    std::string startState = "q1";
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> m_delta;
    std::unordered_map<std::string, std::vector<std::string>> aux;
    aux.insert({lambda, std::vector<std::string>{"q3"}});
    aux.insert({"b", std::vector<std::string>{"q1"}});
    m_delta.insert({"q1", aux});

    aux.clear();
    aux.insert({"a", std::vector<std::string>{"q3"}});
    aux.insert({"b", std::vector<std::string>{"q1"}});
    m_delta.insert({"q2", aux});

    aux.clear();
    aux.insert({"a", std::vector<std::string>{"q3"}});
    aux.insert({"b", std::vector<std::string>{"q3"}});
    m_delta.insert({"q3", aux});

    FiniteAutomaton a(states, symbols, m_delta, startState, finalStates);
    std::cout << a.VerifyAutomaton() << "\n";
    std::cout << a.CheckWord("aabb") << "\n";
    std::cout << a;*/
    DeterministicFiniteAutomaton a;
    a.ConvertFromRegex("a.(a|b)*");

    return 0;
}
