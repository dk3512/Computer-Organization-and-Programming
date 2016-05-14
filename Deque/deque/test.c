#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Here we are going to write some functions to support a deque that stores
 * person data (name, age)
 */
struct person {
	char *name;
	int age;
};

/* Example functions given to you. If you want to truly grasp these concepts,
 * try writing your own structs and functions as well!
 */

// Create a new person
struct person *create_person(const char *name, int age) {
	struct person *p = (struct person*) malloc(sizeof(struct person));
	p->name = malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;
	return p;
}

static int print_count;
static char *last_printed;

// Print a person
void print_person(void *data) {
	struct person *p = (struct person*) data;
	++print_count;
	last_printed = p->name;
	printf("%s, %d\n", p->name, p->age);
}

// Copy a person
void *copy_person(const void *data) {
	struct person *p = (struct person*) data;
	return create_person(p->name, p->age);
}

// Free a person
void free_person(void *data) {
	// This is safe because we should only be passing in person struct pointers
	struct person *p = (struct person*) data;
	// free any malloc'd pointers contained in the person struct (just name)
	free(p->name);
	// Now free the struct itself; this takes care of non-malloc'd data, like age.
	free(p);
}

// Compare people by age
int person_age_comp(const void *data1, const void *data2) {
	struct person *p1 = (struct person*) data1;
	struct person *p2 = (struct person*) data2;
	return p1->age - p2->age;
}

// Compare people by name
int person_name_comp(const void *data1, const void *data2) {
	struct person *p1 = (struct person*) data1;
	struct person *p2 = (struct person*) data2;
	return strcmp(p1->name, p2->name);
}

// Tell if a person is age 50
int is_age_50(const void *data) {
	struct person *p = (struct person*) data;
	return p->age == 50;
}

// Tell if a person is 23 or older
int is_age_23_or_greater(const void *data) {
	struct person *p = (struct person*) data;
	return p->age >= 23;
}

/* This main function does a little testing. Like all good CS Majors, you should
 * test your code here. There is no substitute for testing and you should be
 * sure to test for all edge cases, like calling empty_deque on an empty deque.
 */
