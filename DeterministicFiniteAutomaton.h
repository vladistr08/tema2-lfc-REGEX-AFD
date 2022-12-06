//
// Created by istra on 12/6/22.
//

#ifndef TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H
#define TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H

#include <string>
#include <unordered_map>
#include <vector>

class DeterministicFiniteAutomaton {
public:
    DeterministicFiniteAutomaton() = default;
    DeterministicFiniteAutomaton(const DeterministicFiniteAutomaton &automaton) = default;
    DeterministicFiniteAutomaton(std::vector<std::string> states, std::vector<std::string> symbols, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta, std::string startState, std::vector<std::string> finalStates);

    const std::vector<std::string> &getMStates() const;
    void setMStates(const std::vector<std::string> &mStates);

    const std::vector<std::string> &getMFinalStates() const;
    void setMFinalStates(const std::vector<std::string> &mFinalStates);

    const std::vector<std::string> &getMSymbols() const;
    void setMSymbols(const std::vector<std::string> &mSymbols);

    const std::string &getMStartState() const;
    void setMStartState(const std::string &mStartState);

    const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &getMDelta() const;
    void setMDelta(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &mDelta);

protected:
    std::vector<std::string> m_states, m_finalStates;
    std::vector<std::string> m_symbols;
    std::string m_startState;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_delta;
};


#endif //TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H
