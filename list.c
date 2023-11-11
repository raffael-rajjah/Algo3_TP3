/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD List vu en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct s_SubList{
	int value;
	struct s_SubList* previous;
	struct s_SubList* next;
} SubList;

typedef struct s_LinkedElement {
	int value;
	struct s_LinkedElement* previous;
	struct s_LinkedElement* next;
} LinkedElement;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement* whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_List {
	LinkedElement* sentinel;
	int size;
};


/*-----------------------------------------------------------------*/

List* list_create() {
	List* l = malloc(sizeof(List));
	LinkedElement* sentinel = malloc(sizeof(LinkedElement));
	
	l->sentinel = sentinel;
	l->size = 0;

	sentinel->next = sentinel;
	sentinel->previous = sentinel;


	return l;
}


/*-----------------------------------------------------------------*/

List* list_push_back(List* l, int v) {
	LinkedElement* newElement = malloc(sizeof(LinkedElement));

	newElement->next = l->sentinel;
	newElement->previous = l->sentinel->previous;
	newElement->value = v;

	l->sentinel->previous->next = newElement;

	l->sentinel->previous = newElement;
	if(l->sentinel->next == l->sentinel){
		l->sentinel->next = newElement;
	}

	l->size++;

	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
	
	LinkedElement* currentElement = (*l)->sentinel->next;

	while (currentElement != (*l)->sentinel){
		LinkedElement* f = currentElement;
		currentElement = currentElement->next;
		free(f);		
	}

	free((*l)->sentinel);

	free(*l);
	*l = NULL;
	

}

/*-----------------------------------------------------------------*/

List* list_push_front(List* l, int v) {
	
	LinkedElement* newElement = malloc(sizeof(LinkedElement));
	
	newElement->value = v;
	newElement->previous = l->sentinel;
	newElement->next = l->sentinel->next;

	l->sentinel->next->previous = newElement;

	l->sentinel->next = newElement;
	if(l->sentinel->previous == l->sentinel){
		l->sentinel->previous = newElement;
	}

	l->size++;

	return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List* l) {
	return l->sentinel->next->value;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
	return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {

	LinkedElement* firstElement = l->sentinel->next;

	firstElement->next->previous = l->sentinel;
	l->sentinel->next = firstElement->next;

	free(firstElement);

	l->size--;

	return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_back(List* l){

	LinkedElement* lastElement = l->sentinel->previous;

	lastElement->previous->next = l->sentinel;
	l->sentinel->previous = lastElement->previous;

	free(lastElement);

	l->size--;

	return l;
}

/*-----------------------------------------------------------------*/

List* list_insert_at(List* l, int p, int v) {

	LinkedElement* currentElement = l->sentinel->next;

	for (int i = 0; i < p; i++){
		currentElement = currentElement->next;
	}

	LinkedElement* newElement = malloc(sizeof(LinkedElement));

	newElement->value = v;
	newElement->next = currentElement;

	if(currentElement == l->sentinel){
		newElement->previous  = l->sentinel->previous;

		if(l->size == 0){
			l->sentinel->next = newElement;
		}
		else{
			l->sentinel->previous->next = newElement;

		}
		
		l->sentinel->previous = newElement;
	}
	else{
		newElement->previous = currentElement->previous;
		currentElement->previous->next = newElement;
		currentElement->previous = newElement;
	}


	l->size++;



	return l;
}

/*-----------------------------------------------------------------*/

List* list_remove_at(List* l, int p) {
	LinkedElement* currentElement = l->sentinel->next;

	for (int i = 0; i < p; i++){
		currentElement = currentElement->next;
	}

	if(currentElement->previous == l->sentinel){
		l->sentinel->next = currentElement->next;
	}

	else{
		currentElement->previous->next = currentElement->next;
	}
	


	if (currentElement->next == l->sentinel){
		l->sentinel->previous = currentElement->previous;
	}
	
	else{
		currentElement->next->previous = currentElement->previous;
	}

	// free(currentElement);
	l->size--;

	return l;
}

/*-----------------------------------------------------------------*/

int list_at(const List* l, int p) {
	LinkedElement* currentElement = l->sentinel->next;

	for (int i = 0; i < p; i++){
		currentElement = currentElement->next;
	}

	return currentElement->value;
}

/*-----------------------------------------------------------------*/

bool list_is_empty(const List* l) {
	return l->size == 0;
}

/*-----------------------------------------------------------------*/

int list_size(const List* l) {
	return l->size;
}

/*-----------------------------------------------------------------*/

List* list_map(List* l, SimpleFunctor f) {
	LinkedElement* currentElement = l->sentinel->next;
	while (currentElement != l->sentinel){
		currentElement->value = f(currentElement->value);
		currentElement = currentElement->next;
	}
	
	return l;
}


List* list_reduce(List* l, ReduceFunctor f, void *userData) {

	LinkedElement* currentElement = l->sentinel->next;

	while (currentElement != l->sentinel){
		f(currentElement->value, userData);
		currentElement = currentElement->next;
	}
	

	return l;

}


SubList list_split(SubList l){
	SubList splitter;

	SubList* currentElement1 = &l;
	SubList* currentElement2 = l.next;

	while(currentElement2->next != NULL){
		
		currentElement1 = currentElement1->next;
		currentElement2 = currentElement2->next->next;

	}

	splitter.previous = currentElement1;
	splitter.next = currentElement1->next;

	SubList* temp = currentElement1->next;
	currentElement1->next = &splitter;
	temp->previous = &splitter;

	return splitter;
	

}

SubList list_merge(SubList leftlist, SubList rightlist, OrderFunctor f){
	
	if (f(leftlist.value, rightlist.value)){

		leftlist.next = &rightlist;
		rightlist.previous = &leftlist;

		return leftlist;
	}

	else {

		rightlist.next = &leftlist;
		leftlist.previous = &rightlist;

		return rightlist;
	}
	
}


// SubList list_mergesort(SubList l, OrderFunctor f){
// 	l = list_split(l);

	
	
	

// }

/*-----------------------------------------------------------------*/

List* list_sort(List* l, OrderFunctor f) {

	(void)f;

	LinkedElement* currentElement = l->sentinel->previous;
	SubList* prev = malloc(sizeof(SubList));
	SubList* headSubList = prev;

	prev->previous = NULL;
	prev->next = NULL;
	prev->value = currentElement->value;

	currentElement = currentElement->next;

	while (currentElement != l->sentinel)
	{
		SubList* newSubList = malloc(sizeof(SubList));

		newSubList->next = NULL;
		newSubList->previous = prev;
		newSubList->value = currentElement->value;

		prev->next = newSubList;

		prev = newSubList;
		currentElement = currentElement->next;

	}
	
	SubList* currentSubList = headSubList;	

	SubList splitted = list_split(*headSubList);

	currentSubList = splitted.next;

	// print sublist
	printf("value sublist : ");


	while (currentSubList != NULL)
	{
		printf("%d ", currentSubList->value);
		currentSubList = currentSubList->next;
	}
	

	return l;
}

