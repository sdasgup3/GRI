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

#ifndef NODEBINARYMULT_H
#define NODEBINARYMULT_H

#include "general.h"
#include "nodebinary.h"

class NodeBinaryMult : public NodeBinary
{
public:
	NodeBinaryMult(Node* left, Node* right);
	virtual ~NodeBinaryMult(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	NodeBinaryMult(void);
	NodeBinaryMult(const NodeBinaryMult& object);
	NodeBinaryMult& operator=(const NodeBinaryMult& object);
};

ostream& operator<<(ostream& os, const NodeBinaryMult& node);

#endif /* NODEBINARYMULT_H */

