/*
** This is a port of the X Window System bitmap fonts 5✕7 font
** from https://www.cl.cam.ac.uk/~mgk25/ucs-fonts.html
**
** Conversion from Linux BDF → Adafruit GFX font,
** with the help of this Python script:
** https://gist.github.com/skelliam/322d421f028545f16f6d
** William Skellenger (williamj@skellenger.net)
** Twitter: @skelliam
**
*/


const uint8_t XWindowSystemFont5x7Bitmaps[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20 space */
  0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00, /* 0x21 exclam */
  0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, /* 0x22 quotedbl */
  0x00, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x00, /* 0x23 numbersign */
  0x00, 0x70, 0xA0, 0x70, 0x28, 0x70, 0x00, /* 0x24 dollar */
  0x80, 0x90, 0x20, 0x40, 0x90, 0x10, 0x00, /* 0x25 percent */
  0x00, 0x40, 0xA0, 0x40, 0xA0, 0x50, 0x00, /* 0x26 ampersand */
  0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, /* 0x27 quotesingle */
  0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x00, /* 0x28 parenleft */
  0x40, 0x20, 0x20, 0x20, 0x20, 0x40, 0x00, /* 0x29 parenright */
  0x00, 0x50, 0x20, 0x70, 0x20, 0x50, 0x00, /* 0x2A asterisk */
  0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, /* 0x2B plus */
  0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x40, /* 0x2C comma */
  0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, /* 0x2D hyphen */
  0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, /* 0x2E period */
  0x00, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, /* 0x2F slash */
  0x20, 0x50, 0x50, 0x50, 0x50, 0x20, 0x00, /* 0x30 zero */
  0x20, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00, /* 0x31 one */
  0x60, 0x90, 0x10, 0x20, 0x40, 0xF0, 0x00, /* 0x32 two */
  0xF0, 0x10, 0x60, 0x10, 0x90, 0x60, 0x00, /* 0x33 three */
  0x20, 0x60, 0xA0, 0xF0, 0x20, 0x20, 0x00, /* 0x34 four */
  0xF0, 0x80, 0xE0, 0x10, 0x90, 0x60, 0x00, /* 0x35 five */
  0x60, 0x80, 0xE0, 0x90, 0x90, 0x60, 0x00, /* 0x36 six */
  0xF0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x00, /* 0x37 seven */
  0x60, 0x90, 0x60, 0x90, 0x90, 0x60, 0x00, /* 0x38 eight */
  0x60, 0x90, 0x90, 0x70, 0x10, 0x60, 0x00, /* 0x39 nine */
  0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, /* 0x3A colon */
  0x00, 0x60, 0x60, 0x00, 0x60, 0x40, 0x80, /* 0x3B semicolon */
  0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, /* 0x3C less */
  0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, /* 0x3D equal */
  0x00, 0x40, 0x20, 0x10, 0x20, 0x40, 0x00, /* 0x3E greater */
  0x20, 0x50, 0x10, 0x20, 0x00, 0x20, 0x00, /* 0x3F question */
  0x60, 0x90, 0xB0, 0xB0, 0x80, 0x60, 0x00, /* 0x40 at */
  0x60, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x00, /* 0x41 A */
  0xE0, 0x90, 0xE0, 0x90, 0x90, 0xE0, 0x00, /* 0x42 B */
  0x60, 0x90, 0x80, 0x80, 0x90, 0x60, 0x00, /* 0x43 C */
  0xE0, 0x90, 0x90, 0x90, 0x90, 0xE0, 0x00, /* 0x44 D */
  0xF0, 0x80, 0xE0, 0x80, 0x80, 0xF0, 0x00, /* 0x45 E */
  0xF0, 0x80, 0xE0, 0x80, 0x80, 0x80, 0x00, /* 0x46 F */
  0x60, 0x90, 0x80, 0xB0, 0x90, 0x70, 0x00, /* 0x47 G */
  0x90, 0x90, 0xF0, 0x90, 0x90, 0x90, 0x00, /* 0x48 H */
  0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, /* 0x49 I */
  0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00, /* 0x4A J */
  0x90, 0xA0, 0xC0, 0xC0, 0xA0, 0x90, 0x00, /* 0x4B K */
  0x80, 0x80, 0x80, 0x80, 0x80, 0xF0, 0x00, /* 0x4C L */
  0x90, 0xF0, 0xF0, 0x90, 0x90, 0x90, 0x00, /* 0x4D M */
  0x90, 0xD0, 0xD0, 0xB0, 0xB0, 0x90, 0x00, /* 0x4E N */
  0x60, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00, /* 0x4F O */
  0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80, 0x00, /* 0x50 P */
  0x60, 0x90, 0x90, 0x90, 0xD0, 0x60, 0x10, /* 0x51 Q */
  0xE0, 0x90, 0x90, 0xE0, 0xA0, 0x90, 0x00, /* 0x52 R */
  0x60, 0x90, 0x40, 0x20, 0x90, 0x60, 0x00, /* 0x53 S */
  0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, /* 0x54 T */
  0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00, /* 0x55 U */
  0x90, 0x90, 0x90, 0x90, 0x60, 0x60, 0x00, /* 0x56 V */
  0x90, 0x90, 0x90, 0xF0, 0xF0, 0x90, 0x00, /* 0x57 W */
  0x90, 0x90, 0x60, 0x60, 0x90, 0x90, 0x00, /* 0x58 X */
  0x50, 0x50, 0x50, 0x20, 0x20, 0x20, 0x00, /* 0x59 Y */
  0xF0, 0x10, 0x20, 0x40, 0x80, 0xF0, 0x00, /* 0x5A Z */
  0x70, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00, /* 0x5B bracketleft */
  0x00, 0x80, 0x40, 0x20, 0x10, 0x00, 0x00, /* 0x5C backslash */
  0x70, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, /* 0x5D bracketright */
  0x20, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x5E asciicircum */
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, /* 0x5F underscore */
  0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 grave */
  0x00, 0x00, 0x70, 0x90, 0xB0, 0x50, 0x00, /* 0x61 a */
  0x80, 0x80, 0xE0, 0x90, 0x90, 0xE0, 0x00, /* 0x62 b */
  0x00, 0x00, 0x60, 0x80, 0x80, 0x60, 0x00, /* 0x63 c */
  0x10, 0x10, 0x70, 0x90, 0x90, 0x70, 0x00, /* 0x64 d */
  0x00, 0x00, 0x60, 0xB0, 0xC0, 0x60, 0x00, /* 0x65 e */
  0x20, 0x50, 0x40, 0xE0, 0x40, 0x40, 0x00, /* 0x66 f */
  0x00, 0x00, 0x70, 0x90, 0x60, 0x80, 0x70, /* 0x67 g */
  0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0x00, /* 0x68 h */
  0x20, 0x00, 0x60, 0x20, 0x20, 0x70, 0x00, /* 0x69 i */
  0x10, 0x00, 0x10, 0x10, 0x10, 0x50, 0x20, /* 0x6A j */
  0x80, 0x80, 0xA0, 0xC0, 0xA0, 0x90, 0x00, /* 0x6B k */
  0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, /* 0x6C l */
  0x00, 0x00, 0xA0, 0xF0, 0x90, 0x90, 0x00, /* 0x6D m */
  0x00, 0x00, 0xE0, 0x90, 0x90, 0x90, 0x00, /* 0x6E n */
  0x00, 0x00, 0x60, 0x90, 0x90, 0x60, 0x00, /* 0x6F o */
  0x00, 0x00, 0xE0, 0x90, 0x90, 0xE0, 0x80, /* 0x70 p */
  0x00, 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, /* 0x71 q */
  0x00, 0x00, 0xE0, 0x90, 0x80, 0x80, 0x00, /* 0x72 r */
  0x00, 0x00, 0x70, 0xC0, 0x30, 0xE0, 0x00, /* 0x73 s */
  0x40, 0x40, 0xE0, 0x40, 0x40, 0x30, 0x00, /* 0x74 t */
  0x00, 0x00, 0x90, 0x90, 0x90, 0x70, 0x00, /* 0x75 u */
  0x00, 0x00, 0x50, 0x50, 0x50, 0x20, 0x00, /* 0x76 v */
  0x00, 0x00, 0x90, 0x90, 0xF0, 0xF0, 0x00, /* 0x77 w */
  0x00, 0x00, 0x90, 0x60, 0x60, 0x90, 0x00, /* 0x78 x */
  0x00, 0x00, 0x90, 0x90, 0x50, 0x20, 0x40, /* 0x79 y */
  0x00, 0x00, 0xF0, 0x20, 0x40, 0xF0, 0x00, /* 0x7A z */
  0x10, 0x20, 0x60, 0x20, 0x20, 0x10, 0x00, /* 0x7B braceleft */
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, /* 0x7C bar */
  0x40, 0x20, 0x30, 0x20, 0x20, 0x40, 0x00, /* 0x7D braceright */
  0x50, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x7E asciitilde */
};


