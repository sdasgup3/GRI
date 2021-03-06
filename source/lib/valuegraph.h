#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include "general.h"
#include "value.h"
#include "valueset.h"

class ValueVertex;
class ValueEdge;

class ValueGraph : public Value
{
public:
	ValueGraph(bool directed = false);
	virtual ~ValueGraph(void);

	virtual ValueGraph*         toValueGraph(void) { return this; }

	virtual void dump(ostream& os, uint) const;

	virtual bool toBool(void) const;
	virtual string toString(void) const { return "#Graph"; }

	bool loadFromFile(const string& filename);
	bool saveToFile(const string& filename);

	bool isDirected(void) const;
	bool setDirected(bool directed);
	void invertEdgesDirection(void);

	CountPtr<Value> generateVertex(void);
	CountPtr<Value> generateEdge(CountPtr<Value> begin, CountPtr<Value> end);

	void deleteVertex(CountPtr<Value> vertex);
	void deleteEdge(CountPtr<Value> edge);

	uint getNumVertices(void) const;
	uint getNumEdges(void) const;

	bool containsVertex(CountPtr<Value> vertex) const;
	bool containsEdge(CountPtr<Value> edge) const;

	CountPtr<Value> getVertices(void) const { return m_vertices.clone(); }
	CountPtr<Value> getVertexSetWithProperty(const string& prop, const float val) const;
	CountPtr<Value> getEdges(void) const { return m_edges.clone(); }
	ValueSet* getVerticesPtr(void) { return &m_vertices; }
	ValueSet* getEdgesPtr(void) { return &m_edges; }

	CountPtr<Value> getAdjacencyMatrix(void) const;
	CountPtr<Value> getTransitiveClosure(void) const;
	CountPtr<Value> getShortestPath(const string& wt, 
              ValueVertex* start,
              ValueVertex* end) const;
	CountPtr<Value> getMST(const string& wt) const;

	void setPropertyToAllVertices(identifier name, CountPtr<Value> value);
	void setPropertyToAllEdges(identifier name, CountPtr<Value> value);

	// See ValueEdge::getBeginVertex()
	CountPtr<Value> findVertex(ValueVertex* vertex) const;

	virtual CountPtr<Value> add(const Value&     right) const; // +
	virtual CountPtr<Value> sub(const Value&     right) const; // -
	virtual CountPtr<Value> mult(const Value&    right) const; // *
	virtual CountPtr<Value> div(const Value&     right) const; // /
	virtual CountPtr<Value> mod(const Value&     right) const; // %
	virtual CountPtr<Value> eq(const Value&      right) const; // ==
	virtual CountPtr<Value> eq(const ValueGraph& left)  const;
	virtual CountPtr<Value> ne(const Value&      right) const; // !=
	virtual CountPtr<Value> ne(const ValueGraph& left)  const;
	virtual CountPtr<Value> le(const Value&      right) const; // <=
	virtual CountPtr<Value> ge(const Value&      right) const; // >=
	virtual CountPtr<Value> lt(const Value&      right) const; // <
	virtual CountPtr<Value> gt(const Value&      right) const; // >
	virtual CountPtr<Value> member(const Value&  right) const; // .
	virtual CountPtr<Value> index(const Value&   right) const; // []
	virtual CountPtr<Value> logNOT(void)                const; // !

public:
        void dijkstra(std::vector<std::vector<float>>&,
              int& , int&, std::vector<float>&, 
              std::vector<int>&) const;
        void mst(std::vector<std::vector<float>>&, 
              std::vector<float>&, std::vector<int>&) const;

private:
	bool m_directed;
	ValueSet m_vertices;
	ValueSet m_edges;
};

ostream& operator<<(ostream& os, const ValueGraph& node);

#endif
