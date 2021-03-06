#include "AndExpression.hpp"
#include "AST/BasicBlock.hpp"
#include "AST/ThreeAddressInstruction.hpp"

cs6300::AndExpression::AndExpression(std::shared_ptr<Expression> lhs,
                                     std::shared_ptr<Expression> rhs)
  : m_lhs(lhs), m_rhs(rhs)
{
}

std::shared_ptr<cs6300::BasicBlock> cs6300::AndExpression::emit() const
{
  return emitBinaryOp(ThreeAddressInstruction::And, getLabel(), m_lhs, m_rhs);
}

std::shared_ptr<cs6300::Type> cs6300::AndExpression::type() const
{
  return BuiltInType::getBool();
}

int cs6300::AndExpression::value() const
{
  if (!isConst()) return 0;
  return m_lhs->value() && m_rhs->value();
}
bool cs6300::AndExpression::isConst() const
{
  if (!m_lhs) return false;
  if (!m_rhs) return false;
  return m_lhs->isConst() && m_rhs->isConst();
}

std::string cs6300::AndExpression::name() const
{
  return "\"&&\"";
}

std::vector<std::string> cs6300::AndExpression::ASTDot() const
{
  std::vector<std::string> lines;
  join(m_lhs, lines, id());
  return join(m_rhs, lines, id());
}
