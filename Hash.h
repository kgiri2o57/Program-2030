// Hash.h
// Nischal Khanal
// Lab section 11
// Programming Assignment #3

#ifndef HASH_h
#define HASH_h


#define HASHSIZE 393241
template<class T>
struct myNode
{
public:
	T data;
	myNode<T>* left;
	myNode<T>* right;
	myNode(T d) : data(d), left(nullptr), right(nullptr) {};
};

template<class T>
class Hash
{
public:
	int size;
	Hash();
	void addData(T aData);
	bool isPresent(T aData, int& compares);
	int hashkey(T aData);
	int getSize() { return size; }
private:
	myNode<T>* HashArray[HASHSIZE];
	void addNode(T aData, myNode<T>*& aNode);
	myNode<T>* findNode(T aData, myNode<T>* aNode, int& compares);
};

#endif