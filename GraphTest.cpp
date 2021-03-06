#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Graph.hpp"

SCENARIO ( "Graph nodes work correctly" ) {

	GIVEN ( "A graph node with initial values" ) {
		GraphNode gnode(1, 10);
		
		WHEN ( "I get the values" ) { 

			THEN ( "Values should be the same as the initial state" ) {
				REQUIRE( gnode.getId() == 1 );
				REQUIRE( gnode.getValue() == 10);
				REQUIRE( gnode.getVisit() == false );
				REQUIRE( gnode.getHasParentId() == false );
				REQUIRE( gnode.getParentId() == 0 );
			}
		}

		WHEN ( "I set new values" ) {
			gnode.setId(2);
			gnode.setValue(20);
			gnode.setVisit(true);
			gnode.setHasParentId(true);
			gnode.setParentId(2);

			THEN ( "Values should be the same as the new values I set" ) {
				REQUIRE( gnode.getId() == 2 );
				REQUIRE( gnode.getValue() == 20 );
				REQUIRE( gnode.getVisit() == true );
				REQUIRE( gnode.getHasParentId() == true );
				REQUIRE( gnode.getParentId() == 2 );
			}
		}
	}
}


SCENARIO ( "Graph edges work correctly" ) {

	GIVEN ( "A graph edge with initial values" ) {
		GraphNode* source = new GraphNode(1, 10);
		GraphNode* destination = new GraphNode(2, 20);
		GraphEdge edge(source, destination, 100);

		WHEN ( "I get the values of attributes of edge" ) {

			THEN ( "They look like the initial values I set" ) {
				REQUIRE( edge.getSource() == source );
				REQUIRE( edge.getDestination() == destination );
				REQUIRE( edge.getWeight() == 100 );
			}
		}

		WHEN ( "I set a new value for its weight" ) {
			edge.setWeight(200);

			THEN ( "When I get the edge's weight, it should be the new one" ) {
				REQUIRE( edge.getWeight() == 200 );
			}
		}

		delete source;
		delete destination;
	}
}

SCENARIO ( "Graph attributes" ) {

	GIVEN ( "A new empty graph" ) {
		Graph g;		

		WHEN ( "I get its size and check if it's empty" ) {

			THEN ( "Size should be 0 and it should be empty" ) {
				REQUIRE( g.getNumberOfNodes() == 0 );
				REQUIRE( g.getNumberOfEdges() == 0 );
				REQUIRE( g.isEmpty() );
			}
		}
		
		WHEN ( "I add a new node" ) {
			g.addNode(10);

			THEN ( "Sizes and empty status should reflect the new node" ) {
				REQUIRE( g.getNumberOfNodes() == 1 );
				REQUIRE( g.getNumberOfEdges() == 0 );
				REQUIRE( !g.isEmpty() );
			}
		}
	}
}

SCENARIO ( "Graph basic nodes management" ) {

	GIVEN ( "An empty graph" ) {
		Graph g;
		
		WHEN ( "I add a node and search for its id" ) {
			g.addNode(10);
			
			THEN ( "I should find a valid element" ) {
				REQUIRE ( g.hasNodeWithId(1) );
				REQUIRE ( g.searchNodeById(1) != NULL );
			}
		}

		WHEN ( "I add a node and search for its value" ) {
			g.addNode(20);
			
			THEN ( "I should find a valid element" ) {
				REQUIRE ( g.hasNodeWithValue(20) );
				REQUIRE ( g.searchNodeByValue(20) != NULL );
			}
		}

		WHEN ( "I add somes nodes" ) {
			for (int i = 0; i < 100; i++) {
				g.addNode(i*100);
			}			
			
			THEN ( "Sizes and empty status should reflect the new nodes" ) {
				REQUIRE( g.getNumberOfNodes() == 100 );
				REQUIRE( g.getNumberOfEdges() == 0 );
				REQUIRE( !g.isEmpty() );
			}
		}
		
		WHEN ( "I add somes nodes" ) {
			for (int i = 0; i < 100; i++) {
				g.addNode(i*100);
			}			
			
			THEN ( "I should be able to get all of them by id and value" ) {
				for (int i = 0; i < 100; i++) {
					REQUIRE( g.hasNodeWithId(i+1) );
					REQUIRE( g.searchNodeById(i+1) != NULL );
				}

				for (int i = 0; i < 100; i++) {
					REQUIRE( g.hasNodeWithValue(i*100) );
					REQUIRE( g.searchNodeByValue(i*100) != NULL );
				}
			}
		}
		
		WHEN ( "I add somes nodes and remove half" ) {
			for (int i = 0; i < 100; i++) {
				g.addNode(i*100);
			}			
			
			for (int i = 0; i < 100; i += 2) {
				g.removeNodeById(i+1);
			}
			
			THEN ( "Sizes and empty status should reflect half of the nodes" ) {
				REQUIRE( g.getNumberOfNodes() == 50 );
				REQUIRE( g.getNumberOfEdges() == 0 );
				REQUIRE( !g.isEmpty() );
			}
		}
		
		WHEN ( "I add somes nodes and remove invalid ids" ) {
			for (int i = 0; i < 100; i++) {
				g.addNode(i*100);
			}			
			
			for (int i = 100; i < 200; i++) {
				g.removeNodeById(i+1);
			}
			
			THEN ( "Sizes and empty status should reflect still all the nodes" ) {
				REQUIRE( g.getNumberOfNodes() == 100 );
				REQUIRE( g.getNumberOfEdges() == 0 );
				REQUIRE( !g.isEmpty() );
			}
		}
	}
}

