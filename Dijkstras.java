import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;

public class Dijkstras {

	public static void main(String[] args) {
		Graph g = new Graph();
		g.addVertex('A', Arrays.asList(new Vertex('B', 7), new Vertex('C', 8)));
		g.addVertex('B', Arrays.asList(new Vertex('A', 7), new Vertex('F', 2)));
		g.addVertex('C', Arrays.asList(new Vertex('A', 8), new Vertex('F', 6), new Vertex('G', 4)));
		g.addVertex('D', Arrays.asList(new Vertex('F', 8)));
		g.addVertex('E', Arrays.asList(new Vertex('H', 1)));
		g.addVertex('F', Arrays.asList(new Vertex('B', 2), new Vertex('C', 6), new Vertex('D', 8), new Vertex('G', 9), new Vertex('H', 3)));
		g.addVertex('G', Arrays.asList(new Vertex('C', 4), new Vertex('F', 9)));
		g.addVertex('H', Arrays.asList(new Vertex('E', 1), new Vertex('F', 3)));
		System.out.println(g.getShortestPath('A', 'H'));
	}
	
}

class Vertex implements Comparable<Vertex> {
	
	private Character id;
	private Integer distance;
	
	public Vertex(Character id, Integer distance) {
		super();
		this.id = id;
		this.distance = distance;
	}

	public Character getId() {
		return id;
	}

	public Integer getDistance() {
		return distance;
	}

	public void setId(Character id) {
		this.id = id;
	}

	public void setDistance(Integer distance) {
		this.distance = distance;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((distance == null) ? 0 : distance.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Vertex other = (Vertex) obj;
		if (distance == null) {
			if (other.distance != null)
				return false;
		} else if (!distance.equals(other.distance))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Vertex [id=" + id + ", distance=" + distance + "]";
	}

	@Override
	public int compareTo(Vertex o) {
		if (this.distance < o.distance)
			return -1;
		else if (this.distance > o.distance)
			return 1;
		else
			return this.getId().compareTo(o.getId());
	}
	
}

class Graph {
	
	private final Map<Character, List<Vertex>> vertices;
	
	public Graph() {
		this.vertices = new HashMap<Character, List<Vertex>>();
	}
	
	public void addVertex(Character character, List<Vertex> vertex) {
		this.vertices.put(character, vertex);
	}
	
	public List<Character> getShortestPath(Character start, Character finish) {
		final Map<Character, Integer> distances = new HashMap<Character, Integer>();
		final Map<Character, Vertex> previous = new HashMap<Character, Vertex>();
		PriorityQueue<Vertex> nodes = new PriorityQueue<Vertex>();
		
		for(Character vertex : vertices.keySet()) {
			if (vertex == start) {
				distances.put(vertex, 0);
				nodes.add(new Vertex(vertex, 0));
			} else {
				distances.put(vertex, Integer.MAX_VALUE);
				nodes.add(new Vertex(vertex, Integer.MAX_VALUE));
			}
			previous.put(vertex, null);
		}
		
		while (!nodes.isEmpty()) {
			Vertex smallest = nodes.poll();
			if (smallest.getId() == finish) {
				final List<Character> path = new ArrayList<Character>();
				while (previous.get(smallest.getId()) != null) {
					path.add(smallest.getId());
					smallest = previous.get(smallest.getId());
				}
				return path;
			}

			if (distances.get(smallest.getId()) == Integer.MAX_VALUE) {
				break;
			}
						
			for (Vertex neighbor : vertices.get(smallest.getId())) {
				Integer alt = distances.get(smallest.getId()) + neighbor.getDistance();
				if (alt < distances.get(neighbor.getId())) {
					distances.put(neighbor.getId(), alt);
					previous.put(neighbor.getId(), smallest);
					
					forloop:
					for(Vertex n : nodes) {
						if (n.getId() == neighbor.getId()) {
							nodes.remove(n);
							n.setDistance(alt);
							nodes.add(n);
							break forloop;
						}
					}
				}
			}
		}
		
		return new ArrayList<Character>(distances.keySet());
	}
	
}
