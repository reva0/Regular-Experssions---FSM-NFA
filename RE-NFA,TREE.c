#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int row = 0;
// For Tree structure


// A structure to represent an adjacency list node
struct node
{
    int data;
    struct node* next;
    char edgetype;

}typedef node;

// For Tree structure
struct tree
{
    int key;
    int pat_len;
    struct tree* child1;
    struct tree* child2;
    struct tree* next;
    node** graph1;
}typedef tree;

int total_fsm = 6;

int accept[6][10];
node** graph21[6];
tree* final_tree;
int pat_len[6];
// Function to create a node with 'value' as the data
// stored in it.
// Both the children of this new Node are initially null.
struct tree* newNode(int value)
{
    node* graph_new[10];
    tree* n = (tree*)malloc(sizeof(tree));
    n->key = value;
    n->child1 = NULL;
    n->child2 = NULL;
    n->graph1 = graph_new;
    n->next = NULL;
     return n;
}


// Adds an edge to an adjacency list
node* push(node* first , char edgetype ,int data)
{
    node* new_node = (node*)malloc(sizeof(node));
    new_node->edgetype = edgetype;
    new_node->data = data;
    new_node->next = NULL;
    printf("Inside push edge type is %c\n", edgetype);
    printf("inside push data is %d\n", data);
    if(edgetype == '*')
        printf("%c edge and vertex %d \n", edgetype, data);
    if (first==NULL)
    {
        first = new_node;
        return new_node;
    }
    printf("entering the second value\n");
    first->next = push(first->next,edgetype,data);
    return first;

}
int  build_fsm(int value, char* pat)
{
    int i,n1,start,end,n2,index;
    char edge,edge1;
    char next_edge;
    n2 = strlen(pat);
    int accept1[n2];
    node* graph2[10];
    for(i=0; i< n2;i++){
        accept1[i]= 0;
        graph2[i]= NULL;
    }
           n1 = 0;
    for (i=0; i < n2; i++){
            edge = pat[i];
            printf("entering building graph\n");
            graph2[n1] = push(graph2[n1],edge,n1);
            n1=n1+1;
            }
    start = 0;
    end = n2-1;
   //n1 = 0;
    for (i=0; i<n2; i++){

            edge1= pat[i];
            next_edge = pat[i+1];
           if (edge1 == '('){
                printf("Inside Add_edge\n");
                graph2[i]= push(graph2[i],next_edge,i+1);
            }
            else if(edge1 == '|'){
               graph2[start]=push(graph2[start],next_edge,i+1);
               printf("Inside or add_edge\n");
               printf("char is %c, node is %d, %d\n", next_edge,i+1,start);
               graph2[i-1]=push(graph2[i-1],')',end);
               accept1[i-1] = 1;
            }
            else if(edge1 == ')'){
                accept1[i-1]=1;
                printf("Accept of i %dis is one\n",i);
            }
            else {
                printf("inside else\n");
                printf("next edge is %c\n", next_edge);
                graph2[i]= push(graph2[i],next_edge,i+1);
            }
            if(i < n2-1 && next_edge == '*'){
                    index = i;
                graph2[index]= push(graph2[index],next_edge,index+1);
                printf("value of i%d edge%c and i+1%d is \n", index,next_edge,index+1);
//                getchar();
                graph2[index] = push(graph2[index],edge1,index+1);
                printf("value of i%d edge%c and i+1%d is \n", index,edge1,index+1);
                printf("Inside *\n");
               // getchar();
                graph2[index+1]=push(graph2[index+1],edge1,index);
               // getchar();
                printf("value of i%d edge%c and i+1%d is \n", index+1,edge1,index);
               // getchar();

            }
    }

        for(i =0; i<n2;i++){
        accept[value][i] = accept1[i];

        }
        pat_len[value]=n2;
        printf("Inside build fsm %c\n", graph2[0]->edgetype);
        graph21[value] = (node**)malloc(sizeof(node)*n2);
        for(i=0;i<n2; i++)
        graph21[value][i]= graph2[i];

    return 0;
    }
                       // graph_new[value] = graph2;



//Recursive function to check acceptance of input
int nfa(node** graph, int current, char* input,
        int* accept1, int start,int len1)
{

    int i;
    int start1 = 0;
    int len;
    char c1;
    //int patt_len;

    printf("String length of input is %d\n",strlen(input));
    printf("The value of current is %d and accept of current is %d\n", current,accept1[current]);

    len = strlen(input);
    if((accept1[current]==1) && ( start!= 0))
        return 1;

    if (start==len )
        return accept1[current];
    node* temp = graph[current];
    if(current == 0 && temp !=NULL && start == 0){
            while(temp != NULL){
            if(temp->data <= 1){
                    temp = temp->next;
                printf("ORPATTERN");
                if(temp!= NULL)
                printf("EDGE is %c %dn", temp->edgetype,temp->data);
            }
            else
                break;
        }
    }

    if((start == 0)&& temp !=NULL)
    {
    for (i=0; i< len; i++){
        if( input[i] == temp->edgetype){
            printf("inside match\n");
           start1 = i;
           break;
        }
       }
    }

    else
        start1 = start;
    printf("the starting position is %d\n",start1);
    c1 = getchar();
    while(temp != NULL){
            printf("entering while\n");
      if (input[start1]==temp->edgetype){
            if (nfa(graph,temp->data,input,accept1,start1+1,len1)==1)
            return 1;

            }
            /*else if (temp->edgetype =='*'){
                printf("Entering * pattern\n");
                temp = temp->next;
            }*/
           // if(temp != NULL){
            //printf("Advancing the pointer with current value equal to %d\n", current);
            temp = temp->next;

      }
      if(current != 0){
               if(nfa(graph,0,input,accept1,0,len1)==1)
                return 1;
      }
      else
        return 0;
    return 0;
}
/*int insert(tree* tree_node){
    tree *temp;
    tree *temp1;
    temp = final_tree;
    temp1 = NULL;
    if(temp != NULL)
        temp ->next = tree_node;
    else
        final_tree = tree_node;
    return 0;
}*/
int insertValue(int value )

