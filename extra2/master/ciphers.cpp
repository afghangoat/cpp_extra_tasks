/**
 * \file ciphers.cpp
 *
 * Ebben a fájlban kell megvalósítania az CaesarCipher, MyCipher, CipherQueue osztályok metódusait.
 * 
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "memtrace.h"
#include "ciphers.h"
#include <iostream>

bool megfelel_e(const std::string& str) {
    bool megfelel=true;
	for(std::size_t i=0;i<str.length();i++){
		if((str[i] < 'a' || str[i] > 'z') && str[i] != ' '){
			megfelel=false;
			break;
		}
	}
	return megfelel;
}
CaesarCipher::CaesarCipher(int s): shift(s% 26){
	if(shift<0){
		shift+=26;
	}
}
std::string CaesarCipher::encode(const std::string& message){
	if(megfelel_e(message)==false){
		throw "YSDDH7";
	}
	std::string encoded;
    for (char c : message) {
        if (c >= 'a' && c <= 'z') {
            encoded += 'a' + (c - 'a' + shift) % 26;
        } else {
            encoded += c;
        }
    }
    return encoded;
}

std::string CaesarCipher::decode(const std::string& ciphertext){
	if(megfelel_e(ciphertext)==false){
		throw "YSDDH7";
	}
	std::string decoded;
    for (char c : ciphertext) {
        if (c >= 'a' && c <= 'z') {
            decoded += 'a' + (c - 'a' - shift + 26) % 26;
        } else {
            decoded += c;
        }
    }
    return decoded;
}

Cipher* CaesarCipher::clone() const{
	Cipher* for_return=new CaesarCipher(shift);
	return for_return;
}

MyCipher::MyCipher(const std::string& k): key(k){
	offset=0;
}
MyCipher::MyCipher(const std::string& k, int o): key(k), offset(o){
	//std::cout << "key: " <<key << "\n";
	//std::cout << "offset: " <<offset << "\n";
}


Cipher* MyCipher::clone() const{
	Cipher* for_return=new MyCipher(key,offset);
	return for_return;
}

std::string MyCipher::encode(const std::string& message){
	if(megfelel_e(message)==false){
		throw "YSDDH7";
	}
	std::string encoded;
    std::size_t key_len = key.length();
	
	//std::cout << "key len: " <<key_len << "\n";
	//std::cout << "key: " <<key << "\n";
    
    for (std::size_t i = 0; i < message.length(); i++) {
        char c = message[i];
        if (c == ' ') {
            encoded += ' ';
            continue;
        }
        int shift = offset + i + (key[i % key_len] - 'a')%26;
		//std::cout <<"shift: " << shift << "|";

        unsigned char new_c = c+(shift%26);
		if(new_c<'a'){
			new_c+=26;
		}
		if(new_c>'z'){
			new_c-=26;
		}
		//std::cout <<"regi: " << c << "|"<<"uj: " << new_c << "|"<<"shift: " << shift << "\n";

        encoded += new_c;
    }
    return encoded;
}
std::string MyCipher::decode(const std::string& ciphertext){
	if(megfelel_e(ciphertext)==false){
		throw "YSDDH7";
	}
	std::string decoded;
    std::size_t key_len = key.length();
    
    for (std::size_t i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];
        if (c == ' ') {
            decoded += ' ';
            continue;
        }
        int shift = offset + i + (key[i % key_len] - 'a');
        unsigned char new_c = 'a' + (c - 'a' - shift + 26) % 26;
		if(new_c<'a'){
			new_c+=26;
		}
		if(new_c>'z'){
			new_c-=26;
		}
		decoded+=new_c;
    }
    return decoded;
}

void CipherQueue::add(Cipher* cipher){
	tarolo.push_back(cipher);
}
CipherQueue::CipherQueue(const CipherQueue& other){
	for (Cipher* c : other.tarolo) {
        tarolo.push_back(c->clone());
    }
}
CipherQueue::CipherQueue(){
	//Ide még semmi
}
std::string CipherQueue::encode(const std::string& message){
	if(megfelel_e(message)==false){
		throw "YSDDH7";
	}
	std::string encoded=message;
	for (Cipher* cipher : tarolo) {
		encoded=cipher->encode(encoded);
	}
	return encoded;
}
std::string CipherQueue::decode(const std::string& ciphertext){
	if(megfelel_e(ciphertext)==false){
		throw "YSDDH7";
	}
	std::string decoded=ciphertext;
	for (Cipher* cipher : tarolo) {
		decoded=cipher->decode(decoded);
	}
	return decoded;
}
Cipher* CipherQueue::clone() const{
	Cipher* cqueue=new CipherQueue(*this);
	return cqueue;
}
CipherQueue::~CipherQueue() {
    for (Cipher* c : tarolo) {
        delete c;
    }
}