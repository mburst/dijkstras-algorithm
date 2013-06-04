require 'test/unit'
require_relative 'dijkstras'

class Graph_Test < Test::Unit::TestCase
    
    #Runs before each test
    def setup
        @graph = Graph.new
    end
    
    def test_add_vertex
        @graph.add_vertex('A', {'B' => 7, 'C' => 8})
        assert_equal({"A"=>{"B"=>7, "C"=>8}}, @graph.instance_variable_get(:@vertices), "Failed to add vertex")
    end
    
    def test_shortest_path
        @graph.add_vertex('A', {'B' => 7, 'C' => 8})
        @graph.add_vertex('B', {'A' => 7, 'F' => 2})
        @graph.add_vertex('C', {'A' => 8, 'F' => 6, 'G' => 4})
        @graph.add_vertex('D', {'F' => 8})
        @graph.add_vertex('E', {'H' => 1})
        @graph.add_vertex('F', {'B' => 2, 'C' => 6, 'D' => 8, 'G' => 9, 'H' => 3})
        @graph.add_vertex('G', {'C' => 4, 'F' => 9})
        @graph.add_vertex('H', {'E' => 1, 'F' => 3})
        
        assert_equal(['H', 'F', 'B'], @graph.shortest_path('A', 'H'), 'Failed to find shortest path')
        assert_equal({'A' => 12, 'B' => 5, 'C' => 9, 'D' => 11, 'E' => 1, 'F' => 3, 'G' => 12, 'H' => 0}, @graph.shortest_path('H', 'I'), 'Failed to find shortest paths from root node')
    end
end