//
// Created by Nathan on 16/12/2017.
//

#include "DFA.h"
#include <iostream>

using namespace::std;

DFA::DFA(NFA nfa) {
    triplets = nfa.triplets;
    edges = nfa.edges;
    endState = nfa.tailState;
    determined(nfa);
    printDFA();
}

void DFA::determined(NFA nfa) {
    set<int> set_0;
    set_0.insert(nfa.headState);
    set_0 = e_closure(set_0);
    sets.push_back(set_0);
    judgeTerminal(set_0);
    headSet = set_0;

    for(int i=0; i<sets.size(); i++){
        set<int> current_set = sets[i];
        // 遍历所有边，求move
        set<string>::iterator it;
        for(it=nfa.edges.begin();it!=nfa.edges.end();it++){
            set<int> moveSet = move(current_set,*it);
            moveSet = e_closure(moveSet);
            if(moveSet.size() == 0){
                continue;
            }
            if(!isSetExist(moveSet)){
                sets.push_back(moveSet);
            }
            judgeTerminal(moveSet);
            setTriplets.push_back(SetTriplet(current_set,*it,moveSet));
        }
    }
}

set<int> DFA::move(set<int> states, string edge) {
    set<int> edge_states;
    for(auto state: states){
        for(auto triplet: triplets){
            if(triplet.head == state && triplet.edge == edge){
                edge_states.insert(triplet.tail);
            }
        }
    }
    return edge_states;
}

set<int> DFA::e_closure(set<int> states) {
    set<int> e_states;
    stack<int> state_stack;
    for(auto state : states){
        state_stack.push(state);
    }

    // DFS
    while(!state_stack.empty()){
        int state = state_stack.top();
        state_stack.pop();

        e_states.insert(state);
        for(auto triplet: triplets){
            if((triplet.head == state) && (triplet.edge == "e")){
                state_stack.push(triplet.tail);
            }
        }
    }
    return e_states;
}

bool DFA::isSetExist(std::set<int> _set) {
    for(auto set: sets){
        if(set == _set){
            return true;
        }
    }
    return false;
}

void DFA::judgeTerminal(std::set<int> _set) {
    for(auto state: _set){
        if(state == endState){
            terminalSets.push_back(_set);
            break;
        }
    }
}

bool DFA::isTerminal(std::set<int> _set) {
    for(auto state: _set){
        if(state == endState){
            return true;
        }
    }
    return false;
}

void DFA::printDFA() {
    for(auto set: sets){
        for(auto state: set){
            cout<<state<<",";
        }
        cout<<endl;
    }
}
