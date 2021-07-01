#include "Page.h"

int Page::getId() const {
    return this->id;
}

void Page::setId(int id) {
    this->id = id;
}

int Page::getCount() const {
    return count;
}

void Page::inc(){
    count++;
}

void Page::setCount(int count) {
    this->count = count;
}

Page::Page(int id) {
    this->id = id;
}

Page::~Page() {

}
