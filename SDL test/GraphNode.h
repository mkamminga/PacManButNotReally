#pragma once
#include <vector>
#include <memory>
#include "NodeEdge.h"
#include "BaseObject.h"
#include "BaseVisitiable.h"
#include "GamePlayObject.h"
#include "Item.h"

class SparseGraph;

using std::vector;

class GraphNode : public BaseObject, public std::enable_shared_from_this<GraphNode>
{
private:
	vector<std::shared_ptr<GraphEdge>> edges;
	vector<std::shared_ptr<GamePlayObject>> baseObjects;
	vector<std::shared_ptr<Item>> items;
	std::shared_ptr<SparseGraph> graph;
public:
	GraphNode(int x, int y, std::shared_ptr<SparseGraph> graph) : graph(graph), BaseObject(x, y) {}
	virtual ~GraphNode() {}
	void addEdges(std::shared_ptr<GraphNode> to, double cost);
	void  addObject(std::shared_ptr<GamePlayObject>);
	void  removeObject(std::shared_ptr<GamePlayObject>);
	void  addItem(std::shared_ptr<Item>);
	void  removeItem(std::shared_ptr<Item>);
	const vector<std::shared_ptr<GraphEdge>>& getEdges() const;
	const vector<std::shared_ptr<GamePlayObject>>& getObjects() const;
	const vector<std::shared_ptr<Item>>& getItems() const;
	const std::shared_ptr<SparseGraph> getGraph() const;

	virtual void accept(BaseVisitor*);
};