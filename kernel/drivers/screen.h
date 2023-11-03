#ifndef _SCREEN_H_
#define _SCREEN_H_

#define VGA_MEM (char*)0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25
#define VGA_MEM_MAX (MAX_COLS * MAX_ROWS * 2)

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

enum {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LGREY,
    GREY,
    LBLUE,
    LGREEN,
    LCYAN,
    LRED,
    LMAGENTA,
    LBROWN,
    WHITE
};

#define VGA_ATTR(background, foreground) ((background << 4) | foreground)

void clear_screen();

int print_char(char ch, int x, int y, char attr);
int get_offset(int x, int y);
int get_x(int offset);
int get_y(int offset);

int kprint_at(char* str, int x, int y, char attr);
int kprint(char* str, char attr);

int get_cursor_offset();
void set_cursor_offset(int offset);

#endif