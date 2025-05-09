#include "queue.h"
#include "linked_list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  // struct linked_list ll = { .head = NULL };
  // insert_at_head(&ll, 0);
  // insert_at_head(&ll, 3);
  // insert_at_head(&ll, 2);
  // insert_at_tail(&ll, 4);
  // remove_from_head(&ll);
  // remove_from_head(&ll);
  // remove_from_tail(&ll);
  // remove_from_tail(&ll);
  // printf("here");
  // dump_list(stderr, ll);


  if (argc < 2) {
    fprintf(stderr, "Usage: %s [test file]\n", argv[0]);
    exit(1);
  }

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "Failed to open input file %s\n", argv[1]);
    exit(2);
  }

  int expected;
  fscanf(fp, "%d", &expected);

  struct game_state start;
  start.num_steps = 0;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      int value;
      fscanf(fp, "%d", &value);
      start.tiles[i][j] = value;
      if (value == 0) {
        start.empty_row = i;
        start.empty_col = j;
      }
    }
  }
  fclose(fp);

  int output = number_of_moves(start);
  printf("Outputted number of moves: %d\n", output);
  if (output != expected) {
    fprintf(stderr, "Expected %d moves, got %d\n", expected, output);
    exit(3);
  }

  return 0;
}
