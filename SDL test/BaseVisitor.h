#pragma once

class GraphNode;
class NodeEdge;
class PillItem;
class GhostObject;
class PacManObject;
class GhostWanderingState;
class GhostChasingState;
class GhostChasingPillState;
class GhostFlockingState;
class BaseObject;

class BaseVisitor
{
public:
	virtual void visit(GraphNode* node) = 0;
	virtual void visit(PillItem* pillItem) = 0;
	virtual void visit(GhostObject* ghost) = 0;
	virtual void visit(PacManObject* pacman) = 0;
	virtual void visit(GhostWanderingState* ghostWandering, BaseObject* bo) = 0;
	virtual void visit(GhostChasingState* ghostWandering, BaseObject* bo) = 0;
	virtual void visit(GhostChasingPillState* ghostWandering, BaseObject* bo) = 0;
	virtual void visit(GhostFlockingState* ghostFlocking, BaseObject* bo) = 0;
};