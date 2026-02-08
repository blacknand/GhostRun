#pragma once

#include "IR.h"
#include "Lexer.h"

#include <string>
#include <memory>
#include <map>

class IRParser {
public:
    explicit IRParser(Lexer& lexer) : m_lexer(lexer) {
        m_currentToken = m_lexer.next();
    }

    std::unique_ptr<Function> parseFunction();
private:
    Lexer& m_lexer;
    Token m_currentToken;

    void parseLine(Function& fn, BasicBlock& block);
    void parseLabel(Function& fn, BasicBlock& block);
    void parseInstruction(Function& fn, BasicBlock& block);

    void consume(TokenType type, const std::string& errorMsg);
    bool match(TokenType type);

    std::map<std::string, int> m_labelMap;
};