/*
    Dijkstra's heap implementation
*/


#include<iostream>

using namespace std;

class Node{
    public:
        int ind;
        int weight;
        Node * next;

        Node(int i , int wt){
            ind = i;
            weight = wt;
            next = NULL;
        }
};

class Graph{
    private:
        int vrt , edg;
        
        Node ** adj;
        Node ** tail;
        

    public:

        void add_edge(int u , int v , int wt);

        int djk_algo(int src , int dst);

        Graph(int v , int e){
            this->vrt = v;
            this->edg = e;
            adj = new Node * [vrt];
            tail = new Node * [vrt];

            for(int i = 0 ; i < vrt ; ++i){
                adj[i] = NULL;
                tail[i] = NULL;
            }

        }
};

int main(){

    int v,e;
    cout<<"Enter no of vertices and edges: ";
    cin>>v>>e;
    Graph g1(v,e);

    cout<<"Enter vertice 1 , vertice 2 , weight of edge: ";
    for(int i = 0 ; i < e ; ++i){
        int v1,v2,wt;
        cin>>v1>>v2>>wt;
        g1.add_edge(v1,v2,wt);
    }

    int sr,dst;
    cout<<"Enter source and dest: ";
    cin>>sr>>dst;
    
    int distance = g1.djk_algo(sr,dst);
    cout<<"Minimum distance between "<<sr<<" and "<<dst<<" is "<<distance<<endl;


    return 0;
}

void Graph::add_edge(int u , int v , int wt){

    if(tail[u] == NULL){
        adj[u] = new Node(v , wt);
        tail[u] = adj[u];
    }
    else{
        tail[u]->next = new Node(v , wt);
        tail[u] = tail[u]->next;
    }

    if(tail[v] == NULL){
        adj[v] = new Node(u , wt);
        tail[v] = adj[v];
    }
    else{
        tail[v]->next = new Node(u , wt);
        tail[v] = tail[v]->next;
    }

    return ;
}

void heapify(int * heap , int i , int size , int * dist , int * index){

    while(i != size - 1){

        int crr = i;
        int li = 2*i + 1 , ri = 2*i + 2;

        if(li < size && dist[heap[li]] < dist[heap[crr]]){
            crr = li;
        }

        if(ri < size && dist[heap[ri]] < dist[heap[crr]]){
            crr = ri;
        }

        if(crr == i){
            return ;
        }


        int temp = heap[crr];
        heap[crr] = heap[i];
        heap[i] = temp;

        index[heap[crr]] = crr;
        index[heap[i]] = i;

        i = crr;
    }

}

void dec_key(int * heap , int i , int size , int * dist , int * index){

    while(i != 0){

        int par = (i - 1)/2;

        if(dist[heap[par]] > dist[heap[i]]){
            
            int temp = heap[par];
            heap[par] = heap[i];
            heap[i] = temp;
            

            index[heap[par]] = par;
            index[heap[i]] = i;

            i = par;
        }
        else{
            return ;
        }

    }
    return ;
}

int Graph::djk_algo(int src , int dst){

    int * dist = new int [this->vrt];
    for(int i = 0 ; i < this->vrt ; ++i){
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    int size = this->vrt;

    int * heap = new int [size];

    int * index = new int [size]; // index of vertex in heap

    for(int i = 0 ; i < size ; ++i){
        heap[i] = i;
        index[i] = i;
    }

    

    for(int i = size - 1 ; i >= 0 ; i--){
        heapify(heap , i , size , dist , index);
    }

    while(size > 0){

        int ind = heap[0];

        Node * crr = adj[ind];

        while(crr != NULL){

            if(dist[crr->ind] > dist[ind] + crr->weight){

                dist[crr->ind] = dist[ind] + crr->weight;
                int r_ind = index[crr->ind];
                dec_key(heap , r_ind , size , dist , index);

            }

            crr = crr->next;
        }

        heap[0] = heap[size - 1];
        index[heap[0]] = 0;
        size--;
        heapify(heap , 0 , size , dist , index);
    }

    int ans = dist[dst];

    delete []index;
    delete []dist;
    delete []heap;
    return ans;
}


