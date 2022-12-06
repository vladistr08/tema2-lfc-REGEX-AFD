//
// Created by istra on 12/6/22.
//

#include "DeterministicFiniteAutomaton.h"

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

bool DeterministicFiniteAutomaton::VerifyAutomaton() const {
    //Check if the members are empty
    if(this->m_states.empty() || this->m_finalStates.empty() || this->m_delta.empty() || this->m_symbols.empty())
        return false;
    //Contains startState
    if(std::find(this->m_states.begin(), this->m_states.end(), this->m_startState) == this->m_states.end())
        return false;
    //FinaleStates are included in states
    for(const auto &final: this->m_finalStates){
        if(std::find(this->m_states.begin(), this->m_states.end(), final) == this->m_states.end())
            return false;
    }
    //TODO Verify delta transition function

    return true;
}

std::ostream &operator<<(std::ostream &out, const DeterministicFiniteAutomaton &automaton) {
    out << "The Automaton:\nStates:";
    for(const auto &state: automaton.m_states)
        out << state << " ";

    out << "\nSymbols:";
    for(const auto &symbol: automaton.m_symbols)
        out << symbol << " ";

    out << "\nDelta:\n";
    TextTable table('-', '|', '+');

    table.add("");
    for(const auto &symbol: automaton.m_symbols){
        table.add(symbol);
    }
    table.endOfRow();

    for(auto transitions: automaton.m_delta){
        table.add(transitions.first);

        for(const auto &symbol: automaton.m_symbols){
            if(transitions.second[symbol].empty())
                table.add("");
            else {
                table.add(transitions.second[symbol]);
            }
        }

        table.endOfRow();
    }
    out << table;

    out << "\nStart State:" << automaton.m_startState;

    out << "\nFinal States: ";

    for(const auto &finalState: automaton.m_finalStates){
        out << finalState << " ";
    }
    out << '\n';

    return out;
}

//TODO
bool DeterministicFiniteAutomaton::IsDeterministic() {
    if(!VerifyAutomaton()){
        return false;
    }
    for(const auto &dPair: this->m_delta){
        for(const auto &dtPair: dPair.second){
            if(dtPair.second.size() > 1){
                return false;
            }
        }
    }
    return true;
}

//TODO
bool DeterministicFiniteAutomaton::CheckWord(const std::string &word) {
    std::vector<std::string> posibleStates;
    posibleStates.emplace_back(this->m_startState);

    for(const auto &symbol: word){
        std::string str;
        str += symbol;
        posibleStates = generateStatesForSymbol(str, posibleStates);
    }
    for(const auto &state: posibleStates){
        if(std::find(this->m_finalStates.begin(), this->m_finalStates.end(), state) != this->m_finalStates.end())
            return true;
    }
    return false;
}

std::vector<std::string>
DeterministicFiniteAutomaton::generateStatesForSymbol(const std::string &symbol, const std::vector<std::string> &posibleStates) {
    std::vector<std::string> result;
    for(const auto &state: posibleStates) {
        auto it = this->m_delta.find(state);
        std::vector<std::string> states;
        if(it != this->m_delta.end()){
            if(it->second.find(symbol) != it->second.end()){
                states = it->second.find(symbol)->second;
            }
        }
        if(state.empty())
            continue;
        result = unionVector(result, states);
    }
    return result;
}

std::vector<std::string> DeterministicFiniteAutomaton::unionVector(std::vector<std::string> v1, std::vector<std::string> v2) {
    std::vector<std::string> unifiedVector;
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(unifiedVector));
    return unifiedVector;
}

void DeterministicFiniteAutomaton::PrintAutomaton() const {
    std::cout << *this << '\n';
}
