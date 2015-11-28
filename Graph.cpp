#include <list>
#include <climits>

typedef long long llint;
typedef unsigned llint ullint;

class GraphNode {

private:
	ullint  _id;
	llint value;
	bool _visit;
	bool _hasParentId;
	ullint _parentId;

public:
	GraphNode(ullint id, llint value) {
		setId(id);
		setValue(value);
		setVisit(false);
		setHasParentId(false);
		setParentId(0);
	}
	
	~GraphNode() { 
	}


	//----- Getters and Setters

	//----- Id
	ullint getId() { return _id; }
	void setId(ullint id) { _id = id; }

	//----- Value
	llint getValue() { return _value; }
	void setValue(llint value) { _value = value; }

	//----- Visit
	bool getVisit() { return _visit; }
	void setVisit(bool visit) { _visit = visit; }

	//----- Has Parent Id
	bool getHasParentId() { return _hasParentId; }
	void setHasParentId(bool hasParentId) { _hasParentId = hasParentId; }

	//----- Parent Id
	ullint getParentId() { return _parentId; }
	void setParentId(ullint parentId) { _parentId = parentId; }
}

class GraphEdge {
private:
	const GraphNode* _source;
	const GraphNode* _destination;
	double _weight;

public:
	GraphEdge(const GraphNode* source, const GraphNode* destination, 
			double weight) {
		_source = source;
		_destination = destination;
		_weight = weight;
	}

	~GraphEdge() {
	}


	//----- Getters and Setters
	//----- Source
	const GraphNode* getSource() const { return _source; }

	//----- Destination
	const GraphNode* getDestination() const { return _destination; }

	//----- Weight
	double getWeight() { return _weight; }
	void setWeight(double weight) { _weight = weight; }
}

class Graph {

protected:
	//----- Attributes
	list<GraphNode*> _nodes;
	list<GraphEdge*> _edges;
	list<GraphEdge*> _pathEdges;

	bool _isDirected;
	ullint _id;

	Graph(bool isDirected = false) {
		setIsDirected(isDirected);
		_id = 0;
	}

	~Graph() {
		clear();
	}


	//----- Getters and Setters
	//----- Is Directed
	bool getIsDirected() { return _isDirected; }
	void setIsDirected(bool isDirected) { _isDirected = isDirected; }
	

	//----- Methods
	void clear() {
		// Clear Edges
		list<GraphEdge*>::iterator positionEdge = _edges.begin();

		while (positionEdge != _edges.end()) {
			delete *positionEdge;
			*positionEdge = NULL;
			positionEdge++;
		}

		_edges.clear();

		// Clear Nodes
		list<GraphNode*>:: iterator positionNode = _nodes.begin();
		while (positionNode != _nodes.end()) {
			delete *positionNode;
			*positionNode = NULL;
			positionNode++;
		}

		_nodes.clear();
	}

	bool isEmpty() {
		return _nodes.empty();
	}

	ullint getNumberOfNodes() {
		return _nodes.size();
	}

	ullint getNumberOfEdges() {
		return _edges.size();
	}

	void addNode(llint value) {
		_id++;
		GraphNode* node = new GraphNode(_id, value);
		_nodes.push_back(node);
	}

	void removeNodeById(ullint nodeId) {
		list<GraphEdge*>::iterator positionEdge = _edges.begin();
		const GraphNode* source;
		const GraphNode* destination;

		// Remove edges where node is involved
		while (positionEdge != _edges.end()) {
			source = (*positionEdge)->getSource();
			destination = (*positionEdge)->getDestination();
			
			if ( ( source->getId() == nodeId ) 
				|| ( destination->getId() == nodeId ) ) {
	
				delete *positionEdge;
				*positionEdge = NULL;
				_edges.erase(positionEdge);
			}

			positionEdge++;
		}

		source = NULL;
		destination = NULL;

		// Remove nodes with the given id
		list<GraphNode*>:: iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getId() == nodeId ) {
				delete *positionNode;
				*positionNode = NULL;
				_nodes.erase(positionNode);
				break;
			}

			positionNode++;
		}
	}

	void removeNodeByValue(llint nodeValue) {
		list<GraphEdge*>::iterator positionEdge = _edges.begin();
		const GraphNode* source;
		const GraphNode* destination;

		// Remove edges where node is involved
		while (positionEdge != _edges.end()) {
			source = (*positionEdge)->getSource();
			destination = (*positionEdge)->getDestination();
			
			if ( ( source->getValue() == nodeValue ) 
				|| ( destination->getValue() == nodeValue ) ) {

				delete *positionEdge;
				*positionEdge = NULL;
				_edges.erase(positionEdge);
			}

			positionEdge++;
		}

		source = NULL;
		destination = NULL;

		// Remove nodes with the given id
		list<GraphNode*>:: iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getValue() == nodeValue ) {
				delete *positionNode;
				*positionNode = NULL;
				_nodes.erase(positionNode);
			}

			positionNode++;
		}
	}

	void removeNodeLeastValue() {
		if (isEmpty()) return;

		llint leastValue = LLONG_MAX;

		list<GraphNode*>::iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getValue() < leastValue ) {
				leastValue = (*positionNode)->getValue();
			}
			
			positionNode++;
		}

		removeNodeByValue(leastValue);
	}

	void removeNodeMaxValue() {
		if (isEmpty()) return;

		llint maxValue = LLONG_MIN;

		list<GraphNode*>::iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getValue() > maxValue ) {
				maxValue = (*positionNode)->getValue();
			}
			
			positionNode++;
		}

		removeNodeByValue(maxValue);
	}
}
