#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

struct node
{
  int id;
  int data;
  int size;
  struct node **next;
  bool *branch;
};

struct link {
    int data;
    struct link *next;
};

typedef struct Queue{
    struct link* start;
    struct link* end;
};

double gettime() {
   struct timeval laikas;
   gettimeofday(&laikas, NULL);
   double rez = (double)laikas.tv_sec+(double)laikas.tv_usec/1000000;
   return rez;
}

struct node checkAvailability(struct node nodes[], int v, int n, int Kmax);
struct node revAvailability(struct node nodes[], int v, int n, int Kmax, int idi);

void push(struct link** head, int newData);
void removeElement(struct link** head, int key);
int getElement(struct link* head, int n);

bool goCheck(struct node *one, int prev);

void makeEven(struct node nodes[], int v);
void evenize(struct node *node, struct link** head, struct node nodes[], int v);
void remove_nextarr_element(struct node *node, int id);
void add_odd(struct node *node, int v, int id);

void fleury(struct node nodes[], int v, int id);
bool checkBridge(struct node nodes[], int id, int id2, int v);

void hierholzer(struct node nodes[], int id, int v);
void hierRecursive(struct node nodes[], int id, int *count, struct Queue* q);

void initializeQueue(struct Queue* q);
void addQueue(struct Queue* q, int id);


