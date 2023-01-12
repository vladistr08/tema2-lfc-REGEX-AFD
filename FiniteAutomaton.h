//
// Created by istra on 11/5/22.
//

#ifndef LFC_TEMA1_FINITEAUTOMATON_H
#define LFC_TEMA1_FINITEAUTOMATON_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "UsefulMethods.h"
#include "cpp-text-table-master/TextTable.h"

#define lambda "λ"

class FiniteAutomaton {
public:
    FiniteAutomaton() = default;
    FiniteAutomaton(const FiniteAutomaton &automaton) = default;
    FiniteAutomaton(std::vector<std::string> states, std::vector<std::string> symbols, std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta, std::string startState, std::vector<std::string> finalStates);

    const std::vector<std::string> &getMStates() const;
    void setMStates(const std::vector<std::string> &mStates);

    const std::vector<std::string> &getMFinalStates() const;
    void setMFinalStates(const std::vector<std::string> &mFinalStates);

    const std::vector<std::string> &getMSymbols() const;
    void setMSymbols(const std::vector<std::string> &mSymbols);

    const std::string &getMStartState() const;
    void setMStartState(const std::string &mStartState);

    const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> &getMDelta() const;
    void setMDelta(const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> &mDelta);

    bool VerifyAutomaton() const;
    void PrintAutomaton() const;
    bool CheckWord(const std::string &word);
    bool IsDeterministic();

    friend std::ostream& operator<<(std::ostream &out, const FiniteAutomaton &automaton);
    FiniteAutomaton& operator=(const FiniteAutomaton &f) = default;
    ~FiniteAutomaton() = default;
private:
    std::vector<std::string> findLambdaClosure(const std::string &currentState);
    std::vector<std::string> generateStatesForSymbol(const std::string &symbol, const std::vector<std::string> &posibleStates);
    static std::vector<std::string> unionVector(std::vector<std::string> v1, std::vector<std::string> v2);
protected:
    std::vector<std::string> m_states, m_finalStates;
    std::vector<std::string> m_symbols;
    std::string m_startState;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> m_delta;
};


#endif //LFC_TEMA1_FINITEAUTOMATON_H
