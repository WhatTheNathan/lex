//
// Created by Nathan on 17/12/2017.
//

#include "ODFA.h"
#include <iostream>
#include <map>

using namespace::std;

ODFA::ODFA() {}
ODFA::ODFA(DFA dfa) {
    convertEdges(dfa.edges);
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
        for(auto edge: edges){
            for(auto stateSet: sets[i].set){
                set<int> aTailStateSet = dfa.e_closure(dfa.move(stateSet,edge));;
                for(auto oSet: sets){
                    if(oSet.isInSet(aTailStateSet)){
                        OSetTriplet triplet = OSetTriplet(sets[i],edge,oSet);
                        oSetTriplets.push_back(triplet);
                        break;
                    }
                }
                break;
            }
        }
    }
}

void ODFA::convertEdges(set<string> edgeSet) {
    for(auto edge:edgeSet){
        this->edges.push_back(edge);
    }
}

// 未写lookback
void ODFA::weakDivide(DFA dfa) {
    OSet emptyOSet(emptySet,0);
    list.push_back(emptyOSet);
    while(!list.empty() ){
        // 获取此时所有的叶节点OSet
        map<OSet,OSet> tempMap;
        map<OSet,OSet>::iterator it;

        for(auto oSet: list){
            OSet tempSet = emptyOSet;
            tempMap[oSet] = tempSet;
        }

//        cout<<"list大小 "<<list.size()<<endl;
        OSet judgeSet = list.front();
//        cout<<"judgeSet的set大小 "<<judgeSet.set.size()<<endl;

        // 已经judge过所有边，或者状态集合数为1，则不能再划分
        if(judgeSet.judgeCount == edges.size() || judgeSet.set.size() == 1){
            for(auto stateSet: judgeSet.set){
                // 寻找headSet
                if(stateSet == dfa.headSet){
                    this->headSet = judgeSet;
                    break;
                }
            }
            for(auto stateSet: judgeSet.set){
                // 寻找terminalSet
                map<std::set<int>,std::string>::iterator it;
                for( it=dfa.setTerminal_TokenMap.begin(); it!=dfa.setTerminal_TokenMap.end(); it++)
                {
                    if(stateSet == it->first){
                        judgeSet.tokenName = dfa.setTerminal_TokenMap[stateSet];
                        this->terminalSets.push_back(judgeSet);
                        break;
                    }
                }
            }
            sets.push_back(judgeSet);
            list.pop_front();
            continue;
        }

        for(int i=judgeSet.judgeCount; i<edges.size(); i++){
            // 进行划分
//            cout<<"通过"<<edges[i]<<"划分"<<endl;
            for(auto stateSet: judgeSet.set){
                set<int> moveSet = dfa.move(stateSet,edges[i]);
                if(moveSet.size() == 0){
                    tempMap[emptyOSet].set.insert(stateSet);
                    continue;
                }
                set<int> tailStateSet = dfa.e_closure(moveSet);
                // 属于当前树的叶节点，包括list中以及sets中
                for(auto oSet: list){
                    if(oSet.isInSet(tailStateSet)){
                        tempMap[oSet].set.insert(stateSet);
                    }
                }
                for(auto oSet: sets){
                    if(oSet.isInSet(tailStateSet)){
                        tempMap[oSet].set.insert(stateSet);
                    }
                }
            }
            judgeSet.judgeCount++;

            // 判断是否继续划分
            int continueFlag = 0;
            for(it=tempMap.begin(); it!=tempMap.end(); it++)
            {
                if(it->second.set == judgeSet.set){
                    continueFlag = 1;
                    it->second.set = emptySet;
                    break;
                }
            }
            // 不需要再划分
            if(!continueFlag) {
                list.pop_front();
                // 则将划分出的OSet push到list中
                for(it=tempMap.begin(); it!=tempMap.end(); it++){
                    if(!it->second.set.empty()){
                        it->second.judgeCount = judgeSet.judgeCount;
                        list.push_front(it->second);
                    }
                }
                break;
            }
            // 已经划分所有边，依然未能划分，则更新list中的judgeCount
            if(judgeSet.judgeCount == edges.size()){
                list.pop_front();
                list.push_front(judgeSet);
            }
        }
    }
}

void ODFA::divideByTerminal(DFA dfa) {
    OSet positiveSet(emptySet,0);
    OSet terminalSet(emptySet,0);
    orderTeminalMap[0] = positiveSet;
    int count = 1;
    for(auto set: dfa.terminalVec){
        orderTeminalMap[count] = terminalSet;
        count++;;
    }

    for(auto _set: dfa.sets){
        orderTeminalMap[dfa.setOrder(_set)].set.insert(_set);
    }
    map<int,OSet>::iterator it;
    for( it=this->orderTeminalMap.begin(); it!=this->orderTeminalMap.end(); it++)
    {
//        cout<<"第一次划分所放入的该OSet的size: "<<it->second.set.size()<<endl;
        list.push_back(it->second);
    }
}

void ODFA::printODFA() {
    cout<<"=========headSet==========="<<endl;
    for(auto stateSet: headSet.set){
        for(auto state: stateSet){
            cout<<state<<",";
        }
        cout<<endl;
    }
    cout<<"========headSet============"<<endl;

    for(auto triplet: oSetTriplets){
        cout<<"************************************************************************************"<<endl;
        cout<<"head:"<<endl;
        cout<<"===================="<<endl;
        for(auto set: triplet.head.set){
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
        for(auto set: triplet.tail.set){
            for(auto state: set){
                cout<<state<<",";
            }
            cout<<endl;
        }
        cout<<"===================="<<endl;
        cout<<"************************************************************************************"<<endl;
    }
}

