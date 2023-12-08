#include "containers.h"

NewString::NewString() : length_(1) {
	str_ = new wchar_t[1];
	*str_ = '\0';
}

NewString::NewString(const NewString& copy) {
	str_ = new wchar_t[copy.length_];
	for (length_ = 0; length_ < copy.length_; ++length_)
		str_[length_] = copy.str_[length_];
}

void NewString::append(const wchar_t *str, unsigned long length) {
	NewString buffer(*this);
	if (length > 0) {
		delete[] str_;
		str_ = new wchar_t[length_ += length];
		for (unsigned long i = 0; i < buffer.length_ - 1; ++i)
			str_[i] = buffer.str_[i];
		for (unsigned long i = 0; i < length; ++i)
			str_[buffer.length_ - 1 + i] = str[i];
		str_[length_ - 1] = '\0';
	}
}

// TextContainer::TextContainer(const TextContainer& copy){
// 	storage_ = new Abstract_text*[alloc_];
// 	for (int i = 0; i < size_; ++i)
// 		storage_[i] = copy.storage_[i];
// }

// void TextContainer::push_back(Abstract_text* const &added){
// 	if (size_ == alloc_) {
// 		TextContainer buffer(*this);
// 		delete[] storage_;
// 		storage_ = new Abstract_text*[alloc_ += 5];
// 		for (int i = 0; i < size_; ++i)
// 			storage_[i] = buffer.storage_[i];
// 	}
// 	storage_[size_++] = added;
// }

// Abstract_text*& TextContainer::operator[](int index) const {
// 	if (index < size_ && index >= 0)
// 		return storage_[index];
// 	else
// 		std::cerr << "index out of range\n";
// }