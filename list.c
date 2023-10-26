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
	newElement->previous = l->sentinel->next;
	newElement->value = v;

	l->sentinel->next->next = newElement;

	l->sentinel->next = newElement;
	if(l->sentinel->previous == l->sentinel){
		l->sentinel->previous = newElement;
	}

	l->size++;

	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
	
	LinkedElement* currentElement = (*l)->sentinel->previous;

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
	newElement->next = l->sentinel->previous;

	l->sentinel->previous->previous = newElement;

	l->sentinel->previous = newElement;
	if(l->sentinel->next == l->sentinel){
		l->sentinel->next = newElement;
	}

	l->size++;

	return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List* l) {
	return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
	return l->sentinel->next->value;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {

	LinkedElement* firstElement = l->sentinel->previous;

	firstElement->next->previous = l->sentinel;
	l->sentinel->previous = firstElement->next;

	free(firstElement);

	l->size--;

	return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_back(List* l){

	LinkedElement* lastElement = l->sentinel->next;

	lastElement->previous->next = l->sentinel;
	l->sentinel->next = lastElement->previous;

	free(lastElement);

	l->size--;

	return l;
}

/*-----------------------------------------------------------------*/

List* list_insert_at(List* l, int p, int v) {

	LinkedElement* currentElement = l->sentinel->previous;

	for (int i = 0; i < p; i++){
		currentElement = currentElement->next;
	}

	LinkedElement* newElement = malloc(sizeof(LinkedElement));

	newElement->value = v;
	newElement->next = currentElement;

	if(currentElement == l->sentinel){
		newElement->previous  = l->sentinel->next;
		l->sentinel->next = newElement;

		if(l->size == 0){
			l->sentinel->previous = newElement;
		}
	}
	else{
		newElement->previous = currentElement->previous;
		currentElement->previous->next = newElement;
	}


	l->size++;



	return l;
}

/*-----------------------------------------------------------------*/

List* list_remove_at(List* l, int p) {
	(void)p;
	return l;
}

/*-----------------------------------------------------------------*/

int list_at(const List* l, int p) {
	(void)l;
	return p;
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
	LinkedElement* currentElement = l->sentinel->previous;
	while (currentElement != l->sentinel){
		currentElement->value = f(currentElement->value);
		currentElement = currentElement->next;
	}
	
	return l;
}


List* list_reduce(List* l, ReduceFunctor f, void *userData) {

	LinkedElement* currentElement = l->sentinel->previous;

	while (currentElement != l->sentinel){
		f(currentElement->value, userData);
		currentElement = currentElement->next;
	}
	

	return l;
}

/*-----------------------------------------------------------------*/

List* list_sort(List* l, OrderFunctor f) {
	(void)f;
	return l;
}

