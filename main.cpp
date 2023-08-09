
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

#include <cstdio>
using std::sprintf;

#include <cstring>
using std::strlen;
using std::strtok;
using std::atoi;

#include "app_globals.hpp"
#include "core/document.hpp"
#include "video/framebuffer.hpp"
#include "resource_collection.hpp"
#include "core_collection.hpp"

#include "core/text_render_engine.hpp"
#include "engine/keyboard_engine.hpp"
#include "engine/video_engine.hpp"
#include "engine/disk_engine.h"
#include "core/text_persistence_engine.hpp"
#include "core/open_file_menu.hpp"
#include "core/main_menu.hpp"
#include "core/new_file_menu.hpp"
#include "core/save_as_menu.hpp"

#include "widgets/lcd4x20_msgbox.hpp"
#include "widgets/lcd4x20_inputbox.hpp"
#include "widgets/lcd4x20_splashbox.hpp"
#include "widgets/lcd4x20_menu.hpp"
#include "widgets/lcd4x20_textview.hpp"

#include "rpi2040/rpi2040_uart.hpp"
#include "rpi2040/rpi2040_text_engine.hpp"
#include "rpi2040/rpi2040_usb_keyboard.hpp"
#include "rpi2040/rpi2040_disk_engine.hpp"
#include "rpi2040/rpi2040_lcd4x20_video.hpp"
#include "rpi2040/rpi2040_utils_engine.hpp"

#include "bsp/board.h"

/**
 * Prepare all resources to be used specific for Raspberry PI PICO 2040 board
 */
void prepareRpi2040();
void showIntroWindow();
void loadFileWindow();
void startDocumentWindow();
void showNewDocumentWindow();
void startUartDebug();
void initDefaultFolders();

#include <string.h>
//
#include "my_debug.h"
//
#include "hw_config.h"
//
#include "ff.h" /* Obtains integer types */
//
#include "diskio.h" /* Declarations of disk functions */
#include "sd_card.h"

void sdTest();

//======================================================================
// Main kernel of app
//======================================================================

int main() {

    cout << "System booting..." << endl;

    //======================================================================
    // UART DEBUG
    //======================================================================
    startUartDebug();

    //======================================================================
    // Platform specific initialization
    //======================================================================
    prepareRpi2040();

    cout << "Resources initialized OK" << endl;

    //======================================================================
    // Default folders initialization
    //======================================================================
    initDefaultFolders();

    cout << "Folders initialized OK" << endl;

    //======================================================================
    // Core initialization
    //======================================================================
    cout << "Loading constants..." << endl;

    AppGlobals::getInstance().loadConstants();

    if (!AppGlobals::getInstance().isNewFileCalled()) {

        if (AppGlobals::getInstance().getLastOpennedDocument() != 0
            && !strcmp(AppGlobals::getInstance().getLastOpennedDocument(), "") == 0) {
            cout << "Loading file [" << AppGlobals::getInstance().getLastOpennedDocument() << "]" << endl;
            loadFileWindow();
            AppGlobals::getInstance().setLastOpennedDocument(0);
            AppGlobals::getInstance().saveConstants();
        } else {
            showIntroWindow();
        }

    } else if (!AppGlobals::getInstance().isNewFileCalled() &&
            (AppGlobals::getInstance().getLastOpennedDocument() == 0 ||
            strcmp(AppGlobals::getInstance().getLastOpennedDocument(), "") == 0)) {

        showIntroWindow();

    } else if (AppGlobals::getInstance().isNewFileCalled()) {

        AppGlobals::getInstance().setNewFileCalled(false);
        AppGlobals::getInstance().saveConstants();
        showNewDocumentWindow();
    }

    sdTest();

    startDocumentWindow();

}

//======================================================================
// End Main kernel of app
//======================================================================

void initDefaultFolders()
{
   DiskEngine (*disk) = ResourceCollection::getInstance().getDiskEngine();

   int err = (*disk).touch(AppGlobals::getInstance().STORAGE_DOCUMENTS_DIR, "empty.info");
   if (err < 0) {
       (*disk).mkdir("",AppGlobals::getInstance().STORAGE_DOCUMENTS_DIR);
   }
}


