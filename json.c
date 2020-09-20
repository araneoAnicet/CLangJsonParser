#include "json.h"

int push_json_stack(struct json* json, char element) {
    struct json_char_stack_node* node = (struct json_char_stack_node*) malloc(sizeof(struct json_char_stack_node));
    if (node == NULL) {
        return -1;
    }
    node->value = element;
    json->char_stack.top->next = node;
    json->char_stack.top = node;
    json->char_stack.length++;
    return 0;
}

int serialize_string(struct json* json, struct json_key_value_pair* pair) {
    int i;
    CHECK(push_json_stack(json, '\"'));

    for (i = 0; i < pair->key_length; i++) {
        CHECK(push_json_stack(json, pair->key[i]));
    }
    CHECK(push_json_stack(json, '\"'));
    CHECK(push_json_stack(json, ':'));

    CHECK(push_json_stack(json, '\"'));

    for (i = 0; i < pair->value.string.length; i++) {
        CHECK(push_json_stack(json, pair->value.string.value[i]));
    }
    CHECK(push_json_stack(json, '\"'));
    return 0;
}

int serialize_object(struct json* json, struct json_object* object) {
    int pair_index;
    CHECK(push_json_stack(json, '{'));

    for (pair_index = 0; pair_index < object->number_of_key_value_pairs - 1; pair_index++) {
        if (object->key_value_pairs[pair_index].type == string) {
            CHECK(serialize_string(json, &(object->key_value_pairs[pair_index])));
        }
        CHECK(push_json_stack(json, ','));
    }

    if (object->key_value_pairs[object->number_of_key_value_pairs - 1].type == string) {
        CHECK(serialize_string(json, &(object->key_value_pairs[object->number_of_key_value_pairs - 1])));
    }

    CHECK(push_json_stack(json, '}'));
    return 0;
}

int save_json(struct json* json, FILE* fd) {
    int i;
    struct json_char_stack_node* temp_node = json->char_stack.root.next;
    for (i = 0; i < json->char_stack.length - 1; i++) {
        CHECK(fprintf(fd, "%c", temp_node->value));
        CHECK(printf("%c\n", temp_node->value));
        temp_node = temp_node->next;
    }
    return 0;
}

int serialize_json(struct json* json) {
    CHECK(serialize_object(json, json->root_object));
    return 0;
}
