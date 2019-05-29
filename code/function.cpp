#include "function.h"
#include <cmath>

Function::Function() {
    this->id=0;
    this->name="";
}

Function::Function(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Function::setOutput(Variable *_output) {
    this->output=_output;
}

void Function::addInput(Variable *input) {
    this->inputs.push_back( input );
}

Function::~Function() {

}

Multiplication::Multiplication(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Multiplication::doForward() {
    Variable *first = this->inputs[0];
    Variable *second = this->inputs[1];
    this->output->value=first->value*second->value;
}

void Multiplication::doBackward() {
    this->inputs[0]->derivative+=this->inputs[1]->value*this->output->derivative;
    this->inputs[1]->derivative+=this->inputs[0]->value*this->output->derivative;
}

Sine::Sine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Sine::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=sin( var->value );
}

void Sine::doBackward() {
    this->inputs[0]->derivative+=cos(this->inputs[0]->value)*this->output->derivative;
}

Cosine::Cosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Cosine::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=cos( var->value );
}

void Cosine::doBackward() {
    this->inputs[0]->derivative-=sin(this->inputs[0]->value)*this->output->derivative;
}

Identity::Identity(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Identity::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=var->value;
}

void Identity::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
}

Addition::Addition(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Addition::doForward() {
    Variable *first = this->inputs[0];
    Variable *second = this->inputs[1];
    this->output->value=first->value+second->value;
}

void Addition::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
    this->inputs[1]->derivative+=this->output->derivative;
}

Subtraction::Subtraction(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Subtraction::doForward() {
    Variable *first = this->inputs[0];
    Variable *second = this->inputs[1];
    this->output->value=first->value-second->value;
}

void Subtraction::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative;
    this->inputs[1]->derivative-=this->output->derivative;
}

Division::Division(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Division::doForward() {
    Variable *first = this->inputs[0];
    Variable *second = this->inputs[1];
    this->output->value=first->value/second->value;
}

void Division::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/this->inputs[1]->value;
    this->inputs[1]->derivative-=this->output->derivative*this->inputs[0]->value/(this->inputs[1]->value*this->inputs[1]->value);
}

Tangent::Tangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Tangent::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=tan( var->value );
}

void Tangent::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/(cos(this->inputs[0]->value)*cos(this->inputs[0]->value));
}

ArcCosine::ArcCosine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void ArcCosine::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=acos( var->value );
}

void ArcCosine::doBackward() {
    this->inputs[0]->derivative-=this->output->derivative/sqrt(max(1-this->inputs[0]->value*this->inputs[0]->value,1e-15));
}

ArcSine::ArcSine(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void ArcSine::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=asin( var->value );
}

void ArcSine::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/sqrt(max(1-this->inputs[0]->value*this->inputs[0]->value,1e-15));
}

ArcTangent::ArcTangent(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void ArcTangent::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=atan( var->value );
}

void ArcTangent::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/(1+this->inputs[0]->value*this->inputs[0]->value);
}

Exponential::Exponential(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Exponential::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=exp( var->value );
}

void Exponential::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative*exp( this->inputs[0]->value );
}

Log::Log(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Log::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=log( var->value );
}

void Log::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/this->inputs[0]->value;
}

Log10::Log10(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Log10::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=log10( var->value );
}

void Log10::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative/(this->inputs[0]->value*log(10));
}

Power::Power(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Power::doForward() {
    Variable *first = this->inputs[0];
    Variable *second = this->inputs[1];
    this->output->value=pow(first->value,second->value);
}

void Power::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative*this->inputs[1]->value*pow(this->inputs[0]->value,this->inputs[1]->value-1);
    this->inputs[1]->derivative+=this->output->derivative*this->output->value*log(this->inputs[0]->value);
}

Sqrt::Sqrt(int _id, string _name) {
    this->id=_id;
    this->name=_name;
}

void Sqrt::doForward() {
    Variable *var = this->inputs[0];
    this->output->value=sqrt( var->value );
}


void Sqrt::doBackward() {
    this->inputs[0]->derivative+=this->output->derivative*1/(2*this->output->value);
}