void startUartDebug()
{
    board_init();

    Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();
    rpi2040uart.setup();

    cout << "Debug initialized..." << endl;
}

void loadFileWindow()
{
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    UtilsEngine *utils = ResourceCollection::getInstance().getUtils();
    TextPersistenceEngine *persistence = CoreCollection::getInstance().getTextPersistenceEngine();

    char tmp[50];

    sprintf(tmp, "File: %s", AppGlobals::getInstance().getLastOpennedDocument());

    (*ResourceCollection::getInstance().getSplashBoxEngine())
            .reset()
            .setTitle("Loading...")
            .setMessage(tmp)
            .render();

    (*video).display();
    (*utils).sleepMs(200);

    (*utils).activateActStatus();
    (*persistence).load(AppGlobals::getInstance().getLastOpennedDocument());
    (*utils).deactivateActStatus();

}

void startDocumentWindow()
{
    TextRenderEngine *component = CoreCollection::getInstance().getTextRenderEngine();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboardEngine = ResourceCollection::getInstance().getKeyboardEngine();

    (*component)
        .render();

    (*component)
        .run(video, keyboardEngine);
}


void showIntroWindow()
{
    char tmp[50];

    sprintf(tmp, "Firmware v%s", AppGlobals::APP_VERSION);

    (*ResourceCollection::getInstance().getSplashBoxEngine())
        .reset()
        .setTitle("Text Editor")
        .setMessage(tmp)
        .render();

    (*ResourceCollection::getInstance().getVideoEngine()).display();

    (*ResourceCollection::getInstance().getUtils()).sleepMs(5000);

}


void showNewDocumentWindow()
{
    char tmp[50];

    sprintf(tmp, "Preparing new file...");

    (*ResourceCollection::getInstance().getSplashBoxEngine())
            .reset()
            .setTitle("New file")
            .setMessage(tmp)
            .render();

    (*ResourceCollection::getInstance().getVideoEngine()).display();
    (*ResourceCollection::getInstance().getUtils()).sleepMs(1000);

}



void prepareRpi2040()
{
    Document *currentDocument = new Document;
    FrameBuffer *fb = new FrameBuffer(AppGlobals::FRAMEBUFFER_MAX_ROWS, AppGlobals::FRAMEBUFFER_MAX_COLS);
    
    Rpi2040UsbKeyboard::getInstance().setup();

    Rpi2040Lcd4x20Video *rpi2040Lcd4X20Video = new Rpi2040Lcd4x20Video;
    Rpi2040DiskEngine *rpi2040DiskEngine = new Rpi2040DiskEngine;
    Rpi2040TextEngine *rpi2040TextEngine = new Rpi2040TextEngine(currentDocument, rpi2040Lcd4X20Video);
    Rpi2040UtilsEngine *utilsEngine = new Rpi2040UtilsEngine;

    LCD4X20InputBox *lcd4X20InputBox = new LCD4X20InputBox(fb);
    LCD4X20Menu *lcd4X20Menu = new LCD4X20Menu(fb);
    LCD4X20MsgBox *lcd4X20MsgBox = new LCD4X20MsgBox(fb);
    LCD4X20Splashbox *lcd4X20Splashbox = new LCD4X20Splashbox(fb);
    LCD4X20TextView *lcd4X20TextView = new LCD4X20TextView(fb, lcd4X20Menu);

    TextPersistenceEngine *textPersistenceEngine = new TextPersistenceEngine(currentDocument,
                                                                             rpi2040DiskEngine);


    (*rpi2040DiskEngine).setup();
    (*rpi2040Lcd4X20Video).setFrameBuffer(fb);

    ResourceCollection::getInstance().setKeyboardEngine(&Rpi2040UsbKeyboard::getInstance());
    ResourceCollection::getInstance().setVideoEngine(rpi2040Lcd4X20Video);

    ResourceCollection::getInstance().setInputBoxEngine(lcd4X20InputBox);
    ResourceCollection::getInstance().setMenuEngine(lcd4X20Menu);
    ResourceCollection::getInstance().setMsgBoxEngine(lcd4X20MsgBox);
    ResourceCollection::getInstance().setSplashBoxEngine(lcd4X20Splashbox);
    ResourceCollection::getInstance().setTextViewEngine(lcd4X20TextView);
    ResourceCollection::getInstance().setUtilsEngine(utilsEngine);
    ResourceCollection::getInstance().setDiskEngine(rpi2040DiskEngine);

    OpenFileMenu *openFileMenu = new OpenFileMenu;
    MainMenu *mainMenu = new MainMenu;
    NewFileMenu *newFileMenu = new NewFileMenu;
    SaveAsMenu *saveAsMenu = new SaveAsMenu;

    CoreCollection::getInstance().setCurrentDocument(currentDocument);
    CoreCollection::getInstance().setTextPersistenceEngine(textPersistenceEngine);
    CoreCollection::getInstance().setTextRenderEngine(rpi2040TextEngine);
    CoreCollection::getInstance().setOpenFileMenu(openFileMenu);
    CoreCollection::getInstance().setMainMenu(mainMenu);
    CoreCollection::getInstance().setNewFileMenu(newFileMenu);
    CoreCollection::getInstance().setSaveAsMenu(saveAsMenu);

}



