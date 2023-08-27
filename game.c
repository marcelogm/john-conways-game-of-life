#include <curses.h>
#include <memory.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define ALIVE 'X'
#define DEAD ' '
#define SPACE 32
#define ESC 27

int count_neighbors(int x, int y, char *buffer, int width, int height) {
  int count = 0;

  for (int i = -1; i <= 1; i++) {
    int nx = x + i;

    if (nx < 0) {
      nx = width - 1;
    }
    if (nx >= width) {
      nx = 0;
    }

    for (int j = -1; j <= 1; j++) {
      int ny = y + j;

      if (ny < 0) {
        ny = height - 1;
      }
      if (ny >= height) {
        ny = 0;
      }
      if (nx == x && ny == y) {
        continue;
      }

      char current = buffer[nx * width + ny];
      if (current == ALIVE) {
        count++;
      }
    }
  }

  return count;
}

void randomize_buffer(char *buffer, char *nbuffer, int width, int height) {
  for (int i = 0; i < width * height; i++) {
    nbuffer[i] = buffer[i] = (rand() % 2 == 0) ? ALIVE : DEAD;
  }
}

int main(int argc, char *argv[]) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  initscr();
  noecho();
  timeout(100);

  int input = 0;
  int row_size = w.ws_row - 1;
  int col_size = w.ws_col;
  int buffer_size = w.ws_col * w.ws_row;

  char *buffer = malloc(buffer_size * sizeof(char));
  char *nbuffer = malloc(buffer_size * sizeof(char));
  randomize_buffer(buffer, nbuffer, row_size, col_size);

  while (input != ESC) {

    input = getch();

    if (input == SPACE) {
      randomize_buffer(buffer, nbuffer, row_size, col_size);
    }

    for (int i = 0; i < row_size; i++) {
      for (int j = 0; j < col_size; j++) {
        int current = i * row_size + j;
        int count = count_neighbors(i, j, buffer, row_size, col_size);

        if (buffer[current] == ALIVE) {
          if (count < 2) {
            nbuffer[current] = DEAD;
          } else if (count == 2 || count == 3) {
            nbuffer[current] = ALIVE;
          } else if (count > 3) {
            nbuffer[current] = DEAD;
          }
        } else {
          nbuffer[current] = count == 3 ? ALIVE : DEAD;
        }
        mvprintw(i, j, "%c", nbuffer[current]);
      }
    }

    mvprintw(w.ws_row - 1, 0, "Press ESC to exit. Press SPACE to randomize.");
    refresh();
    memcpy(buffer, nbuffer, buffer_size * sizeof(char));
  }

  echo();
  endwin();
  free(buffer);
  free(nbuffer);
  return 0;
}
