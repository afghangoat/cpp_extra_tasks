/**
 * \file ciphers.h
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef CipherS_H
#define CipherS_H

#include <string>
#include <vector>
#include "memtrace.h"

/**
 * Az ős osztály interfésze
 */ 
class Cipher {
public:
    /**
     * Titkosítja a kapott stringet
     * @param   message titkosítandó üzenet
     * @return  a message szöveg titkosított változata
     */
    virtual std::string encode(const std::string& message) = 0;
    /**
     * Dekódolja a kapott stringet
     * @param   ciphertext titkosított üzenet
     * @return  a megfejtett nyílt szöveg
     */
    virtual std::string decode(const std::string& ciphertext) = 0;
    /**
     * Létrehoz egy másolatot dinamikusan
     * @return  a létrehozott objektumra mutató pointer
     */
    virtual Cipher* clone() const = 0;
    /**
     * Alap destruktor
     */ 
    virtual ~Cipher() { };
};

bool megfelel_e(const std::string& str);

//Osztályok, amiket meg kell csinálni a leírások és az osztálydiagram alapján
class CaesarCipher: public Cipher {
	int shift;
	public:
		CaesarCipher(int s);
		std::string encode(const std::string& message) override;
		std::string decode(const std::string& ciphertext) override;
		Cipher* clone() const override;
		~CaesarCipher() override = default;
};

class MyCipher: public Cipher {
	std::string key;
	int offset;
	public:
		MyCipher(const std::string& k);
		MyCipher(const std::string& k, int o);
		std::string encode(const std::string& message) override;
		std::string decode(const std::string& ciphertext) override;
		Cipher* clone() const override;
		~MyCipher() override = default;
};

class CipherQueue: public Cipher {
	std::vector<Cipher*> tarolo;
	public:
		void add(Cipher* cipher);
		CipherQueue();
		CipherQueue(const CipherQueue& other);
		std::string encode(const std::string& message) override;
		std::string decode(const std::string& ciphertext) override;
		Cipher* clone() const override;
		~CipherQueue() override;
};

#endif