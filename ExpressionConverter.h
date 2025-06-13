#include <string>
#include <vector>
#include "Stack.h"

class ExpressionConverter {
private:
    std::string postfixExpression;
    std::vector<std::string> instructions;
    int tempVarCounter;

    bool isOperator(char c) const;
    bool isOperand(char c) const;
    std::string generateTempVar();

public:
    ExpressionConverter() : tempVarCounter(0) {}

    void setExpression(const std::string& expr);
    std::vector<std::string> convert();
    const std::vector<std::string>& getInstructions() const;
};
