//myHashClass.h
//Kamal Giri
//Program3
//Fall 2022

#ifndef MYHASHCLASS_h
#define MYHASHCLASS_h


//Node Class
template<class T>
class myNode
{
public:
	T data;
	myNode<T>* left;
	myNode<T>* right;
	myNode(T d) {
		data = d;
		left = nullptr;
		right = nullptr;
	}
};

//Hash Class
template<class T>
class myHashClass
{
private:
	int size;
	#define HASHSIZE 399991
	myNode<T>* hashA[HASHSIZE];
	void addNode(T item, myNode<T>*& t);
	myNode<T>* searchNode(T item, myNode<T>* t, int& compares);

public:
	myHashClass();
	int hasher(T item);
	void insert(T item);
	bool find(T item, int& compares);
	int getSize() { return size; }
};


#endif