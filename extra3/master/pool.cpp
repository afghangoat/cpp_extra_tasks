/**
 * \file pool.cpp
 *
 * StringPool osztály implemntációja
 * Valósítsd meg az osztály metódusait, a leírást a header fájlban találod.
 * 
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "memtrace.h"
#include "pool.h"

void StringPool::try_sort() {
	if (needs_sort_again==true) {
        needs_sort_again = false;
        std::sort(pool.begin(), pool.end(),[](const std::pair<RString*, bool>& a, const std::pair<RString*, bool>& b) {
			return a.first->capacity() < b.first->capacity();
		});
    }
	
}


StringPool::StringPool(size_t obj_num, size_t init_cap){
	// Létrehoz obj_num db RString obejktumot, 
	// melyek kapacitása init_cap méretű
	for(size_t i=0;i<obj_num;i++){
		pool.push_back(std::make_pair(new RString(init_cap),false));
	}
	needs_sort_again=false;
	
}

// Visszaad egy szabad RString objektumot ami 
// legalább capacity kapacitással rendelkezik
// azt az objektumot kell visszadni, ami maximális kihasználtságú
// Ha nincs ilyen a pool-ban, akkor létrehoz egyet (capacity kapacitással).
// Visszavonásig az a string objektum nem oszható ki.
// "Foglaltnak" minősül
RString& StringPool::acquire(size_t capacity){
	try_sort();
	for (size_t i = 0; i < pool.size(); ++i) {
		if (acquireable(*(pool[i].first)) && pool[i].first->capacity() >= capacity) {
			pool[i].second=true;
			return *(pool[i].first);
		}
	}
	pool.push_back(std::make_pair(new RString(capacity),true));
	needs_sort_again=true;
	return *(pool.back().first);
}

// Visszaad egy szabad RString objektumot amibe 
// belefér a paraméteül kapott string, azt bele is másolja.
// azt az objektumot kell visszadni, ami maximális kihasználtságú
// Ha nincs ilyen a pool-ban, akkor létrehoz egyet (strlen(str)+1 kapacitással).
// Visszavonásig az a string objektum nem oszható ki.
// "Foglaltnak" minősül
RString& StringPool::acquire(const char* str){
	try_sort();
	size_t len = std::strlen(str);
	for (size_t i = 0; i < pool.size(); ++i) {
		if (acquireable(*(pool[i].first)) && pool[i].first->capacity() > len) {
			std::strcpy(*(pool[i].first), str);
			pool[i].second=true;
			return *(pool[i].first);
		}
	}
	pool.push_back(std::make_pair(new RString(str, len + 1),true));
	std::strcpy(*(pool.back().first), str);
	needs_sort_again=true;
	return *(pool.back().first);
}

// Visszaadja, hogy az str objektum szabad, azaz 
// kiosztható/megszerezhető-e
bool StringPool::acquireable(const RString& str) const{
	for (size_t i = 0; i < pool.size(); ++i) {
		if(*(pool[i].first)==str){
			if(pool[i].second==true){
				return false;
			}
		}
	}
	return true;
}

// Ezután a visszaadott str objektum újra kiosztható másnak
// A függvény "reseteli" a stringet is: a karaktertömb első 
// helyére '\0'-t rak.
// Ha az objektum már nem foglalt, nem dob hibát!
void StringPool::release(RString& str){
	char* data = str;
	if (!acquireable(str)) {
		data[0] = '\0';
	}
	for (size_t i = 0; i < pool.size(); ++i) {
		if(*(pool[i].first)==str){
			pool[i].second=false;
		}
	}
}

// Hozzáfűzi str1 végére str2-t. 
// - Ha str1 kapacitása elegendő
//   akkor str1-ben végzi ezt el, és azt adja vissza
// - Ha nem, akkor egy új string-et kér (acquire), és abban
//   fűzi össze őket, majd visszaadja azt
// Figyelj mit, hogyan kell nyílvántartani! Az str1 és
// str2 csak kiosztott erőforrások lehetnek, a visszatérési 
// érték is szintén kiosztott. 
// Ha a paraméterek nem lefoglalt erőforrások, 
// akkor eldobja a neptun kódodat!
RString& StringPool::append(RString& str1, const RString& str2){
	bool str1_ok = false;
	bool str2_ok = false;

	for (size_t i = 0; i < pool.size(); ++i) {
		
		if (*(pool[i].first) == str1 && !acquireable(*(pool[i].first))) str1_ok = true;
		if (*(pool[i].first) == str2 && !acquireable(*(pool[i].first))) str2_ok = true;
	}

	if (!str1_ok || !str2_ok) throw "YSDDH7";

	if (str1.size() + str2.size() < str1.capacity()) {
		std::strcat(str1, str2);
		return str1;
	} else {
		size_t new_len = str1.size() + str2.size();
		char* temp = new char[new_len + 1];
		std::strcpy(temp, str1);
		std::strcat(temp, str2);
		RString& result = acquire(temp);
		delete[] temp;
		return result;
	}
}

// visszaadja a pool méretét
size_t StringPool::size() const{
	return pool.size();
}

// visszaadja a szabad objektumok számát
size_t StringPool::free_size() const{
	size_t free=0;
	for (size_t i = 0; i < pool.size(); ++i) {
		if(pool[i].second==false){
			free++;
		}
	}
	return free;
}

StringPool::~StringPool() {
	for (size_t i = 0; i < pool.size(); ++i) {
		if(pool[i].first!=nullptr){
			delete pool[i].first;
			pool[i].first=nullptr;
		}
		
	}
	pool.clear();
}