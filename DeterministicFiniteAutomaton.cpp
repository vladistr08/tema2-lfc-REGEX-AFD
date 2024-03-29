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
    //check delta
    for(const auto &it: this->m_delta){
        if(std::find(this->m_states.begin(), this->m_states.end(), it.first) == this->m_states.end())
            return false;
        for(const auto &jt: it.second){
            if(std::find(this->m_states.begin(), this->m_states.end(), jt.second) == this->m_states.end())
                return false;
            if(std::find(this->m_symbols.begin(), this->m_symbols.end(), jt.first) == this->m_symbols.end())
                return false;
        }
    }

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

bool DeterministicFiniteAutomaton::IsDeterministic() const {
    if(!VerifyAutomaton()){
        return false;
    }
    return true;
}

bool DeterministicFiniteAutomaton::CheckWord(const std::string &word) {
    std::string currentState = m_startState;
    for(const auto& chr: word){
        std::string aux = "";
        aux += chr;

        auto it = this->m_delta.find(currentState);
        if(it != this->m_delta.end()){
            auto jt  = it->second.find(aux);
            if(jt != it->second.end()){
                currentState = jt->second;
            }
            else{
                break;
            }
        }
        else{
            break;
        }

    }
    return std::find(m_finalStates.begin(), m_finalStates.end(), currentState) != m_finalStates.end();
}

void DeterministicFiniteAutomaton::PrintAutomaton() const {
    std::cout << *this << '\n';
}

int prioritate(char op)
{
    if (op == '|')
        return 1;
    else if (op == '.')
        return 2;
    else if (op == '*')
        return 3;
    else
        return -1;
}

std::string formaPoloneza(const std::string &regex)
{
    if(!UsefulMethods::isValidRegex(regex)){
        std::cout << "Regex exp is not valid try again!\n";
        return "";
    }
    std::stack<char> op;
    std::string fp = "";
    int l = regex.size();
    for (int i = 0; i < l; i++)
        if (regex[i] == '(')
            op.push(regex[i]);
        else if (regex[i] == ')')
        {
            while (!op.empty() && op.top() != '(')
            {
                fp.push_back(op.top());
                op.pop();
            }
            op.pop();
        }
        else if (prioritate(regex[i]) != -1)
        {
            while (!op.empty() && prioritate(op.top()) >= prioritate(regex[i]))
            {
                fp.push_back(op.top());
                op.pop();
            }
            op.push(regex[i]);
        }
        else
            fp.push_back(regex[i]);
    while (!op.empty())
    {
        fp.push_back(op.top());
        op.pop();
    }
    return fp;
}

