#include <iostream>
#include <unordered_map>
using namespace std;

struct DLL {
	int key;
	int value;
	int freq;
	DLL *next;
	DLL *prev;
	DLL(int key, int value, int freq) {
		this->key = key;
		this->value = value;
		this->freq = freq;
		next = NULL;
		prev = NULL;

	}
};

class Managed_list {
	DLL *head = NULL;
	DLL *tail = NULL;
public:
	Managed_list(DLL *node) {
		head = new DLL(0, 0, 0);
		tail = new DLL(0, 0, 0);
		head->next = node;
		node->prev = head;
		node->next = tail;
		tail->prev = node;
	}
	Managed_list() {

	}
	void insert(DLL *node) {

		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;

	}
	DLL* detach() {
		DLL *temp = head->next;
		temp->next->prev = head;
		head->next = temp->next;
		temp->next = NULL;
		temp->prev = NULL;
		return temp;
	}
	void detachNode(DLL *temp) {
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		temp->next = NULL;
		temp->prev = NULL;

	}
	bool check_empty() {
		if (head->next == tail && tail->prev == head) {
			return true;
		}
		return false;

	}
	void print() {
		DLL *temp = head;
		while (temp) {
			cout << temp->key <<","<< temp->value << " ";
			temp = temp->next;
		}
	}
};
class LFU {
	unordered_map<int, Managed_list> f;
	unordered_map<int, DLL*> map;
	int capacity;
	int min_freq;
public:

	LFU(int capacity) {
		this->capacity = capacity;
	}
	int get(int);
	void set(int, int);
	void print() {
		for (auto i : f) {
			cout << i.first << "-";
			i.second.print();
			cout << endl;
		}
	}

};

int LFU::get(int key) {
	if (map.find(key) == map.end()) {
		return -1;
	}
	DLL *node = map[key];
	Managed_list m = f[node->freq];
	m.detachNode(node);
	if (m.check_empty()) {
				f.erase(node->freq);
				if (node->freq == min_freq) {
					min_freq++;
				}
			}
	node->freq = node->freq + 1;
	if (f.find(node->freq) == f.end()) {
		Managed_list m(node);
		f[node->freq] = m;
	} else {
		f[node->freq].insert(node);
	}
	return map[key]->value;

}
void LFU::set(int key, int val) {
	if (map.find(key) == map.end()) {

		if (map.size() == capacity) {
			DLL *node = f[min_freq].detach();

			map.erase(node->key);
			free(node);
		}
		this->min_freq = 1;
		DLL *node = new DLL(key, val, 1);

		if (f.find(min_freq) == f.end()) {
			Managed_list m(node);
			f[min_freq] = m;
		} else {
			f[min_freq].insert(node);
		}
		map[key] = node;

	} else {
		DLL *node = map[key];
		node->value = val;
		Managed_list m = f[node->freq];
		m.detachNode(node);
		if (m.check_empty()) {
			f.erase(node->freq);
			if (node->freq == min_freq) {
				min_freq++;
			}
		}
		node->freq = node->freq + 1;
		if (f.find(node->freq) == f.end()) {
			Managed_list m(node);
			f[node->freq] = m;
		} else {
			f[node->freq].insert(node);
		}
	}
}

int main(int argc, char **argv) {
	int cap, q, key, val;
	    cin >> cap;
	    cin >> q;
	    LFU cache(cap);
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


