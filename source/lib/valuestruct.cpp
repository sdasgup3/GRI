#include <sstream>
#include "valuestruct.h"
#include "valuebool.h"
#include "valuereference.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

ValueStruct::ValueStruct(void)
  : Value(),
  m_val(),
  m_it()
{

}

ValueStruct::~ValueStruct(void)
{

}

void ValueStruct::clear(void)
{
  
  m_val.clear();
  resetIterator();
}


/////////////////////////////////////////////////////////////////////////////
////
/*
string ValueStruct::toString(void) const
{
  
  ostringstream os;
  map<identifier, CountPtr<Value> >::const_iterator it;

  for(it = m_val.begin(); it != m_val.end(); it++)
    os << ID2STR(it->first) << "=" << it->second->toString() << ",";

  string ret = os.str();
  if(ret.size() != 0)
    ret.resize(ret.size()-1);// remove last ","

  return ret;
}
*/

/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::setItem(identifier name, CountPtr<Value> val)
{
  
  map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);
  if(it != m_val.end())
    m_val.erase(it);

  if(val->isLValue())
    m_val.insert(pair<identifier, CountPtr<Value> >(name,
      CountPtr<Value>(new ValueReference(val->getReferredValue()))));
  else
    m_val.insert(pair<identifier, CountPtr<Value> >(name,
      CountPtr<Value>(new ValueReference(val))));

  return val;
}


CountPtr<Value> ValueStruct::getItem(identifier name)
{
  
  map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);

  if(it != m_val.end())
    return it->second;
  else
    return m_val.insert(pair<identifier, CountPtr<Value> >(name,
      CountPtr<Value>(new ValueReference(VALUENULL)))).first->second;
}

bool ValueStruct::isItemSet(identifier name)
{
  
  return m_val.count(name);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::iterator(void) const
{
  
  ValueStruct* tmp = new ValueStruct;
  tmp->m_val = m_val;
  tmp->resetIterator();

  return CountPtr<Value>(tmp);
}

CountPtr<Value> ValueStruct::hasNext(void) const
{
  
  return (m_it == m_val.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}

CountPtr<Value> ValueStruct::next(void)
{
  
  CountPtr<Value> ret(m_it->second);
  m_it++;
  return ret;
}

void ValueStruct::resetIterator(void)
{
  
  m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::setPropertyToAllStructItems(identifier name, CountPtr<Value> value)
{
  

  map<identifier, CountPtr<Value> >::iterator it;
  for(it = m_val.begin(); it != m_val.end(); ++it)
  {
    ValueStruct* tmp = (*it).second->toValueStruct();
    if(tmp != NULL)
      tmp->setItem(name, value);
  }
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::dump(ostream& os, uint indent) const
{
  
  dumpIndent(os, indent);
  os << "<ValueStruct>" << endl;

  map<identifier, CountPtr<Value> >::const_iterator it;
  for(it = m_val.begin(); it != m_val.end(); it++)
  {
    dumpIndent(os, indent+1);
    os << "<Item name=\"" << ID2STR(it->first) << "\">" << endl;
    it->second->dump(os, indent+2);
    dumpIndent(os, indent+1);
    os << "</Item>" << endl;
  }

  dumpIndent(os, indent);
  os << "</ValueStruct>" << endl;
}

ostream& operator<<(ostream& os, const ValueStruct& node)
{
  node.dump(os, 0);
  return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::add(const Value& right)     const { return right.add(*this); } // +
CountPtr<Value> ValueStruct::sub(const Value& right)     const { return right.sub(*this); } // -
CountPtr<Value> ValueStruct::mult(const Value& right)    const { return right.mult(*this); } // *
CountPtr<Value> ValueStruct::div(const Value& right)     const { return right.div(*this); } // /
CountPtr<Value> ValueStruct::mod(const Value& right)     const { return right.mod(*this); } // %
CountPtr<Value> ValueStruct::eq(const Value& right)      const { return right.eq(*this); } // ==
CountPtr<Value> ValueStruct::eq(const ValueStruct& /*left*/) const { return VALUEBOOL_FALSE; }
CountPtr<Value> ValueStruct::ne(const Value& right)      const { return right.ne(*this); } // !=
CountPtr<Value> ValueStruct::ne(const ValueStruct& /*left*/) const { return VALUEBOOL_TRUE; }
CountPtr<Value> ValueStruct::le(const Value& right)      const { return right.le(*this); } // <=
CountPtr<Value> ValueStruct::ge(const Value& right)      const { return right.ge(*this); } // >=
CountPtr<Value> ValueStruct::lt(const Value& right)      const { return right.lt(*this); } // <
CountPtr<Value> ValueStruct::gt(const Value& right)      const { return right.gt(*this); } // >
CountPtr<Value> ValueStruct::member(const Value& right)  const { return right.member(*this); } // .
CountPtr<Value> ValueStruct::index(const Value& right)   const { return right.index(*this); } // []
CountPtr<Value> ValueStruct::logNOT(void)                const {  return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !


/////////////////////////////////////////////////////////////////////////////
////

bool ValueStruct::toBool(void) const
{
  
  return !m_val.empty();
}
