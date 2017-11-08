PriorityQueue = ->
  @_nodes = []
  @enqueue = (priority, key) ->
    @_nodes.push
      key : key
      priority : priority
    @sort()
    return
  @dequeue = ->
    @_nodes.shift().key
  @sort = ->
    @_nodes.sort = (a, b) ->
      a.priority - b.priority
    return
  @isEmpty = ->
    !@_nodes.length
  return

Graph = ->
  INFINITY = 1 / 0
  @vertices = {}
  @addVertex = (name, edges) ->
    @vertices[name] = edges
    return
  @shortestPath = (start, finish) ->
    nodes = new PriorityQueue
    distances = {}
    previous = {}
    path = []
    smallest = undefined
    vertex = undefined
    neighbor = undefined
    alt = undefined

    for vertex of @vertices
      if vertex is start
        distances[vertex] = 0
        nodes.enqueue(0, vertex)
      else
        distances[vertex] = INFINITY
        nodes.enqueue(INFINITY, vertex)
      previous[vertex] = null

    while not nodes.isEmpty()
      smallest = nodes.dequeue()

      if smallest is finish
        path = []
        while previous[smallest]
          path.push smallest
          smallest = previous[smallest]
        break

      if not smallest or distances[smallest] is INFINITY
        continue
      for neighbor of @vertices[smallest]
        alt = distances[smallest] + @vertices[smallest][neighbor]
        if alt < distances[neighbor]
          distances[neighbor] = alt
          previous[neighbor] = smallest
          nodes.enqueue alt, neighbor
    path
  return

g = new Graph()

g.addVertex 'A',
  B: 7
  C: 8
g.addVertex 'B',
  A: 7
  F: 2
g.addVertex 'C',
  A: 8
  F: 6
  G: 4
g.addVertex 'D', F: 8
g.addVertex 'E', H: 1
g.addVertex 'F',
  B: 2
  C: 6
  D: 8
  G: 9
  H: 3
g.addVertex 'G',
  C: 4
  F: 9
g.addVertex 'H',
  E: 1
  F: 3

console.log g.shortestPath('A', 'H').concat(['A']).reverse()
