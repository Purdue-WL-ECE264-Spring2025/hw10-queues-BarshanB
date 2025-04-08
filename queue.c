#include "queue.h"
#include "tile_game.h"

void add_to_queue(struct queue *q, struct game_state state) {
    if (!q) return;
    size_t serialized = serialize(state);
    append_node(&q->data, serialized);
}

struct game_state remove_from_queue(struct queue *q) {
    if (!q) return (struct game_state){0};
    size_t val = remove_first(&q->data);
    return deserialize(val);
}

int count_moves(struct game_state initial) {
    struct queue q = {0};
    struct linked_list visited = {0};
    
    add_to_queue(&q, initial);
    
    while (q.data.head) {
        struct game_state current = remove_from_queue(&q);
        size_t current_id = serialize(current);
        
        int skip = 0;
        for (struct list_node *node = visited.head; node; node = node->next) {
            if (node->value == current_id) {
                skip = 1;
                break;
            }
        }
        
        if (!skip) {
            prepend_node(&visited, current_id);
            
            int solved = 1;
            int counter = 1;
            for (int i = 0; i < 4 && solved; i++) {
                for (int j = 0; j < 4 && solved; j++) {
                    if (i == 3 && j == 3) {
                        if (current.tiles[i][j] != 0) {
                            solved = 0;
                        }
                    } else {
                        if (current.tiles[i][j] != counter++) {
                            solved = 0;
                        }
                    }
                }
            }
            
            if (solved) {
                destroy_list(visited);
                destroy_list(q.data);
                return current.num_steps;
            }

            struct game_state new_state;
            if (current.empty_row > 0) {
                new_state = current;
                move_down(&new_state);
                add_to_queue(&q, new_state);
            }
            if (current.empty_row < 3) {
                new_state = current;
                move_up(&new_state);
                add_to_queue(&q, new_state);
            }
            if (current.empty_col > 0) {
                new_state = current;
                move_right(&new_state);
                add_to_queue(&q, new_state);
            }
            if (current.empty_col < 3) {
                new_state = current;
                move_left(&new_state);
                add_to_queue(&q, new_state);
            }
        }
    }
    
    destroy_list(q.data);
    destroy_list(visited);
    return -1;
}
