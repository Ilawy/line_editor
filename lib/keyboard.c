#include "./conio.h"
typedef enum
{

    Enter = 10,

    Escape = 27,

    /* ASCII */
    KeySpace = 32,
    KeyExclamation = 33,
    KeyDoubleQuote = 34,
    KeyHashtag = 35,
    KeyDollar = 36,
    KeyPercent = 37,
    KeyAmpersand = 38,
    KeyApostrophe = 39,
    KeyLeftParenthesis = 40,
    KeyRightParenthesis = 41,
    KeyAsterisk = 42,
    KeyPlus = 43,
    KeyComma = 44,
    KeyMinus = 45,
    KeyPeriod = 46,
    KeySlash = 47,
    KeyNumber0 = 48,
    KeyNumber1 = 49,
    KeyNumber2 = 50,
    KeyNumber3 = 51,
    KeyNumber4 = 52,
    KeyNumber5 = 53,
    KeyNumber6 = 54,
    KeyNumber7 = 55,
    KeyNumber8 = 56,
    KeyNumber9 = 57,
    KeyColon = 58,
    KeySemicolon = 59,
    KeyLessThan = 60,
    KeyEquals = 61,
    KeyGreaterThan = 62,
    KeyQuestion = 63,
    KeyAt = 64,
    KeyA = 65,
    KeyB = 66,
    KeyC = 67,
    KeyD = 68,
    KeyE = 69,
    KeyF = 70,
    KeyG = 71,
    KeyH = 72,
    KeyI = 73,
    KeyJ = 74,
    KeyK = 75,
    KeyL = 76,
    KeyM = 77,
    KeyN = 78,
    KeyO = 79,
    KeyP = 80,
    KeyQ = 81,
    KeyR = 82,
    KeyS = 83,
    KeyT = 84,
    KeyU = 85,
    KeyV = 86,
    KeyW = 87,
    KeyX = 88,
    KeyY = 89,
    KeyZ = 90,
    KeyLeftBracket = 91,
    KeyBackslash = 92,
    KeyRightBracket = 93,
    KeyCaret = 94,
    KeyUnderscore = 95,
    KeyGrave = 96,
    Keya = 97,
    Keyb = 98,
    Keyc = 99,
    Keyd = 100,
    Keye = 101,
    Keyf = 102,
    Keyg = 103,
    Keyh = 104,
    Keyi = 105,
    Keyj = 106,
    Keyk = 107,
    Keyl = 108,
    Keym = 109,
    Keyn = 110,
    Keyo = 111,
    Keyp = 112,
    Keyq = 113,
    Keyr = 114,
    Keys = 115,
    Keyt = 116,
    Keyu = 117,
    Keyv = 118,
    Keyw = 119,
    Keyx = 120,
    Keyy = 121,
    Keyz = 122,
    KeyLeftCurlyBracket = 123,
    KeyPipe = 124,
    KeyRightCurlyBracket = 125,
    KeyTilde = 126,
    Backspace = 127,

    /* NON STANDARD */
    ArrowUp = 256,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Home,
    End,
    Insert,
    AltBackSpace,
    Delete,

} KeyboardButton;

KeyboardButton captureKeyboardInput();

#define KEY_ESC_OR_EXTENDED 27
#define EXTEND_ARROW_RIGHT 67
#define EXTEND_ARROW_LEFT 68
#define EXTEND_ARROW_UP 65
#define EXTEND_ARROW_DOWN 66
#define EXTEND_HOME 72
#define EXTEND_END 70
#define EXTEND_INSERT 50
#define EXTEND_DELETE 51

#define KEY_ENTER 10
#define KEY_Y 121
KeyboardButton captureKeyboardInput()
{
    char first = getch();
    switch (first)
    {
    case Enter:
        return Enter;
    case KeySpace ... KeyTilde:
        return first;
    case KEY_ESC_OR_EXTENDED:
        if (kbhit() == 0)
            return Escape;
        char middle = getch();
        if (middle == 91)
        {
            switch (getch())
            {
            case EXTEND_ARROW_UP:
                return ArrowUp;
            case EXTEND_ARROW_DOWN:
                return ArrowDown;
            case EXTEND_ARROW_LEFT:
                return ArrowLeft;
            case EXTEND_ARROW_RIGHT:
                return ArrowRight;
            case EXTEND_HOME:
                return Home;
            case EXTEND_END:
                return End;
            case EXTEND_INSERT:
                getchar(); // ignore 126
                return Insert;
            }
        }
        else if (middle == Backspace)
        {
            return AltBackSpace;
        }
        break;
    case Backspace:
        return Backspace;
    }
}