int main()
{
    srand ( time(NULL) );

    int v;
    int Kmin;
    int Kmax;

    printf("input V:\n");
    scanf("%d", &v);
    printf("input Kmin:\n");
    scanf("%d", &Kmin);
    printf("input Kmax:\n");
    scanf("%d", &Kmax);

    struct node nodes[v];

    int size=v;

    struct link* head = NULL;

    for(int i=0;i<v;i++){
        nodes[i].next=(struct node **)malloc(Kmax * sizeof(struct node *));
        nodes[i].branch=(bool *)malloc((v) * sizeof(bool));
        for(int j=0;j<v;j++){
            nodes[i].branch[j]=true;
        }
        nodes[i].id=i;
        nodes[i].data=0;
        nodes[i].size=0;

        push(&head, i);
    }
    //printf("good");
    for(int i=0;i<v;i++){
            //struct node ans=checkAvailability(nodes, v, i+1, Kmax);

            /*
            for(int i=0;i<ans.size;i++){
                printf("[%d]",i);
                printf("(%d)",ans.next[i]->id);
                printf("\n");
            }
            */
            if(nodes[i].size<Kmax){
                removeElement(&head, i);
                size--;
            }


            //printf("\n%d ", i);
            int b = rand() % (Kmax-Kmin+1)+Kmin;
            b=b-nodes[i].size;
            //printf("b:%d\n", b);
            if(b<=size){
                //printf("goodish");
                for(int z=0;z<b;z++){
                    int ran;
                    //printf("id10:%d\n", nodes[i].id);
                    bool unique;
                    int id;
                    //printf("start\n");
                    do{
                        unique=true;
                        ran = rand() % (size);
                        id=getElement(head, ran);
                        for(int j=0;j<nodes[i].size;j++){
                            //printf("ran:%d node:%d\n", ran, nodes[i].next[j]->id);
                            if(id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);
                    //printf("ran size:%d", nodes[id].size);

                    //printf("removed ");
                    nodes[i].next[nodes[i].size]=&nodes[id];
                    nodes[i].size++;
                    //printf("added1 %d",id);
                    //printf(" %d ", nodes[id].size);
                    nodes[id].next[nodes[id].size]=&nodes[i];
                    nodes[id].size++;
                    //printf("added2 %d\n", size);
                    //printf("size1:%d\n", ans.next[ran]->size);
                    if(nodes[id].size==Kmax){
                        removeElement(&head, id);
                        size--;
                    }
                }
            }
            else if(Kmin<=size){
                //printf("bad1");
                for(int z=0;z<Kmin;z++){

                    int ran;
                    int id;
                    bool unique=true;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
                        unique=true;
                        printf("%d\n", ran);
                        ran = rand() % (size);
                        id=getElement(head, ran);
                        for(int j=0;j<nodes[i].size;j++){
                            if(id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);

                    //printf("id21:%d\n", nodes[i].id);
                    nodes[i].next[nodes[i].size]=&nodes[id];
                    nodes[i].size++;

                    nodes[id].next[nodes[id].size]=&nodes[i];
                    nodes[id].size++;

                    if(nodes[id].size==Kmax){
                        removeElement(&head, id);
                        size--;
                    }
                }
            }
            else{
                //printf("bad2");
                struct node ans2=revAvailability(nodes, v, i+1, Kmax, i);
                if(size+ans2.size<Kmin-nodes[i].size){
                    printf("impossible %d %d", size+ans2.size, Kmin-nodes[i].size);
                }
                else{
                    struct link* current = head;
                    for(int j=0;j<size;j++){
                        nodes[i].next[nodes[i].size]=&nodes[current->data];
                        nodes[i].size++;
                        int tempid=current->data;
                        nodes[tempid].next[nodes[tempid].size]=&nodes[i];
                        nodes[tempid].size++;
                        current = current->next;
                         if(nodes[tempid].size==Kmax){
                            removeElement(&head, tempid);
                            size--;
                        }
                    }

                }
                for(int z=size;z<Kmin;z++){

                    int ran;
                    bool unique=true;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
                        unique=true;
                        ran = rand() % (ans2.size);
                        for(int j=0;j<nodes[i].size;j++){
                            if(ans2.next[ran]->id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);
                    //printf("id21:%d\n", nodes[i].id);
                    nodes[i].next[nodes[i].size]=ans2.next[ran];
                    nodes[i].size++;
                    int tempid=ans2.next[ran]->id;
                    nodes[tempid].next[nodes[tempid].size]=&nodes[i];
                    nodes[tempid].size++;
                }
            }
        }

    for(int i=0;i<v;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes[i].size;j++){
            printf("->(%d)",nodes[i].next[j]->id);
        }
        printf("\n");
    }

    makeEven(nodes, v);

    add_odd(nodes, v, 0);

    printf("\n even? \n");
    for(int i=0;i<v;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes[i].size;j++){
            printf("->(%d)",nodes[i].next[j]->id);
        }
        //printf(" count: %d ",nodes[i].size);
        printf("\n");
    }


    /*
    if(goCheck(&nodes[0], 0)){
        printf("True\n");
    }
    else{
        printf("False\n");
    }
    */
    printf("fleury\n");
    double t_start = gettime();
    fleury(nodes, 0 ,v);
    double t_end = gettime();
    printf("Fleury time: %.2f\n", t_end - t_start);
    printf("\nhierholzer\n");
    t_start = gettime();
    hierholzer(nodes, 0, v);
    t_end = gettime();
    printf("\n");
    printf("Hierholzer time: %.2f\n", t_end - t_start);

    FILE *file;
    char buffer[100];  // You can adjust the buffer size according to your needs

    // Open the file in read mode
    file = fopen("example.txt", "r");

    // Check if the file is successfully opened
    if (file == NULL) {
        perror("Error opening file");
        return 1;  // Return an error code
    }

    //fgets(buffer, sizeof(buffer), file);
    //printf("%s\n", buffer);
    //char extractedString[50];  // Adjust the size as needed
    int v2;
    fscanf(file, "%d", &v2);

    printf("%d\n", v2);
    struct node nodes2[v2];

    for(int i=0;i<v2;i++){
        nodes2[i].next=(struct node **)malloc(v2 * sizeof(struct node *));
        nodes2[i].id=i;
        nodes2[i].data=0;
        nodes2[i].size=0;
    }

    int number;
    int temp;
    // Read data from the file
    for(int i=0;i<v2;i++) {
        fscanf(file, "%d", &number);
        for(int j=0;j<number;j++){
            fscanf(file, "%d", &temp);
            nodes2[i].branch=(bool *)malloc((v) * sizeof(bool));
            for(int j=0;j<v2;j++){
                nodes2[i].branch[j]=true;
            }
            nodes2[i].next[nodes2[i].size]=&nodes2[temp];
            nodes2[i].size++;
        }
    }


    /*
    for(int i=0;i<v2;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes2[i].size;j++){
            printf("->(%d)",nodes2[i].next[j]->id);
        }
        printf("\n");
    }

    //makeEven(nodes2, v2);
    */
    for(int i=0;i<v2;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes2[i].size;j++){
            printf("->(%d)",nodes2[i].next[j]->id);
        }
        printf("\n");
    }

    // Close the file
    fclose(file);
    /*
    if(goCheck(&nodes2[0], 0)){
        printf("True");
    }
    else{
        printf("False");
    }
    printf("False");
    */
    fleury(nodes2, 0 ,v);
    printf("\n");
    hierholzer(nodes2, 0, v2);


    return 0;
}

void makeEven(struct node nodes[], int v){
    struct link* head = NULL;
    for(int i=0;i<v;i++){
        if(nodes[i].size%2!=0){
            push(&head, i);
        }
    }
    int element=getElement(head, 0);
    while(element>-1){
        //printf("\n%d: ", element);
        evenize(&nodes[element], &head, nodes, v);
        element=getElement(head, 0);
    }
}

void fleury(struct node nodes[], int id, int v){
printf("%d ", id);
int sum=0;
for(int i=0;i<nodes[id].size;i++){
    sum+=nodes[id].branch[i];
}
for(int i=0;i<nodes[id].size;i++){
    if(nodes[id].branch[i]){
        nodes[id].branch[i]=false;
        int nextId=nodes[id].next[i]->id;
        if(!checkBridge(nodes, id, nextId, v) || sum==1){
            for(int j=0;j<nodes[nextId].size;j++){
                if(nodes[nextId].next[j]->id==id){
                    nodes[nextId].branch[j]=false;
                }
            }
            fleury(nodes, nextId, v);
            return;

        }
        else{
            nodes[id].branch[i]=true;
        }
    }
}
for(int i=0;i<nodes[id].size;i++){
    if(nodes[id].branch[i]){
        nodes[id].branch[i]=false;
        int nextId=nodes[id].next[i]->id;
        for(int j=0;j<nodes[nextId].size;j++){
            if(nodes[nextId].next[j]->id==id){
                nodes[nextId].branch[j]=false;
            }
        }
        fleury(nodes, nextId, v);
        return;
    }
}

}

void hierholzer(struct node nodes[], int id, int v){
    int *count=(int *)malloc((v) * sizeof(int));
    for(int i=0;i<v;i++){
        count[i]=nodes[i].size;
    }
    struct Queue q;
    initializeQueue(&q);
    addQueue(&q, id);
    int idi;

    struct link *temp=q.start;
    while(temp!=NULL){
        idi=temp->data;
        if(count[idi]>0){
            struct Queue tempQ;
            initializeQueue(&tempQ);
            hierRecursive(nodes, idi, count, &tempQ);
            struct link *tempTemp=temp->next;
            temp->next=tempQ.start;
            tempQ.end->next=tempTemp;
            if(q.end->data=temp->data){
                q.end=tempQ.end;
            }
        }
        temp=temp->next;
    }
    struct link *temp2=q.start;
    /*
    while(temp2!=NULL){
        printf("%d ", temp2->data);
        temp2=temp2->next;
    }
    */


    /*
    int *count=(int *)malloc((v) * sizeof(int));
    int *circuit=(int *)malloc((v*v) * sizeof(int));
    circuit[0]=1;
    circuit[1]=id;
    int sum=0;
    for(int i=0;i<v;i++){
        count[i]=nodes[i].size;
        sum+=nodes[i].size;
    }

    while(sum>0){
        for(int i=1;i<circuit[0]+1;i++){
            int idi=circuit[i];
            if(count[idi]>0){
                int *tempCircuit=(int *)malloc((v*v) * sizeof(int));
                tempCircuit[0]=0;

                hierRecursive(nodes, idi, count, tempCircuit);
                for(int j=0;j<tempCircuit[0];j++){
                    circuit[i+j+tempCircuit[0]]=circuit[i+j];
                    circuit[i+j]=tempCircuit[j+1];
                }
                circuit[0]+=tempCircuit[0];
            }
        }
        sum=0;
        for(int i=0;i<v;i++){
            //printf(" %d ", count[i]);
            sum+=count[i];
        }
    }

     for(int i=1;i<circuit[0]+1;i++){
         printf("%d ", circuit[i]);
     }
     printf("\n");
     */
}

void hierRecursive(struct node nodes[], int id, int *count, struct Queue* q){
    printf("%d ", id);
    addQueue(q, id);
    int failsafe=count[id];
    for(int i=0;i<nodes[id].size;i++){
        //printf(" %d ", nodes[id].branch[i]);
        if(!nodes[id].branch[i]){
            nodes[id].branch[i]=true;
            count[id]--;
            int nextId=nodes[id].next[i]->id;
            count[nextId]--;
            struct Queue tempQ;
            initializeQueue(&tempQ);
            for(int j=0;j<nodes[nextId].size;j++){
                if(nodes[nextId].next[j]->id==id){
                    nodes[nextId].branch[j]=true;

                }
            }
            //printf("branch: %d %d\n", id, nextId);
            hierRecursive(nodes, nextId, count, &tempQ);
            q->end->next=tempQ.start;
            q->end=tempQ.start;
        }
    }
    if(failsafe==count[id]){
        count[id]--;
    }

    /*
    circuit[0]++;
    circuit[circuit[0]]=id;
    //printf("id: %d ", id);
    for(int i=0;i<nodes[id].size;i++){
        //printf(" %d ", nodes[id].branch[i]);
        if(!nodes[id].branch[i]){
            count[id]--;
            nodes[id].branch[i]=true;
            int nextId=nodes[id].next[i]->id;
            count[nextId]--;
            for(int j=0;j<nodes[nextId].size;j++){
                if(nodes[nextId].next[j]->id==id){
                    nodes[nextId].branch[j]=true;
                }
            }
            hierRecursive(nodes, nextId, count, circuit);
            return;
        }
    }
    */
}

bool checkBridge(struct node nodes[], int id, int id2, int v){
    int visited[v];
    int queue[v];
    int neighbor;
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[id] = 1;
    queue[rear++] = id;

    // Iterate over the queue
    while (front != rear) {
        // Dequeue a vertex from queue and print it
        int currentNode = queue[front++];

        // Get all adjacent vertices of the dequeued vertex
        // currentNode If an adjacent has not been visited,
        // then mark it visited and enqueue it
        for(int i=0;i<nodes[currentNode].size;i++) {
            if(nodes[currentNode].branch[i]){
                neighbor=nodes[currentNode].next[i]->id;
                if(neighbor == id2){
                    return false;

                }
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    queue[rear++] = neighbor;
                }
            }
        }
    }
    return true;
}

