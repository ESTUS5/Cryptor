#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;


class cypher{ //abstract
public:
	virtual string crypt(string encoded, string string_to_encrypt) = 0;
	virtual string decrypt(string plain, string string_to_decrypt) = 0;
	~cypher(){
		string crypt();
		string decrypt();
	}
};

class ROT : public cypher{ //szyfr Cezara
public:
		
		string crypt(string encoded, string string_to_encrypt){ // encrypt
			
			char temp;    
			int i;
	
			for(i = 0; string_to_encrypt[i] != '\0'; i++){
				
				temp = string_to_encrypt[i];
				
				if(temp >= 'a' && temp <= 'z'){
			 		temp = temp + 13;
			  	
					if(temp > 'z'){
						temp = temp - 'z' + 'a' - 1;
					}
	
					encoded[i] = temp;
				}
				else if(temp >= 'A' && temp <= 'Z'){
 					temp = temp + 13;
	
					if(temp > 'Z'){
						temp = temp - 'Z' + 'A' - 1;
					}
	
					encoded[i] = temp;
				}
			}
	
    	return encoded;
		}
		
		string decrypt(string plain, string string_to_decrypt){ // decrypt
			
			char temp;
			int i;

			for(i = 0; string_to_decrypt[i] != '\0'; ++i){
				temp = string_to_decrypt[i];
        
        		if(temp == 'x'){
        			temp = ' ';
				}
        		
        		else if(temp >= 'a' && temp <= 'z'){
            		temp = temp - 13;
            
            		if(temp < 'a'){
                		temp = temp + 'z' - 'a' + 1;
            		}
            
            		plain[i] = temp;
        		}
        		else if(temp >= 'A' && temp <= 'Z'){
            		temp = temp - 13;
            
            		if(temp > 'a'){
                		temp = temp + 'Z' - 'A' + 1;
            		}
            
            		plain[i] = temp;
        		}
    		}
    
    	return plain;
		}
		
	~ROT(){
		string crypt(string encoded, string string_to_encrypt);
		string decrypt(string plain, string string_to_decrypt);
	}
};

class XOR : public cypher{ // Szyfr XOR
public:
		string crypt(string encoded, string string_to_encrypt){ // encrypt
			
			encoded = string_to_encrypt;
			int i;
			
			for (i = 0; i < string_to_encrypt.size(); i++){
        		encoded[i] = string_to_encrypt[i] ^ 'X';
			}
			
			return encoded;
}

		string decrypt(string plain, string string_to_decrypt){ // decrypt
			
			plain = string_to_decrypt;
			int i;
			
			for (i = 0; i < string_to_decrypt.size(); i++){
        		plain[i] = string_to_decrypt[i] ^ 'X';
			}
			
			return plain;
		}
		
	~XOR(){
		string crypt(string encoded, string string_to_encrypt);
		string decrypt(string plain, string string_to_decrypt);
	}
};

class loader{ // operacje plik->string, string->plik
public:
	string string_to_encrypt;
	string string_to_decrypt;
	string encoded;
	
	
	string load(int a,string string_to_){
				
		if(a == 1){
			fstream plain_file;
			plain_file.open( "plain.txt", fstream::in | fstream::out ); //otwiera plik plain.txt
			getline( plain_file, string_to_ );
			plain_file.close();
			return string_to_;
		}
		
		else if(a == 2){
			fstream rot_file;
			rot_file.open( "rot.cif", fstream::in | fstream::out ); //otwiera plik rot.cif
			getline( rot_file, string_to_);
			rot_file.close();
			return string_to_;
		}
		
		else if(a == 3){
			fstream xor_file ( "xor.cif",  fstream::in | fstream::out ); //otwiera plik xor.cif
			getline( xor_file, string_to_);
			xor_file.close();
			return string_to_;
		}
	}
	void store(int a,string encoded){ // warunek kiedy XOR, a kiedy ROT
		
		if(a == 1){
			ofstream xor_file ("xor.cif"); //tworzy plik
			xor_file << encoded; //zapisuje do niego szyfr
			xor_file.close();
		}
		
		else if(a == 2){
			ofstream rot_file ("rot.cif"); //tworzy plik
			rot_file << encoded; //zapisuje do niego szyfr
			rot_file.close();
		}
	}
	~loader(){
		string load(char tab[10]);
		void store(string encoded);
	}
};

class printer{
public:
	void print(int a,string to_print){ //warunki kiedy jaki tekst ma wypisywaæ
		
		if(a == 1){
			cout << "Text to encrypt:" << to_print << endl <<endl;
		}
		
		if(a == 2){
			cout << "XOR code:" << to_print << endl;
		}
		
		if(a == 3){
			cout << "ROT code:" << to_print << endl << endl;
		}
		
		if(a == 4){
			cout << "XOR Decrypt:" << to_print << endl;
		}
		
		if(a == 5){
			cout << "ROT Decrypt:" << to_print << endl;
		}
	}
	~printer(){
		void print(int a, string to_print);
	}
};

int main() {
	string string_to_encrypt; 
	string string_to_decrypt;
	string encoded;
	string plain;
	
	loader LOAD; // ³aduje z pliku do stringa i ze stringa do ci¹gu
	printer PRINT; //wypisuje dane na terminalu
	cypher * CYPHER; //abstract, wskaŸnik CYPHER
	XOR x; //obiekt XORa
	ROT r; //obiekt ROTa
	
	string_to_encrypt = LOAD.load(1, string_to_encrypt); //wypisuje zawartoœæ plain.txt
	PRINT.print(1,string_to_encrypt);
	
	CYPHER = &x;
	encoded = CYPHER -> crypt(encoded, string_to_encrypt); // szyfruje XORem
	PRINT.print(2, encoded);
	LOAD.store(1, encoded);
	
	CYPHER = &r;
	encoded = CYPHER -> crypt(encoded, string_to_encrypt); // szyfruje Cezarem
	PRINT.print(3, encoded);
	LOAD.store(2, encoded);
	
	CYPHER = &x;
	string_to_decrypt = LOAD.load(3, string_to_decrypt); // odszyfrowywuje XORa
	plain = CYPHER -> decrypt(plain, string_to_decrypt);
	PRINT.print(4, plain);
	
	CYPHER = &r;
	string_to_decrypt = LOAD.load(2, string_to_decrypt); // odszyfrowywuje Cezara
	plain = CYPHER -> decrypt(plain, string_to_decrypt);	
	PRINT.print(5, plain);

	return 0;
}