FiniteAutomaton DeterministicFiniteAutomaton::ConvertFromRegex(const std::string &regex) {
    if(!UsefulMethods::isValidRegex(regex)){
        std::cout << "Regex is not valid!\n";
        return {};
    }

    std::string fp = formaPoloneza(regex);

    #define q "q"
    std::stack<FiniteAutomaton> StackAutomata;
    int counter = 0;

    auto isChar = [](char c){return (c != '|' && c != '*' && c != '.' && c != '(' && c != ')');};

    for(size_t index = 0; index < fp.length(); index++){
        if(isChar(fp[index])){

            std::vector<std::string> states({std::string{q+std::to_string(counter)}, std::string{q+std::to_string(counter + 1)}}), finalStates({std::string{q+std::to_string(counter + 1)}});
            std::vector<std::string> symbols({std::string{fp[index]}});
            std::string startState = std::string{q+std::to_string(counter)};
            std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta;
            std::unordered_map<std::string, std::vector<std::string>> aux;

            aux.insert({symbols[0], finalStates});
            delta.insert({startState, aux});
            aux.clear();

            auto A = FiniteAutomaton(
                        states, symbols, delta, startState, finalStates
                    );

            StackAutomata.push(A);
            counter += 2;
        }
        else if(fp[index] == '|'){
            auto B = StackAutomata.top();
            StackAutomata.pop();
            auto A = StackAutomata.top();
            StackAutomata.pop();

            std::string startState = std::string{q+std::to_string(counter)};

            std::vector<std::string> finalStates = {std::string{q+std::to_string(counter + 1)}};
            std::vector<std::string> states;

            states.emplace_back(startState);
            states.emplace_back(finalStates[0]);

            std::vector<std::string> bStates = B.getMStates(), aStates = A.getMStates();

            for(const auto & bs: bStates){
                states.emplace_back(bs);
            }
            for(const auto & as: aStates){
                states.emplace_back(as);
            }

            UsefulMethods::removeDuplicates(states);

            std::vector<std::string> symbols;
            std::vector<std::string> aSymbols = A.getMSymbols(), bSymbols = B.getMSymbols();

            for(const auto & as: aSymbols){
                symbols.emplace_back(as);
            }
            for(const auto & bs: bSymbols){
                symbols.emplace_back(bs);
            }
            symbols.emplace_back(lambda);

            UsefulMethods::removeDuplicates(symbols);

            std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta;
            std::unordered_map<std::string, std::vector<std::string>> aux;

            for(auto& [key, value]: A.getMDelta()){
                delta.insert({key, value});
            }
            for(auto& [key, value]: B.getMDelta()){
                delta.insert({key, value});
            }

            aux.insert({lambda, finalStates});
            delta.insert({A.getMFinalStates()[0], aux});
            delta.insert({B.getMFinalStates()[0], aux});

            aux.clear();
            aux.insert({lambda, {A.getMStartState(), B.getMStartState()}});
            delta.insert({startState, aux});

            FiniteAutomaton C(
                    states, symbols, delta, startState, finalStates
                    );
            StackAutomata.push(C);
            counter += 2;
        }
        else if(fp[index] == '.'){
            auto B = StackAutomata.top();
            StackAutomata.pop();
            auto A = StackAutomata.top();
            StackAutomata.pop();

            std::string startState{A.getMStartState()};
            std::vector<std::string> states, symbols, finalStates{B.getMFinalStates()};
            std::vector<std::string> aSymbols = A.getMSymbols(), bSymbols = B.getMSymbols();
            std::vector<std::string> bStates = B.getMStates(), aStates = A.getMStates();

            std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta;

            for(const auto & as: aSymbols){
                symbols.emplace_back(as);
            }
            for(const auto & bs: bSymbols){
                symbols.emplace_back(bs);
            }
            symbols.emplace_back(lambda);
            UsefulMethods::removeDuplicates(symbols);


            for(const auto & bs: bStates){
                if(bs != B.getMStartState())
                    states.emplace_back(bs);
            }
            for(const auto & as: aStates){
                if(as != A.getMFinalStates()[0])
                    states.emplace_back(as);
            }

            std::string middleState = q + std::to_string(index) + "m";
            states.emplace_back(middleState);

            UsefulMethods::removeDuplicates(states);

            for(auto& [key, value]: A.getMDelta()){
                bool ok = 1;
                for(auto& [symb, val]: value){
                    if(val[0] == A.getMFinalStates()[0]){
                        delta.insert({key, {{symb, {middleState}}}});
                        ok = 0;
                        break;
                    }
                }
                if(ok)
                    delta.insert({key, value});
            }
            for(auto& [key, value]: B.getMDelta()){
                if(key == B.getMStartState()){
                    delta.insert({middleState, value});
                }
                else
                    delta.insert({key, value});
            }

            FiniteAutomaton C(
                    states, symbols, delta, startState, finalStates
                    );
            StackAutomata.push(C);
        }
        else if(fp[index] == '*'){
            auto A = StackAutomata.top();
            StackAutomata.pop();

            std::vector<std::string> states{A.getMStates()};
            states.emplace_back(q + std::to_string(counter));
            states.emplace_back(q + std::to_string(counter + 1));

            std::vector<std::string> symbols{A.getMSymbols()};
            if(std::find(symbols.begin(), symbols.end(), lambda) == symbols.end())
                symbols.emplace_back(lambda);

            std::string startState = q + std::to_string(counter);
            std::vector<std::string> finalStates{q + std::to_string(counter + 1)};

            std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> delta;

            delta = A.getMDelta();
            delta[A.getMFinalStates()[0]].insert({lambda, {A.getMStartState(), finalStates[0]}});
            delta[startState].insert({lambda, {A.getMStartState(), finalStates[0]}});

            FiniteAutomaton C(
                    states, symbols, delta, startState, finalStates
                    );
            StackAutomata.push(C);
            counter += 2;
        }
    }

    if(StackAutomata.size() != 1){
        std::cout << "Something went wrong in regex convert function!\n";
        return {};
    }
    FiniteAutomaton resultedAutomata = StackAutomata.top();
    StackAutomata.pop();

    return resultedAutomata;
}