SCENARIO ( "Graph max/least values of nodes" ) {

	GIVEN ( "A graph with some pre-defined nodes" ) {
		Graph g;		
		for (int i = -10; i <= 10; i++) g.addNode(i);
		
		WHEN ( "I search for biggest value of node" ) {
		
			THEN ( "I find a valid node" ) {
				REQUIRE( g.hasNodeWithValue(10) );
			}
		}
		
		WHEN ( "I get the biggest value" ) {

			THEN ( "I find the biggest value I inserted" ) {
				REQUIRE( g.getNodesMaxValue() == 10 );
			}
		}
		
		WHEN ( "I remove the biggest value" ) {
			g.removeNodeMaxValue();
			
			THEN ( "I can't find the biggest value i inserted" ) {
				REQUIRE( g.getNodesMaxValue() == 9 );
				REQUIRE( !g.hasNodeWithValue(10) );
			}
		}
		
		WHEN ( "I search for least value of node" ) {
		
			THEN ( "I find a valid node" ) {
				REQUIRE( g.hasNodeWithValue(-10) );
			}
		}
		
		
		WHEN ( "I get the smallest value" ) {
			
			THEN ( "I find the least value i inserted" ) {
				REQUIRE( g.getNodesLeastValue() == -10 );
			}
		}
		
		WHEN ( "I remove the smallest value" ) {
			g.removeNodeLeastValue();
			
			THEN ( "I can't find the least value i inserted" ) {
				REQUIRE( g.getNodesLeastValue() == -9 );
				REQUIRE( !g.hasNodeWithValue(-10) );
			}
		}
		
		WHEN ( "Add nodes with all new same values and remove them" ) {
			for (int i = 0; i < 1000; i++) {
				g.addNode(555);
			}
			
			g.removeNodesByValue(555);
			
			THEN ( "Count of nodes must return to count before adding them" ) {
				REQUIRE( g.getNumberOfNodes() == 21 );
			}
		}
	}
}

SCENARIO ( "Graph edges management" ) {

	GIVEN ( "A graph with some pre-defined nodes" ) {
		Graph g;		
		for (int i = 0; i < 10; i++) g.addNode(i);
		
		WHEN ( "I add a new edge" ) {
			g.addEdge(1, 2, 12);
		
			THEN ( "The edge count must change" ) {
				REQUIRE( g.getNumberOfEdges() == 1 );
			}
		}
		
		WHEN ( "I add multiple new edges" ) {
			for (int i = 1; i <= 1000; i++) {
				g.addEdge(i%10 + 1, (i+1)%10 + 1, i*10);
			}
		
			THEN ( "The edge count must change" ) {
				REQUIRE( g.getNumberOfEdges() == 1000 );
			}
		}
		
		WHEN ( "I add an edge with a specific weight and search for it by weight" ) {
			g.addEdge(1,2, 51.0);
			g.addEdge(1,2, 132.0);
			g.addEdge(1,2, 47.0);
		
			THEN ( "I should find it" ) {
				REQUIRE( g.searchEdgeByWeight(132.0) != NULL );
				REQUIRE( g.searchEdgeByWeight(51.0) != NULL );
				REQUIRE( g.searchEdgeByWeight(47.0) != NULL );
			}
		}
		
		WHEN ( "I add an edge with a specific weight, remove it and search for it by weight" ) {
			g.addEdge(1,2, 51.0);
			g.addEdge(1,2, 132.0);
			g.addEdge(1,2, 47.0);
			g.removeEdgesByWeight(47.0);
		
			THEN ( "I shouldn't find it" ) {
				REQUIRE( g.searchEdgeByWeight(132.0) != NULL );
				REQUIRE( g.searchEdgeByWeight(51.0) != NULL );
				REQUIRE( g.searchEdgeByWeight(47.0) == NULL );
			}
		}

		WHEN ( "I add an edge with a given node path and search for it" ) {
			g.addEdge(1,2, 51.0);
			g.addEdge(2,3, 132.0);
			g.addEdge(3,2, 47.0);

			THEN ( "I should find it" ) {
				REQUIRE( g.searchEdgeByNodePath(1,2) != NULL );
				REQUIRE( g.searchEdgeByNodePath(2,3) != NULL );
				REQUIRE( g.searchEdgeByNodePath(3,2) != NULL );
			}
		}

		WHEN ( "I add an edge with a given node path, remove it and search for it" ) {
			g.addEdge(1,2, 51.0);
			g.addEdge(2,3, 132.0);
			g.addEdge(3,2, 47.0);
			g.removeEdgeByNodePath(2,3);

			THEN ( "I shouldn't find it" ) {
				REQUIRE( g.searchEdgeByNodePath(1,2) != NULL );
				REQUIRE( g.searchEdgeByNodePath(2,3) == NULL );
				REQUIRE( g.searchEdgeByNodePath(3,2) != NULL );
			}
		}
	}
}

