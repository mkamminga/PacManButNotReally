#pragma once

class GraphNode;
class NodeEdge;
class PillItem;
class GhostObject;
class PacManObject;

class BaseVisitor
{
public:
	virtual void visit(GraphNode* node) = 0;
	virtual void visit(PillItem* pillItem) = 0;
	virtual void visit(GhostObject* ghost) = 0;
	virtual void visit(PacManObject* pacman) = 0;
};

