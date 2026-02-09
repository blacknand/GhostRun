#include <gtest/gtest.h>
#include "Lexer.h"
#include "IRParser.h"
#include "CFGConstructor.h"
#include <algorithm> // for std::find

// Helper to check if edge exists
bool hasEdge(BasicBlock* from, BasicBlock* to) {
    auto& s = from->succs;
    bool foundInSuccs = std::find(s.begin(), s.end(), to) != s.end();
    
    auto& p = to->preds;
    bool foundInPreds = std::find(p.begin(), p.end(), from) != p.end();
    
    return foundInSuccs && foundInPreds;
}

TEST(CFGTest, WiresComplexControlFlow) {
    // A program with a loop and a conditional exit
    // 
    // [entry] -> [loop_header] <==+
    //                 |           |
    //                 v           |
    //            (BEQ exit?)      |
    //                 |           |
    //            (Fallthrough)    |
    //                 v           |
    //            [loop_body] -----+
    //
    // [exit]
    
    std::string source = 
        "entry:\n"
        "  MOV %1, 0\n"
        "  JMP loop_header\n"
        "\n"
        "loop_header:\n"
        "  BEQ %1, 10, exit\n"  // Conditional Branch
        "\n"
        "loop_body:\n"
        "  ADD %1, %1, 1\n"
        "  JMP loop_header\n"   // Back-edge
        "\n"
        "exit:\n"
        "  RET %1\n";

    // 1. Parse
    Lexer lexer(source);
    IRParser parser(lexer);
    auto fn = parser.parseFunction();
    ASSERT_NE(fn, nullptr);
    ASSERT_EQ(fn->blocks.size(), 4); // entry, loop_header, loop_body, exit

    // 2. Build CFG
    CFGConstructor::construct(*fn);

    // 3. Verify Edges
    BasicBlock* entry = fn->blocks[0].get();
    BasicBlock* header = fn->blocks[1].get();
    BasicBlock* body = fn->blocks[2].get();
    BasicBlock* exit = fn->blocks[3].get();

    // Edge 1: entry -> header (JMP)
    EXPECT_TRUE(hasEdge(entry, header));
    EXPECT_EQ(entry->succs.size(), 1);

    // Edge 2: header -> exit (BEQ Taken)
    EXPECT_TRUE(hasEdge(header, exit));

    // Edge 3: header -> body (BEQ Fallthrough - Physically Next)
    EXPECT_TRUE(hasEdge(header, body));
    EXPECT_EQ(header->succs.size(), 2);

    // Edge 4: body -> header (JMP Back-edge)
    EXPECT_TRUE(hasEdge(body, header));
    EXPECT_EQ(body->succs.size(), 1);

    // Edge 5: exit (RET has no successors)
    EXPECT_TRUE(exit->succs.empty());
}

TEST(CFGTest, ThrowsOnMissingLabel) {
    std::string source = 
        "entry:\n"
        "  JMP nonexistent_label\n";

    Lexer lexer(source);
    IRParser parser(lexer);
    auto fn = parser.parseFunction();

    // Should throw runtime_error when it can't find the label
    EXPECT_THROW(CFGConstructor::construct(*fn), std::runtime_error);
}