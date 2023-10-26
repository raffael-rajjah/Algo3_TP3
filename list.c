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

	l->size++;
	l->sentinel->next = newElement;
	if(l->sentinel->previous == l->sentinel){
		l->sentinel->previous = newElement;
	}


	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
	*l=NULL;
}

/*-----------------------------------------------------------------*/

List* list_push_front(List* l, int v) {
	(void)v;
	return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List* l) {
	(void)l;
	return 0;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
	(void)l;
	return 0;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {
	return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_back(List* l){
	return l;
}

/*-----------------------------------------------------------------*/

List* list_insert_at(List* l, int p, int v) {
	(void)v;
	(void)p;
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
	(void)l;
	return false;
}

/*-----------------------------------------------------------------*/

int list_size(const List* l) {
	(void)l;
	return 0;
}

/*-----------------------------------------------------------------*/

List* list_map(List* l, SimpleFunctor f) {

	return l;
}


List* list_reduce(List* l, ReduceFunctor f, void *userData) {
	(void)f;
	(void)userData;
	return l;
}

/*-----------------------------------------------------------------*/

List* list_sort(List* l, OrderFunctor f) {
	(void)f;
	return l;
}

