//
// Created by istra on 12/6/22.
//

#include "DeterministicFiniteAutomaton.h"
#include <utility>

const std::vector<std::string> &DeterministicFiniteAutomaton::getMStates() const {
    return m_states;
}

void DeterministicFiniteAutomaton::setMStates(const std::vector<std::string> &mStates) {
    m_states = mStates;
}

const std::vector<std::string> &DeterministicFiniteAutomaton::getMFinalStates() const {
    return m_finalStates;
}

void DeterministicFiniteAutomaton::setMFinalStates(const std::vector<std::string> &mFinalStates) {
    m_finalStates = mFinalStates;
}

const std::vector<std::string> &DeterministicFiniteAutomaton::getMSymbols() const {
    return m_symbols;
}

void DeterministicFiniteAutomaton::setMSymbols(const std::vector<std::string> &mSymbols) {
    m_symbols = mSymbols;
}

const std::string &DeterministicFiniteAutomaton::getMStartState() const {
    return m_startState;
}

void DeterministicFiniteAutomaton::setMStartState(const std::string &mStartState) {
    m_startState = mStartState;
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &
DeterministicFiniteAutomaton::getMDelta() const {
    return m_delta;
}

void DeterministicFiniteAutomaton::setMDelta(
        const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &mDelta) {
    m_delta = mDelta;
}

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(std::vector<std::string> states,
                                                           std::vector<std::string> symbols,
                                                           std::unordered_map<std::string, std::unordered_map<std::string, std::string>> delta,
                                                           std::string startState,
                                                           std::vector<std::string> finalStates)
                                                           :m_states{std::move(states)},
                                                           m_symbols{std::move(symbols)},
                                                           m_delta{std::move(delta)},
                                                           m_startState{std::move(startState)},
                                                           m_finalStates{std::move(finalStates)}
                                                           {}
