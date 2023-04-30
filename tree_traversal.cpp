#include <iostream>

using namespace std;

template <class T>
struct Node {
	T data;
	Node<T> *lchild = NULL;
	Node<T> *rchild = NULL;
};

template <class T>
class BiTree {
 public:
	BiTree() { root = Create(root); }
	BiTree(Node<T> *_root) { root = _root; }
	~BiTree() { Release(root); }
	void PreOrder() { PreOrder(root); cout << endl; }
	void InOrder() { InOrder(root); cout << endl; }
	void PostOrder() { PostOrder(root); cout << endl; }

 private:
	Node<T> *root;
	Node<T> *Create(Node<T> *bt);
	void Release(Node<T> *bt);
	void PreOrder(Node<T> *bt);
	void InOrder(Node<T> *bt);
	void PostOrder(Node<T> *bt);
};

template <class T>
Node<T> *BiTree<T>::Create(Node<T> *bt) {
	T ch;
	cin >> ch;
	if (ch == '#')
		bt = NULL;
	else {
		bt = new Node<T>;
		bt->data = ch;
		bt->lchild = Create(bt->lchild);
		bt->rchild = Create(bt->rchild);
	}
	return bt;
}

template <class T>
void BiTree<T>::Release(Node<T> *bt) {
	if (bt != NULL) {
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

template <class T>
void BiTree<T>::PreOrder(Node<T> *bt) {
	if (bt == NULL) return;

	cout << bt->data << " ";
	PreOrder(bt->lchild);
	PreOrder(bt->rchild);
}

template <class T>
void BiTree<T>::InOrder(Node<T> *bt) {
	if (bt == NULL) return;

	InOrder(bt->lchild);
	cout << bt->data << " ";
	InOrder(bt->rchild);
}

template <class T>
void BiTree<T>::PostOrder(Node<T> *bt) {
	if (bt == NULL) return;
	PostOrder(bt->lchild);
	PostOrder(bt->rchild);
	cout << bt->data << " ";
}
void build_demo_tree(Node<char> *T[11]);
int main() {
	Node<char> *T[11];
	for (int i = 0; i < 11; i++) T[i] = new Node<char>;
	for (char i = 'A'; i <= 'K'; i++) T[i - 'A']->data = i;
	build_demo_tree(T);

	BiTree Tree(T[0]);

	Tree.PreOrder();
	cout << endl;

	Tree.InOrder();
	cout << endl;

	Tree.PostOrder();
	cout << endl;

	return 0;
}

void build_demo_tree(Node<char> *T[11]) {
	T[0]->lchild = T[1];
	T[0]->rchild = T[2];

	T[1]->lchild = T[3];
	T[1]->rchild = T[4];

	T[2]->lchild = T[5];
	T[2]->lchild = T[6];

	T[3]->lchild = T[7];
	T[3]->rchild = T[8];

	T[4]->rchild = T[9];

	T[5]->rchild = T[10];
}