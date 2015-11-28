#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <list>

using namespace std;

typedef long long llint;
typedef unsigned long long ullint;

class GraphNode {

private:
	ullint  _id;
	llint _value;
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
	ullint getId() const { return _id; }
	void setId(ullint id) { _id = id; }

	//----- Value
	llint getValue() const { return _value; }
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
};

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
};

class Graph {

protected:
	//----- Attributes
	list<GraphNode*> _nodes;
	list<GraphEdge*> _edges;
	list<GraphEdge*> _pathEdges;

	bool _isDirected;
	ullint _id;

public:
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

	llint getNodesLeastValue() {
		llint leastValue = LLONG_MAX;

		for (GraphNode* currentNode : _nodes)
			if (currentNode->getValue() < leastValue)
				leastValue = currentNode->getValue();
				
		return leastValue;
	}

	void removeNodeLeastValue() {
		if (isEmpty()) return;
		removeNodeByValue(getNodesLeastValue());
	}

	llint getNodesMaxValue() {
		llint maxValue = LLONG_MIN;

		for (GraphNode* currentNode : _nodes)
			if (currentNode->getValue() > maxValue)
				maxValue = currentNode->getValue();
				
		return maxValue;
	}

	void removeNodeMaxValue() {
		if (isEmpty()) return;
		removeNodeByValue(getNodesMaxValue());
	}

	GraphNode* searchNodeByValue(llint nodeValue) {
		GraphNode* nodeOutput = NULL;
		list<GraphNode*>::iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getValue() == nodeValue ) {
				nodeOutput = (*positionNode);
				break;
			}
			positionNode++;
		}

		return nodeOutput;
	}

	GraphNode* searchNodeById(ullint nodeId) {
		GraphNode* nodeOutput = NULL;
		list<GraphNode*>::iterator positionNode = _nodes.begin();

		while (positionNode != _nodes.end()) {
			if ( (*positionNode)->getId() == nodeId ) {
				nodeOutput = (*positionNode);
				break;
			}
			positionNode++;
		}

		return nodeOutput;
	}

	bool hasNodeWithValue(llint nodeValue) {
		return searchNodeByValue(nodeValue) != NULL;
	}

	bool hasNodeWithId(ullint nodeId) {
		return searchNodeById(nodeId) != NULL;
	}

	void addEdgeByValue(llint sourceValue, llint destinationValue, double weight) {
		const GraphNode* sourceNode = searchNodeByValue(sourceValue);
		const GraphNode* destinationNode = searchNodeByValue(destinationValue);

		if ( ( sourceNode != NULL ) && ( destinationNode != NULL ) ) {
			GraphEdge* newEdge = new GraphEdge(sourceNode, destinationNode, weight);
			_edges.push_back(newEdge);
		}
	}

	void addEdgeById(ullint sourceId, ullint destinationId, double weight) {
		const GraphNode* sourceNode = searchNodeById(sourceId);
		const GraphNode* destinationNode = searchNodeById(destinationId);

		if ( ( sourceNode != NULL ) && ( destinationNode != NULL ) ) {
			GraphEdge* newEdge = new GraphEdge(sourceNode, destinationNode, weight);
			_edges.push_back(newEdge);
		}
	}

	void removeEdgesByWeight(double weight) {
		list<GraphEdge*>::iterator positionEdge = _edges.begin();
		
		while (positionEdge != _edges.end()) {
			if ( (*positionEdge)->getWeight() == weight ) {
				delete *positionEdge;
				*positionEdge = NULL;
				_edges.erase(positionEdge);
			}

			positionEdge++;
		}
	}

	void removeEdgesByNodeValuePath(llint sourceValue, llint destinationValue) {
		const GraphNode* sourceNode;
		const GraphNode* destinationNode;
		list<GraphEdge*>::iterator positionEdge = _edges.begin();

		while (positionEdge != _edges.end()) {
			sourceNode = (*positionEdge)->getSource();
			destinationNode = (*positionEdge)->getDestination();
			
			if ( (sourceNode->getValue() == sourceValue) 
				|| (destinationNode->getValue() == destinationValue) ) {
				
				delete *positionEdge;
				*positionEdge = NULL;
				_edges.erase(positionEdge);
			}

			positionEdge++;
		}
	}

	void removeEdgeByNodeIdPath(ullint sourceId, ullint destinationId) {
		const GraphNode* sourceNode;
		const GraphNode* destinationNode;
		list<GraphEdge*>::iterator positionEdge = _edges.begin();
		
		while (positionEdge != _edges.end()) {
			sourceNode = (*positionEdge)->getSource();
			destinationNode = (*positionEdge)->getDestination();
			
			if ( (sourceNode->getId() == sourceId) 
				|| (destinationNode->getId() == destinationId) ) {

				delete *positionEdge;
				*positionEdge = NULL;
				_edges.erase(positionEdge);
			}

			positionEdge++;
		}
	}
};
