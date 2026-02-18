#pragma once

#include "IR.h"

#include <map>
#include <bitset>
#include <set>


struct LivenessInfo {
    // Block ID -> set
    // set is indexed by register number/variable ID
    std::map<int, std::vector<bool>> UEVar;
    std::map<int, std::vector<bool>> VarKill;
};

// Hold the results of the equations solved
struct LivenessResult {
    // Block ID -> set
    std::map<int, std::set<int>> liveoutSet;
    std::map<int, std::set<int>> liveinSet;     
};

LivenessInfo computeUseDef(Function& fn);

class LivenessAnalysis {
public:
    // Gathers the initial information and stores in the internal bitsets
    LivenessResult analyse(Function& fn);
};