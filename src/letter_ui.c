#include "global.h"
#include "ui_menu.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "constants/letters.h"

/*
 * 
 */

//==========DEFINES==========//
struct LetterResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u8 pageNumber;
    u8 letter;
};

enum WindowIds
{
    WINDOW_1,
};

static const u8 *const sLetters[14][10] = 
{
    [LETTER_RIDDLE_ENCODED] = 
    {
        gText_LetterRiddleEncodedPageOne,
    },

    [LETTER_RIDDLE_DECODED] =
    {
        gText_LetterRiddleDecodedPageOne,
        gText_LetterRiddleDecodedPageTwo,
    },

    [LETTER_MEL_MIKE_ENCODED] =
    {
        gText_LetterMelMikeEncodedPageOne,
    },

    [LETTER_MEL_MIKE_DECODED] =
    {
        gText_LetterMelMikeDecodedPageOne,
        gText_LetterMelMikeDecodedPageTwo,
        gText_LetterMelMikeDecodedPageThree,
        gText_LetterMelMikeDecodedPageFour,
        gText_LetterMelMikeDecodedPageFive,
        gText_LetterMelMikeDecodedPageSix,
    },

    [LETTER_TY_ALEX_ENCODED] =
    {
        gText_LetterTyAlexEncodedPageOne,
        gText_LetterTyAlexEncodedPageTwo,
    },

    [LETTER_TY_ALEX_DECODED] =
    {
        gText_LetterTyAlexDecodedPageOne,
        gText_LetterTyAlexDecodedPageTwo,
        gText_LetterTyAlexDecodedPageThree,
    },

    [LETTER_MARY_ARIC_ENCODED] =
    {
        gText_LetterMaryAricEncodedPageOne,
        gText_LetterMaryAricEncodedPageTwo,
    },

    [LETTER_MARY_ARIC_DECODED] =
    {
        gText_LetterMaryAricDecodedPageOne,
        gText_LetterMaryAricDecodedPageTwo,
        gText_LetterMaryAricDecodedPageThree,
        gText_LetterMaryAricDecodedPageFour,
        gText_LetterMaryAricDecodedPageFive,
    },

    [LETTER_MOM_DAD_ENCODED] =
    {
        gText_LetterMomDadEncodedPageOne,
    },

    [LETTER_MOM_DAD_DECODED] =
    {
        gText_LetterMomDadDecodedPageOne,
        gText_LetterMomDadDecodedPageTwo,
        gText_LetterMomDadDecodedPageThree,
        gText_LetterMomDadDecodedPageFour,
        gText_LetterMomDadDecodedPageFive,
        gText_LetterMomDadDecodedPageSix,
        gText_LetterMomDadDecodedPageSeven,
        gText_LetterMomDadDecodedPageEight,
        gText_LetterMomDadDecodedPageNine,
        gText_LetterMomDadDecodedPageTen,
    },

    [LETTER_BRO_SIS_ENCODED] =
    {
        gText_LetterBroSisEncodedPageOne,
    },

    [LETTER_BRO_SIS_DECODED] =
    {
        gText_LetterBroSisDecodedPageOne,
        gText_LetterBroSisDecodedPageTwo,
        gText_LetterBroSisDecodedPageThree,
        gText_LetterBroSisDecodedPageFour,
        gText_LetterBroSisDecodedPageFive,
        gText_LetterBroSisDecodedPageSix,
        gText_LetterBroSisDecodedPageSeven,
    },

    [LETTER_CHRIS_ENCODED] =
    {
        gText_LetterChrisEncodedPageOne,
    },

    [LETTER_CHRIS_DECODED] =
    {
        gText_LetterChrisDecodedPageOne,
        gText_LetterChrisDecodedPageTwo,
        gText_LetterChrisDecodedPageThree,
        gText_LetterChrisDecodedPageFour,
        gText_LetterChrisDecodedPageFive,
        gText_LetterChrisDecodedPageSix,
    },
};

static const u8 sLettersMaxPages[14] =
{
    [LETTER_RIDDLE_ENCODED] = 1,
    [LETTER_RIDDLE_DECODED] = 2,
    [LETTER_MEL_MIKE_ENCODED] = 1,
    [LETTER_MEL_MIKE_DECODED] = 6,
    [LETTER_TY_ALEX_ENCODED] = 2,
    [LETTER_TY_ALEX_DECODED] = 3,
    [LETTER_MARY_ARIC_ENCODED] = 2,
    [LETTER_MARY_ARIC_DECODED] = 5,
    [LETTER_MOM_DAD_ENCODED] = 1,
    [LETTER_MOM_DAD_DECODED] = 10,
    [LETTER_BRO_SIS_ENCODED] = 1,
    [LETTER_BRO_SIS_DECODED] = 7,
    [LETTER_CHRIS_ENCODED] = 1,
    [LETTER_CHRIS_DECODED] = 6,
};


//==========EWRAM==========//
static EWRAM_DATA struct LetterResources *sLetterDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

//==========STATIC=DEFINES==========//
static void Menu_RunSetup(void);
static bool8 Menu_DoGfxSetup(void);
static bool8 Menu_InitBgs(void);
static void Menu_FadeAndBail(void);
static bool8 Menu_LoadGraphics(void);
static void Menu_InitWindows(void);
static void PrintToWindow(u8 windowId, u8 colorIdx);
static void Task_MenuWaitFadeIn(u8 taskId);
static void Task_LetterMain(u8 taskId);

//==========CONST=DATA==========//
static const struct BgTemplate sMenuBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    }, 
    {
        .bg = 1,    // this bg loads the UI tilemap
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    },
    {
        .bg = 2,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .priority = 0
    }
};

