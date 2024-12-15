#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
  int id;
  int heapId;
  int data;
  int size;
  int inSize;
  struct node **next;
  int *weight;
};

struct Heap
{
    struct node **array;
    int size;
    int capacity;
};

struct link {
    int data;
    struct Node *next;
};

struct node checkAvailability(struct node nodes[], int v, int n, int Kmax);
struct node revAvailability(struct node nodes[], int v, int n, int Kmax, int idi);

void push(struct link** head, int newData);
void removeElement(struct link** head, int key);
int getElement(struct link* head, int n);

void djikstra(struct node *node, int src, int v);
int minDistance(struct node *node, bool sptSet[]);
void decreaseKey(struct Heap* heap, int i, int value);
void swap(struct Heap *heap, int a, int b);


int extractMin(struct Heap *heap);


int genRandom(int size, int idi, struct link* head);

int v;

int main()
{
    srand ( time(NULL) );


    int KinMin;
    int KinMax;
    int KoutMin;
    int KoutMax;

    int weightSize=10;

    printf("input V:\n");
    scanf("%d", &v);
    printf("input KinMin:\n");
    scanf("%d", &KinMin);
    printf("input KinMax:\n");
    scanf("%d", &KinMax);
    printf("input KoutMin:\n");
    scanf("%d", &KoutMin);
    printf("input KoutMax:\n");
    scanf("%d", &KoutMax);

    struct node nodes[v];

    int size=v;
    int sizeM=v;

    struct link* head = NULL;
    struct link* head2 = NULL;

    for(int i=0;i<v;i++){
        nodes[i].next=(struct node **)malloc(KoutMax * sizeof(struct node *));
        nodes[i].weight=(int *)malloc(KoutMax * sizeof(int));
        nodes[i].id=i;
        nodes[i].heapId=i;
        nodes[i].data=INT_MAX;
        nodes[i].size=0;
        nodes[i].inSize=0;

        push(&head, i);
        push(&head2, i);
    }
    //printf("good");
    for(int i=0;i<v;i++){
            int b = rand() % (KoutMax-KoutMin+1)+KoutMin;
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

                        if(sizeM!=0){
                            id=genRandom(sizeM, i, head);
                        }
                        else{
                            id=genRandom(size, i, head2);
                        }
                        for(int j=0;j<nodes[i].size;j++){
                            //printf("ran:%d node:%d\n", ran, nodes[i].next[j]->id);
                            if(id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);
                    //printf("ran size:%d", nodes[id].size);

                    //printf("check 1");
                    nodes[i].next[nodes[i].size]=&nodes[id];
                    nodes[i].weight[nodes[i].size]=rand() % (weightSize)+1;
                    nodes[i].size++;
                     //printf("check 2");

                    //printf("check 3");
                    //printf("added1 %d",id);
                    //printf(" %d ", nodes[id].size);
                    nodes[id].inSize++;
                    //printf("added2 %d\n", size);
                    //printf("size1:%d\n", ans.next[ran]->size);
                    if(nodes[id].inSize==KinMin){
                        removeElement(&head, id);
                        sizeM--;
                    }
                    if(nodes[id].inSize==KinMax){
                        removeElement(&head2, id);
                        size--;
                    }
                }
            }
            else if(KoutMin<=size){
                //printf("bad1");
                for(int z=0;z<KoutMin;z++){
                    bool unique=true;
                    int ran;
                    int id;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
                        if(sizeM!=0){
                            id=genRandom(sizeM, i, head);
                        }
                        else{
                            id=genRandom(size, i, head2);
                        }
                        for(int j=0;j<nodes[i].size;j++){
                            if(id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);

                    //printf("id21:%d\n", nodes[i].id);
                    nodes[i].next[nodes[i].size]=&nodes[id];
                    nodes[i].weight[nodes[i].size]=rand() % (weightSize)+1;
                    nodes[i].size++;


                    nodes[id].inSize++;

                    if(nodes[id].inSize==KinMin){
                        removeElement(&head, id);
                        sizeM--;
                    }
                    if(nodes[id].inSize==KinMax){
                        removeElement(&head2, id);
                        size--;
                    }
                }
            }
            else{
                //printf("bad2");
                //struct node ans2=revAvailability(nodes, v, i+1, KoutMax, i);
                if(size<KoutMin-nodes[i].size){
                    printf("impossible %d %d", size, KoutMin-nodes[i].size);
                }
                else{
                    printf("bad");
                }
        }
    }
    while(sizeM!=0){
        int i = rand() % (v);
        if(nodes[i].size<KoutMax){
                    int ran;
                    bool unique;
                    int id;
                    do{
                        unique=true;

                        if(sizeM!=0){
                            id=genRandom(sizeM, i, head);
                        }
                        else{
                            id=genRandom(size, i, head2);
                        }
                        for(int j=0;j<nodes[i].size;j++){
                            //printf("ran:%d node:%d\n", ran, nodes[i].next[j]->id);
                            if(id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);

                    nodes[i].next[nodes[i].size]=&nodes[id];
                    nodes[i].weight[nodes[i].size]=rand() % (weightSize)+1;
                    nodes[i].size++;

                    nodes[id].inSize++;

                    if(nodes[id].inSize==KinMin){
                        removeElement(&head, id);
                        sizeM--;
                    }
                    if(nodes[id].inSize==KinMax){
                        removeElement(&head2, id);
                        size--;
                    }
        }
    }

    for(int i=0;i<v;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes[i].size;j++){
            printf("->(%d w:%d)",nodes[i].next[j]->id, nodes[i].weight[j]);
        }
        printf("\n");
    }


    int src;
    printf("input src:\n");
    scanf("%d", &src);

    djikstra(nodes, src, v);

    for(int i=0;i<v;i++){
        printf("[%d]",i);
        printf(": %d",nodes[i].data);
        printf("\n");
    }


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
        nodes2[i].weight=(int *)malloc(KoutMax * sizeof(int));
        nodes2[i].id=i;
        nodes2[i].heapId=i;
        nodes2[i].data=INT_MAX;
        nodes2[i].size=0;
    }

    int number;
    int temp;
    // Read data from the file
    for(int i=0;i<v2;i++) {
        fscanf(file, "%d", &number);
        for(int j=0;j<number;j++){
            fscanf(file, "%d", &temp);
            nodes2[i].next[nodes2[i].size]=&nodes2[temp];
            fscanf(file, "%d", &temp);
            nodes2[i].weight[nodes2[i].size]=temp;
            nodes2[i].size++;
        }
    }

    for(int i=0;i<v2;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes2[i].size;j++){
            printf("->(%d w:%d)",nodes2[i].next[j]->id, nodes2[i].weight[j]);
        }
        printf("\n");
    }

    // Close the file
    fclose(file);

    printf("input src:\n");
    scanf("%d", &src);

    djikstra(nodes2, src, v2);

    for(int i=0;i<v2;i++){
        printf("[%d]",i);
        printf(": %d)",nodes2[i].data);
        printf("\n");
    }


    return 0;
}

