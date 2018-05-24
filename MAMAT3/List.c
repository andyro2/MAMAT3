#include "List.h"

typedef struct Node_
{
	PElem* elem;
	PKey* key;
	PNode pNext; 
} Node;

typedef struct List_
{
	PNode pNode;
	CLONE_FUNC clone_func;
	DESTROY_FUNC destroy_func;
	COMPARE_KEYS_FUNC comp_keys_func;
	PRINT_FUNC print_func;
	GET_KEY_FUNC get_key_func;
	int num; 
} List;

PList List_Create(CLONE_FUNC clone_func, DESTROY_FUNC destroy_func, COMPARE_KEYS_FUNC comp_keys_func, PRINT_FUNC print_func, GET_KEY_FUNC get_key_func)
{
	PList l;
	if ((clone_func == NULL) || (destroy_func == NULL) || (comp_keys_func == NULL) || (print_func == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	l = (PList)malloc(sizeof(struct List_)); //option to use memset and array of elements
	if (l == NULL) {
		free(l);
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	/*l->pNode = (Node*)malloc(sizeof(struct Node_));
	if (l->pNode == NULL) {
	free(l);
	return NULL;
	}*/ //I don't think the Node should be allocated in List Create
	l->pNode = NULL; 
	l->clone_func = clone_func;
	l->destroy_func = destroy_func;
	l->comp_keys_func = comp_keys_func;
	l->print_func = print_func;
	l->get_key_func = get_key_func;
	l->num = 0;
	return l;
}

void List_Delete(PList l)
{
	if (l == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Node* currNode = l->pNode;
	Node* tempNode = l->pNode;
	while (currNode) {
		currNode = currNode->pNext;
		l->destroy_func(tempNode->elem); //we assume also frees key (maybe? :/ )
		free(tempNode); //if node dosen't have alloc then free is a warning (therefore needs alloc or no free)
		l->num--; 
		tempNode = currNode;
	}
	//free(l->destroy_func); // free all the func? They didnt (lecture&exercise) so I guess we Shouldn't
	free(l);
	return;
}

void List_Print(PList l)
{
	if (l == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	Node* currNode = l->pNode;
	while (currNode) {
		l->print_func(currNode->elem);
		currNode = currNode->pNext;
	}
	return;
}

Result List_Add_Elem(PList l, PElem elem)
{
	PElem new;
	Node* currNode, *prevNode;
	if ((l == NULL) || (elem = NULL)) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	/*new = (PElem)malloc(sizeof(PElem)); //There is no Elem Object => ERROR?
	if (new == NULL) {
	free(new);
	printf(MALLOC_ERR_MSG);
	return FAILURE;
	}*/
	new = l->clone_func(elem); 
	currNode = l->pNode;
	prevNode = l->pNode;
	while (currNode) {
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	currNode = (Node*)malloc(sizeof(struct Node_));
	if (currNode == NULL) {
		free(currNode);
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	currNode->elem = new;
	currNode->key = l->get_key_func(new);
	currNode->pNext = NULL;
	prevNode->pNext = currNode;
	l->num++;
	return SUCCESS;
}

Result List_Remove_Elem(PList l, PKey key)
{
	Node* currNode, *prevNode;
	if ((l == NULL) || (key = NULL)) {
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	currNode = l->pNode;
	prevNode = l->pNode;
	while (currNode) {
		if (l->comp_keys_func(l->get_key_func(currNode->elem), key)) {
			prevNode->pNext = currNode->pNext;
			l->destroy_func(currNode->elem); //we assume also frees key
			free(currNode);
			l->num--;
			return SUCCESS;
		}
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	return FAILURE;
}

PElem List_Get_First(PList l)
{
	//PNode n;
	if ((l == NULL) || (l->pNode == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	//n = l->pNode; //unnecessary
	return l->pNode->elem;
}

PElem List_Get_Next(PList l)
{
	PNode n;
	if ((l == NULL) || (l->pNode == NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	n = l->pNode;
	if (n->pNext == NULL)
		return NULL;
	n = n->pNext;
	return n->elem;
}

void List_Duplicte(PList l_exist, PList l_new)
{
	PElem new;
	Node* currNode, *prevNode;
	if ((l_exist == NULL) || (l_new == NULL) || (l_new->pNode != NULL)) { //not empty new list
		printf(ARG_ERR_MSG);
		return;
	}
	currNode = l_exist->pNode;
	prevNode = l_exist->pNode;
	while (currNode) {
		new = l_new->clone_func(currNode->elem);
		if (List_Add_Elem(l_new, new) == FAILURE) {
			printf(MALLOC_ERR_MSG);
			return;
		}
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	return;
}

PElem List_Get_Elem(PList l, PKey key)
{
	Node* currNode, *prevNode;
	if ((l == NULL) || (key = NULL)) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	currNode = l->pNode;
	prevNode = l->pNode;
	while (currNode) {
		if (l->comp_keys_func(l->get_key_func(currNode->elem), key))
			return currNode->elem;
		prevNode = currNode;
		currNode = currNode->pNext;
	}
	return NULL;
}