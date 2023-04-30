#include <iostream>

using namespace std;

template <class T>
struct Node {
	T data;
	Node<T> *lchild = nullptr;
	Node<T> *rchild = nullptr;
};

template <class T>
class BiTree {
 private:
	Node<T> *root = nullptr;
	void Release(Node<T> *_nodeptr);
	void InOrder(Node<T> *_nodeptr);
	Node<T> *Find_Min(Node<T> *_root);
	Node<T> *Find_Max(Node<T> *_root);

 public:
	BiTree() {}
	~BiTree() { Release(root); }
	Node<T> *find_pre(T _data) const;
	Node<T> *find_val(T _data) const;
	bool search(T _data) const;
	void insert(T _data);
	void remove(T _data);
	void inorder() { InOrder(root); }
};

template <class T>
bool BiTree<T>::search(const T _data) const {
	if (find_val(_data) == nullptr) return false;
	return true;
}

template <class T>
Node<T> *BiTree<T>::Find_Min(Node<T> *_root) {
	if (_root == nullptr) return nullptr;
	if (_root->lchild == nullptr) return _root;
	return Find_Min(_root->lchild);
}

template <class T>
Node<T> *BiTree<T>::Find_Max(Node<T> *_root) {
	if (_root == nullptr) return nullptr;
	if (_root->rchild == nullptr) return _root;
	return Find_Max(_root->rchild);
}

template <class T>
void BiTree<T>::Release(Node<T> *_nodeptr) {
	if (_nodeptr != nullptr) {
		Release(_nodeptr->lchild);
		Release(_nodeptr->rchild);
		delete _nodeptr;
	}
}

template <class T>
void BiTree<T>::InOrder(Node<T> *_nodeptr) {
	if (_nodeptr == nullptr) return;

	InOrder(_nodeptr->lchild);
	cout << _nodeptr->data << " ";
	InOrder(_nodeptr->rchild);
}

template <class T>
void BiTree<T>::insert(T _data) {
	if (this->root == nullptr) {
		this->root = new Node<T>{_data};
		return;
	}
	Node<T> *nodeptr = this->root;
	Node<T> *prevptr = this->root;
	while (nodeptr != nullptr) {
		if (_data == nodeptr->data) return;
		prevptr = nodeptr;
		nodeptr = _data < nodeptr->data ? nodeptr->lchild : nodeptr->rchild;
	}
	if (_data < prevptr->data)
		prevptr->lchild = new Node<T>{_data};
	else
		prevptr->rchild = new Node<T>{_data};
}

template <class T>
Node<T> *BiTree<T>::find_val(T _data) const {
	Node<T> *nodeptr = this->root;
	while (nodeptr != nullptr) {
		if (_data == nodeptr->data) return nodeptr;
		nodeptr = _data < nodeptr->data ? nodeptr->lchild : nodeptr->rchild;
	}
	return nullptr;
}

template <class T>
Node<T> *BiTree<T>::find_pre(T _data) const {
	Node<T> *nodeptr = this->root;
	Node<T> *prevptr = this->root;
	while (nodeptr != nullptr) {
		if (_data == nodeptr->data) return prevptr;
		prevptr = nodeptr;
		nodeptr = _data < nodeptr->data ? nodeptr->lchild : nodeptr->rchild;
	}
	return nullptr;
}

template <class T>
void BiTree<T>::remove(T _data) {
	Node<T> *nodeptr = this->find_val(_data);
	if (nodeptr == nullptr) return;
	Node<T> *prevptr = this->find_pre(_data);
	if (nodeptr->lchild == nullptr && nodeptr->rchild == nullptr) {
		if (prevptr->lchild == nodeptr) {
			prevptr->lchild = nullptr;
			delete nodeptr;
		} else if (prevptr->rchild == nodeptr) {
			prevptr->rchild = nullptr;
			delete nodeptr;
		}
	} else if (nodeptr->lchild != nullptr && nodeptr->rchild == nullptr) {
		if (prevptr->lchild == nodeptr) {
			prevptr->lchild = nodeptr->lchild;
			delete nodeptr;
		} else if (prevptr->rchild == nodeptr) {
			prevptr->rchild = nodeptr->lchild;
			delete nodeptr;
		}
	} else if (nodeptr->lchild == nullptr && nodeptr->rchild != nullptr) {
		if (prevptr->lchild == nodeptr) {
			prevptr->lchild = nodeptr->rchild;
			delete nodeptr;
		} else if (prevptr->rchild == nodeptr) {
			prevptr->rchild = nodeptr->rchild;
			delete nodeptr;
		}
	} else if (nodeptr->lchild != nullptr && nodeptr->rchild != nullptr) {
		Node<T> *beforeptr = Find_Max(nodeptr->lchild);
		Node<T> *prev_beforeptr = find_pre(beforeptr->data);
		nodeptr->data = beforeptr->data;
		if (prev_beforeptr->lchild == beforeptr) {
			prev_beforeptr->lchild = nullptr;
			delete beforeptr;
		} else if (prev_beforeptr->rchild == beforeptr) {
			prev_beforeptr->rchild = nullptr;
			delete beforeptr;
		}
	}
}

int main() {
	BiTree<int> demo;
	demo.insert(2);
	demo.insert(1);
	demo.insert(3);
	demo.insert(0);
	demo.remove(1);
	cout << demo.search(1) << " " << demo.search(0) << endl;
	return 0;
}