void djikstra(struct node *node, int src, int v){
    struct Heap heap;

    int parent[v];

    heap.array=(struct node **)malloc(v * sizeof(struct node *));
    for(int i=0;i<v;i++){
        heap.array[i]=&node[i];
        parent[i]=-1;
    }

    heap.capacity=v;
    heap.size=v;

    decreaseKey(&heap, src, 0);




    for(int count = 0; count < v-1; count++) {
        int u = extractMin(&heap);


        for (int i = 0; i < node[u].size; i++){
            if (node[u].data != INT_MAX && node[u].data + node[u].weight[i] < node[u].next[i]->data){
                parent[node[u].next[i]->id]=node[u].id;
                decreaseKey(&heap, node[u].next[i]->heapId, node[u].data + node[u].weight[i]);
            }
        }
    }

    for(int i=0;i<v;i++){
        printf("[%d]",i);
        int j=i;
        while(parent[j]!=-1){
            j=parent[j];
            printf("<-(%d)",j);
        }
        printf("\n");
    }
    printf("\n");


}

void minHeapify(struct Heap *heap, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    // Check if left child is smaller than current smallest
    if (l < heap->size && heap->array[l]->data < heap->array[smallest]->data) {
        smallest = l;
    }

    // Check if right child is smaller than current smallest
    if (r < heap->size && heap->array[r]->data < heap->array[smallest]->data) {
        smallest = r;
    }

    // If the smallest element is not the current element, swap and recurse
    if (smallest != i) {
        swap(heap, i, smallest);
        minHeapify(heap, smallest); // Recursively heapify the affected subtree
    }


}

void swap(struct Heap *heap, int a, int b) {
    struct node *temp = heap->array[a];
    int tempId=heap->array[a]->heapId;
    heap->array[a] =  heap->array[b];
    //heap->array[a]->heapId=*b->heapId;
    heap->array[b] = temp;
    heap->array[b]->heapId=heap->array[a]->heapId;
    heap->array[a]->heapId=tempId;

}

void decreaseKey(struct Heap* heap, int i, int value) {
    //printf("id:%d, value:%d\n", i, value);
    if (i >= heap->size) {
        printf("Index out of bounds.\n");
        return;
    }
    if (value > heap->array[i]->data) {
        printf("New value is greater than the current value.\n");
        return;
    }
    heap->array[i]->data = value;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->array[i]->data < heap->array[parent]->data) {
            swap(heap, i, parent);
            i = parent;
        } else {
            break;
        }
    }
}

int extractMin(struct Heap *heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return -1;
    }

    int root = heap->array[0]->id;
    heap->array[0] = heap->array[heap->size - 1];
    heap->array[0]->heapId=0;
    heap->size--;

    minHeapify(heap, 0);

    return root;
}

int minDistance(struct node *node, bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int i = 0; i < v; i++)
        if (sptSet[i] == false && node[i].data <= min)
            min = node[i].data, min_index = i;

    return min_index;
}

int genRandom(int size, int idi, struct link* head)
{
    int ran;
    int id=idi;
    while(idi==id){
        ran = rand() % (size);
        id=getElement(head, ran);
        if(size==1 && idi==id){
            printf("edge case");
            break;
        }
    }

    return id;
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

    printf("List has less elements.\n");
    printf("i:%d count:%d", n, count);
    return -1; // You might want to handle this differently based on your requirements
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
