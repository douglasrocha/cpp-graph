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
