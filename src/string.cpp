#include "string.hpp"
#include <utility>
#include <iostream>

String::String(const char *s)
{
	int len = strlen(s);
	buf = new char[len+1];

	for (int i = 0; i < len; ++i){
		buf[i] = s[i];
	}
	buf[len] = '\0';
	delete[] s;
}

//COPY CONSTRUCTOR
String::String(const String &s)
	{
	int len = strlen(s.buf);
	buf = new char[len+1];

	for (int i = 0; i<len; ++i){
		buf[i] = s.buf[i];
	}
	buf[len] = '\0';
	}

//MOVE CONSTRUCTOR
String::String(String &&s)
	: buf (s.buf)
	{
	delete[] s.buf;
	s.buf = nullptr;
	}

void String::swap(String &s){
	std::swap(buf, s.buf);
}

//COPY ASSIGNMENT
String& String::operator=(const String &s){
	if (&s == this) return *this;

	int len = strlen(s.buf);
	buf = new char[len+1];

	for(int i = 0; i<len; ++i){
		buf[i] = s.buf[i];
	}
	buf[len] = '\0';
	return *this;
}

//MOVE ASSIGNMENT
String& String::operator=(String &&s){
	if(&s == this) return *this;
	delete(buf);
	swap(s);
	s.buf = nullptr;
	return *this;
}

char& String::operator[](int index){
	int lim = strlen(buf);
	if (index < lim && index>=0) return buf[index];
	else if (index < 0 && lim != 0) return buf[lim+index-1];
	else if (index >= lim && lim != 0) return buf[index%lim];
	else return buf[0];
}

const char& String::operator[](int index) const{
	int lim = strlen(buf);
	if (index < lim && index>= 0) return buf[index];
	else if (index < 0 && lim != 0) return buf[lim+index-1];
	else if (index >= lim && lim!=0) return buf[index%lim];
	else return buf[0];
}

int String::size() const{
	return strlen(buf);
}

String String::reverse() const{
	String temp;
	
	reverse_cpy(temp.buf, buf);

	return temp;
}

int String::indexOf(char c) const{
	const char* temp = strchr(buf, c);
	if (temp != nullptr) return temp - buf; else return -1;

}

int String::indexOf(const String &s) const{
	const char* temp = strstr(buf, s.buf);
	if (temp != nullptr) return temp - buf; else return -1;

}

bool String::operator==(const String &s) const{
	if(strcmp(buf, s.buf) == 0) return true; else return false;	
}

bool String::operator!=(const String &s) const{
	if(strcmp(buf, s.buf) != 0) return true; else return false;
}

bool String::operator>(const String &s) const{
	if(strcmp(buf, s.buf) > 0) return true; else return false;
}

bool String::operator<(const String &s) const{
	if(strcmp(buf, s.buf) < 0) return true; else return false;
}

bool String::operator<=(const String &s) const{
	if(strcmp(buf, s.buf) <= 0) return true; else return false;
}

bool String::operator>=(const String &s) const{
	if(strcmp(buf, s.buf) >= 0) return true; else return false;
}

String String::operator+(const String &s) const{
	String sup = String(strlen(buf) + strlen(s.buf) + 1);
	sup.buf = strcpy(sup.buf, buf);
	sup.buf = strcat(sup.buf, s.buf);
	
	return sup;
}


String& String::operator+=(const String &s){
	int total_len = strlen(buf) + strlen(s.buf);
	String sup = String(total_len+1);
	sup.buf = strcpy(sup.buf, buf);
	sup.buf = strcat(sup.buf, s.buf);
	buf = new char[total_len+1];
	for(int i = 0; i<total_len; ++i){
		buf[i] = sup.buf[i];
	}
	buf[total_len] = '\0';

	return *this;
}


void String::print(std::ostream &out) const{
	out << buf;
}

void String::read(std::istream &in){
	delete[] buf;
	buf = new char[1024];
	in.getline(buf, 1023);
}

String::~String(){
	delete[] buf;
}







int String::strlen(const char *s){
	const char* temp = s;
	for(; *temp != '\0'; ++temp) {}
	return temp-s;
}

char* String::strcpy(char *dest, const char *src){
	int counter = 0;

	for (; src[counter] != '\0'; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';
	return dest;

}

char* String::strdup(const char *src){
	int src_len = strlen(src);
	String *temp = new String(src_len + 1);
	return strcpy(temp->buf, src);
}

char* String::strncpy(char *dest, const char *src, int n){
	
	int counter = 0;
	for (; src[counter] != '\0' && counter < n; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';
	return dest;
}



char* String::strcat(char *dest, const char *src){
	int dest_counter = strlen(dest);
	const char *s = src;
	for(; *s != '\0'; ++dest_counter, ++s) dest[dest_counter] = *s;
		
	dest[dest_counter] = '\0';

	return dest;

}




char* String::strncat(char *dest, const char *src, int n){
	
	int counter{0};
	int dest_counter = strlen(dest);

	for (; src[counter] != '\0' && counter < n; ++counter, ++dest_counter) dest[dest_counter] = src[counter];
	dest[dest_counter] = '\0';
	return dest;
}




int String::strcmp(const char *left, const char *right){
	
	for (; *left != '\0' && *right != '\0' && *left == *right; ++left, ++right){}
	return *left - *right;
}

int String::strncmp(const char *left, const char *right, int n){
	for (int counter=0; *left != '\0' && *right != '\0' && *left == *right && counter < n; ++counter){}
	return *left - *right;
}


void String::reverse_cpy(char *dest, const char *src){
	int src_len{strlen(src)};
	for (int counter = 0; counter < src_len; ++counter){
		dest[counter] = src[src_len-1-counter];
	}
	dest[src_len] = '\0';
}

const char* String::strchr(const char *str, char c){
	int counter{0};
	for (; str[counter] != '\0' && str[counter] != c; ++counter) {}
	if (str[counter] == c) return &str[counter]; else return nullptr;
}

const char* String::strstr(const char *haystack, const char *needle){
	int hay_size{strlen(haystack)};
	int ned_size{strlen(needle)};
	if (ned_size > hay_size || ned_size == 0) return nullptr;
	for (int counter = 0; counter < hay_size - ned_size+1; ++counter){
		if (strcmp(&haystack[counter], needle) == 0){
			return &haystack[counter];
		}
	} 
	return nullptr;
}

String::String(int length){
	buf = new char [length];
}

std::ostream &operator<<(std::ostream &out, const String& s){
	s.print(out);
	return out;
}

std::istream &operator>>(std::istream &in, String &s){
	s.read(in);
	return in;
}
