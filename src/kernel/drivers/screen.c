#include "screen.h"

void clear_screen() {
    int offset = 0;
    char* vidmem = VGA_MEM;

    while (offset <= VGA_MEM_MAX) {
        vidmem[offset + 0] = ' ';
        vidmem[offset + 1] = VGA_ATTR(BLACK, GREY);
        offset += 2;
    }
    set_cursor_offset(0);
}

int print_char(char ch, int x, int y, char attr) {
    unsigned char *vidmem = VGA_MEM;

    if (x >= MAX_COLS || y >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = VGA_ATTR(BLACK, RED);
        return get_offset(x, y);
    }

    int offset;
    if (x >= 0 && y >= 0) offset = get_offset(x, y);
    else offset = get_cursor_offset();

    if (ch == '\n') {
        y = get_y(offset);
        offset = get_offset(0, y + 1);
    } else {
        vidmem[offset + 0] = ch;
        vidmem[offset + 1] = attr;
        offset += 2;
    }

    if(offset >= VGA_MEM_MAX) {
        for(int i = 1; i < MAX_ROWS; i++)
            memcpy(get_offset(0, i - 1) + VGA_MEM, get_offset(0, i) + VGA_MEM, MAX_COLS * 2);

        char* bottomline = get_offset(0, MAX_ROWS - 1) + VGA_MEM;
        for(int i = 0; i < MAX_COLS * 2; i++)
            bottomline[i] = 0;
        
        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_offset(int x, int y) {
    return (x + y * MAX_COLS) * 2;
}

int get_x(int offset) {
    return (offset / 2) % MAX_COLS;
}

int get_y(int offset) {
    return (offset / 2) / MAX_COLS;
}

int kprint_at(char* str, int x, int y, char attr) {
    int offset;
    if (x >= 0 && y >= 0)
        offset = get_offset(x, y);
    else {
        offset = get_cursor_offset();
        y = get_y(offset);
        x = get_x(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (str[i] != 0) {
        offset = print_char(str[i++], x, y, attr);
        /* Compute row/col for next iteration */
        y = get_y(offset);
        x = get_x(offset);
    }
    return offset;
}

int kprint(char* str, char attr) {
    return kprint_at(str, -1, -1, attr);
}

int get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}
