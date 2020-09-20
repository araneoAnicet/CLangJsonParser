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
    if (push_json_stack(json, '\"') == -1) {
        return -1;
    }

    for (i = 0; i < pair->key_length; i++) {
        if (push_json_stack(json, pair->key[i]) == -1) {
            return -1;
        }
    }
    if (push_json_stack(json, '\"') == -1) {
        return -1;
    }

    if (push_json_stack(json, ':') == -1) {
        return -1;
    }


    if (push_json_stack(json, '\"') == -1) {
        return -1;
    }
    for (i = 0; i < pair->value.string.length; i++) {
        if (push_json_stack(json, pair->value.string.value[i]) == -1) {
            return -1;
        }
    }
    if (push_json_stack(json, '\"') == -1) {
        return -1;
    }
    return 0;
}

int serialize_object(struct json* json, struct json_object* object) {
    int pair_index;
    if (push_json_stack(json, '{') == -1) {
        return -1;
    }

    for (pair_index = 0; pair_index < object->number_of_key_value_pairs - 1; pair_index++) {
        if (object->key_value_pairs[pair_index].type == string) {
            if (serialize_string(json, &(object->key_value_pairs[pair_index])) == -1) {
                return -1;
            }
        }
        push_json_stack(json, ',');
    }

    if (object->key_value_pairs[object->number_of_key_value_pairs - 1].type == string) {
        if (serialize_string(json, &(object->key_value_pairs[object->number_of_key_value_pairs - 1])) == -1) {
            return -1;
        }
    }

    if (push_json_stack(json, '}') == -1) {
        return -1;
    }
    return 0;
}

int save_json(struct json* json, FILE* fd) {
    int i;
    struct json_char_stack_node* temp_node = json->char_stack.root.next;
    for (i = 0; i < json->char_stack.length - 1; i++) {
        fprintf(fd, "%c", temp_node->value);
        printf("%c\n", temp_node->value);
        temp_node = temp_node->next;
    }
    return 0;
}

int serialize_json(struct json* json) {
    if (serialize_object(json, json->root_object) == -1) {
        return -1;
    }
    return 0;
}
