import unittest
from dijkstras import Graph

class Graph_Test(unittest.TestCase):
    
    #Runs before each test
    def setUp(self):
        self.graph = Graph()
    
    def test_add_vertex(self):
        self.graph.add_vertex('A', {'B': 7, 'C': 8})
        self.assertEqual(self.graph.vertices, {'A': {'C': 8, 'B': 7}})
        
    def test_shortest_path(self, ):
        self.graph.add_vertex('A', {'B': 7, 'C': 8})
        self.graph.add_vertex('B', {'A': 7, 'F': 2})
        self.graph.add_vertex('C', {'A': 8, 'F': 6, 'G': 4})
        self.graph.add_vertex('D', {'F': 8})
        self.graph.add_vertex('E', {'H': 1})
        self.graph.add_vertex('F', {'B': 2, 'C': 6, 'D': 8, 'G': 9, 'H': 3})
        self.graph.add_vertex('G', {'C': 4, 'F': 9})
        self.graph.add_vertex('H', {'E': 1, 'F': 3})
        
        self.assertEqual(self.graph.shortest_path('A', 'H'), ['H', 'F', 'B'])
        self.assertEqual(self.graph.shortest_path('H', 'I'), {'A': 12, 'B': 5, 'C': 9, 'D': 11, 'E': 1, 'F': 3, 'G': 12, 'H': 0})

unittest.main()