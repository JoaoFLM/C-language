#include "linked_list.c"

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
