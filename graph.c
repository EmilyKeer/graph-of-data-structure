/** �ڽӱ�������ȱ����͹�����ȱ��� **/
#include<stdio.h>
#include<stdlib.h>  //exit(0)
#include<malloc.h>  //malloc
#define MaxVex 255

typedef char VertexType;
typedef int Bool;
Bool visited[MaxVex]; //ȫ�����飬��¼ͼ�нڵ����״̬

typedef struct EdgeNode  //�߽��
{
	int adjvex;
	struct EdgeNode *pNext;
}EdgeNode;
typedef struct VertexNode //�ܽ��
{
	VertexType data;
	EdgeNode * firstedge;
}VertexNode, AdjList[MaxVex];  //��������

typedef struct Graph  //����ͼ
{
	AdjList adjList;  //�������
	int numVertexes;  //�����
}Graph, *GraphAdjList;

typedef struct LoopQueue  //��������
{
	int data[MaxVex];
	int front, rear;
}LoopQueue, *Queue;


void post_error(FILE *fp2);//���������fp2���ERROR
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
	GraphAdjList G1 = (GraphAdjList)malloc(sizeof (Graph));//�Ѿ�����λ���ˣ��ں�����malloc��λ�ó�ͻ
if ((fp=fopen("input.txt","r"))==NULL)
{
	exit(0);
}
if ((fp2=fopen("output.txt","w"))==NULL)
{
	exit(0);
}
line_num = CountLine (fp); //���������������Ѿ����ļ���ָ��ص���ͷ

ch=fgetc(fp);//��ʱ��ftell(fp)==1
while(ch!=EOF)
{
	if (ch>='0' && ch <='9')
	{
		ungetc(ch, fp);
		fscanf(fp, "%d", &count);

		if (count != line_num-1) //����������ԣ�����
		{
			post_error(fp2);
		fcloseall();
		exit(0);
		}
		printf("�����������%d\n", count);
	}
	else if (ch == '\n')
	{
		break;
	}
	else if (ch != ' ')//��������ĸ�������ַ�
	{
		post_error(fp2);
		fcloseall();
		exit(0);
	}
	ch=fgetc(fp);  //ѭ���ı�֤
}
pointer_pos = ftell(fp);
//��һ�ν������
CreateALGraph1(G, count, fp);
//rewind(fp);//��ָ���ػؿ�ͷ
//CreateALGraph1(G1, count, fp);//��α���G��ֵ��
fseek(fp, (pointer_pos)*1L, 0);//�ֻص��˵�һ�е�ĩβ
CreateALGraph2(G, fp);
//fseek(fp, (pointer_pos)*1L, 0);//�ֻص��˵�һ�е�ĩβ
//CreateALGraph2(G1, fp);
DFSTraverse(G,fp2);
a=0;
while(visited[a])//0 1 2 3 ��������
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

void initQueue(Queue Q)  //��ʼ������һ������
{
	Q->front = 0;
	Q->rear = 0;

}

Bool QueueEmpty (Queue Q)  //�����п�
{
	if (Q->front == Q->rear) return 1;
	else return 0;
}

Bool QueueFull (Queue Q)
{
	if ((Q->rear+1)%MaxVex == Q->front) return 1;
	else return 0;
}

void EnQueue (Queue Q, int e)  //eֵ���β��rear
{
	if (!QueueFull (Q))
	{
		Q->data[Q->rear] = e;
		Q->rear = (Q->rear+1)%MaxVex;
	}
}

void DeQueue (Queue Q, int *e)  //ɾ����ͷ
{
	if (!QueueEmpty(Q))
	{
		*e = Q->data[Q->front];
		Q->front = (Q->front+1)%MaxVex;
	}
}

void CreateALGraph1 (GraphAdjList G, int count, FILE *fp)//�ļ���ָ��ӵڶ��п�ʼ
{
	int i;
	char ch;
	/*if (G==NULL) 
	{
		G = (GraphAdjList)malloc(sizeof (Graph));
	}*/
	G->numVertexes = count;//�����
	for (i=0; i<G->numVertexes; i++)
	{
		fscanf(fp, "%d", &G->adjList[i].data);  //����0123����ͬʱҲ���ܽ�����
		ch = fgetc(fp);
		while(ch!='\n')
		{
			ch = fgetc(fp);
		}
	}
}
//G���ʳ�ͻ��
void CreateALGraph2 (GraphAdjList G, FILE *fp)//�ļ���ָ��ӵڶ��п�ʼ
{
	char ch;
	EdgeNode *ptrEdgeNode; //Ҫ���ʼ�ĵط�����
	int x0,i,k;//x0��ԭ��㣬i j��������������
	for (k=0; k<G->numVertexes;++k)///////////////////////////////////////////
	{
		fscanf(fp, "%d", &x0);
		G->adjList[x0].firstedge=NULL; //���һ��ָ��NULL
		ch=fgetc(fp);
		while(ch!= '\n')
		{
			ungetc(ch,fp);
			fscanf(fp, "%d", &i);
	ptrEdgeNode = (EdgeNode*)malloc(sizeof (EdgeNode));
	ptrEdgeNode ->adjvex = i;
	ptrEdgeNode->pNext = G->adjList[x0].firstedge;
	G->adjList[x0].firstedge = ptrEdgeNode;
		ch=fgetc(fp);//��Ҫ����Ȼ����ѭ������ÿһ�����һ����fscanf֮��Ҫchһ�µ������з�

		}


	}
	
}
void DFS(GraphAdjList G, int i, FILE *fp2)
{
	EdgeNode *p = G->adjList[i].firstedge; //������
	visited[i]=1;
	fprintf(fp2, "%d ", G->adjList[i].data);
	while(p)
	{
		if (!visited[p->adjvex])
		{
			DFS(G, p->adjvex,fp2);
		}
				p=p->pNext;//λ�ã���������������������������������
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