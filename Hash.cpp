// Hash.cpp
// Nischal Khanal
// Lab section 11
// Programming Assignment #3

#include "Hash.h"
template<class T>
Hash<T>::Hash()
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		HashArray[i] = nullptr;
	}
	size = 0;
}

template<class T>
void Hash<T>::addData(T aData)
{
	int key = hashkey(aData);
	addNode(aData, HashArray[key]);
}

template<class T>
bool Hash<T>::isPresent(T aData, int& compares)
{
	int key = hashkey(aData);
	if (findNode(aData, HashArray[key], compares) != nullptr)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<class T>
int Hash<T>::hashkey(T aData)
{
	unsigned int hash = 0;
	int size = aData.length();
	for (int i = 0; i < size; i++)
	{
		hash = (hash * HASHSIZE) + aData[i];
	}
	return hash % HASHSIZE;
}

template<class T>
void Hash<T>::addNode(T aData, myNode<T>*& aNode)
{
	if (aNode == nullptr)
	{
		aNode = new myNode<T>(aData);
		size++;
	 }
	int c = aData.compare(aNode->data);
	if (c < 0)
	{
		addNode(aData, aNode->left);
	}
	else if (c > 0)
	{
		addNode(aData, aNode->right);
	}
}



template<class T>
myNode<T>* Hash<T>::findNode(T aData, myNode<T>* aNode, int& compares)
{
	if (aNode == nullptr)
	{
		return nullptr;
	}

	int c = aData.compare(aNode->data);
	if (c < 0)
	{
		compares++;
		return findNode(aData, aNode->left, compares);
	}
	else if (c > 0)
	{
		compares++;
		return findNode(aData, aNode->right, compares);
	}
	else
	{
		compares++;
		return aNode;
	}
}