DeterministicFiniteAutomaton DeterministicFiniteAutomaton::ConvertFromNFA(FiniteAutomaton automaton) {
    std::vector<std::string> symbols = automaton.getMSymbols(), newSymbols;

    std::vector<std::string> states = automaton.getMStates(), newStates{};

    std::vector<std::string> finalStates = automaton.getMFinalStates(), newFinalStates{};

    std::string startState = automaton.getMStartState(), newStartState{};

    auto delta = automaton.getMDelta();

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> newDelta;

    size_t counter = 0;
    std::unordered_map<std::string, std::unordered_set<std::string>> newStatesMap;
    std::unordered_set<std::string> currentStates;

    //Symbols
    for(const auto &symbol: symbols){
        if(symbol != lambda){
            newSymbols.emplace_back(symbol);
        }
    }

    #define p "p"

    //Initialize the first state
    std::queue<std::string> statesToGenerateDelta;
    newStates.emplace_back(p + std::to_string(counter));
    newStartState = p + std::to_string(counter);
    statesToGenerateDelta.emplace(newStartState);


    //Prepare start of algorithm
    currentStates.emplace(startState);

    while(!statesToGenerateDelta.empty()){
        std::string currentNewState = statesToGenerateDelta.front();
        statesToGenerateDelta.pop();

        for(const auto &symbol: newSymbols){
            std::vector<std::string> currentFound{}, auxClosure{};
            for(const auto & state: currentStates){
                currentFound = UsefulMethods::unionVector(currentFound, automaton.findLambdaClosure(state, symbol, auxClosure));
            }
            UsefulMethods::removeDuplicates(currentFound);

            currentStates.clear();
            for(const auto & state: currentFound){
                currentStates.emplace(state);
            }
            currentFound.clear();

            if(currentStates.empty())
                continue;

            bool ok = true;
            std::string toState;
            for(auto &[state, setValue]: newStatesMap){
                if(UsefulMethods::equalSets(currentStates, setValue)){
                    toState = state;
                    ok = false;
                    break;
                }
            }

            if(ok){
                counter++;

                toState = p + std::to_string(counter);

                newDelta[currentNewState].insert({symbol, toState});
                newStatesMap[currentNewState] = currentStates;

                newStates.emplace_back(toState);
                statesToGenerateDelta.emplace(toState);
            }
            else{
                newDelta[currentNewState].insert({symbol, toState});
            }
        }
    }

    for(auto &[state, setValue]: newStatesMap){
        for(const auto &el: setValue){
            if(std::find(finalStates.begin(), finalStates.end(), el) != finalStates.end()){
                newFinalStates.emplace_back(state);
                continue;
            }
        }
    }

    DeterministicFiniteAutomaton newAutomaton(newStates, newSymbols, newDelta, newStartState, newFinalStates);
    newAutomaton.PrintAutomaton();

    return newAutomaton;

}

