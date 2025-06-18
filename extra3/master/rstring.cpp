/**
 * \file rstring.cpp
 *
 * RString osztály implemntációja
 * Valósítsd meg az osztály metódusait, a leírást a header fájlban találod.
 * 
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "memtrace.h"
#include "rstring.h"

RString::RString(size_t capacity){
	max_capacity=capacity;
	len=0;
    adat = new char[max_capacity];
	adat[0]='\0';
}
// Létrehoz egy karaktertömböt strlen(str) + 1 mérettel
// majd odamásolja str tartalmát 
RString::RString(const char* str){
	max_capacity = std::strlen(str)+1;
	if (max_capacity<=1) {
        str=new char[1]{ '\0' };
    } else {
		adat=new char[max_capacity];
        std::strcpy(adat, str);
		adat[max_capacity-1]='\0';
    }
	len=max_capacity-1;
}

// Létrehoz egy karaktertömböt capacity mérettel,
// majd odamásolja az str string-et
// Ha a string nem fér bele, eldobja a neptun-kódodat
RString::RString(const char* str, size_t capacity){
	max_capacity=capacity;
    adat = new char[max_capacity]{'\0'};
	size_t temp_len=std::strlen(str); //'\0'
	if(temp_len>=max_capacity){
		delete[] adat;
		throw "YSDDH7";
	} else {
		len=temp_len;
		std::strcpy(adat,str);
	}
	
	adat[max_capacity-1]='\0';
}

// Megadja a string méretét (strlen)
size_t RString::size() const{
	return std::strlen(adat);
}

// Megadja a karaktertömb kapacitását
size_t RString::capacity() const{
	return max_capacity;
}

// Visszaadja a string memóriaterületére mutató pointert
RString::operator char*() const{
	return adat;
}

// Bemásolja a karaktertömbbe a paraméterül kapott 
// karakterláncot, ha nem fér bele, eldobja a neptun kódot
RString& RString::operator=(const char* str){
	size_t newstr_len=std::strlen(str);
	if(newstr_len>=max_capacity){
		throw "YSDDH7";
	} else {
		len=newstr_len;
		for(size_t i=0;i<max_capacity;i++){
			adat[i]='\0';
		}
		std::strcpy(adat,str);
	}
	return *this;
}

RString::~RString(){
	if(adat!=nullptr){
		delete[] adat;
		adat=nullptr;
	}
}