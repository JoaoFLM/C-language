#include "malloc.c"


struct Node{
    int value;
    struct Node* proximo;
};

void CreateNodeList(int value, struct Arena* arena, struct Node** head){
    struct Node* new_node = ArenaAlloc(arena, sizeof(struct Node));
    new_node->value = value;
    new_node->proximo = NULL;

    if(*head == NULL){
	*head = new_node; 
	return;
    }

    struct Node* temp = *head;
    while(temp->proximo != NULL){
	temp = temp->proximo;
    }

    temp->proximo = new_node;

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

int main(){
    const size_t PAGE_SIZE = (size_t)sysconf(_SC_PAGESIZE);
    
    struct Arena* arena = CreateArena(sizeof(struct Node) * 10, PAGE_SIZE);

    struct Node* node = {NULL};

    CreateNodeList(1, arena, &node);
    CreateNodeList(2, arena, &node);
    CreateNodeList(3, arena, &node);

    struct Node* temp = node;
    for(int i = 0; temp != NULL; i++){
	printf("Nó número: %d\nvalor: %d\n", i, temp->value);
	temp = temp->proximo;
    }

	printf("--------------------------\n");

    RemoveNodeList(&node);

    temp = node;
    for(int i = 0; temp != NULL; i++){
	printf("Nó número: %d\nvalor: %d\n", i, temp->value);
	temp = temp->proximo;
    }

    ArenaRelease(arena);
    return 0;
}
