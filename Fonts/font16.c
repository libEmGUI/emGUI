#ifndef __FONT16_C
#define __FONT16_C

//#include "font16.h"

static const unsigned char HEIGHT_16[] = { 16 };

static  const unsigned char GAP[] = { 6,0,0,0,0,0,0,0,0,0,0,0,0 };
static const unsigned char UZK_GAP[] = { 3,0,0,0,0,0,0 };
static const unsigned char char16_backspace[] = { 20,16,16,56,56,124,124,254,254,56,56,56,56,56,56,56,56,56,56,56,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const unsigned char char16_shift[] = { 28,14,63,51,51,243,227,0,252,252,96,224,224,0,0,246,246,0,0,24,255,255,27,0,24,254,254,24,0,3,3,3,3,3,1,0,3,3,0,3,3,3,0,3,3,3,0,3,3,3,0,0,0,3,3,3,3 };
//const unsigned char char16_backspace[]={23,0,16,40,40,200,0,240,64,192,0,0,208,0,0,32,248,40,0,32,240,32,0,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,2,3,0,0,0,1,1,1,0};
static const unsigned char char16_enter[] = { 28,255,255,51,51,3,3,0,248,248,48,240,240,0,24,254,254,24,0,0,248,248,88,24,0,248,248,24,24,3,3,3,3,3,3,0,3,3,0,3,3,3,0,3,3,3,3,0,3,3,3,3,0,3,3,0,0 };
static const unsigned char char16_clear[] = { 14,0,0,255,255,255,255,255,255,255,255,255,255,255,255,0,0,3,3,3,3,3,3,3,3,3,3,3,3 };
static const unsigned char char16_033[] = { 6,0,0,0,0,254,254,0,0,0,0,13,13 };// const unsigned char char16_034[]={5,0,0,2,6,4,0,0,0,0,0}; // !!!_apostrof
static const unsigned char char16_034[] = { 7,0,2,6,4,2,6,4,0,0,0,0,0,0,0 }; // "
// const unsigned char char16_035[]={12,255,255,3,3,3,3,3,3,3,3,3,3,255,255,192,192,192,192,192,192,192,192,192,192};
static const unsigned char char16_035[] = { 11,0,0,8,248,15,8,8,8,248,15,8,0,1,15,1,1,1,1,15,1,1,0 }; // #
static const unsigned char char16_036[] = { 12,255,255,3,3,243,243,243,3,3,3,3,3,255,255,192,192,207,207,207,192,192,192,192,192 };
// const unsigned char char16_037[]={11,3,3,3,3,3,3,3,255,255,224,224,192,192,192,192,192,192,192,255,255,7,7};
static const unsigned char char16_037[] = { 8,0,14,10,142,96,24,6,1,0,8,6,1,0,14,10,14 }; // %
static const unsigned char char16_038[] = { 12,255,255,3,3,243,243,243,3,3,243,243,243,255,255,192,192,207,207,207,192,192,207,207,207 };
//const unsigned char char16_039[]={11,3,3,243,243,243,3,3,255,255,224,224,192,192,207,207,207,192,192,255,255,7,7};
static const unsigned char char16_039[] = { 5,0,0,2,6,4,0,0,0,0,0 }; // !!!_apostrof '

static const unsigned char char16_040[] = { 5,0,248,252,6,6,0,3,7,12,12 };
static const unsigned char char16_041[] = { 7,0,0,0,6,6,252,248,0,0,0,12,12,7,3 };
static const unsigned char char16_042[] = { 8,0,36,168,112,252,112,168,36,0,1,0,0,1,0,0,1 };
static const unsigned char char16_043[] = { 9,32,32,32,32,254,32,32,32,32,0,0,0,0,3,0,0,0,0 };
static const unsigned char char16_044[] = { 4,0,0,0,0,0,0,4,12 };
static const unsigned char char16_045[] = { 8,0,0,192,192,192,192,192,192,0,0,0,0,0,0,0,0 };
static const unsigned char char16_046[] = { 4,0,0,0,0,0,0,12,12 };
static const unsigned char char16_047[] = { 8,0,0,0,192,240,60,15,3,0,12,15,3,0,0,0,0 }; // !_division " / "
static const unsigned char char16_048[] = { 8,0,252,2,1,1,1,2,252,0,3,12,8,8,8,4,3 };
static const unsigned char char16_049[] = { 6,0,0,8,4,2,255,0,0,0,0,0,15 };
static const unsigned char char16_050[] = { 8,0,4,2,1,1,129,98,28,0,8,12,10,9,8,8,8 };
static const unsigned char char16_051[] = { 8,0,4,2,33,33,49,94,128,0,6,12,8,8,8,4,3 };
static const unsigned char char16_052[] = { 8,128,64,48,12,2,255,0,0,1,1,1,1,1,15,1,1 };
static const unsigned char char16_053[] = { 8,0,56,23,17,17,17,33,193,0,2,4,8,8,8,4,3 };
static const unsigned char char16_054[] = { 8,0,252,66,33,33,33,66,134,0,3,4,8,8,8,4,3 };
static const unsigned char char16_055[] = { 8,0,1,1,1,225,25,7,1,0,0,0,15,0,0,0,0 };
static const unsigned char char16_056[] = { 8,0,140,82,33,33,33,82,140,0,3,4,8,8,8,4,3 };
static const unsigned char char16_057[] = { 8,0,60,66,129,129,129,66,252,0,2,12,8,8,8,4,3 };

static const unsigned char char16_058[] = { 4,0,0,24,24,0,0,6,6 };
static const unsigned char char16_059[] = { 5,0,0,0,12,12,0,0,0,4,12 };
static const unsigned char char16_060[] = { 11,0,0,0,0,0,8,12,254,254,12,8,0,0,0,0,0,0,0,15,15,0,0 };
static const unsigned char char16_061[] = { 8,0,0,96,96,96,96,96,96,0,0,3,3,3,3,3,3 };
static const unsigned char char16_062[] = { 11,0,0,0,0,0,0,0,252,252,0,0,0,0,0,0,0,2,6,15,15,6,2 };
static const unsigned char char16_063[] = { 8,0,0,24,28,6,134,252,120,0,0,0,0,13,13,0,0 };
static const unsigned char char16_064[] = { 8,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };

static const unsigned char char16_065[] = { 12,0,0,0,192,184,134,129,134,184,192,0,0,0,12,3,0,0,0,0,0,0,0,3,12 };
static const unsigned char char16_066[] = { 10,0,255,33,33,33,33,33,33,115,140,0,15,8,8,8,8,8,8,4,3 };
static const unsigned char char16_067[] = { 11,0,248,4,2,1,1,1,1,1,2,4,0,1,6,4,8,8,8,8,8,4,2 };
static const unsigned char char16_068[] = { 11,0,255,1,1,1,1,1,1,2,4,248,0,15,8,8,8,8,8,8,4,2,1 };
static const unsigned char char16_069[] = { 10,0,255,33,33,33,33,33,33,33,1,0,15,8,8,8,8,8,8,8,8 };
static const unsigned char char16_070[] = { 9,0,255,33,33,33,33,33,33,1,0,15,0,0,0,0,0,0,0 };
static const unsigned char char16_071[] = { 11,0,248,4,2,1,1,65,65,66,68,192,0,1,2,4,8,8,8,8,4,2,1 };
static const unsigned char char16_072[] = { 10,0,255,32,32,32,32,32,32,32,255,0,15,0,0,0,0,0,0,0,15 };
static const unsigned char char16_073[] = { 3,0,0,255,0,0,15 };
static const unsigned char char16_074[] = { 8,0,0,0,0,0,0,0,255,0,3,12,8,8,8,4,3 };
static const unsigned char char16_075[] = { 10,0,255,128,64,32,48,200,4,2,1,0,15,0,0,0,0,0,1,6,8 };
static const unsigned char char16_076[] = { 8,0,255,0,0,0,0,0,0,0,15,8,8,8,8,8,8 };
static const unsigned char char16_077[] = { 12,0,255,6,24,96,128,0,128,96,24,6,255,0,15,0,0,0,1,2,1,0,0,0,15 };
static const unsigned char char16_078[] = { 10,0,255,2,12,16,96,128,0,0,255,0,15,0,0,0,0,0,3,4,15 };
static const unsigned char char16_079[] = { 11,0,248,4,2,1,1,1,1,2,4,248,0,1,2,4,8,8,8,8,4,6,1 };
static const unsigned char char16_080[] = { 10,0,255,65,65,65,65,65,65,34,28,0,15,0,0,0,0,0,0,0,0 };
static const unsigned char char16_081[] = { 11,0,248,4,2,1,1,1,1,2,4,248,0,1,2,4,8,8,10,10,4,14,11 };
static const unsigned char char16_082[] = { 10,0,255,65,65,65,65,193,65,34,28,0,15,0,0,0,0,0,3,4,8 };
static const unsigned char char16_083[] = { 10,0,12,18,33,33,33,65,65,66,132,0,3,4,8,8,8,8,8,4,3 };
static const unsigned char char16_084[] = { 10,0,1,1,1,1,255,1,1,1,1,0,0,0,0,0,15,0,0,0,0 };
static const unsigned char char16_085[] = { 10,0,255,0,0,0,0,0,0,0,255,0,3,4,8,8,8,8,8,4,3 };
static const unsigned char char16_086[] = { 10,0,3,28,224,0,0,0,224,24,7,0,0,0,0,3,12,3,0,0,0 };
static const unsigned char char16_087[] = { 16,1,14,112,128,0,128,112,14,1,14,112,128,0,128,112,15,0,0,0,3,12,3,0,0,0,0,0,3,12,3,0,0 };
static const unsigned char char16_088[] = { 12,0,0,1,2,140,80,32,80,140,2,1,0,0,8,4,2,1,0,0,0,1,2,4,8 };
static const unsigned char char16_089[] = { 10,0,1,6,8,48,192,48,8,6,1,0,0,0,0,0,15,0,0,0,0 };
static const unsigned char char16_090[] = { 10,0,1,1,1,129,97,17,13,3,1,0,8,12,11,8,8,8,8,8,8 };
// const unsigned char char16_091[]={13,0,0,0,128,192,96,48,152,200,96,48,24,8,0,0,0,0,1,3,6,12,9,3,6,12,8};
static const unsigned char char16_091[] = { 4,0,255,1,1,0,15,8,8 }; // bracket_square1[
static const unsigned char char16_092[] = { 8,0,3,15,60,240,192,0,0,0,0,0,0,0,3,15,12 }; // !_kos.cherta 
// const unsigned char char16_093[]={14,0,0,0,0,8,24,48,96,200,152,48,96,192,128,0,0,0,0,8,12,6,3,9,12,6,3,1,0};
static const unsigned char char16_093[] = { 4,0,1,1,255,0,8,8,15 }; // bracket_square2 ]

static const unsigned char char16_095[] = { 15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,48,48,48,48,48,48,48,48,48,48,48,48,48,48 };
static const unsigned char char16_096[] = { 5,0,0,2,6,4,0,0,0,0,0 };
static const unsigned char char16_097[] = { 8,0,32,144,136,136,72,72,240,0,7,8,8,8,8,4,15 };
static const unsigned char char16_098[] = { 8,0,255,16,8,8,8,16,224,0,15,4,8,8,8,4,3 };
static const unsigned char char16_099[] = { 8,0,224,16,8,8,8,16,32,0,3,4,8,8,8,4,2 };
static const unsigned char char16_100[] = { 8,0,224,16,8,8,8,16,255,0,3,4,8,8,8,4,15 };
static const unsigned char char16_101[] = { 8,0,224,144,136,136,136,144,224,0,3,4,8,8,8,4,2 };
static const unsigned char char16_102[] = { 5,0,8,254,9,9,0,0,15,0,0 };
static const unsigned char char16_103[] = { 8,0,224,16,8,8,8,16,248,0,35,68,72,72,72,36,31 };
static const unsigned char char16_104[] = { 8,0,255,16,8,8,8,8,240,0,15,0,0,0,0,0,15 };
static const unsigned char char16_105[] = { 2,0,243,0,15 };
static const unsigned char char16_106[] = { 3,0,0,243,0,64,63 };
static const unsigned char char16_107[] = { 7,0,248,128,128,96,16,8,0,15,0,0,3,4,8 };
static const unsigned char char16_108[] = { 2,0,255,0,15 };
static const unsigned char char16_109[] = { 12,0,248,16,8,8,8,240,16,8,8,8,240,0,15,0,0,0,0,15,0,0,0,0,15 };
static const unsigned char char16_110[] = { 8,0,248,16,8,8,8,8,240,0,15,0,0,0,0,0,15 };
static const unsigned char char16_111[] = { 8,0,224,16,8,8,8,16,224,0,3,4,8,8,8,4,3 };
static const unsigned char char16_112[] = { 8,0,248,16,8,8,8,16,224,0,127,4,8,8,8,4,3 };
static const unsigned char char16_113[] = { 8,0,224,16,8,8,8,16,248,0,3,4,8,8,8,8,127 };
static const unsigned char char16_114[] = { 6,0,248,16,8,8,8,0,15,0,0,0,0 };
static const unsigned char char16_115[] = { 7,0,112,136,136,136,136,16,0,4,8,8,8,8,7 };
static const unsigned char char16_116[] = { 6,0,8,8,255,8,8,0,0,0,15,8,8 };
static const unsigned char char16_117[] = { 8,0,248,0,0,0,0,0,248,0,7,8,8,8,8,4,15 };
static const unsigned char char16_118[] = { 8,0,24,224,0,0,0,224,24,0,0,0,3,14,3,0,0 };
static const unsigned char char16_119[] = { 12,0,24,224,0,128,96,24,96,128,0,224,24,0,0,3,12,3,0,0,0,3,12,3,0 };
static const unsigned char char16_120[] = { 9,0,8,16,32,192,192,32,16,8,0,8,4,2,1,1,2,4,8 };
static const unsigned char char16_121[] = { 9,0,0,56,192,0,0,0,192,56,0,0,64,64,103,28,7,1,0 };
static const unsigned char char16_122[] = { 7,8,8,8,136,104,24,8,8,12,11,8,8,8,8 };

// const unsigned char char16_123[]={13,0,0,64,224,176,24,76,230,178,24,12,6,2,0,0,0,0,1,3,6,12,9,3,6,12,8};
static const unsigned char char16_123[] = { 5,32,80,142,1,1,0,0,7,8,8 }; // {
static const unsigned char char16_124[] = { 5,0,0,0,255,255,0,0,0,15,15 };
// const unsigned char char16_125[]={15,0,0,0,0,2,6,12,24,178,230,76,24,176,224,64,0,0,0,0,8,12,6,3,9,12,6,3,1,0,0};
static const unsigned char char16_125[] = { 5,1,1,142,80,32,8,8,7,0,0 }; // } 
static const unsigned char char16_126[] = { 11,0,0,0,0,0,192,32,16,16,32,192,0,0,0,0,0,0,1,2,2,1,0 };
static const unsigned char char16_127[] = { 8,0,254,254,6,6,6,254,254 };
static const unsigned char char16_128[] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static const unsigned char char16_129[] = { 16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
static const unsigned char char16_130[] = { 6,0,0,0,64,192,128,0,0,0,0,0,0 };
static const unsigned char char16_131[] = { 1,255,255 };
static const unsigned char char16_132[] = { 6,0,0,0,128,192,64,0,0,0,0,0,0 };
static const unsigned char char16_133[] = { 4,3,4,8,8,0,0,0,0 };
static const unsigned char char16_134[] = { 4,8,8,4,3,0,0,0,0 };
static const unsigned char char16_135[] = { 4,0,0,0,0,192,32,16,16 };
static const unsigned char char16_136[] = { 4,0,0,0,0,16,16,32,192 };
static const unsigned char char16_137[] = { 7,0,0,8,4,2,4,8,0,0,0,0,0,0,0 };
static const unsigned char char16_138[] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,1,3,7,15,31,63,127,255,255,127,63,31,15,7,3,1 };
static const unsigned char char16_139[] = { 8,128,192,96,48,24,12,6,3,1,3,6,12,24,48,96,192 };

static const unsigned char char16_147[] = { 6,0,0,0,2,6,4,0,0,0,0,0,0 };
static const unsigned char char16_148[] = { 6,0,0,0,4,6,2,0,0,0,0,0,0 };
static const unsigned char char16_149[] = { 5,0,0,0,0,0,0,0,14,14,14 };

static const unsigned char char16_155[] = { 8,3,6,12,24,48,96,192,128,192,96,48,24,12,6,3,1 };

static const unsigned char char16_166[] = { 5,0,0,0,238,238,0,0,0,0,0 };

static const unsigned char char16_168[] = { 11,0,0,128,127,1,1,1,1,1,255,0,120,12,11,8,8,8,8,8,8,15,120 };

static const unsigned char char16_171[] = { 8,32,80,168,84,138,5,2,1,0,0,0,1,2,5,2,4 };

static const unsigned char char16_185[] = { 12,0,255,6,24,96,128,0,255,0,23,21,23,0,15,0,0,0,1,6,15,0,0,0,0 }; // ¹
static const unsigned char char16_187[] = { 8,1,2,5,138,84,168,80,32,4,2,5,2,1,0,0,0 };

static const unsigned char char16_193[] = { 10,0,255,33,33,33,33,33,33,65,128,0,15,8,8,8,8,8,8,4,3 };
static const unsigned char char16_194[] = { 16,1,14,112,128,0,128,112,14,1,14,112,128,0,128,112,15,0,0,0,3,12,3,0,0,0,0,0,3,12,3,0,0 };
static const unsigned char char16_195[] = { 9,0,0,255,1,1,1,1,1,1,0,0,15,0,0,0,0,0,0 };
static const unsigned char char16_196[] = { 12,0,0,0,128,127,1,1,1,1,1,255,0,0,120,12,11,8,8,8,8,8,8,15,120 };
static const unsigned char char16_198[] = { 16,0,1,1,2,204,80,32,32,255,32,32,80,204,2,1,1,0,8,6,1,0,0,0,0,15,0,0,0,0,1,6,8 };
static const unsigned char char16_199[] = { 9,0,12,2,1,33,33,82,76,128,0,2,4,8,8,8,8,4,3 };
static const unsigned char char16_200[] = { 11,0,255,0,0,128,64,32,16,8,6,255,0,15,6,1,0,0,0,0,0,0,15 };
static const unsigned char char16_201[] = { 11,0,255,0,0,131,66,34,19,8,6,255,0,15,6,1,0,0,0,0,0,0,15 };
static const unsigned char char16_203[] = { 10,0,0,0,254,3,1,1,1,1,255,0,8,8,7,0,0,0,0,0,15 };
static const unsigned char char16_207[] = { 10,0,255,1,1,1,1,1,1,1,255,0,15,0,0,0,0,0,0,0,15 };
static const unsigned char char16_211[] = { 10,0,3,12,48,192,0,192,48,12,3,0,0,8,8,12,3,0,0,0,0 };
static const unsigned char char16_212[] = { 12,0,240,8,8,4,4,255,4,4,8,8,240,0,0,1,1,2,2,15,2,2,1,1,0 };
static const unsigned char char16_214[] = { 13,0,255,0,0,0,0,0,0,0,0,255,0,0,0,15,8,8,8,8,8,8,8,8,15,8,120 };
static const unsigned char char16_215[] = { 9,0,63,64,128,128,128,128,64,255,0,0,0,0,0,0,0,0,15 };
static const unsigned char char16_216[] = { 14,0,255,0,0,0,0,0,253,0,0,0,0,0,255,0,15,8,8,8,8,8,15,8,8,8,8,8,15 };
static const unsigned char char16_217[] = { 15,0,255,0,0,0,0,0,253,0,0,0,0,0,255,0,0,15,8,8,8,8,8,15,8,8,8,8,8,15,120 };
static const unsigned char char16_218[] = { 13,0,1,1,1,1,255,32,32,32,32,32,64,128,0,0,0,0,0,15,8,8,8,8,8,4,3 };
static const unsigned char char16_219[] = { 13,0,255,32,32,32,32,32,64,128,0,0,0,255,0,15,8,8,8,8,8,4,3,0,0,0,15 };
static const unsigned char char16_220[] = { 9,0,255,32,32,32,32,32,64,128,0,15,8,8,8,8,8,4,3 };
static const unsigned char char16_221[] = { 11,0,4,2,1,1,33,33,33,34,36,248,0,2,4,8,8,8,8,8,4,2,1 };
static const unsigned char char16_222[] = { 15,0,255,64,64,64,248,4,2,1,1,1,1,2,4,248,0,15,0,0,0,1,2,4,8,8,8,8,4,2,1 };
static const unsigned char char16_223[] = { 11,0,0,28,34,65,193,65,65,65,65,255,0,0,8,4,3,0,0,0,0,0,15 };
static const unsigned char char16_225[] = { 8,0,252,18,9,9,9,17,225,0,3,4,8,8,8,4,3 };
static const unsigned char char16_226[] = { 8,0,248,136,136,136,136,136,112,0,15,8,8,8,8,8,7 };
static const unsigned char char16_227[] = { 6,0,248,8,8,8,8,0,15,0,0,0,0 };
static const unsigned char char16_228[] = { 10,0,0,0,248,8,8,8,8,248,0,0,120,14,9,8,8,8,8,15,120 };
static const unsigned char char16_230[] = { 12,0,8,16,96,128,128,248,128,128,96,16,8,0,8,4,3,0,0,15,0,0,3,4,8 };
static const unsigned char char16_231[] = { 7,0,48,8,136,136,136,112,0,6,8,8,8,8,7 };
static const unsigned char char16_232[] = { 8,0,248,0,0,128,96,16,248,0,15,6,1,0,0,0,15 };
static const unsigned char char16_233[] = { 8,0,248,1,2,130,98,17,248,0,15,6,1,0,0,0,15 };
static const unsigned char char16_235[] = { 10,0,0,0,248,8,8,8,8,8,248,0,8,8,7,0,0,0,0,0,15 };
static const unsigned char char16_236[] = { 10,0,248,56,192,0,0,0,192,56,248,0,15,0,0,3,12,3,0,0,15 };
static const unsigned char char16_237[] = { 8,0,248,128,128,128,128,128,248,0,15,0,0,0,0,0,15 };
static const unsigned char char16_239[] = { 8,0,248,8,8,8,8,8,248,0,15,0,0,0,0,0,15 };
static const unsigned char char16_242[] = { 8,0,8,8,8,248,8,8,8,0,0,0,0,15,0,0,0 };
static const unsigned char char16_244[] = { 12,0,224,16,8,8,16,255,16,8,8,16,224,0,3,4,8,8,4,127,4,8,8,4,3 };
static const unsigned char char16_246[] = { 9,0,248,0,0,0,0,0,248,0,0,15,8,8,8,8,8,15,120 };
static const unsigned char char16_247[] = { 8,0,120,128,0,0,0,0,248,0,0,0,1,1,1,1,15 };
static const unsigned char char16_248[] = { 12,0,248,0,0,0,0,248,0,0,0,0,248,0,15,8,8,8,8,15,8,8,8,8,15 };
static const unsigned char char16_249[] = { 13,0,248,0,0,0,0,248,0,0,0,0,248,0,0,15,8,8,8,8,15,8,8,8,8,15,120 };
static const unsigned char char16_250[] = { 10,0,8,8,248,128,128,128,128,128,0,0,0,0,15,8,8,8,8,8,7 };
static const unsigned char char16_251[] = { 11,0,248,128,128,128,128,128,0,0,0,248,0,15,8,8,8,8,8,7,0,0,15 };
static const unsigned char char16_252[] = { 8,0,248,128,128,128,128,128,0,0,15,8,8,8,8,8,7 };
static const unsigned char char16_253[] = { 8,0,32,16,8,136,136,144,224,0,2,4,8,8,8,4,3 };
static const unsigned char char16_254[] = { 12,0,248,128,128,128,224,16,8,8,8,16,224,0,15,0,0,0,3,4,8,8,8,4,3 };
static const unsigned char char16_255[] = { 8,0,112,136,136,136,136,136,248,0,12,3,1,0,0,0,15 };

unsigned char const* const FONT_ASCII_16_X[] =
{ HEIGHT_16,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_clear,\

UZK_GAP,\

char16_shift,\

char16_backspace,\

UZK_GAP,\

char16_enter,\

UZK_GAP,\

UZK_GAP,\

char16_enter,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_033,\

char16_034,\

char16_035,\

char16_036,\

char16_037,\

char16_038,\

char16_039,\

char16_040,\

char16_041,\

char16_042,\

char16_043,\

char16_044,\

char16_045,\

char16_046,\

char16_047,\

char16_048,\

char16_049,\

char16_050,\

char16_051,\

char16_052,\

char16_053,\

char16_054,\

char16_055,\

char16_056,\

char16_057,\

char16_058,\

char16_059,\

char16_060,\

char16_061,\

char16_062,\

char16_063,\

char16_064,\

char16_065,\

char16_066,\

char16_067,\

char16_068,\

char16_069,\

char16_070,\

char16_071,\

char16_072,\

char16_073,\

char16_074,\

char16_075,\

char16_076,\

char16_077,\

char16_078,\

char16_079,\

char16_080,\

char16_081,\

char16_082,\

char16_083,\

char16_084,\

char16_085,\

char16_086,\

char16_087,\

char16_088,\

char16_089,\

char16_090,\

char16_091,\

char16_092,\

char16_093,\

UZK_GAP,\

char16_095,\

char16_096,\

char16_097,\

char16_098,\

char16_099,\

char16_100,\

char16_101,\

char16_102,\

char16_103,\

char16_104,\

char16_105,\

char16_106,\

char16_107,\

char16_108,\

char16_109,\

char16_110,\

char16_111,\

char16_112,\

char16_113,\

char16_114,\

char16_115,\

char16_116,\

char16_117,\

char16_118,\

char16_119,\

char16_120,\

char16_121,\

char16_122,\

char16_123,\

char16_124,\

char16_125,\

char16_126,\

char16_127,\

char16_128,\

char16_129,\

char16_130,\

char16_131,\

char16_132,\

char16_133,\

char16_134,\

char16_135,\

char16_136,\

char16_137,\

char16_138,\

char16_139,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_147,\

char16_148,\

char16_149,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_155,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_166,\

UZK_GAP,\

char16_168,\

UZK_GAP,\

UZK_GAP,\

char16_171,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_185,\

UZK_GAP,\

char16_187,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

UZK_GAP,\

char16_065,\

char16_193,\

char16_066,\

char16_195,\

char16_196,\

char16_069,\

char16_198,\

char16_199,\

char16_200,\

char16_201,\

char16_075,\

char16_203,\

char16_077,\

char16_072,\

char16_079,\

char16_207,\

char16_080,\

char16_067,\

char16_084,\

char16_211,\

char16_212,\

char16_088,\

char16_214,\

char16_215,\

char16_216,\

char16_217,\

char16_218,\

char16_219,\

char16_220,\

char16_221,\

char16_222,\

char16_223,\

char16_097,\

char16_225,\

char16_226,\

char16_227,\

char16_228,\

char16_101,\

char16_230,\

char16_231,\

char16_232,\

char16_233,\

char16_107,\

char16_235,\

char16_236,\

char16_237,\

char16_111,\

char16_239,\

char16_112,\

char16_099,\

char16_242,\

char16_121,\

char16_244,\

char16_120,\

char16_246,\

char16_247,\

char16_248,\

char16_249,\

char16_250,\

char16_251,\

char16_252,\

char16_253,\

char16_254,\

char16_255,\

};

#endif