void evenize(struct node *node, struct link** head, struct node nodes[], int v){
    bool found=false;
    struct link* temp = *head;
    temp = temp->next;
    while(!found){
        //printf("%d ", temp->data);
        bool exists=false;
        for(int i=0;i<node->size;i++){
            if(node->next[i]->id==temp->data){
                exists=true;
                break;
            }
        }
        if(exists){
            if(temp->next==NULL){
                break;
            }
            temp = temp->next;
        }
        else{
            found=true;
            node->next[node->size]=&nodes[temp->data];
            node->size++;
            int tempid=temp->data;
            //printf("node: %d ", node->id);
            nodes[tempid].next[nodes[tempid].size]=node;
            nodes[tempid].size++;
            removeElement(head, node->id);
            removeElement(head, tempid);
        }
    }
    if(node->size%2!=0){
        int ran;
        bool unique=true;
        do{
            unique=true;
            ran = rand() % (v);
            for(int j=0;j<node->size;j++){
                if(ran==node->next[j]->id || ran==node->id){
                    unique=false;
                    break;
                }
            }
        }while(!unique);
        //printf("ran: %d ", ran);
        node->next[node->size]=&nodes[ran];
        node->size++;
        int tempid=ran;
        //printf("node: %d ", node->id);
        nodes[tempid].next[nodes[tempid].size]=node;
        nodes[tempid].size++;
        removeElement(head, node->id);
        push(head, tempid);
    }
    /*
    for(int i=0;i<node->size;i++){
        if(node->next[i]->size%2!=0){
           remove_nextarr_element(node->next[i], node->id);
           remove_nextarr_element(node, node->next[i]->id);
           break;
        }
    }
    if(node->size%2!=0){
        for(int i=0;i<node->size;i++){
            if(node->next[i]->size!=0){
               remove_nextarr_element(node->next[i], node->id);
               evenize(node->next[i]);
               remove_nextarr_element(node, node->next[i]->id);
               break;
            }
        }
    }
    */
}

