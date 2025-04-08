#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    size_t encoded = serialize(state);
    insert_at_tail(&q->data, encoded);
}

struct game_state dequeue(struct queue *q) {
    size_t decoded_val = remove_from_head(&q->data);
    return deserialize(decoded_val);
}

int number_of_moves(struct game_state start) {
    struct queue q = { .data.head = NULL };
    struct linked_list visited = { .head = NULL };

    enqueue(&q, start);

    while (q.data.head) {
        struct game_state current = dequeue(&q);
        size_t current_id = serialize(current);

        int already_seen = 0;
        for (struct list_node *node = visited.head; node; node = node->next) {
            if (node->value == current_id) {
                already_seen = 1;
                break;
            }
        }

        if (!already_seen) {
            insert_at_head(&visited, current_id);

            int solved = 1;
            int val = 1;
            for (int r = 0; r < 4 && solved; r++) {
                for (int c = 0; c < 4 && solved; c++) {
                    if (r == 3 && c == 3) {
                        if (current.tiles[r][c] != 0) solved = 0;
                    } else if (current.tiles[r][c] != val++) {
                        solved = 0;
                    }
                }
            }

            if (solved) {
                free_list(visited);
                free_list(q.data);
                return current.num_steps;
            }

            struct game_state new_state;

            if (current.empty_row > 0) {
                new_state = current;
                move_down(&new_state);
                enqueue(&q, new_state);
            }

            if (current.empty_row < 3) {
                new_state = current;
                move_up(&new_state);
                enqueue(&q, new_state);
            }

            if (current.empty_col > 0) {
                new_state = current;
                move_right(&new_state);
                enqueue(&q, new_state);
            }

            if (current.empty_col < 3) {
                new_state = current;
                move_left(&new_state);
                enqueue(&q, new_state);
            }
        }
    }

    free_list(q.data);
    free_list(visited);
    return -1;
}
