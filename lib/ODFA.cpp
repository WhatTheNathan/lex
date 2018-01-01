//
// Created by Nathan on 17/12/2017.
//

#include "ODFA.h"
#include <iostream>
#include <map>

using namespace::std;

ODFA::ODFA(DFA dfa) {
    optimization(dfa);
}

void ODFA::optimization(DFA dfa) {
    divideByTerminal(dfa);
    weakDivide(dfa);
    generateTriplet(dfa);
    printODFA();
}

void ODFA::generateTriplet(DFA dfa) {
    for(int i=0; i<sets.size(); i++){
        for(auto stateSet: sets[i].set){
            set<int> aTailStateSet = dfa.e_closure(dfa.move(stateSet,"a"));;
            for(auto oSet: sets){
                if(oSet.isInSet(aTailStateSet)){
                    OSetTriplet triplet = OSetTriplet(sets[i].set,"a",oSet.set);
                    oSetTriplets.push_back(triplet);
                    break;
                }
            }
        }

        for(auto stateSet: sets[i].set){
            set<int> aTailStateSet = dfa.e_closure(dfa.move(stateSet,"b"));;
            for(auto oSet: sets){
                if(oSet.isInSet(aTailStateSet)){
                    OSetTriplet triplet = OSetTriplet(sets[i].set,"b",oSet.set);
                    oSetTriplets.push_back(triplet);
                    break;
                }
            }
        }
    }
}

void ODFA::weakDivide(DFA dfa) {
    while(!list.empty() ){
        // 获取此时所有的叶节点状态集合
        map<OSet,OSet> tempMap;
        map<OSet,OSet>::iterator it;
        for(auto oSet: list){
            OSet tempSet = OSet(emptySet,0);
            tempMap[oSet] = tempSet;
        }

        int continueFlag = 0;
        OSet judgeSet = list.front();
//        list.pop_front();
        // 已经judge过a和b，则不能再分
        if(judgeSet.judgeCount == 2 || judgeSet.set.size() == 1){
            sets.push_back(judgeSet);

            for(auto state: judgeSet.set){
                // 寻找headSet
                if(state == dfa.headSet){
                    this->headSet = judgeSet.set;
                    break;
                }
            }
            for(auto state: judgeSet.set){
                // 寻找terminalSet
                vector<set<int>>::iterator ifind = find(dfa.terminalSets.begin(), dfa.terminalSets.end(), state);
                if(ifind != dfa.terminalSets.end())
                {
                    this->terminalSets.push_back(judgeSet);
                }
            }
            list.pop_front();
            continue;
        }

        // 未用a,b划分过
        if(judgeSet.judgeCount == 0){
            for(auto stateSet: judgeSet.set){
                set<int> tailStateSet = dfa.e_closure(dfa.move(stateSet,"a"));
                for(auto oSet: list){
                    if(oSet.isInSet(tailStateSet)){
                        tempMap[oSet].set.insert(stateSet);
                    }
                }
            }

            // 如果用a划分划分不出来，则仍需要用b再次划分
            for(it=tempMap.begin(); it!=tempMap.end(); it++)
            {
                if(it->second.set == judgeSet.set){
                    continueFlag = 1;
                    it->second.set = emptySet;
                    break;
                }
            }
        }

        // 已经用a划分过
        if(judgeSet.judgeCount == 1 || continueFlag == 1){
            continueFlag = 0;
            for(auto stateSet: judgeSet.set){
                set<int> tailStateSet = dfa.e_closure(dfa.move(stateSet,"b"));
                for(auto oSet: list){
                    if(oSet.isInSet(tailStateSet)){
                        tempMap[oSet].set.insert(stateSet);
                    }
                }
            }
            for(it=tempMap.begin(); it!=tempMap.end(); it++)
            {
                if(it->second.set == judgeSet.set){
                    continueFlag = 1;
                    it->second.set = emptySet;
                    break;
                }
            }
        }

        if(continueFlag == 1) {
            judgeSet.judgeCount++;
            list.push_back(judgeSet);
        }else{
            for(it=tempMap.begin(); it!=tempMap.end(); it++){
                if(!it->second.set.empty()){
                    it->second.judgeCount++;
                    list.push_back(it->second);
                }
            }
        }
        list.pop_front();
    }
}

void ODFA::divideByTerminal(DFA dfa) {
    OSet positiveSet(emptySet,0);
    OSet terminalSet(emptySet,0);

    for(auto set: dfa.sets){
        if(dfa.isTerminal(set)){
            terminalSet.set.insert(set);
        }else {
            positiveSet.set.insert(set);
        }
    }

    list.push_back(positiveSet);
    list.push_back(terminalSet);
}

void ODFA::printODFA() {
    cout<<"===================="<<endl;
    for(auto set: headSet){
        for(auto state: set){
            cout<<state<<",";
        }
        cout<<endl;
    }
    cout<<"===================="<<endl;

    for(auto triplet: oSetTriplets){
        cout<<"head:"<<endl;
        cout<<"===================="<<endl;
        for(auto set: triplet.head){
            for(auto state: set){
                cout<<state<<",";
            }
            cout<<endl;
        }
        cout<<"===================="<<endl;

        cout<<"edge:"<<endl;
        cout<<triplet.edge<<endl;

        cout<<"tail:"<<endl;
        cout<<"===================="<<endl;
        for(auto set: triplet.tail){
            for(auto state: set){
                cout<<state<<",";
            }
            cout<<endl;
        }
        cout<<"===================="<<endl;
        cout<<"************************************************************************************"<<endl;
    }
}