void add_odd(struct node nodes[], int v, int id){
    bool unique=true;
    int ran;
    if(nodes[id].size==v-1){
        printf("impossible");
        return;
    }
    do{
        unique=true;
        ran = rand() % (v);
        for(int j=0;j<nodes[id].size;j++){
            if(nodes[ran].id==nodes[id].next[j]->id || nodes[ran].id==id){
                unique=false;
                break;
            }
        }
    }while(!unique);
    //printf("id21:%d\n", nodes[i].id);
    nodes[id].next[nodes[id].size]=&nodes[ran];
    nodes[id].size++;
    int tempid=nodes[ran].id;
    nodes[tempid].next[nodes[tempid].size]=&nodes[id];
    nodes[tempid].size++;

}

void remove_nextarr_element(struct node *node, int id) {
    bool found=false;
    for (int i = 0; i < node->size; i++) {
        if(found){
            node->next[i] = node->next[i + 1];
        }
        else{
            if(node->next[i]->id == id){
                found = true;
                if(i < node->size - 1){
                    node->next[i] = node->next[i + 1];
                }
            }
        }
    }
    if(found)
        node->size=node->size-1;
}


bool goCheck(struct node *node, int prev){
    node->data=1;
    for(int i=0;i<node->size;i++){
        if(node->next[i]->id!=prev){
            printf("%d\n", node->next[i]->id);
            if(node->next[i]->data==1){
                return false;
            }
            else if(!goCheck(node->next[i], node->id)){
                return false;
            }
        }
    }
    return true;
}


