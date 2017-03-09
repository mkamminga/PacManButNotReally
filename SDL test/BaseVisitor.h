#pragma once

class CowObject;
class HareObject;
class GraphNode;
class NodeEdge;
class PillItem;
class GunItem;

class BaseVisitor
{
public:
	virtual void visit(CowObject* cow) = 0;
	virtual void visit(HareObject* hare) = 0;
	virtual void visit(GraphNode* node) = 0;
	virtual void visit(PillItem* node) = 0;
	virtual void visit(GunItem* node) = 0;
};

