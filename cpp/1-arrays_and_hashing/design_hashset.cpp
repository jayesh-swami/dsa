#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>
#include <list>

using std::cout;
using std::move;
using std::pair;
using std::sort;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::pow;
using std::list;

/**
 * Using chaining for collision resolution
 */
class MyHashSet {
private:
	// Prime number just below 20k to have a good load factor
	static const int TABLE_SIZE = 19997;
	vector<list<int>> hash;

	int calculateHash(int n) {
		return n % TABLE_SIZE;
	}
public:
	MyHashSet(): hash(TABLE_SIZE) {}
    
	void add(int key) {
		int index = calculateHash(key);

		for(int n: hash[index]) {
			if(n == key) return;
		}

		hash[index].push_back(key);
	}
    
	bool contains(int key) {
		int index = calculateHash(key);

		for(int n: hash[index]) {
			if(n == key) return true;
		}
		return false;
	}
    
	void remove(int key) {
		int index = calculateHash(key);
       		
		for(auto it = hash[index].begin(); it != hash[index].end(); it++) {
			if(*it == key) {
				hash[index].erase(it);
				return;
			}
		}
		return;
	}
};

/**
 * Using Linear Probing/Quadratic Probing for collision resolution
 */
class MyHashSetLinearProbing {
private:
	// Prime number just below 20k to have a good load factor
	
	static const int TABLE_SIZE = 19997;
	enum class Status { EMPTY, DELETED, EXISTS };
	vector<int> hash;
	vector<Status> hashStatus;
	int currentSize;

	int calculateHash(int n) {
		int h = n % TABLE_SIZE;
		
		// Negative keys handling
		return h < 0 ? h + TABLE_SIZE : h;
	}

	int find(int key) {
		int hashIdx = calculateHash(key);

		for(int i = 0; i < TABLE_SIZE; i++) {
			int idx = (hashIdx + i) % TABLE_SIZE;
			if(hashStatus[idx] == Status::EMPTY) return -1;
			if(hashStatus[idx] == Status::EXISTS and hash[idx] == key) return idx;
		}

		return -1;
	}

public:
	MyHashSetLinearProbing(): hash(TABLE_SIZE), hashStatus(TABLE_SIZE, Status::EMPTY), currentSize(0) {}

	void add(int key) {
		if(currentSize >= TABLE_SIZE) {
			// Silent return since the num-ops is max 10k so in reality we will never hit the ceiling
			return;
		}

		if(find(key) != -1) return;

		int hashIdx = calculateHash(key);
		
		for(int i = 0; i < TABLE_SIZE; i++) {
			int idx = (hashIdx + i) % TABLE_SIZE;
			if(hashStatus[idx] != Status::EXISTS) {
				hash[idx] = key;
				hashStatus[idx] = Status::EXISTS;
				currentSize++;
				break;
			};
		}
		
		return;
	}
    
	bool contains(int key) {
		return find(key) != -1; 			
	}
    
	void remove(int key) {
		int idx = find(key);

		if(idx == -1) return;

		hashStatus[idx] = Status::DELETED;
		currentSize--;
	}
};


int main() {

	return 0;
}