struct node checkAvailability(struct node nodes[], int v, int n, int Kmax){
    struct node ans;
    ans.next=(struct node **)malloc(v * sizeof(struct node *));
    ans.id=0;
    ans.data=0;
    ans.size=0;

    for(int i=n;i<v;i++){
        if(nodes[i].size<Kmax){
            ans.next[ans.size]=&nodes[i];
            ans.size++;
        }
    }
    return ans;
}

struct node revAvailability(struct node nodes[], int v, int n, int Kmax, int idi){
    struct node ans;
    ans.next=(struct node **)malloc(v * sizeof(struct node *));
    ans.id=0;
    ans.data=0;
    ans.size=0;
    //printf("ans:%d", ans.size);

    for(int i=0;i<n;i++){
        if(nodes[i].size<Kmax){
            bool cor=true;
            for(int j=0;j<nodes[idi].size;j++){
                if(nodes[i].id==nodes[idi].id){
                    cor=false;
                    break;
                }
            }
            if(cor){
                ans.next[ans.size]=&nodes[i];
                ans.size++;
            }
        }
    }
    return ans;
}




// Function to remove a specific member from the list
void removeElement(struct link** head, int key) {
    struct link* temp = *head;
    struct link* prev = NULL;

    //printf("REMOVED %d ", key);

    // If the key is present at the head
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Search for the key to be deleted
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If the key is not present in the list
    if (temp == NULL) {
        printf("Key not found in the list.\n");
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;

    // Free the memory occupied by the node
    free(temp);
}

// Function to print the elements of the list
void printList(struct link* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Function to add a new element to the list
void push(struct link** head, int newData) {
    struct link* newNode = (struct link*)malloc(sizeof(struct link));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

int getElement(struct link* head, int n) {
    int count = 0;
    struct link* current = head;

    while (current != NULL) {
        if (count == n) {
            return current->data;
        }
        current = current->next;
        count++;
    }

    //printf("List has less elements.\n");
    //printf("i:%d count:%d", n, count);
    return -1; // You might want to handle this differently based on your requirements
}


void initializeQueue(struct Queue* q) {
    q->start = NULL;
    q->end = NULL;
}

void addQueue(struct Queue* q, int id) {
    struct link* newLink = (struct link*)malloc(sizeof(struct link));
    newLink->data = id;
    newLink->next = NULL;
    if(q->start == NULL){
        q->start = newLink;
        q->end = newLink;
    }
    else{
        q->end->next=newLink;
        q->end=newLink;
    }
}


/*
int main() {
    struct link* head = NULL;

    // Adding elements to the list
    push(&head, 3);
    push(&head, 7);
    push(&head, 9);
    push(&head, 5);

    printf("Original list: ");
    printList(head);

    // Removing a specific member from the list
    int keyToRemove = 9;
    removeElement(&head, keyToRemove);

    printf("List after removing %d: ", keyToRemove);
    printList(head);

    return 0;
}
*/
