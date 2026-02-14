#include <gtest/gtest.h>
#include <IR.h>
#include <Liveness.h>

class LivenessAnalysisTest : public testing::Test {
protected:
    /*
    The test fixture operates on this test IR program:
    Block A (entry):
        %1 = MOV 10
        %2 = MOV 20
        JMP B

    Block B:
        %3 = ADD %1, %2
        BEQ %3, 30, C

    Block C (exit):
        RET %3
    */

    LivenessAnalysisTest() {
        Function f;
        f.name = "test_func";

        BasicBlock entry;
        entry.id = 1;
        entry.label = "entry";

        BasicBlock B;
        B.id = 2;
        B.label = "test_block_B";

        BasicBlock exit;
        exit.id = 3;
        exit.label = "exit";

        // %1 = MOV 10
        Imm i10 = {10};
        VReg v1 = {1};
        B.instrs.push_back(Instruction {
            .op = Opcode::MOV,
            .def = v1,
            .uses = {i10}
        });

        // %2 = MOV 20
        Imm i20 = {20};
        VReg v2 = {2};
        B.instrs.push_back(Instruction {
            .op = Opcode::MOV,
            .def = v2,
            .uses = {i20}
        });

        // JMP B
        Operand b_exit = Label{.name="test_block_B"};
        B.instrs.push_back(Instruction {
            .op = Opcode::JMP,
            .def = std::monostate{},
            .uses = {b_exit}
        });

    }
};

TEST_F(LivenessAnalysisTest, GatherInitialInfo) {
    Function f;
}

TEST_F(LivenessAnalysisTest, Analyse) {
    Function f;
}