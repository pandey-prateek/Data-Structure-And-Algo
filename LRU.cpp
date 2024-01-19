#include <iostream>
#include <unordered_map>
using namespace std;

struct DLL {
	int key;
	int value;
	DLL *next;
	DLL *prev;
	DLL(int key, int value) {
		this->key = key;
		this->value = value;
		next = NULL;
		prev = NULL;

	}
};

class LRU {
	unordered_map<int, DLL*> map;
	DLL *head = NULL;
	DLL *tail = NULL;
	int capacity;
public:
	LRU(int capacity) {
		this->capacity = capacity;
		head = new DLL(0, 0);
		tail = new DLL(0, 0);
		head->next = tail;
		tail->prev = head;
	}
	int get(int);
	void set(int, int);
	void print() {
		DLL *temp = head;
		while (temp) {
			cout << temp->key << temp->value << " ";
			temp = temp->next;
		}
	}
};
int LRU::get(int key) {
	if (map.find(key) == map.end()) {
		return -1;
	}
	DLL *temp = map[key];
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	temp->prev = tail->prev;
	temp->next = tail;
	tail->prev->next = temp;
	tail->prev = temp;
	map[key] = temp;
	return map[key]->value;
	return map[key]->value;
}
void LRU::set(int key, int val) {
	if (map.find(key) == map.end()) {
		if (map.size() == capacity) {
			DLL *temp = head->next;
			temp->next->prev = head;
			head->next = temp->next;
			temp->next = NULL;
			temp->prev = NULL;
			map.erase(temp->key);
			free(temp);

		}
		DLL *node = new DLL(key, val);
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
		map[key] = node;
	} else {
		DLL *temp = map[key];
		temp->value = val;
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		temp->prev = tail->prev;
		temp->next = tail;
		tail->prev->next = temp;
		tail->prev = temp;
		map[key] = temp;
	}

}

int main(int argc, char **argv) {
	int cap, q, key, val;
		    cin >> cap;
		    cin >> q;
		    LRU cache(cap);
		    while (q--)
		    {
		        int type;
		        cin >> type;
		        switch (type)
		        {
		        case 1:
		            cin >> key;
		            cout << cache.get(key) << endl;
		            break;
		        case 2:
		            cin >> key;
		            cin >> val;
		            cache.set(key, val);
		            break;
		        default:
		            cout << "Wrong choice";
		        }

		    }
		    return 0;
}


