#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* Please use this value as your canary! */
#define CANARY 0x2110CAFE

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist;



void* my_malloc(size_t size)
{
	if (size == 0) {
		return NULL;
	}
	int block = size + sizeof(metadata_t) + 2 * sizeof(int);
	if (block > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}
	metadata_t* current = freelist;
	metadata_t* tmp = current;
	metadata_t* prev = freelist;
	//loop through freelist
	while(current) {
		prev = current;
		//check freelist for a big enough block
		if (current->block_size >= block) {
			current = (metadata_t*) ((char*)current + block);
			current->block_size = prev->block_size - block;
			//check if when splitting, there is room for another block to malloc
			if (current->block_size < sizeof(metadata_t) + 2 * sizeof(int) + 1) {
				//set canaries and metadata
				tmp->block_size = block + current->block_size;
				tmp->request_size = size;
				int* cp = (int*)((char*)tmp + sizeof(metadata_t)); 
				*cp = CANARY;
				int* cp2 = (int *) ((char *)tmp + sizeof(int) + sizeof(metadata_t) + size);
				*cp2 = CANARY;
				ERRNO = NO_ERROR;
				freelist = freelist->next;
				tmp->next = NULL;
				tmp->prev = NULL;
				return (void*)((char*)tmp + sizeof(metadata_t) + sizeof(int));
			}
			// if the free block previous is null, then set the freelist to the current
			if (prev -> prev == NULL) {
				current->next = freelist->next;
				if (freelist->next != NULL) {
					freelist->next->prev = current;
				}
				freelist = current;
				freelist->prev = NULL;
			} else { //set the previous and next of the new free block
				prev->prev->next = current;
				prev->next = current -> next;
				current->prev = prev->prev;
			}
			//set canaries and tmp to give to user
			tmp->block_size = block;
			tmp->request_size = size;
			int* cp = (int*)((char*)tmp + sizeof(metadata_t)); 
			*cp = CANARY;
			int* cp2 = (int *) ((char *)tmp + sizeof(int) + sizeof(metadata_t) + size);
			*cp2 = CANARY;
			ERRNO = NO_ERROR;
			return (void*)((char*)tmp + sizeof(metadata_t) + sizeof(int));
		}
			current = current->next;
			tmp = current;
	}
	//create a new block
	metadata_t* current2 = (metadata_t*) my_sbrk(SBRK_SIZE);
	if (current2 == NULL) {
		ERRNO = OUT_OF_MEMORY;
	 	return NULL;
	}
	tmp = current2;
	current2 = (metadata_t*)((char*)tmp + block);
	current2->block_size = SBRK_SIZE - block;
	current2->request_size = 0;
	current2->prev = NULL;
	current2->next = NULL;

	//set the new free block
	if (freelist == NULL) {
		freelist = current2;
	} else if (freelist -> block_size == 0) {
		freelist = current2;
	} else {
		prev -> next = current2;
		current2 -> prev = prev;
	}
	//set canries and temp to give to user
	tmp->block_size = block;
	tmp->request_size = size;
	tmp->prev = NULL;
	tmp->next = NULL;
	int* cp = (int*)((char*)tmp + sizeof(metadata_t)); 
	*cp = CANARY;
	int* cp2 = (int *) ((char *)tmp + sizeof(int) + sizeof(metadata_t) + size);
	*cp2 = CANARY;
	ERRNO = NO_ERROR;
	return (void*)((char*)tmp + sizeof(metadata_t) + sizeof(int));



	
}

void my_free(void* ptr)
{
	if (ptr == NULL) {
		return;
	}
	// variables to see if memory addresses are consecutive
	int l = 0;
	int r = 0;
	//freeingblock is the pointer to freed block
	metadata_t* freeingBlock = (metadata_t*)((char*)ptr - (sizeof(int) + sizeof(metadata_t)));
	//check if canaries are corrupted
	int* cp = (int*) ((char*) freeingBlock + sizeof(metadata_t));
	int* cp2 = (int*) ((char*) freeingBlock + sizeof(metadata_t) + sizeof(int) + freeingBlock->request_size);
	if (*cp != CANARY) {
		ERRNO = CANARY_CORRUPTED;
		return;
	} else if (*cp2 != CANARY) {
		ERRNO = CANARY_CORRUPTED;
		return;
	}
	metadata_t* leftFree = freelist;
	metadata_t* rightFree = freelist;
	//find the left consecutive block
	while(leftFree && !l) {
		if((metadata_t*)((char*) leftFree + leftFree->block_size) == freeingBlock) {
			l = 1;
		}
		if (!l) {
			leftFree = leftFree->next;
		}
	}
	//find the right consecutive block
	while(rightFree && !r) {
		if ((metadata_t*)((char*) freeingBlock + freeingBlock->block_size) == rightFree) {
			r = 1;
		}
		if (!r) {
			rightFree = rightFree->next;

		}
	}
	//merge left and right block with freeing block
	if (l && r) { 
		leftFree->block_size = leftFree->block_size + freeingBlock->block_size + rightFree->block_size;
		if (rightFree->prev != NULL) {
			rightFree->prev->next = rightFree->next;
		}
		if (rightFree->next != NULL) {
			rightFree->next->prev = rightFree->prev;
		}
		rightFree = NULL;
		freeingBlock = leftFree;
		freeingBlock -> request_size = 0;
	} else if (l) { //merge left block with freeing block
		leftFree->block_size = leftFree->block_size + freeingBlock->block_size;
		freeingBlock = leftFree;
	} else if (r) {
		//merge freeing block with right block
		freeingBlock->block_size = freeingBlock->block_size + rightFree->block_size;
		freeingBlock->next = rightFree->next;
		if (freeingBlock->next != NULL) {
			freeingBlock->next->prev = freeingBlock;
		}
		freeingBlock->prev = rightFree->prev;
		if (rightFree->prev != NULL) {
			rightFree->prev->next = freeingBlock;				
		}
		freeingBlock->request_size = 0;
		if (rightFree == freelist) {
			freelist = freeingBlock;
			freelist->prev = NULL;
		}
	} else {
		// free block with no left and right consecutive blocks
		if (freelist->block_size == 0) {
			freelist = freeingBlock;
		} else {
			freeingBlock->next = freelist;
			freelist->prev = freeingBlock;
			freeingBlock->request_size = 0;
			freelist = freeingBlock;
		}
	}
}