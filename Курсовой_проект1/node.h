#pragma once

#include <string>
#include "date.h"
#include <memory>

using namespace std;

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation
{
    Or,
    And,
};

class Node {
    //??
public:
    virtual int Evaluate() const = 0;
};

class EmptyNode : public Node
{
    //??
public:
    int Evaluate() const override;

private:
};

class DateComparisonNode : public Node
{
    //??
public:
    DateComparisonNode(Comparison cmp, Date date) : cmp_(cmp), date_(date)){};

    int Evaluate() const override;
private:
    Comparison cmp_;
    Date date_;
};

class  EventComparisonNode : public Node
{
    //??
public:
    EventComparisonNode(Comparison cmp, string value) : cmp_(cmp), value_(value){};
    int Evaluate() const override;
private:
    Comparison cmp_;
    string value_;
};

class LogicalOperationNode  : public Node
{
    //??
public:
    LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) : op_(op), left_(left), right_(right){};
    int Evaluate() const override;
private:
    //??????
    LogicalOperation op_;
    shared_ptr<Node> left_;
    shared_ptr<Node> right_;
};