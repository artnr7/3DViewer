// Resolution 16:9

#define PIXEL_BLOCK_SIZE 100 // HD
#define W 16
#define H 9
#define OBJECTW_W_TO_MENUW_W_RATIO 4

// Main Window ---------------→
#define INIT_AX_MAIN_WINDOW 50
#define INIT_AY_MAIN_WINDOW 50
#define INIT_W_MAIN_WINDOW (W * PIXEL_BLOCK_SIZE)
#define INIT_H_MAIN_WINDOW (H * PIXEL_BLOCK_SIZE)

// Object Widget ----------→
#define INIT_AX_OBJECT_WIDGET (OBJECTW_W_TO_MENUW_W_RATIO * PIXEL_BLOCK_SIZE)
#define INIT_AY_OBJECT_WIDGET 0
#define INIT_W_OBJECT_WIDGET                                                   \
  ((W - OBJECTW_W_TO_MENUW_W_RATIO) * PIXEL_BLOCK_SIZE)
#define INIT_H_OBJECT_WIDGET (H * PIXEL_BLOCK_SIZE)

// Menu Widget ----------→
#define INIT_AX_MENU_WIDGET 0
#define INIT_AY_MENU_WIDGET 0
#define INIT_W_MENU_WIDGET (OBJECTW_W_TO_MENUW_W_RATIO * PIXEL_BLOCK_SIZE)
#define INIT_H_MENU_WIDGET (H * PIXEL_BLOCK_SIZE)
