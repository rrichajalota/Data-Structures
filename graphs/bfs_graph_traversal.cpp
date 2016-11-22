//Breadth First Traversal in graphs 
#include <iostream>
#include <queue>
using namespace std;

#define MAXV 1000 // no. of vertices 
bool processed[MAXV+1];
bool discovered[MAXV+1];
int parent[MAXV+1];

struct edgenode{
	int y;       // the node it connects to 
	int weight; //edge weight
	edgenode *next; // next edge in this list
};

struct graph{
	edgenode *edges[MAXV + 1]; //edges in a graph
	int degree[MAXV+1]; //OUT DEGREE OF EACH VERTEX
	int nvertices;      //no. of vertices in a graph
	int nedges;         //no. of edges in a graph
	bool directed;      // is the graph directed or not
};

void initialize_graph(graph *g, bool directed){
	int i;
	g->nvertices=0;
	g->nedges= 0;
	g->directed= directed;
	
	for(i =1; i <=MAXV; i++)
		g->degree[i]= 0;
		
	for(i=1; i <= MAXV; i++)
		g->edges[i]= NULL;
}

void insert_edge(graph *g, int x, int y, bool directed){
	edgenode *p = new edgenode;   // temp. pointer
	p->weight=0;
	p->y=y;
	p->next= g->edges[x];
	g->edges[x]= p; // inserted p at the head of the list
	g->degree[x]++; 
	
	if(directed == false)
		insert_edge(g,y,x,true);
	else 
		g->nedges++;
}

//reading a graph as input from the user
void read_graph(graph *g, bool directed){
	int i;
	int num_edges;   //no. of edges 
	int x, y; 		// vertices in an edge (x,y)
	
	initialize_graph(g, directed);
	
	cin>>g->nvertices>>num_edges;   // In the first line user enters no. of vertices and no. of edges
	
	for(i=1; i<=num_edges; i++){	// User then enters the endpoints (x,y) for the no. of edges
		cin>>x>>y;
		insert_edge(g,x,y,directed);
	}
}

//print the graph
void print_graph(graph *g){
	int i;
	edgenode* p; 
	for(i=1; i <= g->nvertices; i++){
		cout<<i<<"->";
		p= g->edges[i];
		while(p != NULL){
			cout<< p->y<<"\t";
			p= p->next;
		}
		cout<<endl;
	}
}

/* -------------code for BFS-----------------------*/
void initialize_search(graph *g){
	int i;
	for(i=1; i<= g->nvertices; i++){
		processed[i]= discovered[i]=0;
		parent[i]= -1;
	}
}

void process_vertex_late(int v){
	return;
}

void process_vertex_early(int v){
	cout<<"\n processed vertex : "<<v<<endl;
}

void process_edge(int v, int y){
	cout<<"processed edge : "<<v<<"->"<<y;
}

void bfs(graph *g, int start){
	
	initialize_search(g);
	queue<int> q;
	int v; // current vertex
	int y; //successor vertex;
	edgenode *p; //temp. pointer
	
	q.push(start);
	discovered[start]=1;
	while(q.empty()!= true){
		v = q.front();
		q.pop();
		process_vertex_early(v);
		processed[v]= 1;
		p= g->edges[v];
		while(p!=NULL){
			y= p->y;
			if((processed[y] == false) || g->directed)
				process_edge(v,y);
			if(discovered[y] == false){
				q.push(y);
				discovered[y]= true;
				parent[y]= v;
			}
			p= p->next;
		}
		process_vertex_late(v);
	}
}

int main() {
	graph g;
	bool directed;
	cin>>directed;
	read_graph(&g, directed);
	print_graph(&g);
	//for bfs 
	int start;
	cin>>start;
	bfs(&g, start);
	return 0;
}