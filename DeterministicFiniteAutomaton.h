//
// Created by istra on 12/6/22.
//

#ifndef TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H
#define TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include "cpp-text-table-master/TextTable.h"

class DeterministicFiniteAutomaton {
public:
    DeterministicFiniteAutomaton() = default;
    DeterministicFiniteAutomaton(const DeterministicFiniteAutomaton &automaton) = default;
    DeterministicFiniteAutomaton(std::vector<std::string> states, std::vector<std::string> symbols, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta, std::string startState, std::vector<std::string> finalStates);

    bool VerifyAutomaton() const;
    void PrintAutomaton() const;
    bool IsDeterministic() const;
    bool CheckWord(const std::string &word);

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

    DeterministicFiniteAutomaton ConvertFromRegex(const std::string &regex);

    friend std::ostream& operator<<(std::ostream &out, const DeterministicFiniteAutomaton &automaton);
    DeterministicFiniteAutomaton& operator=(const DeterministicFiniteAutomaton &f) = default;
    ~DeterministicFiniteAutomaton() = default;

protected:
    std::vector<std::string> m_states, m_finalStates;
    std::vector<std::string> m_symbols;
    std::string m_startState;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_delta;
};


#endif //TEMA2_LFC_REGEX_AFD_DETERMINISTICFINITEAUTOMATON_H
