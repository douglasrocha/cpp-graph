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

			THEN ( "When I get the edge's edge, its weight should be the new one" ) {
				REQUIRE( edge.getWeight() == 200 );
			}
		}

		delete source;
		delete destination;
	}
}
