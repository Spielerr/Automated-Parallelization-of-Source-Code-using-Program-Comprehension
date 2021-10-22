







struct queue
{
  int items[SIZE];
  int front;
  int rear;
};

struct queue *createQueue();
void enqueue(struct queue *q, int);
int dequeue(struct queue *q);
void display(struct queue *q);
int isEmpty(struct queue *q);
void printQueue(struct queue *q);

struct node
{
  int vertex;
  struct node *next;
};

struct node *createNode(int);

struct Graph
{
  int numVertices;
  struct node **adjLists;
  int *colour;
};


void bfs(struct Graph *graph, int startVertex)
{
  struct queue *q = createQueue();

  graph->colour[startVertex] = Gray;
  enqueue(q, startVertex);

  while (!isEmpty(q))
  {
    printQueue(q);
    int currentVertex = dequeue(q);
    printf("\nVisited %d\n", currentVertex);

    struct node *temp = graph->adjLists[currentVertex];

    while (temp)
    {
      int adjVertex = temp->vertex;

      if (graph->colour[adjVertex] == White)
      {
        graph->colour[adjVertex] = Gray;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
  graph->colour = Black;
}


struct node *createNode(int v)
{
  struct node *newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}


struct Graph *createGraph(int vertices)
{
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node *));
  graph->colour = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++)
  {
    graph->adjLists[i] = NULL;
    graph->colour[i] = White;
  }

  return graph;
}


void addEdge(struct Graph *graph, int src, int dest)
{
  
  struct node *newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  
  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}


struct queue *createQueue()
{
  struct queue *q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}


int isEmpty(struct queue *q)
{
  if (q->rear == -1)
    return 1;
  else
    return 0;
}


void enqueue(struct queue *q, int value)
{
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else
  {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}


int dequeue(struct queue *q)
{
  int item;
  if (isEmpty(q))
  {
    printf("Queue is empty");
    item = -1;
  }
  else
  {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
      printf("\nResetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

void printQueue(struct queue *q)
{
  int i = q->front;

  if (isEmpty(q))
  {
    printf("Queue is empty");
  }
  else
  {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++)
    {
      printf("%d ", q->items[i]);
    }
  }
}