int main(void) {

	printf("\nTEST CASE 1\nAn empty deque should have size 0:\n");
	deque *d1 = create_deque();
	printf("Size: %d\n", size(d1));
	assert(!size(d1));
	assert(!d1->head);
	assert(!d1->tail);
	assert(is_empty(d1));

	printf("\nTEST CASE 2\nAfter adding one element, size should be 1:\n");
	push_front(d1, create_person("Andrew", 26));
	printf("Size: %d\n", size(d1));
	assert(size(d1) == 1);
	assert(!is_empty(d1));

	printf("\nTEST CASE 3\nTraversal should print the one element:\n");
	print_count = 0;
	last_printed = NULL;
	traverse(d1, print_person);
	assert(!strcmp(last_printed, "Andrew") && print_count == 1);

	printf("\nTEST CASE 4\nThe one element should be the front:\n");
	print_count = 0;
	last_printed = NULL;
	print_person(front(d1));
	assert(!strcmp(last_printed, "Andrew") && print_count == 1);

	printf("\nTEST CASE 5\nThe one element should be the back:\n");
	print_count = 0;
	last_printed = NULL;
	print_person(back(d1));
	assert(!strcmp(last_printed, "Andrew") && print_count == 1);

	printf("\nTEST CASE 6\nAndrew should be contained in the deque:\n");
	struct person *andrew = create_person("Andrew", 50);
	printf("Andrew %s in deque\n", contains(d1, andrew, person_name_comp) ?
			"is" : "isn\'t");
	struct person *ptemp = (struct person*) contains(d1, andrew, person_name_comp);
	assert(ptemp->age == 26);

	printf("\nTEST CASE 7\nCollin should not be contained in the deque:\n");
	struct person *collin = create_person("Collin", 23);
	printf("Collin %s in deque\n", contains(d1, collin, person_name_comp) ?
			"is" : "isn\'t");
	assert(!contains(d1, collin, person_name_comp));

	printf("\nTEST CASE 8\nPop Andrew from the front...\n");
	ptemp = (struct person*) pop_front(d1);
	assert(!size(d1));
	assert(!person_name_comp(andrew, ptemp));
	printf("Success!\n");
	free_person(ptemp);

	printf("\nTEST CASE 9\nAdd Collin, pop from the back...\n");
	push_back(d1, collin);
	assert(size(d1) == 1);
	ptemp = pop_back(d1);
	assert(ptemp == collin);
	assert(!size(d1));
	printf("Success!\n");

	// Free these people because we are done using them
	free_person(andrew);
	free_person(collin);

	printf("\nTEST CASE 10\nThere should be 7 elements in this deque:\n");
	// (L, 66) -> (A, 25) -> (M, 22) -> (N, 23) -> (H, 21) -> (C, 24) -> (B, 28)
	deque *d2 = create_deque();
	push_front(d2, create_person("Nick", 23));
	push_back(d2, create_person("Henry", 21));
	push_front(d2, create_person("Marie", 22));
	push_back(d2, create_person("Clayton", 24));
	push_front(d2, create_person("Andrew", 25));
	push_back(d2, create_person("Brandon", 28));
	push_front(d2, create_person("Leahy", 66));
	printf("Size: %d\n", size(d2));
	assert(size(d2) == 7);

	printf("\nTEST CASE 11\nFront should be last element pushed to front (Leahy):\n");
	ptemp = (struct person*) front(d2);
	print_person(ptemp);
	struct person *leahy = create_person("Leahy", 67);
	assert(!person_name_comp(leahy, ptemp));
	assert(ptemp->age == 66);
	
	printf("\nTEST CASE 12\nBack should be last element pushed to back (Brandon):\n");
	ptemp = (struct person*) back(d2);
	print_person(ptemp);
	struct person *brandon = create_person("Brandon", 29);
	assert(!person_name_comp(brandon, ptemp));
	assert(ptemp->age == 28);

	printf("\nTEST CASE 13\nThe person at index 2 should be Marie:\n");
	ptemp = (struct person*) get(d2, 2);
	print_person(ptemp);
	struct person *marie = create_person("Marie", 23);
	assert(!person_name_comp(marie, ptemp));
	assert(ptemp->age == 22);

	printf("\nTEST CASE 14\nThere should be someone age 24 in the deque:\n");
	struct person *person24 = create_person("", 24);
	ptemp = (struct person*) contains(d2, person24, person_age_comp);
	print_person(ptemp);
	assert(!strcmp(ptemp->name, "Clayton"));

	printf("\nTEST CASE 15\nThere should be nobody age 30 in the deque:\n");
	struct person *person30 = create_person("", 30);
	ptemp = (struct person*) contains(d2, person30, person_age_comp);
	if(ptemp) {
		printf("Found: ");
		print_person(ptemp);
	} else {
		printf("Success!\n");
	}
	assert(!ptemp);

	// Clean up temporary people
	free_person(leahy);
	free_person(brandon);
	free_person(marie);
	free_person(person24);
	free_person(person30);

	printf("\nTEST CASE 16\nPopping front and back leaves a size 5 deque:\n");
	// (A, 25) -> (M, 22) -> (N, 23) -> (H, 21) -> (C, 24)
	assert(ptemp = (struct person*) pop_front(d2));
	free_person(ptemp);
	assert(ptemp = (struct person*) pop_back(d2));
	free_person(ptemp);
	printf("Size: %d\n", size(d2));
	assert(size(d2) == 5);

	printf("\nTEST CASE 17\nPrint the 5 elements from the deque:\n");
	print_count = 0;
	last_printed = NULL;
	traverse(d2, print_person);
	assert(print_count == 5);
	assert(!strcmp(last_printed, "Clayton"));

	printf("\nTEST CASE 18\nRemoving people age 50 (0 people):\n");
	// (A, 25) -> (M, 22) -> (N, 23) -> (H, 21) -> (C, 24)
	int removed = remove_if(d2, is_age_50, free_person);
	printf("Removed %d %s\n", removed, removed == 1 ? "person" : "people");
	assert(!removed);

	printf("\nTEST CASE 19\nRemoving people age 23 or greater (3 people):\n");
	// (M, 22) -> (H, 21)
	removed = remove_if(d2, is_age_23_or_greater, free_person);
	printf("Removed %d %s\n", removed, removed == 1 ? "person" : "people");
	assert(removed == 3);

	printf("\nTEST CASE 20\nOnly two people should be left in the deque:\n");
	printf("Size: %d\n", size(d2));
	print_count = 0;
	last_printed = NULL;
	traverse(d2, print_person);
	assert(print_count == 2);
	assert(!strcmp(last_printed, "Henry"));

	// Empty the deque now that we're done with it
	empty_deque(d2, free_person);
	assert(!size(d2));

	printf("\nTEST CASE 21\nLet's try making a copy of a deque of 4 people:\n");
	deque *d3 = create_deque();
	push_front(d3, create_person("Baijun", 20));
	push_front(d3, create_person("Brandi", 21));
	push_front(d3, create_person("Patrick", 19));
	push_front(d3, create_person("Shayan", 22));
	printf("Original:\n");
	traverse(d3, print_person);
	printf("Copy:\n");
	deque *d4 = copy_deque(d3, copy_person);
	print_count = 0;
	last_printed = NULL;
	traverse(d4, print_person);
	assert(print_count == 4);
	assert(!strcmp(last_printed, "Baijun"));

	printf("\nTEST CASE 22\nAfter emptying first deque, second should persist:\n");
	empty_deque(d3, free_person);
	print_count = 0;
	last_printed = NULL;
	traverse(d4, print_person);
	assert(print_count == 4);
	assert(!strcmp(last_printed, "Baijun"));
	empty_deque(d4, free_person);
	assert(!size(d4));

	printf("\nTEST CASE 23\nPassing in null deques to functions should return 0...\n");
	assert(!copy_deque(NULL, NULL));
	assert(!front(NULL));
	assert(!back(NULL));
	assert(!is_empty(NULL));
	assert(!size(NULL));
	assert(!contains(NULL, NULL, NULL));
	assert(!pop_front(NULL));
	assert(!pop_back(NULL));
	assert(!remove_if(NULL, NULL, NULL));
	printf("Success!\n");

	printf("\n\n**MICAH TEST CASES**");

    printf("\nTEST CASE 01\n");
    printf("Creating deque\n");
    deque* dm = create_deque();
    assert(dm->size == 0);
    printf("Empty deque size == 0\n");
    assert(dm->head == NULL);
    printf("Empty deque head == NULL\n");
    assert(dm->tail == NULL);
    printf("Empty deque tail == NULL\n");
    printf("Success!");

    struct person* ellie = create_person("Ellie", 23);
    struct person* micah = create_person("Micah", 23);
    struct person* mark = create_person("Mark", 19);
    struct person* kaan = create_person("Kaan", 19);

    printf("\n\nTEST CASE 02\n");
    printf("Adding to deque\n");
    printf("push to front of empty deque\n");
    push_front(dm, ellie);
    assert(dm->size == 1);
    printf("Size = 1\n");
    assert(dm->head);
    printf("head exists\n");
    assert(dm->tail);
    printf("tail exists\n");
    push_back(dm, micah);
    printf("push to back of deque\n");
    assert(dm->size == 2);
    printf("Size = 2\n");
    push_front(dm, mark);
    printf("push to front of deque\n");
    assert(dm->size == 3);
    printf("Size = 3\n");
    push_back(dm, kaan);
    printf("push to back of deque\n");
    assert(dm->size == 4);
    printf("Size = 4\n");
    push_front(NULL, ellie);
    printf("push to front of NULL\n");
    push_back(NULL, micah);
    printf("push to back of NULL\n");
    printf("Success!");

    deque* dm2 = create_deque();

    struct person* ellie2 = create_person("Ellie", 23);
    struct person* micah2 = create_person("Micah", 23);
    struct person* mark2 = create_person("Mark", 19);
    struct person* kaan2 = create_person("Kaan", 19);

    printf("\n\nTEST CASE 03\n");
    printf("Adding to deque 2\n");
    printf("push to back of empty deque\n");
    push_back(dm2, ellie2);
    assert(dm2->size == 1);
    printf("Size = 1\n");
    assert(dm2->head);
    printf("head exists\n");
    assert(dm2->tail);
    printf("tail exists\n");
    push_front(dm2, micah2);
    printf("push to front of deque\n");
    assert(dm2->size == 2);
    printf("Size = 2\n");
    push_back(dm2, mark2);
    printf("push to back of deque\n");
    assert(dm2->size == 3);
    printf("Size = 3\n");
    push_front(dm2, kaan2);
    printf("push to front of deque\n");
    assert(dm2->size == 4);
    printf("Size = 4\n");
    printf("Success!");

    deque* dme = create_deque();
    deque* dmo = create_deque();
    struct person* ellie3 = create_person("Ellie", 23);
    push_front(dmo, ellie3);
    struct person* bob = create_person("Bob", 60);

    printf("\n\nTEST CASE 04\n");
    printf("Querying to deques\n");
    assert(front(dm) == mark);
    printf("front of deque is Mark\n");
    assert(back(dm) == kaan);
    printf("back of deque is Kaan\n");
    assert(front(dm2) == kaan2);
    printf("front of deque2 is Kaan\n");
    assert(back(dm2) == mark2);
    printf("back of deque2 is Mark\n");
    assert(!front(dme));
    printf("front of empty deque test\n");
    assert(!back(dme));
    printf("back of empty deque test\n");
    assert(front(dmo) == back(dmo));
    printf("front = back of single element deque\n");
    printf("deque1 tests:\n");
    assert(!get(dm, -1));
    printf("index -1 test\n");
    assert(get(dm, 0) == mark);
    printf("index 0 = Mark\n");
    assert(get(dm, 1) == ellie);
    printf("index 1 = Ellie\n");
    assert(get(dm, 2) == micah);
    printf("index 2 = Micah\n");
    assert(get(dm, 3) == kaan);
    printf("index 3 = Kaan\n");
    assert(!get(dm, 4));
    printf("index 4 test\n");
    printf("deque2 tests:\n");
    assert(!get(dm2, -1));
    printf("index -1 test\n");
    assert(get(dm2, 0) == kaan2);
    printf("index 0 = Kaan\n");
    assert(get(dm2, 1) == micah2);
    printf("index 1 = Micah\n");
    assert(get(dm2, 2) == ellie2);
    printf("index 2 = Ellie\n");
    assert(get(dm2, 3) == mark2);
    printf("index 3 = Mark\n");
    assert(!get(dm2, 4));
    printf("index 4 test\n");
    assert(!get(dme, 0));
    printf("get from empty deque\n");
    assert(get(dmo, 0) == ellie3);
    printf("get from single element deque\n");
    assert(!is_empty(dm));
    printf("deque1 is not empty\n");
    assert(!is_empty(dm2));
    printf("deque2 is not empty\n");
    assert(is_empty(dme));
    printf("new deque is empty\n");
    assert(!is_empty(dmo));
    printf("single element deque is not empty\n");
    assert(size(dm) == 4);
    printf("size of deque1 = 4\n");
    assert(size(dm2) == 4);
    printf("size of deque2 = 4\n");
    assert(size(dme) == 0);
    printf("size of empty deque = 0\n");
    assert(size(dmo) == 1);
    printf("size of single element deque = 1\n");
    assert(contains(dm, ellie, person_name_comp));
    printf("deque1 contains Ellie\n");
    assert(!contains(dm, bob, person_name_comp));
    printf("deque1 doesn't contains Bob\n");
    assert(contains(dm2, ellie2, person_name_comp));
    printf("deque2 contains Ellie\n");
    assert(!contains(dm2, bob, person_name_comp));
    printf("deque2 doesn't contains Bob\n");
    assert(!contains(dme, ellie, person_name_comp));
    printf("empty deque doesn't contains Ellie\n");
    assert(!contains(dme, bob, person_name_comp));
    printf("empty deque doesn't contains Bob\n");
    assert(contains(dmo, ellie3, person_name_comp));
    printf("single element deque contains Ellie\n");
    assert(!contains(dmo, bob, person_name_comp));
    printf("single element deque doesn't contains Bob\n");
    printf("Success!");

    printf("\n\nTEST CASE 04\n");
    printf("Traversing deques\n");
    print_count = 0;
    last_printed = NULL;
    traverse(dm, print_person);
    assert(!strcmp(last_printed, "Kaan") && print_count == 4);
    printf("Traverse deque1 tests\n");
    print_count = 0;
    last_printed = NULL;
    traverse(dm2, print_person);
    assert(!strcmp(last_printed, "Mark") && print_count == 4);
    printf("Traverse deque2 tests\n");
    print_count = 0;
    last_printed = NULL;
    traverse(dme, print_person);
    assert(!last_printed && print_count == 0);
    printf("Traverse empty deque tests\n");
    print_count = 0;
    last_printed = NULL;
    traverse(dmo, print_person);
    assert(!strcmp(last_printed, "Ellie") && print_count == 1);
    printf("Traverse single element deque tests\n");
    printf("Success!");

    printf("\n\nTEST CASE 05\n");
    printf("Copying deques\n");
    deque* dmc = copy_deque(dm, copy_person);
    assert(size(dmc) == 4);
    printf("Copyting deque1\n");
    deque* dmc2 = copy_deque(dm2, copy_person);
    assert(size(dmc2) == 4);
    printf("Copyting deque2\n");
    deque* dmce = copy_deque(dme, copy_person);
    assert(size(dmce) == 0);
    printf("Copyting empty deque\n");
    deque* dmco = copy_deque(dmo, copy_person);
    assert(size(dmco) == 1);
    printf("Copyting single element deque\n");
    printf("Success!");

    printf("\n\nTEST CASE 06\n");
    printf("Removing from deques\n");
    printf("Forgot to comment throughout writing the\n"
            "test cases and don't have the motivation to\n"
            "do it now, but it covers all the edge cases\n"
            "I could think of.\n");
    struct person* front1 = pop_front(dmc);
    assert(person_name_comp(front1, mark) == 0);
    assert(size(dmc) == 3);
    free_person(front1);
    struct person* front2 = pop_front(dmc2);
    assert(person_name_comp(front2, kaan) == 0);
    assert(size(dmc2) == 3);
    free_person(front2);
    assert(!pop_front(dmce));
    struct person* fronto = pop_front(dmco);
    assert(person_name_comp(fronto, ellie) == 0);
    assert(size(dmco) == 0);
    free_person(fronto);
    struct person* back1 = pop_back(dmc);
    assert(person_name_comp(back1, kaan) == 0);
    assert(size(dmc) == 2);
    free_person(back1);
    struct person* back2 = pop_back(dmc2);
    assert(person_name_comp(back2, mark) == 0);
    assert(size(dmc2) == 2);
    free_person(back2);
    assert(!pop_back(dmce));
    front1 = pop_front(dmc);
    assert(person_name_comp(front1, ellie) == 0);
    assert(size(dmc) == 1);
    free_person(front1);
    assert(front(dmc) == back(dmc));
    back2 = pop_back(dmc2);
    assert(person_name_comp(back2, ellie) == 0);
    assert(size(dmc2) == 1);
    free_person(back2);
    assert(front(dmc2) == back(dmc2));
    back1 = pop_back(dmc);
    assert(person_name_comp(back1, micah) == 0);
    assert(size(dmc) == 0);
    free_person(back1);
    back2 = pop_back(dmc2);
    assert(person_name_comp(back2, micah) == 0);
    assert(size(dmc2) == 0);
    free_person(back2);
    free(dmc);
    free(dmc2);
    free(dmce);
    free(dmco);
    empty_deque(dm, free_person);
    empty_deque(dm2, free_person);
    empty_deque(dme, free_person);
    empty_deque(dmo, free_person);
    free(dm);
    free(dm2);
    free(dme);
    free(dmo);
    free_person(bob);
    deque* dm4 = create_deque();
    struct person* ellie4 = create_person("Ellie", 23);
    struct person* micah4 = create_person("Micah", 23);
    struct person* mark4 = create_person("Mark", 19);
    struct person* kaan4 = create_person("Kaan", 19);
    struct person* bob4 = create_person("Bob", 60);
    push_back(dm4, ellie4);
    push_back(dm4, micah4);
    push_back(dm4, kaan4);
    push_back(dm4, mark4);
    push_back(dm4, bob4);
    remove_if(dm4, is_age_23_or_greater, free_person);
    assert(size(dm4) == 2);
    assert(front(dm4) == kaan4);
    assert(back(dm4) == mark4);
    empty_deque(dm4, free_person);
    free(dm4);
    deque* dm5 = create_deque();
    struct person* ellie5 = create_person("Ellie", 23);
    remove_if(dm5, is_age_23_or_greater, free_person);
    push_front(dm5, ellie5);
    remove_if(dm5, is_age_23_or_greater, free_person);
    assert(size(dm5) == 0);
    free(dm5);
    printf("but...Success!");

	// TODO
	printf("\nMake sure to write more test cases as well in test.c! "
			"The ones given aren't comprehensive.\n"
			"Also test using valgrind. Half credit will be given to functions "
			"with memory leaks or memory errors.\n");



	// Clean up any malloc'd structures leftover to prevent memory leaks
	free(d1);
	free(d2);
	free(d3);
	free(d4);

	return 0;
}
