#include "malloc.c"


struct Node{
    int value;
    struct Node* anterior; 
    struct Node* proximo;
};

void CreateNodeList(int value, struct Arena* arena, struct Node** head){
    struct Node* new_node = ArenaAlloc(arena, sizeof(struct Node));
    new_node->value = value;
    new_node->proximo = NULL;
    new_node->anterior = NULL;

    if(*head == NULL){
	*head = new_node; 
	return;
    }

    struct Node* temp = *head; 
    while(temp->proximo != NULL){
	temp = temp->proximo;
    }
    temp->proximo = new_node;
    new_node->anterior = temp;

    return;
}

void RemoveNodeList(struct Node** head){
    if(*head == NULL){
	return;
    }
    
    struct Node* temp = *head;
    while(temp->proximo->proximo != NULL){
	temp = temp->proximo;
    }

    temp->proximo = NULL;

    return;
}

struct Node* GetNodeById(struct Node** node, int id){
    struct Node* temp = *node;
    for(int i = 0; i < id; i++){
	if(temp->proximo != NULL){
	    temp = temp->proximo;
	}
    }

    return temp;
}

int main(){
    const size_t PAGE_SIZE = (size_t)sysconf(_SC_PAGESIZE);
    
    struct Arena* arena = CreateArena(sizeof(struct Node) * 10, PAGE_SIZE);

    struct Node* node = {NULL};

    CreateNodeList(1, arena, &node);
    CreateNodeList(2, arena, &node);
    CreateNodeList(3, arena, &node);

    struct Node* temp = node;
    
    int i = 0;
   
    while (temp != NULL) {
	printf("Nó número: %d\nvalor: %d\n", i, temp->value);
	i++;
	if (temp->proximo == NULL) break;
	temp = temp->proximo;
    }

    printf("--------------------------\n");

    while (temp != NULL) {
	printf("Nó número: %d\nvalor: %d\n", i, temp->value);
	temp = temp->anterior;
	i--;
    }

    printf("--------------------------\n");
    
    int index = 0;

    temp = GetNodeById(&node, index);

    for(int i = index; temp != NULL; i--){
	printf("Nó número: %d\nvalor: %d\n", i, temp->value);
	temp = temp->anterior;
    }

    ArenaRelease(arena);
    return 0;
}
