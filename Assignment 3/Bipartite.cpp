#include <iostream>
using namespace std;

// Adjacency list has been implemeted as an array of linked lists


struct Node{                                            // To represent a Node in the graph
    int num;
    Node* next;
};

void insert(Node* List[],int a,int b)                   // Used to make the adjacency list 
{                                                       
    Node* temp = new Node;
    temp->num  = b;
    temp->next = List[a]->next;                         
    List[a]->next = temp;                               // Adds b to the linked list of nodes connected to a via an edge 
}   

bool dfs(Node* List[], int u, int color[])              // updates color & returns True if graph is bipartite 
{
    for (Node* v = List[u]->next; v!=NULL; v=v->next)   // scanning through edges of Node u of graph
    {
      if (color[v->num] == -1) 
      {  
         color[v->num] = color[u]^1;                    // Assigning the opposite set of u to unvisited Nodes
         if (!dfs(List, v->num, color))
            return false;                               // Graph found non-bipartite during recursive calls
      }
      else if (color[v->num] == color[u])
            return false;                               // Graph not bipartite - Nodes of edge(u,v) have same color
   }
   return true;                                         // Graph bipartite - colors properly assigned to the 2 sets
}   

void bipartite(Node* List[], int v, int e)
{
    int color[v];
    
    for(int i=0;i<v;i++)                          // Initially assign -1 to represent that the node
        color[i]=-1;                              // hasn't been visited in the dfs
    
    color[0] = 0;                                 // First Node should of be first set
    
    if(dfs(List,0,color))                         // Prints YES and the 2 sets if graph found bipartite after dfs search
    {
        cout<<"YES"<<endl;
        for(int k=0;k<v;k++)
            cout<<color[k]+1<<endl;
    }   
    else                                          // Prints NO if graph found non-bipartite after dfs search
        cout<<"NO";
}

int main() {
    int v,e;
    cin>>v>>e;
        
    Node* L[v];
    for(int i=0;i<v;i++)                                    // Initialises Linked List of all nodes
    {
        L[i] = new Node;
        L[i]->num = i;
        L[i]->next= NULL;
    }
    for(int i=0;i<e;i++)                                    // Calls insert() and develops the adjacency list
    {
        int a,b;
        cin>>a>>b;
        insert(L,a,b);                                      // Both insert(L,a,b) and insert(L,b,a) as
        insert(L,b,a);                                      // the graph is undirected
    }    
    
    bipartite(L,v,e);                                       // Call Bipartite to check the graph
    
    return 0;
}
