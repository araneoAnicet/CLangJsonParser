#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct json_string;
struct json_number;
struct json_boolean;
struct json_array;
struct json_object;
enum json_types;
union json_value;
struct json_key_value_pair;
struct json;
struct json_char_stack;
struct json_char_stack_node;


struct json_string {
    const char* value;
    int length;
};

struct json_number {
    int value;
};

struct json_boolean {
    bool value;
};

enum json_types {
    string,
    number,
    null,
    boolean,
    array,
    object
};

union json_value {
    struct json_string string;
    struct json_number number;
    struct json_boolean boolean;
    struct json_array* array;
    struct json_object* object;
};

struct json_key_value_pair {
    enum json_types type;
    union json_value value;
    const char* key;
    int key_length;
};

struct json_object {
    struct json_key_value_pair* key_value_pairs;
    int number_of_key_value_pairs;
};

struct json_array {
    struct json_object* objects;
    int length;
};

struct json_char_stack_node {
    char value;
    struct json_char_stack_node* next;
};

struct json_char_stack {
    struct json_char_stack_node root;
    struct json_char_stack_node* top;
    int length;
};

struct json {
    struct json_object* root_object;
    struct json_char_stack char_stack;
    
};

int push_json_stack(struct json* json, char element);
int serialize_json(struct json* json);
int serialize_object(struct json* json, struct json_object* object);
int serialize_string(struct json* json, struct json_key_value_pair* pair);
int serialize_number(struct json* json, struct json_key_value_pair* pair);
int serialize_null(struct json*);
int serialize_array(struct json* json, struct json_array* array);
int serialize_boolean(struct json* json, struct json_key_value_pair* pair);
int save_json(struct json* json, FILE* fd);
