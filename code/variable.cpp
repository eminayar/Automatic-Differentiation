#include "variable.h"

Node::~Node() {}

Variable::Variable() {
    this->value=0.0;
    this->derivative=0.0;
    this->from=NULL;
}

Variable::Variable(int _id, string _name, double _value) {
    this->id=_id;
    this->name=_name;
    this->value=_value;
}

void Variable::setFrom(Function *_from) {
    this->from=_from;
}

void Variable::addTo(Function *_to) {
    this->to.push_back( _to );
}

Variable::~Variable() {

}