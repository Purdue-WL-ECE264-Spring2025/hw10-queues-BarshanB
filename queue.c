#include "queue.h"
#include "tile_game.h"

void add_to_queue(struct queue *q, struct game_state st) {
    if (!q) return;
    size_t serialized = convert_to_number(st);
    append_to_end(&q->storage, serialized);
}

struct game_state take_from_queue(struct queue *q) {
    if (!q) return (struct game_state){0};
    size_t val = pop_front(&q->storage);
    return convert_to_state(val);
}

int count_required_moves(struct game_state initial) {
    struct queue q = {0};
    struct linked_list seen = {0};
    
    add_to_queue(&q, initial);
    
    while (q.storage.first) {
        struct game_state current = take_from_queue(&q);
        size_t current_id = convert_to_number(current);
        
        int already_visited = 0;
        for (struct list_node *n = seen.first; n; n = n->next_ptr) {
            if (n->data == current_id) {
                already_visited = 1;
                break;
            }
        }
        
        if (!already_visited) {
            add_to_front(&seen, current_id);
            
            int is_solved = 1;
            int expected = 1;
            for (int i = 0; i < 4 && is_solved; i++) {
                for (int j = 0; j < 4 && is_solved; j++) {
                    if (i == 3 && j == 3) {
                        if (current.tiles[i][j] != 0) {
                            is_solved = 0;
                        }
                    } else {
                        if (current.tiles[i][j] != expected++) {
                            is_solved = 0;
                        }
                    }
                }
            }
            
            if (is_solved) {
                cleanup_list(seen);
                cleanup_list(q.storage);
                return current.step_count;
            }
            
            struct game_state next_state;
            if (current.empty_row > 0) {
                next_state = current;
                slide_down(&next_state);
                add_to_queue(&q, next_state);
            }
            if (current.empty_row < 3) {
                next_state = current;
                slide_up(&next_state);
                add_to_queue(&q, next_state);
            }
            if (current.empty_col > 0) {
                next_state = current;
                slide_right(&next_state);
                add_to_queue(&q, next_state);
            }
            if (current.empty_col < 3) {
                next_state = current;
                slide_left(&next_state);
                add_to_queue(&q, next_state);
            }
        }
    }
    
    cleanup_list(q.storage);
    cleanup_list(seen);
    return -1;
}
