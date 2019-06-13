#pragma once/*
#define N_DISPLAY_W 700
#define N_DISPLAY_H 700
#define GRAPH_RADIUS ((N_DISPLAY_W/2)-30)

#define C_DISPLAY_W N_DISPLAY_W
#define C_DISPLAY_H 200

#define DISPLAY_W N_DISPLAY_W
#define DISPLAY_H (N_DISPLAY_H + C_DISPLAY_H)

#define DISPLAY_H	700
#define DISPLAY_W	700
#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 15
#define BLOCK_IMAGE "bloque.png"
#define ARROW_RIGHT_IMAGE "Right.png"
#define ARROW_LEFT_IMAGE "Left.png"
#define ARROW_H 25
#define ARROW_W 50
#define SPACE_BTW 30
#define IMAGE_W ((DISPLAY_W/3)-SPACE_BTW)
#define IMAGE_H ((DISPLAY_H/3)-SPACE_BTW)
#define DIF 10

#define RADIO TEXTSIZE*2
#define NODE_DIF_X ((RADIO*5)+10)
#define NODE_DIF_Y 0

#define FIRST_COL(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_W)))
#define SECOND_COL(x) (((x) >= ((SPACE_BTW*2)+IMAGE_W)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_W*2))))
#define THIRD_COL(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_W*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_W*3))))

#define FIRST_ROW(x) (((x)>=SPACE_BTW) && ((x) <= (SPACE_BTW+IMAGE_H)))
#define SECOND_ROW(x) (((x) >= ((SPACE_BTW*2)+IMAGE_H)) && ((x) <= ((SPACE_BTW*2)+(IMAGE_H*2))))
#define THIRD_ROW(x) (((x) >= ((SPACE_BTW*3)+(IMAGE_H*2))) && ((x) <= ((SPACE_BTW*3)+(IMAGE_H*3))))

#define B_R_CORNER(x,y,dx,dy) (((x)>=(DISPLAY_W-(dx))) && ((x)<=DISPLAY_W)) && (((y)>=(DISPLAY_H-(dy))) && ((y)<=DISPLAY_H))
#define B_L_CORNER(x,y,dx,dy) (((x)<=(dx)) && ((y)<=(dy)))

#define ITEM_1(x,y) (FIRST_ROW(y) && FIRST_COL(x))
#define ITEM_2(x,y) (FIRST_ROW(y) && SECOND_COL(x))
#define ITEM_3(x,y) (FIRST_ROW(y) && THIRD_COL(x))
#define ITEM_4(x,y) (SECOND_ROW(y) && FIRST_COL(x))
#define ITEM_5(x,y) (SECOND_ROW(y) && SECOND_COL(x))
#define ITEM_6(x,y) (SECOND_ROW(y) && THIRD_COL(x))
#define ITEM_7(x,y) (THIRD_ROW(y) && FIRST_COL(x))
#define ITEM_8(x,y) (THIRD_ROW(y) && SECOND_COL(x))
#define ITEM_9(x,y) (THIRD_ROW(y) && THIRD_COL(x))

*/