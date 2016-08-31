/** 邻接表深度优先遍历和广度优先遍历 **/
#include<stdio.h>
#include<stdlib.h>  //exit(0)
#include<malloc.h>  //malloc
#define MaxVex 255

typedef char VertexType;
typedef int Bool;
Bool visited[MaxVex]; //全局数组，记录图中节点访问状态

typedef struct EdgeNode  //边结点
{
	int adjvex;
	struct EdgeNode *pNext;
}EdgeNode;
typedef struct VertexNode //总结点
{
	VertexType data;
	EdgeNode * firstedge;
}VertexNode, AdjList[MaxVex];  //顶点数组

typedef struct Graph  //建立图
{
	AdjList adjList;  //结点数组
	int numVertexes;  //结点数
}Graph, *GraphAdjList;

typedef struct LoopQueue  //建立队列
{
	int data[MaxVex];
	int front, rear;
}LoopQueue, *Queue;


void post_error(FILE *fp2);//如果出错，就fp2输出ERROR
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
int main()
{
	FILE *fp;
	FILE *fp2;
	char ch;
	int  count;
	int line_num;
	int pointer_pos;
	int a;
	GraphAdjList G = (GraphAdjList)malloc(sizeof (Graph));
	GraphAdjList G1 = (GraphAdjList)malloc(sizeof (Graph));//已经建好位置了，在函数内malloc会位置冲突
if ((fp=fopen("input.txt","r"))==NULL)
{
	exit(0);
}
if ((fp2=fopen("output.txt","w"))==NULL)
{
	exit(0);
}
line_num = CountLine (fp); //数行数，函数内已经把文件流指针回到开头

ch=fgetc(fp);//此时，ftell(fp)==1
while(ch!=EOF)
{
	if (ch>='0' && ch <='9')
	{
		ungetc(ch, fp);
		fscanf(fp, "%d", &count);

		if (count != line_num-1) //如果行数不对，报错
		{
			post_error(fp2);
		fcloseall();
		exit(0);
		}
		printf("给出结点数：%d\n", count);
	}
	else if (ch == '\n')
	{
		break;
	}
	else if (ch != ' ')//输入了字母和其他字符
	{
		post_error(fp2);
		fcloseall();
		exit(0);
	}
	ch=fgetc(fp);  //循环的保证
}
pointer_pos = ftell(fp);
//第一次建立结点
CreateALGraph1(G, count, fp);
//rewind(fp);//流指针重回开头
//CreateALGraph1(G1, count, fp);//如何保持G的值？
fseek(fp, (pointer_pos)*1L, 0);//又回到了第一行的末尾
CreateALGraph2(G, fp);
//fseek(fp, (pointer_pos)*1L, 0);//又回到了第一行的末尾
//CreateALGraph2(G1, fp);
DFSTraverse(G,fp2);
a=0;
while(visited[a])//0 1 2 3 ……置零
{
	visited[a] = 0;
	a++;
}
BFSTraverse (G, fp2);
fcloseall();
free(G);
while(1);
return 0;
}


int CountLine (FILE *fp)
{
	int n=1;
	char ch;
while(!feof(fp))
{
	ch=fgetc(fp);
	if (ch == '\n' && ((ch=fgetc(fp))>='0' && ch<='9')) n++;
}
rewind(fp);
return n;
}

void post_error(FILE * fp2)
{
	fprintf(fp2, "%s", "ERROR");
}

void initQueue(Queue Q)  //初始化建立一个队列
{
	Q->front = 0;
	Q->rear = 0;

}

Bool QueueEmpty (Queue Q)  //队列判空
{
	if (Q->front == Q->rear) return 1;
	else return 0;
}

Bool QueueFull (Queue Q)
{
	if ((Q->rear+1)%MaxVex == Q->front) return 1;
	else return 0;
}

void EnQueue (Queue Q, int e)  //e值入队尾，rear
{
	if (!QueueFull (Q))
	{
		Q->data[Q->rear] = e;
		Q->rear = (Q->rear+1)%MaxVex;
	}
}

