#include "valueset.h"
#include "valuebool.h"
#include "valuenull.h"
#include "valuestruct.h"


/////////////////////////////////////////////////////////////////////////////
////

ValueSet::ValueSet(void)
	: Value(),
	m_val(),
	m_it(m_val.begin())
{

}

ValueSet::~ValueSet(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::clear(void)
{
	
	m_val.clear();
	m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::clone(void) const
{
	
	ValueSet* ret = new ValueSet;
	ret->m_val = m_val;
	ret->resetIterator();
	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::dump(ostream& os, uint indent) const
{
	

	dumpIndent(os, indent);
	os << "<ValueSet>" << endl;

	set_container::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
		(*it)->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueSet>" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::insert(CountPtr<Value> value)
{
	

	if(contains(value))
		return;

	m_val.push_back(value);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::remove(CountPtr<Value> value)
{
	

	set_container::iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		if(*it == value)
		{
			m_val.erase(it);
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::remove(const ValueSet& set)
{
	
	set_container::const_iterator it;
	for(it = set.m_val.begin(); it != set.m_val.end(); ++it)
		remove(*it);
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueSet::contains(CountPtr<Value> value) const
{
	

	set_container::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		if(*it == value)
			return true;
	}

	return false;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::findItem(const Value* value) const
{
	

	set_container::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		if(it->getPtr() == value)
			return *it;
	}

	return VALUENULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::setPropertyToAllStructItems(identifier name, CountPtr<Value> value)
{
	

	set_container::iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		ValueStruct* tmp = (*it)->toValueStruct();
		if(tmp != NULL)
			tmp->setItem(name, value);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getUnion(const ValueSet& vs) const
{
	

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_val.begin(); it != m_val.end(); ++it)
		ret->insert(*it);

	for(it = vs.m_val.begin(); it != vs.m_val.end(); it++)
		ret->insert(*it);

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getIntersection(const ValueSet& vs) const
{
	

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		if(vs.contains(*it))
			ret->insert(*it);
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getDifference(const ValueSet& vs) const
{
	

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		if(!vs.contains(*it))
			ret->insert(*it);
	}

	return CountPtr<Value>(ret);
}

/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::iterator(void) const
{
	
	ValueSet* tmp = new ValueSet;
	tmp->m_val = m_val;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::hasNext(void) const
{
	
	return (m_it == m_val.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::next(void)
{
	
	return *(m_it++);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::resetIterator(void)
{
	
	m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::add(const Value& right)        const { return right.add(*this); } // +
CountPtr<Value> ValueSet::sub(const Value& right)        const { return right.sub(*this); } // -
CountPtr<Value> ValueSet::mult(const Value& right)       const { return right.mult(*this); } // *
CountPtr<Value> ValueSet::div(const Value& right)        const { return right.div(*this); } // /
CountPtr<Value> ValueSet::mod(const Value& right)        const { return right.mod(*this); } // %
CountPtr<Value> ValueSet::eq(const Value& right)         const { return right.eq(*this); } // ==
CountPtr<Value> ValueSet::eq(const ValueSet& left) const { return (left.m_val == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueSet::ne(const Value& right)         const { return right.ne(*this); } // !=
CountPtr<Value> ValueSet::ne(const ValueSet& left) const { return (left.m_val != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueSet::le(const Value& right)         const { return right.le(*this); } // <=
CountPtr<Value> ValueSet::ge(const Value& right)         const { return right.ge(*this); } // >=
CountPtr<Value> ValueSet::lt(const Value& right)         const { return right.lt(*this); } // <
CountPtr<Value> ValueSet::gt(const Value& right)         const { return right.gt(*this); } // >
CountPtr<Value> ValueSet::member(const Value& right)     const { return right.member(*this); } // .
CountPtr<Value> ValueSet::index(const Value& right)      const { return right.index(*this); } // []
CountPtr<Value> ValueSet::logNOT(void)                   const {  return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !


/////////////////////////////////////////////////////////////////////////////
////
