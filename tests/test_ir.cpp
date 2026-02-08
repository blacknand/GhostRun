#include <gtest/gtest.h>
#include <ion/IR.h>

TEST(IRTest, FullGraphWithInstructions) {
    Function f;
    f.name = "test_func";

    BasicBlock entry;
    entry.id = 1;
    entry.label = "entry";

    BasicBlock exit;
    exit.id = 2;
    exit.label = "exit";

    VReg r1 = {1};
    Imm val = {10};

    entry.instrs.push_back({
        Opcode::MOV,
        r1,
        {val}
    });

    entry.succs.push_back(&exit);
    exit.preds.push_back(&entry);

    f.blocks.push_back(std::make_unique<BasicBlock>(entry));
    f.blocks.push_back(std::make_unique<BasicBlock>(exit));

    // Check there is 2 blocks inside test_func
    ASSERT_EQ(f.blocks.size(), 2);

    // Check that the successor block inside entry is exit
    ASSERT_EQ(f.blocks[0]->succs[0], &exit);
    ASSERT_EQ(f.blocks[0]->succs[0]->label, "exit");

    // Check instruction count
    ASSERT_EQ(entry.instrs.size(), 1);
    const Instruction& i = entry.instrs[0];

    // Check correct instruction
    EXPECT_EQ(i.op, Opcode::MOV);

    // Check vreg is %1
    const VReg* defReg = std::get_if<VReg>(&i.def);
    ASSERT_NE(defReg, nullptr);
    EXPECT_EQ(defReg->id, 1);
}