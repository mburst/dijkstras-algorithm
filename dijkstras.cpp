#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename VertexT = char, typename DistanceT = int>
class Graph
{
    unordered_map<VertexT, const unordered_map<VertexT, DistanceT>> vertices;
    
public:
    void add_vertex(VertexT name, const unordered_map<VertexT, DistanceT>& edges)
    {
        vertices.insert(typename unordered_map<VertexT, const unordered_map<VertexT, DistanceT>>::value_type(name, edges));
    }
    
    vector<VertexT> shortest_path(VertexT start, VertexT finish)
    {
        unordered_map<VertexT, DistanceT> distances;
        unordered_map<VertexT, VertexT> previous;
        vector<VertexT> nodes;
        vector<VertexT> path;
        
        auto comparator = [&] (VertexT left, VertexT right) { return distances[left] > distances[right]; };

        for (auto& vertex : vertices)
        {
            if (vertex.first == start)
            {
                distances[vertex.first] = 0;
            }
            else
            {
                distances[vertex.first] = numeric_limits<DistanceT>::max();
            }
            
            nodes.push_back(vertex.first);
            push_heap(begin(nodes), end(nodes), comparator);
        }
        
        while (!nodes.empty())
        {
            pop_heap(begin(nodes), end(nodes), comparator);
            VertexT smallest = nodes.back();
            nodes.pop_back();
            
            if (smallest == finish)
            {
                while (previous.find(smallest) != end(previous))
                {
                    path.push_back(smallest);
                    smallest = previous[smallest];
                }
                
                break;
            }
            
            if (distances[smallest] == numeric_limits<DistanceT>::max())
            {
                break;
            }
            
            for (auto& neighbor : vertices[smallest])
            {
                DistanceT alt = distances[smallest] + neighbor.second;
                if (alt < distances[neighbor.first])
                {
                    distances[neighbor.first] = alt;
                    previous[neighbor.first] = smallest;
                    make_heap(begin(nodes), end(nodes), comparator);
                }
            }
        }
        
        return path;
    }
};

int main()
{
    Graph<> g;
    g.add_vertex('A', {{'B', 7}, {'C', 8}});
    g.add_vertex('B', {{'A', 7}, {'F', 2}});
    g.add_vertex('C', {{'A', 8}, {'F', 6}, {'G', 4}});
    g.add_vertex('D', {{'F', 8}});
    g.add_vertex('E', {{'H', 1}});
    g.add_vertex('F', {{'B', 2}, {'C', 6}, {'D', 8}, {'G', 9}, {'H', 3}});
    g.add_vertex('G', {{'C', 4}, {'F', 9}});
    g.add_vertex('H', {{'E', 1}, {'F', 3}});
    
    for (const auto& vertex : g.shortest_path('A', 'H'))
    {
        cout << vertex << endl;
    }
    
    return 0;
}