SCENARIO ( "Getting edges' according to tail and arrows" ) {
	GIVEN ( "A graph with some pre-defined nodes and edges" ) {
		Graph g;
		for (int i = 1; i <= 5; i++) g.addNode(0);
		for (int i = 2; i <= 5; i++) g.addEdge(1, i, 5*i);
		g.addEdge(5, 2, 100);

		WHEN ( "I look for the destinations of the first node" ) {
			auto v = g.getEdgesWhereNodeIsSource(1);
			sort(v.begin(), v.end(), [](GraphEdge* lhs, GraphEdge* rhs) {
				return lhs->getDestination()->getId() < 
					rhs->getDestination()->getId();
			});
			
			THEN ( "I should find out all the other nodes that it points to" ) {
				REQUIRE( v[0]->getDestination()->getId() == 2 );
				REQUIRE( v[0]->getSource()->getId() == 1 );
				REQUIRE( v[1]->getDestination()->getId() == 3 );
				REQUIRE( v[1]->getSource()->getId() == 1 );
				REQUIRE( v[2]->getDestination()->getId() == 4 );
				REQUIRE( v[2]->getSource()->getId() == 1 );
				REQUIRE( v[3]->getDestination()->getId() == 5 );
				REQUIRE( v[3]->getSource()->getId() == 1 );
			}
		}

		WHEN ( "I look for the sources of a given node" ) {
			auto v = g.getEdgesWhereNodeIsDestination(2);
			sort(v.begin(), v.end(), [](GraphEdge* lhs, GraphEdge* rhs) {
				return lhs->getDestination()->getId() < 
					rhs->getDestination()->getId();
			});

			THEN ( "I should find all the nodes that points to the given node" ) {
				REQUIRE( v[0]->getDestination()->getId() == 2 );
				REQUIRE( v[0]->getSource()->getId() == 1 );
				REQUIRE( v[1]->getDestination()->getId() == 2 );
				REQUIRE( v[1]->getSource()->getId() == 5 );
			}
		}
	}
}

SCENARIO ( "Djikstra Shortest Path Algorithm" ) {
	
	GIVEN ( "A graph with some predefined nodes and edges" ) {
		Graph g;
		for (int i = 1; i <= 4; i++) g.addNode(i);
		g.addEdge(1,2,24);
		g.addEdge(2,1,24);
		g.addEdge(1,4,20);
		g.addEdge(4,1,20);
		g.addEdge(3,1,3);
		g.addEdge(1,3,3);
		g.addEdge(4,3,12);
		g.addEdge(3,4,12);
		
		WHEN ( "I look for the shortest path of a given node" ) {
			auto shortestDistances = g.djikstra(1);

			THEN ( "The shortest path should be calculated for every other node" ) {
				REQUIRE( shortestDistances[1] == 0 );
				REQUIRE( shortestDistances[2] == 24 );
				REQUIRE( shortestDistances[3] == 3 );
				REQUIRE( shortestDistances[4] == 15 );
			}
		}
	}
}

SCENARIO ( "Cleaning Graph" ) {
	GIVEN ( "A graph with some nodes and edges" ) {
		Graph g;
		for (int i = 0; i < 1000; i++) g.addNode(i*100);
		for (int i = 0; i < 100; i++) g.addEdge(i+1, i+2, i*12);

		WHEN ( "I count the number of nodes and edges" ) {
			THEN ( "The number of elements should be the same that I created" ) {
				REQUIRE( g.getNumberOfNodes() == 1000 );
				REQUIRE( g.getNumberOfEdges() == 100 );
			}
		}

		WHEN ( "I clear the graph" ) {
			g.clear();

			THEN ( "The numbers of elements of the graph should be zero" ) {
				REQUIRE( g.getNumberOfNodes() == 0 );
				REQUIRE( g.getNumberOfEdges() == 0 );
			}
		}
	}
}
