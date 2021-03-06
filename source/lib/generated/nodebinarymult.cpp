/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


/****************************************************************************
 *                                                                          *
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#include "generated/nodebinarymult.h"
#include "value.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBinaryMult::NodeBinaryMult(Node* left, Node* right)
	: NodeBinary(left, right)
{

}

NodeBinaryMult::~NodeBinaryMult(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeBinaryMult::execute(void)
{
	return m_left->execute()->mult(*(m_right->execute()));
}

void NodeBinaryMult::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<NodeBinaryMult>" << endl;

	m_left->dump(os, indent+1);
	m_right->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</NodeBinaryMult>" << endl;
}

ostream& operator<<(ostream& os, const NodeBinaryMult& node)
{
	node.dump(os, 0);
	return os;
}

