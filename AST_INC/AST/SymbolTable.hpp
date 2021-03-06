#ifndef CS6300_SYMBOL_TABLE_HPP
#define CS6300_SYMBOL_TABLE_HPP

#include "Symbol.hpp"
#include "ThreeAddressInstruction.hpp"
#include <memory>
#include <map>

namespace cs6300
{

class Type;
class Expression;

class SymbolTable
{
public:
  SymbolTable(std::shared_ptr<SymbolTable> parent,
              cs6300::MemoryLocation memory_location)
    : m_memorylocation(memory_location)
    , m_parent(parent)
    , m_memory_offset(0)
    , m_param_offset(0)
  {
  }

  std::shared_ptr<Type> lookupType(std::string id);
  std::shared_ptr<Symbol> lookupVariable(std::string id);
  std::shared_ptr<Expression> lookupConstant(std::string id);
  void addConstant(std::string id, std::shared_ptr<Expression>);
  void addType(std::string id, std::shared_ptr<Type>);
  void addVariable(std::string id, std::shared_ptr<Type> type);
  void addParameter(std::string id, std::shared_ptr<Type> type);

  cs6300::MemoryLocation getMemoryLocation() { return m_memorylocation; }

  std::shared_ptr<SymbolTable> getParent() { return m_parent; }
  int stackSpace()
  {
    return m_memorylocation == cs6300::GLOBAL ? 0 : m_memory_offset;
  };

private:
  cs6300::MemoryLocation m_memorylocation;
  std::shared_ptr<SymbolTable> m_parent;
  int m_memory_offset;
  int m_param_offset;
  std::map<std::string, std::shared_ptr<Type>> m_types;
  std::map<std::string, std::shared_ptr<Symbol>> m_variables;
  std::map<std::string, std::shared_ptr<Expression>> m_consts;
};
}
#endif
