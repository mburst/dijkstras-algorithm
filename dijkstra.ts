
/**
 * A node for priorioty linked list / stack and such
 */
class PriorityNode {
	key:number;
	priority:number;

	constructor(key: number,priority: number){
		this.key = key;
		this.priority = priority;
	}
}

/**
 * A priority queue with highest priority always on top
 * This queue is sorted by priority for each enqueue
 */
class PriorityQueue {

	nodes:PriorityNode[] = [];

	/**
	 * Enqueue a new node
	 * @param {[type]} priority
	 * @param {[type]} key     
	 */
	enqueue(priority:number, key:number){
		this.nodes.push(new PriorityNode(key, priority));
		this.nodes.sort(
			function(a, b) {
				return a.priority - b.priority;
			}
		)
	}

	/**
	 * Dequeue the highest priority key
	 */
	dequeue():number{
		return this.nodes.shift().key;
	}

	/**
	 * Checks if empty
	 */
	empty():boolean{
		return !this.nodes.length;
	}
}

/**
 * Computes the shortest path between two node
 */
class Dijkstra{

	infinity = 1/0;
	vertices = {};

	/**
	 * Add a new vertex and related edges
	 * @param {[type]} name  [description]
	 * @param {[type]} edges [description]
	 */
	addVertex(name:string, edges:any){
		this.vertices[name] = edges;
	}

	/**
	 * Computes the shortest path from start to finish
	 * @param {[type]} start  [description]
	 * @param {[type]} finish [description]
	 */
	shortestPath(start:string, finish:string){

		let nodes = new PriorityQueue(),
		distances = {},
		previous = {},
		path = [],
		smallest, 
		vertex, 
		neighbor, 
		alt;

		//Init the distances and queues variables
		for(vertex in this.vertices){
			if(vertex === start){
				distances[vertex] = 0;
				nodes.enqueue(0, vertex);
			}else{
				distances[vertex] = this.infinity;
				nodes.enqueue(this.infinity, vertex);
			}

			previous[vertex] = null;
		}

		//continue as long as the queue haven't been emptied.
		while(!nodes.empty()){


			smallest = nodes.dequeue();

			//we are the last node
			if(smallest === finish){

				//Compute the path
				while(previous[smallest]){
					path.push(smallest);
					smallest = previous[smallest];
				}
				break;
			}

			//No distance known. Skip.
			if(!smallest || distances[smallest] === this.infinity){
				continue;
			}

			//Compute the distance for each neighbor
			for(neighbor in this.vertices[smallest]){
				alt = distances[smallest] + this.vertices[smallest][neighbor];

				if(alt < distances[neighbor]){
					distances[neighbor] = alt;
					previous[neighbor] = smallest;
					nodes.enqueue(alt, neighbor);
				}
			}
		}
		//the starting point isn't in the solution & 
		//the solution is from end to start.
		return path.concat(start).reverse();
	}
}

let graph:Dijkstra = new Dijkstra();
graph.addVertex('A', { B: 7, C: 8 });
graph.addVertex('C', { A: 8 });
graph.addVertex('B', { A: 7, F: 8 });
graph.addVertex('F', { B: 8 });

console.log(graph.shortestPath('A', 'F'));