void DeQueue (Queue Q, int *e)  //删掉队头
{
	if (!QueueEmpty(Q))
	{
		*e = Q->data[Q->front];
		Q->front = (Q->front+1)%MaxVex;
	}
}

void CreateALGraph1 (GraphAdjList G, int count, FILE *fp)//文件流指针从第二行开始
{
	int i;
	char ch;
	/*if (G==NULL) 
	{
		G = (GraphAdjList)malloc(sizeof (Graph));
	}*/
	G->numVertexes = count;//结点数
	for (i=0; i<G->numVertexes; i++)
	{
		fscanf(fp, "%d", &G->adjList[i].data);  //这里0123……同时也是总结点序号
		ch = fgetc(fp);
		while(ch!='\n')
		{
			ch = fgetc(fp);
		}
	}
}
//G访问冲突？
void CreateALGraph2 (GraphAdjList G, FILE *fp)//文件流指针从第二行开始
{
	char ch;
	EdgeNode *ptrEdgeNode; //要在最开始的地方定义
	int x0,i,k;//x0是原结点，i j是相关联顶点序号
	for (k=0; k<G->numVertexes;++k)///////////////////////////////////////////
	{
		fscanf(fp, "%d", &x0);
		G->adjList[x0].firstedge=NULL; //最后一定指向NULL
		ch=fgetc(fp);
		while(ch!= '\n')
		{
			ungetc(ch,fp);
			fscanf(fp, "%d", &i);
	ptrEdgeNode = (EdgeNode*)malloc(sizeof (EdgeNode));
	ptrEdgeNode ->adjvex = i;
	ptrEdgeNode->pNext = G->adjList[x0].firstedge;
	G->adjList[x0].firstedge = ptrEdgeNode;
		ch=fgetc(fp);//重要！不然会死循环：在每一行最后一个数fscanf之后，要ch一下调到换行符

		}


	}
	
}
void DFS(GraphAdjList G, int i, FILE *fp2)
{
	EdgeNode *p = G->adjList[i].firstedge; //先声明
	visited[i]=1;
	fprintf(fp2, "%d ", G->adjList[i].data);
	while(p)
	{
		if (!visited[p->adjvex])
		{
			DFS(G, p->adjvex,fp2);
		}
				p=p->pNext;//位置！！！！！！！！！！！！！！！！！
	}
	
}

void DFSTraverse (GraphAdjList G, FILE *fp2)
{
	int i;
	for (i=0; i<G->numVertexes;++i)
	{
		visited[i] = 0;
	}
	for (i=0; i<G->numVertexes; ++i)
	{
			printf("@@@@@%d\n",i);
		if (!visited[i])
		{
			DFS(G,i,fp2);
		}
			
	}
	fprintf(fp2, "%c",'\n');
}

void BFSTraverse (GraphAdjList G, FILE *fp2)
{
	int i;
	EdgeNode *p;
	Queue Q = (Queue) malloc (sizeof(LoopQueue));
	for (i=0; i<G->numVertexes; ++i)
	{
		visited[i]=0;
	}
	initQueue (Q);
	for(i=0; i<G->numVertexes; ++i)
	{p = G->adjList[i].firstedge;
		if (!visited[i])
		{
			visited[i] = 1;
			fprintf(fp2, "%d ", G->adjList[i].data);
			EnQueue (Q, i);
			while(!QueueEmpty (Q))
			{
				DeQueue (Q, &i);
				
				while(p)
				{
					
					if (!visited[p->adjvex])
					{
						visited[p->adjvex] = 1;
						fprintf(fp2, "%d ", G->adjList[p->adjvex].data);
						EnQueue (Q, p->adjvex);
					}
					p=p->pNext;
					//printf("%d",p->adjvex);
					//while(1);
				}
			}
		}
	}
	fprintf(fp2, "%c",'\n');
}