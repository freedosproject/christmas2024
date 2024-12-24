/* simulate a fire */

#include <stdio.h>
#include <stdlib.h>                    /* rand */
#include <time.h>                      /* time */

#include <conio.h>
#include <graph.h>

#include <i86.h>                       /* delay */

void flame(int col)
{
    char str[4];                /* 0, 1, 2, 3 */
    char flame[4] = { 0xb0, 0xb1, 0xb2, 0xdb };
    int i, n;

    /* fill the string with spaces + flame */

    n = rand() % 4;                    /* 0, 1, 2, 3 */

    for (i = 0; i < n; i++) {
        str[i] = ' ';
    }

    for (n = 0; i < 4; i++) {
        str[i] = flame[n++];
    }

    /* draw */

    _settextwindow(10, col, 14, col);  /* 0, 1, 2, 3, 4 .. one more than str */
    _settextposition(1, 1);

    if (rand() & 1) {
        _settextcolor(6);              /* brown = orange */
    }
    else {
        _settextcolor(14);             /* br yellow */
    }

    _outmem(str, 4);
}

int main()
{
    int col;

    /* set display */

    if (_setvideomode(_TEXTC80) == 0) {
        puts("failed to set the video mode");
        return 1;
    }

    _displaycursor(_GCURSOROFF);

    srand(time(NULL));

    /* draw a rug */

    _setbkcolor(2);                    /* iRGB = 0010 = 2 */
    _settextwindow(14, 29, 20, 50);    /* values are in row,col */
    _clearscreen(_GWINDOW);            /* just the window with bk color */

    /* chimney */

    _setbkcolor(4);                    /* iRGB = 0100 = 4 */
    _settextwindow(1, 30, 14, 49);     /* 1 'narrower' than rug */
    _clearscreen(_GWINDOW);

    /* fireplace */

    _settextwindow(9, 28, 14, 51);     /* 1 'wider' than rug */
    _clearscreen(_GWINDOW);

    /* draw some flames */

    _setbkcolor(0);                    /* black */

    do {
        for (col = 30; col < 50; col++) {
            flame(col);
        }
        delay(100);                    /* 1/10 second */
    } while (kbhit() == 0);

    /* exit */

    if (getch() == 0) {
        getch();                       /* if 0, it's an "extended" key like F1, F2, .. */
    }

    _setvideomode(_DEFAULTMODE);

    return 0;
}
