#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue* q, struct game_state state) {
    insert_at_head(&q->data, serialize(state));
}

struct game_state dequeue(struct queue* q) {
    return deserialize(remove_from_tail(&q->data));
}

bool isSolved(struct game_state state) {
    if (state.empty_col != 3 && state.empty_row != 3) {
        return false;
    }
    for (int i = 1; i <= 15; i++) {
        if (state.tiles[(i - 1) / 4][(i - 1) % 4] != i) {
            return false;
        }
    }
    return true;
}

uint64_t encodeTiles(struct game_state state) {
    uint64_t out = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out *= 16;
            out += state.tiles[i][j];
        }
    }
    return out;
}

void enqueueTiles(struct queue* q, struct game_state state) {
    insert_at_head(&q->data, encodeTiles(state));
}

bool containsTiles(struct queue* q, struct game_state state) {
    struct list_node* n = q->data.head;
    uint64_t stateEnc = encodeTiles(state);
    while (n != NULL) {
        if (n->value == stateEnc) {
            return true;
        }
        n = n->next;
    }
    return false;
}


int number_of_moves(struct game_state start) {
    struct linked_list llNewStates = { .head = NULL };
    struct queue newStates = { .data = llNewStates };

    struct linked_list llVisited = { .head = NULL };
    struct queue visited = { .data = llVisited };

    enqueue(&newStates, start);
    enqueueTiles(&visited, start);
    int counter = 0;
    while (newStates.data.head != NULL) {
        counter++;
        struct game_state state = dequeue(&newStates);
        // printf("%8d depth: %d\n", counter, state.num_steps);
        if (isSolved(state)) {
            free_list(newStates.data);
            free_list(visited.data);
            return state.num_steps;
        }
        if (state.num_steps > 12) {
            free_list(newStates.data);
            free_list(visited.data);
            return 12;
        }
        for (int i = 0; i < 4; i++) {
            struct game_state nextState = state;
            switch (i) {
            case 0:
                move_up(&nextState);
                break;
            case 1:
                move_down(&nextState);
                break;
            case 2:
                move_left(&nextState);
                break;
            case 3:
                move_right(&nextState);
                break;
            default:
                break;
            }

            if (containsTiles(&visited, nextState)) {
                continue;
            }
            enqueue(&newStates, nextState);
            enqueueTiles(&visited, nextState);
        }
    }
    free_list(newStates.data);
    free_list(visited.data);
    return -1;
}
