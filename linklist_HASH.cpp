#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int HASHSIZE = 5;

struct Node {
	string key;
	string value;
	Node* next = nullptr;
};

class HashTable {
 private:
	vector<Node*> table = vector<Node*>(HASHSIZE, nullptr);

 public:
	HashTable() {}
	~HashTable();
	size_t hash(string _key);
	Node* find_key(string _key);
	bool search_key(string _key);
	void insert(string _key, string _value);
	void display();
};

HashTable::~HashTable() {
	for (int i = 0; i < HASHSIZE; i++) {
		Node* head = table[i];
		while (head != nullptr) {
			Node* prev = head;
			head = head->next;
			delete prev;
		}
	}
}

size_t HashTable::hash(string _key) {
	size_t hash = 5381;
	for (auto Iter : _key) hash += (hash << 5) + Iter;
	return hash % HASHSIZE;
}

void HashTable::insert(string _key, string _value) {
	auto index = hash(_key);
	if (table[index] == nullptr) {
		table[index] = new Node{_key, _value, nullptr};
		return;
	}

	Node* head = table[index];
	if (head->key == _key) return;
	while (head->next != nullptr) {
		if (head->next->key == _key) return;
		head = head->next;
	}
	head->next = new Node{_key, _value, nullptr};
	return;
}

void HashTable::display() {
	for (auto Iter : table) {
		auto head = Iter;
		while (head != nullptr) {
			cout << head->key << "-" << head->value << " ";
			head = head->next;
		}
        cout << endl;
	}
}

int main() {
	string key[] = {"a", "b", "c", "d", "e", "f"};
	string value[] = {"value1", "value2", "value3", "value4", "value5", "value6"};
	HashTable demo;
	for(int i = 0; i < 6; i++)
        demo.insert(key[i], value[i]);
    demo.display();
    return 0;
}