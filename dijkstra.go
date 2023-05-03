type edge struct {
    to   int
    cost int
}

type node struct {
    id    int
    dist  int
    edges []edge
}

func dijkstra(nodes []node, start int) []int {
    const inf = 1<<31 - 1
    dist := make([]int, len(nodes))
    for i := range dist {
        dist[i] = inf
    }
    dist[start] = 0
    pq := priorityQueue{{start, 0}}
    for len(pq) > 0 {
        curr := pq.pop()
        if dist[curr.id] < curr.dist {
            continue
        }
        for _, e := range nodes[curr.id].edges {
            if newDist := dist[curr.id] + e.cost; newDist < dist[e.to] {
                dist[e.to] = newDist
                pq.push(node{e.to, newDist})
            }
        }
    }
    return dist
}

type priorityQueue []node

func (pq *priorityQueue) push(n node) {
    heap.Push(pq, n)
}

func (pq *priorityQueue) pop() node {
    return heap.Pop(pq).(node)
}

func (pq priorityQueue) Len() int {
    return len(pq)
}

func (pq priorityQueue) Less(i, j int) bool {
    return pq[i].dist < pq[j].dist
}

func (pq priorityQueue) Swap(i, j int) {
    pq[i], pq[j] = pq[j], pq[i]
}

func (pq *priorityQueue) Push(x interface{}) {
    *pq = append(*pq, x.(node))
}

func (pq *priorityQueue) Pop() interface{} {
    old := *pq
    n := len(old)
    item := old[n-1]
    *pq = old[0 : n-1]
    return item
}

func main() {
    nodes := []node{
        {0, 0, []edge{{1, 4}, {2, 2}}},
        {1, math.MaxInt32, []edge{{3, 1}}},
        {2, math.MaxInt32, []edge{{1, 1}, {3, 5}}},
        {3, math.MaxInt32, []edge{}},
    }
    dist := dijkstra(nodes, 0)
    fmt.Println(dist)
}