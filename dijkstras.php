<?php
class PriorityQueue extends SplPriorityQueue
{
    public function compare( $priority1, $priority2 )
    {
        if ($priority1 === $priority2) return 0;
        return $priority1 < $priority2 ? 1 : -1;
    }
}

class Graph
{
  private $verticies;

	function __construct()
	{
		$this->verticies = array();
	}

	public function add_vertex( $name, $edges )
	{
		$this->verticies[ $name ] = $edges;
	}

	public function shortest_path( $start, $finish )
	{
		$distances = array();
		$previous = array();
		$nodes = new PriorityQueue();

		foreach ( $this->verticies AS $vertex => $value )
		{
			if ( $vertex === $start )
			{
				$distances[ $vertex ] = 0;
				$nodes->insert( $vertex, 0 );
			}
			else
			{
				$distances[ $vertex ] = PHP_INT_MAX;
				$nodes->insert( $vertex, PHP_INT_MAX );
			}
			$previous[ $vertex ] = null;
		}

		$nodes->top();
		while ( $nodes->valid() )
		{
			$smallest = $nodes->current();

			if ( $smallest === $finish )
			{
				$path = array();
				while ( $previous[ $smallest ] )
				{
					$path[] = $smallest;
					$smallest = $previous[ $smallest ];
				}
				$path[] = $start;

				return array_reverse( $path );
			}

			if ( $smallest === null || $distances[ $smallest ] === PHP_INT_MAX )
			{
				break;
			}

			foreach ( $this->verticies[ $smallest ] AS $neighbor => $value )
			{
				$alt = $distances[ $smallest ] + $this->verticies[ $smallest ][ $neighbor ];
				if ( $alt < $distances[ $neighbor ] )
				{
					$distances[ $neighbor ] = $alt;
					$previous[ $neighbor ] = $smallest;
					$nodes->insert( $neighbor, $alt );

				}
			}

			$nodes->next();
		}

		return $distances;
	}

	public function __toString()
	{
		return print_r( $this->verticies, true );
	}
}

$graph = new Graph();
$graph->add_vertex( 'A', array( 'B' => 7, 'C' => 8 ) );
$graph->add_vertex( 'B', array( 'A' => 7, 'F' => 2 ) );
$graph->add_vertex( 'C', array( 'A' => 8, 'F' => 6, 'G' => 4 ) );
$graph->add_vertex( 'D', array( 'F' => 8 ) );
$graph->add_vertex( 'E', array( 'H' => 1 ) );
$graph->add_vertex( 'F', array( 'B' => 2, 'C' => 6, 'D' => 8, 'G' => 9, 'H' => 3 ) );
$graph->add_vertex( 'G', array( 'C' => 4, 'F' => 9 ) );
$graph->add_vertex( 'H', array( 'E' => 1, 'F' => 3 ) );
print_r($graph->shortest_path('A', 'H'));
