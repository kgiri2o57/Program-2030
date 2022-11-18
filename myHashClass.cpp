//myHashClass.cpp
//Kamal Giri
//Program3
//Fall 2022

#include "myHashClass.h"

//Constructor
template<class T>
myHashClass<T>::myHashClass()
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		hashA[i] = nullptr;
	}
	size = 0;
}

//hash function
template<class T>
int myHashClass<T>::hasher(T item)
{
	unsigned int val = 0;

	for (int i = 0; i < item.length(); i++)
	{
		val = (val * HASHSIZE) + item[i] *(i*i);
	}
	return val % HASHSIZE;
}

template<class T>
void myHashClass<T>::addNode(T item, myNode<T>*& t)
{
	if (t == nullptr)
	{
		t = new myNode<T>(item);
		size++;
	}
	int val = item.compare(t->data);
	if (val < 0)
	{
		addNode(item, t->left);
	}
	else if (val > 0)
	{
		addNode(item, t->right);
	}
}



template<class T>
void myHashClass<T>::insert(T item)
{
	int key = hasher(item);
	addNode(item, hashA[key]);
}

template<class T>
myNode<T>* myHashClass<T>::searchNode(T item, myNode<T>* t, int& compares)
{
	if (t == nullptr)
	{
		return nullptr;
	}

	int val = item.compare(t->data);
	if (val < 0)
	{
		compares++;
		return searchNode(item, t->left, compares);
	}
	else if (val > 0)
	{
		compares++;
		return searchNode(item, t->right, compares);
	}
	else
	{
		compares++;
		return t;
	}
}


template<class T>
bool myHashClass<T>::find(T item, int& compares)
{
	int key = hasher(item);
	if (searchNode(item, hashA[key], compares) != nullptr)
	{
		return true;
	}
	else 
	{
		return false;
	}
}





