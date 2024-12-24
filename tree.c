#include <stdio.h>
#include <stdlib.h>                    /* rand */
#include <time.h>                      /* time */

#include <conio.h>
#include <graph.h>

int main()
{
    char tree[] = { 0xb0, 0xb1, 0xb2,  /* tree */
        0xf8, 0xf9, 0xfa,              /* dots */
        0xfe /* lights */
    };
    char t[1];
    int row, col;
    int i, c;

    if (_setvideomode(_TEXTC80) == 0) {
        puts("cannot set video mode");
        return 1;
    }

    srand(time(NULL));

    /* draw a trunk */

    _settextcolor(6);                  /* brown */

    for (row = 20; row < 23; row++) {
        _settextposition(row, 40 - 1);
        _outmem(tree, 3);
    }

    /* draw a tree */

    _setbkcolor(2);                    /* green background */

    for (row = 0; row < 20; row++) {
        _settextposition(1 + row, 40 - row);

        for (col = 40 - row; col <= 40 + row; col++) {
            i = rand() % 7;            /* 0 to 6 */

            if (i < 3) {               /* 0, 1, 2 (tree) */
                c = ((rand() & 1) ? 0 : 10);    /* black or br green */
            }
            else {
                c = 9 + (rand() % 7);  /* 9 to 15 */
            }

            _settextcolor(c);
            t[0] = tree[i];
            _outmem(t, 1);
        }
    }

    /* draw a star */

    t[0] = '*';
    _settextcolor(14);                 /* br yellow */
    _settextposition(1, 40);
    _outmem(t, 1);

    /* print a message */

    _settextcolor(15);                 /* br white */
    _setbkcolor(0);                    /* black */
    _settextposition(25, 1);
    _outtext("Merry Christmas!");

    /* done */

    if (getch() == 0) {
        getch();
    }

    _setvideomode(_DEFAULTMODE);

    return 0;
}
