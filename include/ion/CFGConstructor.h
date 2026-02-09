#pragma once

#include "IR.h"

#include <map>
#include <string>

class CFGConstructor {
public:
    static void construct(Function& fn);
    static void dumpCFG(const Function& fn);
private:
    static void addEdge(BasicBlock* from, BasicBlock* to);
    // std::string getTargetLabel(const Instruction& istr);
};