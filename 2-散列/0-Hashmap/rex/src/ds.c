/**
 * @brief create a int stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
#include "ds.h"

Node* create_node_int(int value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=inte;
	sn->element.i=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_float(float value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=floate;
	sn->element.f=value;
	return sn;
}

/**
 * @brief create a double stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_double(double value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=doublee;
	sn->element.lf=value;
	return sn;
}

/**
 * @brief create a string stack node
 * @details [long description]
 * 
 * @param value [description]
 * @return [description]
 */
Node* create_node_string(const char* value){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=stringe;
	sn->element.s=(char*)value;
	return sn;
}

/**
 * create a struct varible node
 * @param  struct_content the pointer of the struct
 * @return                [description]
 */
Node* create_node_struct(void* struct_content){
	Node* sn=(Node*)malloc(sizeof(Node));
	sn->type=structe;
	sn->element.st=struct_content;
	return sn;
}