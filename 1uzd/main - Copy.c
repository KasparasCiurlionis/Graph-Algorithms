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
int getElement(struct Node* head, int n);

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

    struct link* head = NULL;

    for(int i=0;i<v;i++){
        nodes[i].next=(struct node **)malloc(Kmax * sizeof(struct node *));
        nodes[i].id=i;
        nodes[i].data=0;
        nodes[i].size=0;

        push(&head, i);
    }
    for(int i=0;i<v;i++){
            struct node ans=checkAvailability(nodes, v, i+1, Kmax);

            /*
            for(int i=0;i<ans.size;i++){
                printf("[%d]",i);
                printf("(%d)",ans.next[i]->id);
                printf("\n");
            }
            */
            int b = rand() % (Kmax-Kmin+1)+Kmin;
            b=b-nodes[i].size;
            //printf("b:%d\n", b);
            if(b<=ans.size){
                printf("goodish\n");
                for(int z=0;z<b;z++){
                    int ran;
                    //printf("id10:%d\n", nodes[i].id);
                    bool unique;
                    do{
                        unique=true;
                        ran = rand() % (ans.size);
                        for(int j=0;j<nodes[i].size;j++){
                            //printf("ran:%d node:%d\n", ran, nodes[i].next[j]->id);
                            if(ans.next[ran]->id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);
                    //printf("ran1:%d\n", ran);

                    nodes[i].next[nodes[i].size]=ans.next[ran];
                    nodes[i].size++;

                    int tempid=ans.next[ran]->id;
                    //printf("tempid:%d\n", tempid);


                    nodes[tempid].next[nodes[tempid].size]=&nodes[i];
                    nodes[tempid].size++;
                    //printf("size1:%d\n", ans.next[ran]->size);
                }
            }
            else if(Kmin<=ans.size){
                printf("bad1");
                for(int z=0;z<Kmin;z++){
                    bool unique=true;
                    int ran;
                    //printf("id20:%d\n", nodes[i].id);
                    do{
                        ran = rand() % (ans.size);
                        for(int j=0;j<nodes[i].size;j++){
                            if(ans.next[ran]->id==nodes[i].next[j]->id){
                                unique=false;
                                break;
                            }
                        }
                    }while(!unique);
                    //printf("id21:%d\n", nodes[i].id);
                    nodes[i].next[nodes[i].size]=ans.next[ran];
                    nodes[i].size++;
                    int tempid=ans.next[ran]->id;
                    nodes[tempid].next[nodes[tempid].size]=&nodes[i];
                    nodes[tempid].size++;
                }
            }
            else{
                printf("bad2");
                struct node ans2=revAvailability(nodes, v, i+1, Kmax, i);
                if(ans.size+ans2.size<Kmin-nodes[i].size){
                    printf("impossible");
                }
                else{
                    for(int j=0;j<ans.size;j++){
                        nodes[i].next[nodes[i].size]=ans.next[j];
                        nodes[i].size++;
                        int tempid=ans.next[j]->id;
                        nodes[tempid].next[nodes[tempid].size]=&nodes[i];
                        nodes[tempid].size++;
                    }

                }
                for(int z=ans.size;z<Kmin;z++){
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


    FILE *file;
    char buffer[100];  // You can adjust the buffer size according to your needs

    // Open the file in read mode
    file = fopen("example.txt", "r");

    // Check if the file is successfully opened
    if (file == NULL) {
        perror("Error opening file");
        return 1;  // Return an error code
    }

    fgets(buffer, sizeof(buffer), file);
    printf("%s\n", buffer);
    char extractedString[50];  // Adjust the size as needed
    if (sscanf(buffer, "%[^\n]", extractedString) == 1) {
        printf("Extracted string: %s\n", extractedString);
    }
    int v2 = (int)extractedString;
    printf("%d\n", v2);
    struct node nodes2[v2];
    // Read data from the file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Process the data as needed
        printf("%s\n", buffer);
    }

    // Close the file
    fclose(file);


    return 0;
}

struct node checkAvailability(struct node nodes[], int v, int n, int Kmax){
    struct node ans;
    ans.next=(struct node **)malloc(v * sizeof(struct node *));
    ans.id=0;
    ans.data=0;
    ans.size=0;
    printf("n:%d", n);

    for(int i=n;i<v;i++){
        if(nodes[i].size<Kmax){
            ans.next[ans.size]=&nodes[i];
            ans.size++;
        }
    }
    printf("finito");
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

int getElement(struct Node* head, int n) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        count++;
        if (count == n) {
            return current->data;
        }
        current = current->next;
    }

    printf("List has less elements.\n");
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
