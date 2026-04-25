// Resolution 16:9
#ifndef CONFIG_H_
#define CONFIG_H_

#include <qtypes.h>

#include <cstdint>

inline constexpr uint16_t PIXEL_BLOCK_SZ = 110;  // HD

inline constexpr uint16_t W = 16;
inline constexpr uint16_t H = 9;
inline constexpr uint16_t OBJW_W_TO_MENUW_W_RATIO = 4;

// Main Window ---------------→
inline constexpr uint16_t INIT_AX_MAIN_WIN = 0;
inline constexpr uint16_t INIT_AY_MAIN_WIN = 0;
inline constexpr uint16_t INIT_W_MAIN_WIN = W * PIXEL_BLOCK_SZ;
inline constexpr uint16_t INIT_H_MAIN_WIN = H * PIXEL_BLOCK_SZ;

// Object Widget ----------→
inline constexpr uint16_t INIT_AX_OBJECT_WIDGET =
    OBJW_W_TO_MENUW_W_RATIO * PIXEL_BLOCK_SZ;
inline constexpr uint16_t INIT_AY_OBJECT_WID = 0;
inline constexpr uint16_t INIT_W_OBJECT_WID =
    (W - OBJW_W_TO_MENUW_W_RATIO) * PIXEL_BLOCK_SZ;
inline constexpr uint16_t INIT_H_OBJ_WID = H * PIXEL_BLOCK_SZ;

// Menu Widget ----------→
inline constexpr uint16_t INIT_AX_MENU_WID = 0;
inline constexpr uint16_t INIT_AY_MENU_WID = 0;
inline constexpr uint16_t INIT_W_MENU_WID =
    OBJW_W_TO_MENUW_W_RATIO * PIXEL_BLOCK_SZ;
inline constexpr uint16_t INIT_H_MENU_WID = H * PIXEL_BLOCK_SZ;

#endif
