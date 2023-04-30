#include <iostream>

using namespace std;

template <class T>
struct Node {
	T data;
	int height = 0;
	Node<T>* lchild = nullptr;
	Node<T>* rchild = nullptr;
};

template <class T>
class BiTree {
 private:
	Node<T>* root = nullptr;
	void Release(Node<T>* _node);
	void InOrder(Node<T>* _node);
	Node<T>* Find_Min(Node<T>* _root);
	Node<T>* Find_Max(Node<T>* _root);
	Node<T>* Insert(T _data, Node<T>* _node);
	Node<T>* Remove(T _data, Node<T>* _node);
	int GetHeight(Node<T>* _node);
	void ResetHeight(Node<T>* _node);
	int GetBalance(Node<T>* _node);
	Node<T>* ResetBalance(Node<T>* _node);
	/* Tackle unbalanced root node */
	Node<T>* LL_Rotate(Node<T>* _ubroot);
	Node<T>* RR_Rotate(Node<T>* _ubroot);
	Node<T>* LR_Rotate(Node<T>* _ubroot);
	Node<T>* RL_Rotate(Node<T>* _ubroot);

 public:
	BiTree() {}
	~BiTree() { Release(root); }
	Node<T>* find_pre(T _data) const;
	Node<T>* find_val(T _data) const;
	bool search(T _data) const;
	void insert(T _data) { root = Insert(_data, root); }
	void remove(T _data) { root = Remove(_data, root); }
	void inorder() { InOrder(root); }
};

template <class T>
Node<T>* BiTree<T>::ResetBalance(Node<T>* _node) {
	int balance = GetBalance(_node);
	if (balance > 1 && GetBalance(_node->lchild) > 0) return LL_Rotate(_node);
	if (balance < -1 && GetBalance(_node->rchild) < 0) return RR_Rotate(_node);
	if (balance > 1 && GetBalance(_node->lchild) < 0) return LR_Rotate(_node);
	if (balance < -1 && GetBalance(_node->rchild) > 0) return RL_Rotate(_node);
	return _node;
}
template <class T>
int BiTree<T>::GetHeight(Node<T>* _node) {
	if (_node == nullptr) return 0;
	return _node->height;
}

template <class T>
void BiTree<T>::ResetHeight(Node<T>* _node) {
	_node->height = max(GetHeight(_node->lchild), GetHeight(_node->rchild)) + 1;
}

template <class T>
int BiTree<T>::GetBalance(Node<T>* _node) {
	return GetHeight(_node->lchild) - GetHeight(_node->rchild);
}

template <class T>
Node<T>* BiTree<T>::LL_Rotate(Node<T>* _ubroot) {
	Node<T>* x = _ubroot->lchild;
	_ubroot->lchild = x->rchild;
	x->rchild = _ubroot;
	ResetHeight(_ubroot);
	ResetHeight(x);
	return x;
}

template <class T>
Node<T>* BiTree<T>::RR_Rotate(Node<T>* _ubroot) {
	Node<T>* x = _ubroot->rchild;
	_ubroot->rchild = x->lchild;
	x->lchild = _ubroot;
	ResetHeight(_ubroot);
	ResetHeight(x);
	return x;
}

template <class T>
Node<T>* BiTree<T>::LR_Rotate(Node<T>* _ubroot) {
	Node<T>* x = _ubroot->lchild;
	_ubroot->lchild = RR_Rotate(x);
	return LL_Rotate(_ubroot);
}

template <class T>
Node<T>* BiTree<T>::RL_Rotate(Node<T>* _ubroot) {
	Node<T>* x = _ubroot->rchild;
	_ubroot->rchild = LL_Rotate(x);
	return RR_Rotate(_ubroot);
}

template <class T>
Node<T>* BiTree<T>::Insert(T _data, Node<T>* _node) {
	if (_node == nullptr) return new Node{_data};

	if (_data < _node->data)
		_node->lchild = Insert(_data, _node->lchild);
	else if (_data > _node->data)
		_node->rchild = Insert(_data, _node->rchild);
	else
		return _node;

	ResetHeight(_node);
	return ResetBalance(_node);
}

template <class T>
Node<T>* BiTree<T>::Remove(T _data, Node<T>* _node) {
	if (_node == nullptr) {
		cout << _data << " dosen't included\n";
		return _node;
	}

	if (_data < _node->data)
		_node->lchild = Remove(_data, _node->lchild);
	else if (_data > _node->data)
		_node->rchild = Remove(_data, _node->rchild);
	else if (_data == _node->data) {
		if (_node->lchild != nullptr && _node->rchild != nullptr) {
			Node<T>* afternode = _node->rchild;
			while (afternode->lchild) afternode = afternode->lchild;
			_node->data = afternode->data;
			_node->rchild = Remove(afternode->data, _node->rchild);
		} else {
			Node<T>* temp = _node;
			_node = _node->lchild ? _node->lchild : _node->rchild;
			delete temp;
			if (_node == nullptr) return nullptr;	 // leaf node
		}
	}
	ResetHeight(_node);
	return ResetBalance(_node);
}
template <class T>
bool BiTree<T>::search(const T _data) const {
	if (find_val(_data) == nullptr) return false;
	return true;
}

template <class T>
Node<T>* BiTree<T>::Find_Min(Node<T>* _root) {
	if (_root == nullptr) return nullptr;
	if (_root->lchild == nullptr) return _root;
	return Find_Min(_root->lchild);
}

template <class T>
Node<T>* BiTree<T>::Find_Max(Node<T>* _root) {
	if (_root == nullptr) return nullptr;
	if (_root->rchild == nullptr) return _root;
	return Find_Max(_root->rchild);
}

template <class T>
void BiTree<T>::Release(Node<T>* _nodeptr) {
	if (_nodeptr != nullptr) {
		Release(_nodeptr->lchild);
		Release(_nodeptr->rchild);
		delete _nodeptr;
	}
}

template <class T>
void BiTree<T>::InOrder(Node<T>* _nodeptr) {
	if (_nodeptr == nullptr) return;

	InOrder(_nodeptr->lchild);
	cout << _nodeptr->data << " ";
	InOrder(_nodeptr->rchild);
}

template <class T>
Node<T>* BiTree<T>::find_val(T _data) const {
	Node<T>* nodeptr = this->root;
	while (nodeptr != nullptr) {
		if (_data == nodeptr->data) return nodeptr;
		nodeptr = _data < nodeptr->data ? nodeptr->lchild : nodeptr->rchild;
	}
	return nullptr;
}

template <class T>
Node<T>* BiTree<T>::find_pre(T _data) const {
	Node<T>* nodeptr = this->root;
	Node<T>* prevptr = this->root;
	while (nodeptr != nullptr) {
		if (_data == nodeptr->data) return prevptr;
		prevptr = nodeptr;
		nodeptr = _data < nodeptr->data ? nodeptr->lchild : nodeptr->rchild;
	}
	return nullptr;
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