{
    int i;
    tree* new1;
    int pat_len;
    i = value;
            if(i == 0 )
            {
              new1=newNode(value);
              new1->graph1 = graph21[value];
              printf("AFTER BUILD FSM The edge type is %c\n",new1->graph1[1]->edgetype);

               //insert2 = insert(new1);
               final_tree = new1;
            }
            else if (i ==1)
            {
                new1=final_tree;
                new1->next = newNode(value);
                new1 = new1->next;
                new1->graph1 = graph21[value];
                //insert2 = insert(new1);
            }
             else if (i ==2)
            {
                new1=final_tree;
                new1->child1 = newNode(value);
                new1 = new1->child1;
                new1->graph1 = graph21[value];
                //insert2 = insert(new1);
            }
             else if (i ==3)
            {
                new1=final_tree;
                new1->child2 = newNode(value);
                new1 = new1->child2;
                new1->graph1 = graph21[value];
               // insert2 = insert(new1);
            }
             else if (i ==4)
            {
                new1=final_tree;
                new1->next->child1 = newNode(value);
                new1 = new1->next->child1;
                new1->graph1 = graph21[value];
              //  insert2 = insert(new1);
            }
             else if (i ==5)
            {
                new1=final_tree;
                new1->next->child2 = newNode(value);
                new1 = new1->next->child2;
                new1->graph1 = graph21[value];
               // insert2 = insert(new1);
            }
    return 0;
}


int create_tree()
{

    int i,n;
    int insert;
    for( i =0; i<total_fsm; i++){
            n=i;
        insert = insertValue(n);
        printf("built  pattern%d\n",i);
    }
    return 0;
}

// Driver program to test above functions
int main()
{
    int n1,n2;
    int n[6],len_fsm,len_fsm1,len;
    int start, or,end,fsm;
    tree* tree1;
    int i,i1,j;
    char *pattern_tree[10],*pattern;
    char* patt;
    int result;
    int final_result[6];
    int result_tree, result_graph;
    int value;
    int acc[10];
    int index;
    char input[20];
    node** graph_n;


    printf("Entering main\n");

    fsm = 0;

    for (i =0; i< total_fsm; i++){
            printf("enter pattern length\n");
            scanf("%d", &len_fsm);
            n[fsm]= len_fsm;
            pattern_tree[fsm] = (char*)malloc(sizeof(char)*len_fsm);
            patt=(char*)malloc(sizeof(char)*len_fsm);
            printf("Enter string\n");

            scanf("%s", pattern_tree[fsm]);

            patt = pattern_tree[fsm];

            result_graph = build_fsm(fsm,patt);
           // graph_new5[fsm]=graph_n;
            fsm =fsm+1;
    }
            result_tree = create_tree();
           /* if(final_tree1 != NULL){
                printf("Printing key %d\n",final_tree1->key);
                printf("the edge is %c\n", final_tree1->graph1[0]->edgetype);
            }*/



    //total_graph_push = index;
    printf("enter input string\n");
    scanf("%s", input);
   tree1 = NULL;
   for (i = 0; i<total_fsm; i++ ){
        if(i==0)
            tree1= final_tree;
        else if(i==1)
            tree1 = final_tree->next;
        else if(i==2)
            tree1 = final_tree->child1;
        else if(i==3)
            tree1= final_tree->child2;
        else if(i==4)
            tree1= final_tree->next->child1;
        else
            tree1= final_tree->next->child2;
            len_fsm1= n[i];
            if(tree1 != NULL){
                for(i1 =0 ; i1 < len_fsm1 ; i1++){
                    acc[i1]=accept[i][i1];
                    }
                    graph_n = (node**)malloc(sizeof(node)*len_fsm1);
                    graph_n=tree1->graph1;
                    }   //graph1 = graph[1];
            printf("Entering NFA\n");
          //  getchar();
            len = pat_len[i];

    final_result[i]= nfa(graph_n,1,input,acc,0,len);
   /* if(result == 1){
                printf("String %s accepted %d\n", input, tree1->key);
                return 0*/

   }
   for(i=0;i<total_fsm;i++){
        if(final_result[i]==1){
        if(result ==0)
        result = 1;
        printf("String %s accepted with index %d\n", input,i);
        }
   }
   if(result == 0)
   printf("String not accepted\n");
     return 0;
}