/* {offset, width, height, advance cursor, x offset, y offset} */
const GFXglyph XWindowSystemFont5x7Glyphs[] PROGMEM = {
  { 0, 8, 7, 6, 0, -6 }, /* 0x00 char0 */
  { 7, 8, 7, 6, 0, -6 }, /* 0x20 space */
  { 14, 8, 7, 6, 0, -6 }, /* 0x21 exclam */
  { 21, 8, 7, 6, 0, -6 }, /* 0x22 quotedbl */
  { 28, 8, 7, 6, 0, -6 }, /* 0x23 numbersign */
  { 35, 8, 7, 6, 0, -6 }, /* 0x24 dollar */
  { 42, 8, 7, 6, 0, -6 }, /* 0x25 percent */
  { 49, 8, 7, 6, 0, -6 }, /* 0x26 ampersand */
  { 56, 8, 7, 6, 0, -6 }, /* 0x27 quotesingle */
  { 63, 8, 7, 6, 0, -6 }, /* 0x28 parenleft */
  { 70, 8, 7, 6, 0, -6 }, /* 0x29 parenright */
  { 77, 8, 7, 6, 0, -6 }, /* 0x2A asterisk */
  { 84, 8, 7, 6, 0, -6 }, /* 0x2B plus */
  { 91, 8, 7, 6, 0, -6 }, /* 0x2C comma */
  { 98, 8, 7, 6, 0, -6 }, /* 0x2D hyphen */
  { 105, 8, 7, 6, 0, -6 }, /* 0x2E period */
  { 112, 8, 7, 6, 0, -6 }, /* 0x2F slash */
  { 119, 8, 7, 6, 0, -6 }, /* 0x30 zero */
  { 126, 8, 7, 6, 0, -6 }, /* 0x31 one */
  { 133, 8, 7, 6, 0, -6 }, /* 0x32 two */
  { 140, 8, 7, 6, 0, -6 }, /* 0x33 three */
  { 147, 8, 7, 6, 0, -6 }, /* 0x34 four */
  { 154, 8, 7, 6, 0, -6 }, /* 0x35 five */
  { 161, 8, 7, 6, 0, -6 }, /* 0x36 six */
  { 168, 8, 7, 6, 0, -6 }, /* 0x37 seven */
  { 175, 8, 7, 6, 0, -6 }, /* 0x38 eight */
  { 182, 8, 7, 6, 0, -6 }, /* 0x39 nine */
  { 189, 8, 7, 6, 0, -6 }, /* 0x3A colon */
  { 196, 8, 7, 6, 0, -6 }, /* 0x3B semicolon */
  { 203, 8, 7, 6, 0, -6 }, /* 0x3C less */
  { 210, 8, 7, 6, 0, -6 }, /* 0x3D equal */
  { 217, 8, 7, 6, 0, -6 }, /* 0x3E greater */
  { 224, 8, 7, 6, 0, -6 }, /* 0x3F question */
  { 231, 8, 7, 6, 0, -6 }, /* 0x40 at */
  { 238, 8, 7, 6, 0, -6 }, /* 0x41 A */
  { 245, 8, 7, 6, 0, -6 }, /* 0x42 B */
  { 252, 8, 7, 6, 0, -6 }, /* 0x43 C */
  { 259, 8, 7, 6, 0, -6 }, /* 0x44 D */
  { 266, 8, 7, 6, 0, -6 }, /* 0x45 E */
  { 273, 8, 7, 6, 0, -6 }, /* 0x46 F */
  { 280, 8, 7, 6, 0, -6 }, /* 0x47 G */
  { 287, 8, 7, 6, 0, -6 }, /* 0x48 H */
  { 294, 8, 7, 6, 0, -6 }, /* 0x49 I */
  { 301, 8, 7, 6, 0, -6 }, /* 0x4A J */
  { 308, 8, 7, 6, 0, -6 }, /* 0x4B K */
  { 315, 8, 7, 6, 0, -6 }, /* 0x4C L */
  { 322, 8, 7, 6, 0, -6 }, /* 0x4D M */
  { 329, 8, 7, 6, 0, -6 }, /* 0x4E N */
  { 336, 8, 7, 6, 0, -6 }, /* 0x4F O */
  { 343, 8, 7, 6, 0, -6 }, /* 0x50 P */
  { 350, 8, 7, 6, 0, -6 }, /* 0x51 Q */
  { 357, 8, 7, 6, 0, -6 }, /* 0x52 R */
  { 364, 8, 7, 6, 0, -6 }, /* 0x53 S */
  { 371, 8, 7, 6, 0, -6 }, /* 0x54 T */
  { 378, 8, 7, 6, 0, -6 }, /* 0x55 U */
  { 385, 8, 7, 6, 0, -6 }, /* 0x56 V */
  { 392, 8, 7, 6, 0, -6 }, /* 0x57 W */
  { 399, 8, 7, 6, 0, -6 }, /* 0x58 X */
  { 406, 8, 7, 6, 0, -6 }, /* 0x59 Y */
  { 413, 8, 7, 6, 0, -6 }, /* 0x5A Z */
  { 420, 8, 7, 6, 0, -6 }, /* 0x5B bracketleft */
  { 427, 8, 7, 6, 0, -6 }, /* 0x5C backslash */
  { 434, 8, 7, 6, 0, -6 }, /* 0x5D bracketright */
  { 441, 8, 7, 6, 0, -6 }, /* 0x5E asciicircum */
  { 448, 8, 7, 6, 0, -6 }, /* 0x5F underscore */
  { 455, 8, 7, 6, 0, -6 }, /* 0x60 grave */
  { 462, 8, 7, 6, 0, -6 }, /* 0x61 a */
  { 469, 8, 7, 6, 0, -6 }, /* 0x62 b */
  { 476, 8, 7, 6, 0, -6 }, /* 0x63 c */
  { 483, 8, 7, 6, 0, -6 }, /* 0x64 d */
  { 490, 8, 7, 6, 0, -6 }, /* 0x65 e */
  { 497, 8, 7, 6, 0, -6 }, /* 0x66 f */
  { 504, 8, 7, 6, 0, -6 }, /* 0x67 g */
  { 511, 8, 7, 6, 0, -6 }, /* 0x68 h */
  { 518, 8, 7, 6, 0, -6 }, /* 0x69 i */
  { 525, 8, 7, 6, 0, -6 }, /* 0x6A j */
  { 532, 8, 7, 6, 0, -6 }, /* 0x6B k */
  { 539, 8, 7, 6, 0, -6 }, /* 0x6C l */
  { 546, 8, 7, 6, 0, -6 }, /* 0x6D m */
  { 553, 8, 7, 6, 0, -6 }, /* 0x6E n */
  { 560, 8, 7, 6, 0, -6 }, /* 0x6F o */
  { 567, 8, 7, 6, 0, -6 }, /* 0x70 p */
  { 574, 8, 7, 6, 0, -6 }, /* 0x71 q */
  { 581, 8, 7, 6, 0, -6 }, /* 0x72 r */
  { 588, 8, 7, 6, 0, -6 }, /* 0x73 s */
  { 595, 8, 7, 6, 0, -6 }, /* 0x74 t */
  { 602, 8, 7, 6, 0, -6 }, /* 0x75 u */
  { 609, 8, 7, 6, 0, -6 }, /* 0x76 v */
  { 616, 8, 7, 6, 0, -6 }, /* 0x77 w */
  { 623, 8, 7, 6, 0, -6 }, /* 0x78 x */
  { 630, 8, 7, 6, 0, -6 }, /* 0x79 y */
  { 637, 8, 7, 6, 0, -6 }, /* 0x7A z */
  { 644, 8, 7, 6, 0, -6 }, /* 0x7B braceleft */
  { 651, 8, 7, 6, 0, -6 }, /* 0x7C bar */
  { 658, 8, 7, 6, 0, -6 }, /* 0x7D braceright */
  { 665, 8, 7, 6, 0, -6 }, /* 0x7E asciitilde */
};

const GFXfont XWindowSystemFont5x7 PROGMEM = {
  (uint8_t  *)XWindowSystemFont5x7Bitmaps,
  (GFXglyph *)XWindowSystemFont5x7Glyphs,
  0x20, 0x7E, 6 };