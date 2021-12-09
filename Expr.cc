#include <memory>
#include <cmath>

#include "Expr.h"

namespace expr {

std::ostream& operator<<(std::ostream& o, const shared_ptr<Expr>& eptr) {
    return o << eptr->toString();
}

string Num::toString() const {
    std::ostringstream s; // ostringstream is used to operate on strings
    s << num_; // Instead of std::cout object, num_ was sent to s, an ostringstream object
    return s.str();
}

Sum::Sum(shared_ptr<Expr> left, shared_ptr<Expr> right)
        : left_(left), right_(right) {}

Prod::Prod(shared_ptr<Expr> left, shared_ptr<Expr> right)
        : left_(left), right_(right) {}

shared_ptr<Expr> Sum::clone() const {
    return std::make_shared<Sum>(left_->clone(), right_->clone());
}

shared_ptr<Expr> Prod::clone() const {
    return std::make_shared<Prod>(left_->clone(), right_->clone());
}

shared_ptr<Expr> Num::clone() const {
    return std::make_shared<Num>(num_);
}

shared_ptr<Expr> Var::clone() const {
    return std::make_shared<Var>(name_);
}

shared_ptr<Expr> Num::setVariables(const std::map<std::string, double>& values) const {
    // TODO: Implement setVariables
    return std::make_shared<Num>(num_);
}

shared_ptr<Expr> Sum::setVariables(const std::map<std::string, double>& values) const {
    // TODO: Implement setVariables
    return std::make_shared<Sum>(left_->setVariables(values), right_->setVariables(values));
}

shared_ptr<Expr> Prod::setVariables(const std::map<std::string, double>& values) const {
    // TODO: Implement setVariables
    return std::make_shared<Prod>(left_->setVariables(values), right_->setVariables(values));
}

shared_ptr<Expr> Var::setVariables(const std::map<std::string, double>& values) const {
    auto result = values.find(name_);
    if (result == values.end()) {
        // TODO: Finish implementing
        return std::make_shared<Var>(name_);
    } else {
        // TODO: Finish implementing
        return std::make_shared<Num>(result->second);
    }
}

shared_ptr<Expr> operator+(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
    return std::make_shared<Sum>(lhs, rhs);
}

shared_ptr<Expr> operator*(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
    return std::make_shared<Prod>(lhs, rhs);
}

double Var::evaluate() const {
    return NAN;
}
double Num::evaluate() const {
    return num_;
}
double Sum::evaluate() const {
    return left_->evaluate() + right_->evaluate();
}
double Prod::evaluate() const {
    return left_->evaluate() * right_->evaluate();
}

// TODO: Implement more functions here

}  // namespace