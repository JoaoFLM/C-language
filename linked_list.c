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
