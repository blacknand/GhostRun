#include <gtest/gtest.h>
#include <ion/IR.h>

TEST(IRTest, ManualGraphConstruction) {
    // Function f;
    // f.name = "test_func";

    // BasicBlock* entry = new BasicBlock();
    // entry->id = 1;
    // entry->label = "entry";

    // BasicBlock* exit = new BasicBlock();
    // exit->id = 2;
    // exit->label = "exit";

    // entry->succs.push_back(exit);
    // exit->preds.push_back(entry);

    // f.blocks.push_back(entry);
    // f.blocks.push_back(exit);

    // // Check there is 2 blocks inside test_func
    // ASSERT_EQ(f.blocks.size(), 2);

    // // Check that the successor block inside entry is exit
    // EXPECT_EQ(f.blocks[0]->succs[0], exit);
    // EXPECT_EQ(f.blocks[0]->succs[0]->label, "exit");

    // for (auto* b : f.blocks) delete b;
}