// Hardware Configuration of SPI "objects"
// Note: multiple SD cards can be driven by one SPI if they use different slave
// selects.
static spi_t spis[] = {  // One for each SPI.
        {
                .hw_inst = spi1,  // SPI component
                .miso_gpio = 12,  // GPIO number (not Pico pin number)
                .mosi_gpio = 11,
                .sck_gpio = 14,

                // .baud_rate = 1000 * 1000
                .baud_rate = 1000000
                // .baud_rate = 25 * 1000 * 1000 // Actual frequency: 20833333.
        }};

// Hardware Configuration of the SD Card "objects"
static sd_card_t sd_cards[] = {  // One for each SD card
        {
                .pcName = "0:",   // Name used to mount device
                .spi = &spis[0],  // Pointer to the SPI driving this card
                .ss_gpio = 13,    // The SPI slave select GPIO for this SD card
                .use_card_detect = false,
                .card_detect_gpio = 22,  // Card detect
                .card_detected_true = 1  // What the GPIO read returns when a card is
                // present.
        }};



/* ********************************************************************** */
size_t sd_get_num() { return count_of(sd_cards); }
sd_card_t *sd_get_by_num(size_t num) {
    if (num <= sd_get_num()) {
        return &sd_cards[num];
    } else {
        return NULL;
    }
}
size_t spi_get_num() { return count_of(spis); }
spi_t *spi_get_by_num(size_t num) {
    if (num <= spi_get_num()) {
        return &spis[num];
    } else {
        return NULL;
    }
}



void sdTest()
{
    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buf[100];
    char filename[] = "test02.txt";

    // Initialize chosen serial port
    stdio_init_all();

    // Wait for user to press 'enter' to continue
    printf("\r\nSD card test. Press 'enter' to start.\r\n");
    while (true) {
        buf[0] = getchar();
        if ((buf[0] == '\r') || (buf[0] == '\n')) {
            break;
        }
    }

    // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }

    // Mount drive
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        while (true);
    }

    // Open file for writing ()
    fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Write something to file
    ret = f_printf(&fil, "This is another test\r\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }
    ret = f_printf(&fil, "of writing to an SD card.\r\n");
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        while (true);
    }

    // Close file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Open file for reading
    fr = f_open(&fil, filename, FA_READ);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file (%d)\r\n", fr);
        while (true);
    }

    // Print every line in file over serial
    printf("Reading from file '%s':\r\n", filename);
    printf("---\r\n");
    while (f_gets(buf, sizeof(buf), &fil)) {
        printf(buf);
    }
    printf("\r\n---\r\n");

    // Close file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Unmount drive
    f_unmount("0:");


}