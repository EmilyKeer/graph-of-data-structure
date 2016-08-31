# graph-of-data-structure
## Data structure | Graph
### Keywords: `connected undirected graph`  `depth-first`  `breadth-first`  `traversal`  


__Create an adjacency list and figure out the depth-first and breadth-first traversal paths!__


Language: C </br>
> The repository includes:
* 1 source file
* 1 input_txt (for testing the source code)
* 1 demmand for the code (in Chinese; complete requirement for the tasks)

TASK concerning **Graph** :</br>
*   **Write an `algorithm`: **
*  __first__ Use the adjacency list to create a graph (connected undirected graph);
*  __then__　:
*  1. figure out the depth-first traversal path
*  2. figure out the breadth-first traversal path

***

### Preview:

```c
#include<stdio.h>
#include<stdlib.h>  //exit(0)
#include<malloc.h>  //malloc
#define MaxVex 255

typedef char VertexType;
typedef int Bool;
Bool visited[MaxVex]; //global array: record the visit status of the panel points in the graph

typedef struct EdgeNode  
{
	int adjvex;
	struct EdgeNode *pNext;
}EdgeNode;
typedef struct VertexNode 
{
	VertexType data;
	EdgeNode * firstedge;
}VertexNode, AdjList[MaxVex];  

typedef struct Graph  //build up a graph
{
	AdjList adjList;  
	int numVertexes;  
}Graph, *GraphAdjList;

typedef struct LoopQueue  //build up a queue
{
	int data[MaxVex];
	int front, rear;
}LoopQueue, *Queue;


void post_error(FILE *fp2);
void post_null(FILE *fp2);
int CountLine (FILE *fp);
void initQueue(Queue Q);
Bool QueueEmpty (Queue Q) ;
Bool QueueFull (Queue Q);
void EnQueue (Queue Q, int e);
void DeQueue (Queue Q, int *e);
void CreateALGraph1 (GraphAdjList G, int count, FILE *fp);
void CreateALGraph2 (GraphAdjList G, FILE *fp);
void DFS(GraphAdjList G, int i, FILE *fp2);
void DFSTraverse (GraphAdjList G, FILE *fp2);
void BFSTraverse (GraphAdjList G, FILE *fp2);


```

### Say thanks to ...
This project is my assignment for the course Data Structure when I was a first-year student at :blue_book: [the Department of Electrical Engineering at South China University of Technology](http://www.scut.edu.cn/ee/). </br>
I really appreciate the guidance and help from my teacher Dr. Qin, along with my classmates.:bowtie:

## Please feel free to give suggestions and comments!

