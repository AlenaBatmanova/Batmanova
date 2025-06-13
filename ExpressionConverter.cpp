#include "ExpressionConverter.h"
#include <stdexcept>
#include <cctype>

using namespace std;

void ExpressionConverter::setExpression(const std::string& expr) {
    postfixExpression = expr;
    instructions.clear();
    tempVarCounter = 0;
}

bool ExpressionConverter::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool ExpressionConverter::isOperand(char c) const {
    return isalpha(c);
}

std::string ExpressionConverter::generateTempVar() {
    return "T" + to_string(++tempVarCounter);
}

std::vector<std::string> ExpressionConverter::convert() {
    if (postfixExpression.empty()) {
        throw invalid_argument("Выражение пустое. Введите корректное постфиксное выражение.");
    }

    Stack<string> stack;

    for (char c : postfixExpression) {
        if (isOperand(c)) {
            string operand(1, c);
            stack.push(operand);
        }
        else if (isOperator(c)) {
            if (stack.size() < 2) {
                throw invalid_argument("Недопустимое постфиксное выражение:");
            }

            string right = stack.pop();
            string left = stack.pop();
            string tempVar = generateTempVar();

            instructions.push_back("LD " + left);
            switch (c) {
            case '+':
                instructions.push_back("AD " + right);
                break;
            case '-':
                instructions.push_back("SB " + right);
                break;
            case '*':
                instructions.push_back("ML " + right);
                break;
            case '/':
                instructions.push_back("DV " + right);
                break;
            }
            instructions.push_back("ST " + tempVar);
            stack.push(tempVar);
        }
        else {
            throw invalid_argument("Недопустимое постфиксное выражение.");
        }
    }

    if (stack.size() != 1) {
        throw invalid_argument("Недопустимое постфиксное выражение.");
    }

    if (!instructions.empty() && instructions.back().substr(0, 2) == "ST") {
        instructions.pop_back();
    }

    return instructions;
}

const std::vector<std::string>& ExpressionConverter::getInstructions() const {
    return instructions;
}
