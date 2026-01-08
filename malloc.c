#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct Arena {
    char* base_ptr;
    size_t reserved_size;
    size_t committed_size;
    size_t current_offset;
    size_t PAGE_SIZE;
};

//size_t PAGE_SIZE = (size_t)sysconf(_SC_PAGESIZE);

struct Arena* CreateArena(size_t reserve_size, size_t PAGE_SIZE){
    struct Arena* arena = (struct Arena*)malloc(sizeof(struct Arena));

    if (!arena) return NULL;
    reserve_size = (reserve_size + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE;

    void* block = mmap(NULL, reserve_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(block == MAP_FAILED){
	free(arena);
	return NULL;
    }

    arena->base_ptr = (char*)block;
    arena->reserved_size = reserve_size;
    arena->committed_size = 0;
    arena->current_offset = 0;
    arena->PAGE_SIZE = PAGE_SIZE;
    return arena;
}

void* ArenaAlloc(struct Arena* arena, size_t size){
    if(!arena || size == 0) return NULL;

    size_t new_offset = arena->current_offset + size;

    if(new_offset > arena->reserved_size) {
	return NULL;
    }

    if(new_offset > arena->committed_size){
	size_t new_commit_target = (new_offset + arena->PAGE_SIZE - 1) / arena->PAGE_SIZE * arena->PAGE_SIZE;

	if(new_commit_target > arena->reserved_size){
	    new_commit_target = arena->reserved_size;
	}
    
	size_t size_to_commit = new_commit_target - arena->committed_size;
	void* commit_start_addr = arena->base_ptr + arena->committed_size;

	if (mprotect(commit_start_addr, size_to_commit, PROT_READ | PROT_WRITE) != 0) {
            return NULL;
        }

	arena->committed_size = new_commit_target;	
    }

    void* memory = arena->base_ptr + arena->current_offset;
    arena->current_offset = new_offset;

    return memory;
}

void ArenaReset(struct Arena* arena){
    arena->current_offset = 0;
}

void ArenaRelease(struct Arena* arena){
    munmap(arena->base_ptr, arena->reserved_size);
    free(arena);
}


//int main()
//{
//   return 0;
//}
