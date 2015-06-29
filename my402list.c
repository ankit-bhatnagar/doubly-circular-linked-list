#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "my402list.h"
#include "cs402.h"

int Traverse(My402List *list)
    {
        My402ListElem *elem=NULL;
		int len=0;
        for (elem=My402ListFirst(list); elem != NULL; elem=My402ListNext(list, elem)) 
		{
            len++;
        }
		return len;
    }
	
int  My402ListLength(My402List* dum_list)
{
	//calculates length
	int length;
	length=Traverse(dum_list);
	
	return length;
}	

int  My402ListEmpty(My402List* dum_list)
{
	//tells if empty
	int chk;
	chk=My402ListLength(dum_list);
	if(chk==0)
		return TRUE;
	else
		return FALSE;
}	

int  My402ListAppend(My402List* dum_list, void* value)
{
	//If list is empty, just add obj to the list. Otherwise, add obj after Last(). 
	//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise
	int chk_emp=0;
	chk_emp=My402ListEmpty(dum_list);
	
	if(chk_emp==TRUE)
	{
		//empty
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		//memset(val,0, sizeof(val));
		
		if(n==NULL)
			return FALSE;
		
		n->next=&(dum_list->anchor);
		n->prev=&(dum_list->anchor);
		n->obj=value;
		
		dum_list->anchor.next=n;
		dum_list->anchor.prev=n;
		
		return TRUE;
	}
    else
	{
		//add after last!!
		
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		
		if(n==NULL)
			return FALSE;
		
		n->prev=My402ListLast(dum_list);
		n->next=&(dum_list->anchor);
		n->obj=value;
		
		dum_list->anchor.prev->next=n;
		dum_list->anchor.prev=n;
		return TRUE;
	}
	return TRUE;
}

int  My402ListPrepend(My402List* dum_list, void* value)
{
	//If list is empty, just add obj to the list. Otherwise, add obj before First().
	//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise
	int chk_emp=0;
	chk_emp=My402ListEmpty(dum_list);
	
	if(chk_emp==TRUE)
	{
		//empty
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		if(n==NULL)
			return FALSE;
		
		n->next=&(dum_list->anchor);
		n->prev=&(dum_list->anchor);
		n->obj=value;
		
		dum_list->anchor.next=n;
		dum_list->anchor.prev=n;
		
		return TRUE;
	}
    else
	{
		//add before first!!
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		if(n==NULL)
			return FALSE;
		
		n->prev=&(dum_list->anchor);
		n->next=My402ListFirst(dum_list);
		n->obj=value;
		
		dum_list->anchor.next->prev=n;
		dum_list->anchor.next=n;
		return TRUE;
	}
	return TRUE;
}	

void My402ListUnlink(My402List* dum_list, My402ListElem* elem)
{
	//Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem is on the list
	
	if(elem->next==&(dum_list->anchor) && elem->prev==&(dum_list->anchor))
	{
		dum_list->anchor.next=NULL;
		dum_list->anchor.prev=NULL;
	}
	else
	{
		elem->next->prev=elem->prev;
		elem->prev->next=elem->next;
	}
}	

void My402ListUnlinkAll(My402List* dum_list)
{
	//Unlink and delete all elements from the list and make the list empty. Please do not delete the objects pointed to be the list elements
	dum_list->anchor.next=NULL;
	dum_list->anchor.prev=NULL;
}	

int  My402ListInsertBefore(My402List* dum_list, void* value, My402ListElem* elem)
{
	//Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend
	//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise
	int ret=0;
	if(elem->next==&(dum_list->anchor) && elem->prev==&(dum_list->anchor))
	{
		ret=My402ListPrepend(dum_list,value);
		if(ret==0)
			return FALSE;
		else
			return TRUE;
	}	
	
	else
	{
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		if(n==NULL)
			return FALSE;
		
		n->next=elem;
		n->prev=elem->prev;
		n->obj=value;
		
		elem->prev->next=n;
		elem->prev=n;
		return TRUE;
	}
	return TRUE;
}	

int  My402ListInsertAfter(My402List* dum_list, void* value, My402ListElem* elem)
{
	//Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append
	//This function returns TRUE if the operation is performed successfully and returns FALSE otherwise
	int ret=0;
	if(elem->next==&(dum_list->anchor) && elem->prev==&(dum_list->anchor))
	{
		ret=My402ListAppend(dum_list,value);
		if(ret==0)
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		My402ListElem* n=(My402ListElem*) malloc(sizeof(My402ListElem));
		if(n==NULL)
			return FALSE;
		
		n->prev=elem;
		n->next=elem->next;
		n->obj=value;
		
		elem->next->prev=n;
		elem->next=n;
		return TRUE;
	}
	return TRUE;
}	

My402ListElem *My402ListFirst(My402List* dum_list)
{
	//Returns the first list element or NULL if the list is empty
	if(dum_list->anchor.next==NULL)
		return NULL;
	else
		return dum_list->anchor.next;
	return NULL; //dummy
}	

My402ListElem *My402ListLast(My402List* dum_list)
{
	//Returns the last list element or NULL if the list is empty
	if(dum_list->anchor.prev==NULL)
		return NULL;
	else
		return dum_list->anchor.prev;
	return NULL; //dummy
}	

My402ListElem *My402ListNext(My402List* dum_list, My402ListElem* elem)
{
	//Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list
	if(elem->next==&(dum_list->anchor))
		return NULL;
	else
		return elem->next;
	return NULL; //dummy
}	

My402ListElem *My402ListPrev(My402List* dum_list, My402ListElem* elem)
{
	//Returns elem->prev or NULL if elem is the first item on the list. Please do not check if elem is on the list
	if(elem->prev==&(dum_list->anchor))
		return NULL;
	else
		return elem->prev;
	return NULL; //dummy
}

My402ListElem *My402ListFind(My402List* dum_list, void* value)
{
	//Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found
	My402ListElem *elem=NULL;
	for (elem=My402ListFirst(dum_list); elem != NULL; elem=My402ListNext(dum_list, elem)) 
		{
             if(elem->obj==value)
				 return elem;
        }
	return NULL;	
}	

int My402ListInit(My402List* dum_list)
{
	//Initialize the list into an empty list. Returns TRUE if all is well and returns FALSE if there is an error initializing the list
	
	dum_list->anchor.next=NULL;
	dum_list->anchor.prev=NULL;
	dum_list->anchor.obj=NULL;
	return TRUE;
}	
