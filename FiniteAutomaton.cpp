//
// Created by istra on 11/5/22.
//

#include "FiniteAutomaton.h"

#include <utility>
#include <queue>

FiniteAutomaton::FiniteAutomaton(std::vector<std::string> states, std::vector<std::string> symbols, std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta, std::string startState, std::vector<std::string> finalStates)
:       m_states(std::move(states)),
        m_symbols(std::move(symbols)),
        m_delta(std::move(delta)),
        m_startState(std::move(startState)),
        m_finalStates(std::move(finalStates))
        {}

bool FiniteAutomaton::VerifyAutomaton() const {
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
    //Verify delta transition function
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>>> kv(this->m_delta.begin(), this->m_delta.end());
    for(const auto &stateTransition: kv){

        if(std::find(this->m_states.begin(), this->m_states.end(), stateTransition.first) == this->m_states.end())
            return false;

        std::vector<std::pair<std::string, std::vector<std::string>>> kv2(stateTransition.second.begin(), stateTransition.second.end());

        for(const auto &transition: kv2){
            if(std::find(this->m_symbols.begin(), this->m_symbols.end(), transition.first) == this->m_symbols.end())
                return false;

            for(const auto & state: transition.second)
                if(std::find(this->m_states.begin(), this->m_states.end(), state) == this->m_states.end())
                    return false;
        }
        kv2.clear();
    }
    kv.clear();
    return true;
}

void FiniteAutomaton::PrintAutomaton() const {
    std::cout << *this;
}

std::ostream &operator<<(std::ostream &out, const FiniteAutomaton &automaton) {
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
                std::string toAdd;
                for (const auto &el: transitions.second[symbol]) {
                    toAdd += el;
                    toAdd += " ";
                }
                table.add(toAdd);
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

bool FiniteAutomaton::CheckWord(const std::string &word) {
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

std::vector<std::string> FiniteAutomaton::findLambdaClosure(const std::string &currentState){

    std::vector<std::string> closure;
    closure = this->m_delta[currentState].find(lambda)->second;

    std::queue<std::string> currentFound;

    for(const auto &state: closure){
        currentFound.push(state);
    }

    while(!currentFound.empty()){
        std::string state = currentFound.front();
        std::vector<std::string> transitionsFound{};
        if(!m_delta[state].empty() && m_delta[state].find(lambda) != m_delta[state].end())
            transitionsFound = this->m_delta[state].find(lambda)->second;
        if(!transitionsFound.empty()){
            for(const auto &transition: transitionsFound){
                if(std::find(closure.begin(), closure.end(), transition) == closure.end()){
                    closure.emplace_back(transition);
                    currentFound.push(transition);
                }
            }
        }
        currentFound.pop();
    }

    return closure;
}

std::vector<std::string>
FiniteAutomaton::generateStatesForSymbol(const std::string &symbol, const std::vector<std::string> &posibleStates) {
    std::vector<std::string> result;
    for(const auto &state: posibleStates) {
        auto it = this->m_delta.find(state);
        std::vector<std::string> states;
        if(it != this->m_delta.end()){
            if(it->second.find(symbol) != it->second.end()){
                states = it->second.find(symbol)->second;
            }
            if(it->second.find(lambda) != it->second.end()){
                std::vector<std::string> resultLambdaClosure = findLambdaClosure(state);
                states = unionVector(states, resultLambdaClosure);
            }
        }
        if(state.empty())
            continue;
        result = unionVector(result, states);
        UsefulMethods::removeDuplicates(result);
    }
    return result.empty() ? posibleStates : result;
}

std::vector<std::string> FiniteAutomaton::unionVector(std::vector<std::string> v1, std::vector<std::string> v2) {
    std::vector<std::string> unifiedVector;
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(unifiedVector));
    return unifiedVector;
}

bool FiniteAutomaton::IsDeterministic() {
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

const std::vector<std::string> &FiniteAutomaton::getMStates() const {
    return m_states;
}

void FiniteAutomaton::setMStates(const std::vector<std::string> &mStates) {
    m_states = mStates;
}

const std::vector<std::string> &FiniteAutomaton::getMFinalStates() const {
    return m_finalStates;
}

void FiniteAutomaton::setMFinalStates(const std::vector<std::string> &mFinalStates) {
    m_finalStates = mFinalStates;
}

const std::vector<std::string> &FiniteAutomaton::getMSymbols() const {
    return m_symbols;
}

void FiniteAutomaton::setMSymbols(const std::vector<std::string> &mSymbols) {
    m_symbols = mSymbols;
}

const std::string &FiniteAutomaton::getMStartState() const {
    return m_startState;
}

void FiniteAutomaton::setMStartState(const std::string &mStartState) {
    m_startState = mStartState;
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> &
FiniteAutomaton::getMDelta() const {
    return m_delta;
}

void FiniteAutomaton::setMDelta(
        const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> &mDelta) {
    m_delta = mDelta;
}
