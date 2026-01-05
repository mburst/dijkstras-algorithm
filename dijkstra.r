use std::cmp::Ordering;
use std::collections::BinaryHeap;

#[derive(Clone, Copy, Eq, PartialEq)]
struct Node {
    id: usize,
    dist: i32,
}

impl Ord for Node {
    fn cmp(&self, other: &Node) -> Ordering {
        other.dist.cmp(&self.dist)
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Node) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Edge {
    to: usize,
    cost: i32,
}

fn dijkstra(nodes: &Vec<Vec<Edge>>, start: usize) -> Vec<i32> {
    let mut dist = vec![i32::MAX; nodes.len()];
    let mut pq = BinaryHeap::new();

    dist[start] = 0;
    pq.push(Node { id: start, dist: 0 });

    while let Some(Node { id, dist: _ }) = pq.pop() {
        for edge in &nodes[id] {
            let new_dist = dist[id] + edge.cost;
            if new_dist < dist[edge.to] {
                dist[edge.to] = new_dist;
                pq.push(Node {
                    id: edge.to,
                    dist: new_dist,
                });
            }
        }
    }

    dist
}

fn main() {
    let nodes = vec![
        vec![Edge { to: 1, cost: 4 }, Edge { to: 2, cost: 2 }],
        vec![Edge { to: 3, cost: 1 }],
        vec![Edge { to: 1, cost: 1 }, Edge { to: 3, cost: 5 }],
        vec![],
    ];
    let dist = dijkstra(&nodes, 0);
    println!("{:?}", dist);
}