static const struct WindowTemplate sMenuWindowTemplates[] = 
{
    [WINDOW_1] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 2,   // position from left (per 8 pixels)
        .tilemapTop = 4,    // position from top (per 8 pixels)
        .width = 25,        // width (per 8 pixels) -- how big the box is before text gets cut off
        .height = 15,        // height (per 8 pixels) -- ^^
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    },
};

static const u32 sMenuTiles[] = INCBIN_U32("graphics/mail/dream/tiles.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/mail/dream/map.bin.lz");
static const u16 sMenuPalette[] = INCBIN_U16("graphics/mail/dream/palette.gbapal");

enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};
static const u8 sMenuWindowFontColors[][3] = 
{
    [FONT_BLACK]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,  TEXT_COLOR_DARK_GRAY},
    [FONT_RED]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

//==========FUNCTIONS==========//

// This is our main initialization function if you want to call the menu from elsewhere
void LetterUI_Init(MainCallback callback, u8 letter)
{
    if ((sLetterDataPtr = AllocZeroed(sizeof(struct LetterResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    // initialize stuff
    sLetterDataPtr->gfxLoadState = 0;
    sLetterDataPtr->savedCallback = callback;
    sLetterDataPtr->pageNumber = 0;
    sLetterDataPtr->letter = letter;

    SetMainCallback2(Menu_RunSetup);
}

static void SetLettersReadVar(u16 flag)
{
    u16 lettersRead;
    if (!FlagGet(flag))
    {
        FlagSet(flag);
        lettersRead = VarGet(VAR_LETTERS_READ);
        lettersRead++;
        VarSet(VAR_LETTERS_READ, lettersRead);
    }
}

static void Menu_RunSetup(void)
{
    // track which letters are read
    switch (sLetterDataPtr->letter)
    {
        case LETTER_RIDDLE_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_1);
            break;
        case LETTER_MEL_MIKE_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_2);
            break;
        case LETTER_TY_ALEX_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_3);
            break;
        case LETTER_MARY_ARIC_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_4);
            break;
        case LETTER_MOM_DAD_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_5);
            break;
        case LETTER_BRO_SIS_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_6);
            break;
        case LETTER_CHRIS_DECODED:
            SetLettersReadVar(FLAG_READ_LETTER_7);
            break;
    }

    while (1)
    {
        if (Menu_DoGfxSetup() == TRUE)
            break;
    }
}

static void Menu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void Menu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 Menu_DoGfxSetup(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (Menu_InitBgs())
        {
            sLetterDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            Menu_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (Menu_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        LoadMessageBoxAndBorderGfx();
        Menu_InitWindows();
        gMain.state++;
        break;
    case 5:
        PrintToWindow(WINDOW_1, FONT_WHITE);
        taskId = CreateTask(Task_MenuWaitFadeIn, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(Menu_VBlankCB);
        SetMainCallback2(Menu_MainCB);
        return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void Menu_FreeResources(void)
{
    try_free(sLetterDataPtr);
    try_free(sBg1TilemapBuffer);
    FreeAllWindowBuffers();
}


static void Task_MenuWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sLetterDataPtr->savedCallback);
        Menu_FreeResources();
        DestroyTask(taskId);
    }
}

static void Menu_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_MenuWaitFadeAndBail, 0);
    SetVBlankCallback(Menu_VBlankCB);
    SetMainCallback2(Menu_MainCB);
}

static bool8 Menu_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;

    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sMenuBgTemplates, NELEMS(sMenuBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 Menu_LoadGraphics(void)
{
    switch (sLetterDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sMenuTiles, 0, 0, 0);
        sLetterDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sMenuTilemap, sBg1TilemapBuffer);
            sLetterDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sMenuPalette, 0, 32);
        sLetterDataPtr->gfxLoadState++;
        break;
    default:
        sLetterDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void Menu_InitWindows(void)
{
    u32 i;

    InitWindows(sMenuWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);

    FillWindowPixelBuffer(WINDOW_1, 0);
    LoadUserWindowBorderGfx(WINDOW_1, 720, 14 * 16);
    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);

    ScheduleBgCopyTilemapToVram(2);
}

static void PrintToWindow(u8 windowId, u8 colorIdx)
{
    const u8 pageNum = sLetterDataPtr->pageNumber;
    const u8 letter = sLetterDataPtr->letter;
    const u8 *str = sLetters[letter][pageNum];
    u8 x = 1;
    u8 y = 1;

    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(windowId, 1, x, y, 0, 0, sMenuWindowFontColors[colorIdx], 0xFF, str);
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, 3);
}

static void Task_MenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_LetterMain;
}

static void Task_MenuTurnOff(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        SetMainCallback2(sLetterDataPtr->savedCallback);
        Menu_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_UINextPage(u8 taskId)
{
    if (sLetterDataPtr->pageNumber < (sLettersMaxPages[sLetterDataPtr->letter] - 1))
    {
        sLetterDataPtr->pageNumber++;
        PrintToWindow(WINDOW_1, FONT_WHITE);
    }
    gTasks[taskId].func = Task_LetterMain;
}

static void Task_UIPreviousPage(u8 taskId)
{
    if (sLetterDataPtr->pageNumber > 0)
    {
        sLetterDataPtr->pageNumber--;
        PrintToWindow(WINDOW_1, FONT_WHITE);
    }
    gTasks[taskId].func = Task_LetterMain;

}


/* This is the meat of the UI. This is where you wait for player inputs and can branch to other tasks accordingly */
static void Task_LetterMain(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_MenuTurnOff;
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        // also add if currentPage < totalPages so we don't try to render past the last page
        gTasks[taskId].func = Task_UINextPage;
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        // also add if currentPage > 0 (or 1?) so we don't try to render prior to the first page
        gTasks[taskId].func = Task_UIPreviousPage;
    }
}
