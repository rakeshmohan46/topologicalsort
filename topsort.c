#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#define MAX 100

typedef struct edge
{
 int vertex;
 struct edge *next;
}Node;

Node **node;
Node * adj;
int stack[MAX];
int top = -1;

int Insertvertexedges(char * argv);
void Insertedges(char * filename, int vertex);
void PrintAdjacencylist(char * argv,int vertex);
void toposort(int vertex);
bool isempty();
void push(int vertex);
int pop();

int main(int argc, char **argv)
{
  char * filename = malloc(strlen(argv[1]) + 1);
  strcpy(filename, argv[1]);
  int vertex=0;
  vertex = Insertvertexedges(filename);
  Insertedges(filename, vertex);
  PrintAdjacencylist(filename,vertex);
  toposort(vertex);
  return; 
}

FILE * fp;

int Insertvertexedges(char filename[])
{

int vertex,edges;
char line[100];
fp = fopen(filename,"r");

if (fp == NULL) perror ("Error opening file");
   else {
     if ( fgets (line , 10 , fp) != NULL )
     {
       sscanf(line,"%d %d",&vertex,&edges);
     }
     printf("\nNumber of Vertices = %d Number of Edges = %d\n",vertex,edges); 

}
 return vertex;
}
   

void Insertedges(char * filename, int vertex)
{
    int src,dst;
    adj = malloc(vertex * sizeof(Node));
    Node *ptr;
    char line[100]; 

if (fp == NULL) perror ("Error opening file");
   else {
        while(fgets(line,sizeof(line),fp)!= NULL)
          {
            if(strlen(line) == 1)
              continue;
            else
              {
                sscanf(line,"%d %d",&src,&dst);

                ptr = (Node *)malloc(sizeof(Node));
                ptr->vertex = dst;
               
                if(adj[src].next == NULL){
                  adj[src].next = ptr;
                }
                else
                {
                    ptr->next = adj[src].next;
                    adj[src].next = ptr;
                }
                adj[dst].vertex++;

              }
          }  
        }  
    fclose(fp);
    return;
}


void PrintAdjacencylist(char *filename,int vertex)
{
    int i;
    Node *ptr;

    for(i=0; i<vertex; i++)
      {
        Node * temp = adj[i].next;
        printf("\nVertex:%d In-degree:%d \n",i,adj[i].vertex);
        
        if((adj[i].next)!= 0)
        {
        printf("\nNode:%d->",i);
        
        while(temp != NULL){
            printf(":%d", temp->vertex);
            temp = temp->next;
        }

        printf("\n");
      }
    }
    printf("\n");
return;
}

void toposort(int vertex)
{
  Node * ptr;
  int dst,i,src,element;

  printf("\nTopologically sorted order is:\n");
   for(i=0; i<vertex; i++)
    {
      
      if(adj[i].vertex == 0)
      {
      push(i);
      }
    }
    
      while(!isempty())
      {
        
        element=pop();
        printf("\n %d\n",element);

         ptr = adj[element].next;

          while(ptr!= NULL)
          {
            adj[ptr->vertex].vertex--;
            if(adj[ptr->vertex].vertex == 0)
              push(ptr->vertex);
            ptr=ptr->next;
          }
      }

    }
   
bool isempty()
{
return(top == -1);
}


void push(int vertex)
{   
   top++;
   stack[top] = vertex;
}
 
int pop()
{
   int element;
 
   element = stack[top];
   top--;
 
   return element;
}   

