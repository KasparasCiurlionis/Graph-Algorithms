#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct node
{
  int id;
  int data;
  int size;
  struct node **next;
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

bool goCheck(struct node *one, int prev);

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
                    bool unique=true;
                    int ran;
                    int id;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
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
                    bool unique=true;
                    int ran;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
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

    if(goCheck(&nodes[0], 0)){
        printf("True\n");
    }
    else{
        printf("False\n");
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
            nodes2[i].next[nodes2[i].size]=&nodes2[temp];
            nodes2[i].size++;
        }
    }

    for(int i=0;i<v2;i++){
        printf("[%d]",i);
        for(int j=0;j<nodes2[i].size;j++){
            printf("->(%d)",nodes2[i].next[j]->id);
        }
        printf("\n");
    }

    // Close the file
    fclose(file);

    if(goCheck(&nodes2[0], 0)){
        printf("True");
    }
    else{
        printf("False");
    }


    return 0;
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
