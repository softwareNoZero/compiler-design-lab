#include <iostream>
#include <string>
#include <map>
#include <memory>
using namespace std;

enum class Type
{
    INT,
    FLOAT,
    BOOL,
    STRING,
    ERROR,
    VOID
};

string typeToString(Type type)
{
    switch (type)
    {
        case Type::INT:
            return "int";

        case Type::FLOAT:
            return "float";

        case Type::BOOL:
            return "bool";

        case Type::STRING:
            return "string";

        case Type::ERROR:
            return "error";

        case Type::VOID:
            return "void";
    }

    return "unknown";
}

class ASTNode
{
public:
    virtual Type analyze() = 0;

    virtual ~ASTNode() {}
};

map<string, Type> symbolTable;

class LiteralNode : public ASTNode
{
    Type type;

public:
    LiteralNode(Type t)
    {
        type = t;
    }

    Type analyze() override
    {
        return type;
    }
};

class VariableNode : public ASTNode
{
    string name;

public:
    VariableNode(string n)
    {
        name = n;
    }

    Type analyze() override
    {
        if (symbolTable.find(name) == symbolTable.end())
        {
            cout << "Semantic Error: Variable '"
                 << name << "' is not declared.\n";

            return Type::ERROR;
        }

        return symbolTable[name];
    }
};

class BinaryOpNode : public ASTNode
{
    string op;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

public:
    BinaryOpNode(string o, unique_ptr<ASTNode> l,
                 unique_ptr<ASTNode> r)
    {
        op = o;
        left = move(l);
        right = move(r);
    }

    Type analyze() override
    {
        Type leftType = left->analyze();
        Type rightType = right->analyze();

        if (leftType == Type::ERROR ||
            rightType == Type::ERROR)
        {
            return Type::ERROR;
        }

        if (op == "+" || op == "-" ||
            op == "*" || op == "/")
        {
            if ((leftType == Type::INT ||
                 leftType == Type::FLOAT) &&
                (rightType == Type::INT ||
                 rightType == Type::FLOAT))
            {
                if (leftType == Type::FLOAT ||
                    rightType == Type::FLOAT)
                {
                    return Type::FLOAT;
                }

                return Type::INT;
            }

            cout << "Semantic Error: Invalid operands for '"
                 << op << "': "
                 << typeToString(leftType) << " and "
                 << typeToString(rightType) << "\n";

            return Type::ERROR;
        }

        if (op == "<" || op == ">" ||
            op == "==" || op == "!=")
        {
            if (leftType == rightType)
            {
                return Type::BOOL;
            }

            cout << "Semantic Error: Cannot compare "
                 << typeToString(leftType) << " and "
                 << typeToString(rightType) << "\n";

            return Type::ERROR;
        }

        cout << "Semantic Error: Unknown operator "
             << op << "\n";

        return Type::ERROR;
    }
};

class AssignmentNode : public ASTNode
{
    string variable;
    unique_ptr<ASTNode> expression;

public:
    AssignmentNode(string v, unique_ptr<ASTNode> e)
    {
        variable = v;
        expression = move(e);
    }

    Type analyze() override
    {
        if (symbolTable.find(variable) == symbolTable.end())
        {
            cout << "Semantic Error: Variable '"
                 << variable << "' is not declared.\n";

            return Type::ERROR;
        }

        Type variableType = symbolTable[variable];
        Type expressionType = expression->analyze();

        if (expressionType == Type::ERROR)
            return Type::ERROR;

        if (variableType != expressionType)
        {
            cout << "Semantic Error: Cannot assign "
                 << typeToString(expressionType)
                 << " to variable '" << variable
                 << "' of type "
                 << typeToString(variableType) << ".\n";

            return Type::ERROR;
        }

        return Type::VOID;
    }
};

void declareVariable(string name, Type type)
{
    if (symbolTable.find(name) != symbolTable.end())
    {
        cout << "Semantic Error: Variable '"
             << name << "' is already declared.\n";

        return;
    }

    symbolTable[name] = type;

    cout << "Declared variable '" << name
         << "' as " << typeToString(type) << ".\n";
}

int main()
{
    cout << "Semantic Analyzer\n\n";

    // Variable declarations
    declareVariable("x", Type::INT);
    declareVariable("y", Type::FLOAT);
    declareVariable("flag", Type::BOOL);

    cout << "\nSemantic Analysis\n";

    // x = 10
    {
        auto ast = make_unique<AssignmentNode>(
            "x",
            make_unique<LiteralNode>(Type::INT));

        if (ast->analyze() != Type::ERROR)
            cout << "x = 10 -> Valid\n";
    }

    // y = x + 10
    {
        auto expression = make_unique<BinaryOpNode>(
            "+",
            make_unique<VariableNode>("x"),
            make_unique<LiteralNode>(Type::INT));

        auto ast = make_unique<AssignmentNode>(
            "y", move(expression));

        if (ast->analyze() != Type::ERROR)
            cout << "y = x + 10 -> Valid\n";
    }

    // flag = 10
    {
        auto ast = make_unique<AssignmentNode>(
            "flag",
            make_unique<LiteralNode>(Type::INT));

        if (ast->analyze() != Type::ERROR)
            cout << "flag = 10 -> Valid\n";
    }

    // x = true
    {
        auto ast = make_unique<AssignmentNode>(
            "x",
            make_unique<LiteralNode>(Type::BOOL));

        if (ast->analyze() != Type::ERROR)
            cout << "x = true -> Valid\n";
    }

    // x = z
    {
        auto ast = make_unique<AssignmentNode>(
            "x",
            make_unique<VariableNode>("z"));

        if (ast->analyze() != Type::ERROR)
            cout << "x = z -> Valid\n";
    }

    // x + flag
    {
        auto expression = make_unique<BinaryOpNode>(
            "+",
            make_unique<VariableNode>("x"),
            make_unique<VariableNode>("flag"));

        Type result = expression->analyze();

        if (result != Type::ERROR)
            cout << "x + flag -> Valid\n";
    }

    // Duplicate declaration
    declareVariable("x", Type::FLOAT);

    return 0;
}
