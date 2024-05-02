#include "string.hpp"
#include <utility>

String::String(const char *s){
	buf = strdup(s);
}

String::String(const String &s){
	buf = strdup(s.buf);
}



//String::String(String &&s);

void String::swap(String &s){
	int s_len{strlen(s.buf)};
	String temp = String(s_len+1);
	temp.buf = strdup(s.buf);
	delete[] s.buf;
	//s.buf = nullptr;

	s.buf = strdup(buf);
	delete[] buf;
	//buf = nullptr;

	buf = strdup(temp.buf);
	delete[] temp.buf;
	//temp.buf = nullptr;
}

String& String::operator=(String s){
	delete[] buf;
	buf = strdup(s.buf);
	return *this;
}

//String String::&operator=(String &&s);

char& String::operator[](int index){
	int lim = strlen(buf);
	if (index < lim && index>= 0) {
		return buf[index];
	}else if (index < 0 && lim != 0){
		return buf[lim+index-1];
	}else if (index >= lim && lim!=0){
		return buf[index%lim];
	}else throw("Out of bounds!");
}

const char& String::operator[](int index) const{
	int lim = strlen(buf);
	if (index < lim && index>= 0) {
		return buf[index];
	}else if (index < 0 && lim != 0){
		return buf[lim+index-1];
	}else if (index >= lim && lim!=0){
		return buf[index%lim];
	}else throw("Out of bounds!");
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
	if (temp != nullptr) return temp - buf; else throw("Out of bounds!");

}

int String::indexOf(String s) const{
	const char* temp = strstr(buf, s.buf);
	if (temp != nullptr) return temp - buf; else throw("Out of bounds!");

}

bool String::operator==(String s) const{
	if(strcmp(buf, s.buf) == 0) return true; else return false;	
}

bool String::operator!=(String s) const{
	if(strcmp(buf, s.buf) != 0) return true; else return false;
}

bool String::operator>(String s) const{
	if(strcmp(buf, s.buf) > 0) return true; else return false;
}

bool String::operator<(String s) const{
	if(strcmp(buf, s.buf) < 0) return true; else return false;
}

bool String::operator<=(String s) const{
	if(strcmp(buf, s.buf) <= 0) return true; else return false;
}

bool String::operator>=(String s) const{
	if(strcmp(buf, s.buf) >= 0) return true; else return false;
}

String String::operator+(String s) const{
	char * sup = new char[strlen(buf) + strlen(s.buf) + 1];
	strcpy(sup, buf);
	strcat(sup, s.buf);
	return String(sup);

}

String& String::operator+=(String s){
	char *sup = new char[strlen(buf) + strlen(s.buf) + 1];
	strcpy(sup, buf);
	buf = strcat(sup, s.buf);
	return *this;
}




























void String::print(std::ostream &out) const{
	String temp = String(buf);

	out<<temp;
}

void String::read(std::istream &in){
	String temp = String(MAXLEN);
	in >> temp;
}

String::~String(){
	delete[] buf;
}


const char* String::get_buf() {
	return buf;
}

void String::set_buf(const char *src){
	const char * temp_src = src;
	char * temp_buf = buf;

	while (*temp_src != '\0'){
		*temp_buf = *temp_src;
		++temp_buf; ++temp_src;
	}
	*temp_buf = '\0';
}


int String::strlen(const char *s){
	int counter{0};
	for(; s[counter] != '\0'; ++counter){}
	return counter;
}

char* String::strcpy(char *dest, const char *src){
	
	int counter = 0;

	for (; src[counter] != '\0'; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';
	return dest;

}

//STR DUP STR DUP STR DUP STR DUP STR DUP STRDUP

char* String::strdup(const char *src){
	int src_len = strlen(src);
	char* dup = new char[src_len + 1];
	return strcpy(dup, src);
}

char* String::strncpy(char *dest, const char *src, int n){
	
	int counter = 0;

	for (; src[counter] != '\0' && counter < n; ++counter) dest[counter] = src[counter];
	dest[counter] = '\0';

	return dest;
}



char* String::strcat(char *dest, const char *src){
	int counter{0};
	int dest_counter = strlen(dest);

	for(; src[counter] != '\0'; ++counter, ++dest_counter) dest[dest_counter] = src[counter];
		
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
	int str_len{strlen(str)};
	int counter{0};
	for (; counter < str_len && str[counter] != c; ++counter) {}
	if (str[counter] == c) return &str[counter]; else return nullptr;
}

const char* String::strstr(const char *haystack, const char *needle){
	int hay_len{strlen(haystack)};
	int ned_len{strlen(needle)};
	int counter{0};
	for (; counter < hay_len - ned_len; ++counter){
		if (strcmp(&haystack[counter], needle) == 0){
			return &haystack[counter];
		}
	} return nullptr;
}

String::String(int length){
	buf = {new char [length] {} };
}

std::ostream &operator<<(std::ostream &out, String s){
	s.print(out);
	return out;
}

std::istream &operator>>(std::istream &in, String &s){
	s.read(in);
	return in;
}
