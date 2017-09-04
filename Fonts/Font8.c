#include "Fonts/Font.h"

static const unsigned char HEIGHT_8[] = { 8 };

static const unsigned char GAP8[] = { 6,0,0,0,0,0,0 };
static const unsigned char UZK_GAP8[] = { 3,0,0,0 };

static const unsigned char char8_033[] = { 4,0,0,0,94 };
static const unsigned char char8_034[] = { 5,0,0,6,0,6 };
static const unsigned char char8_035[] = { 6,0,36,126,36,126,36 };
static const unsigned char char8_036[] = { 6,0,92,84,254,84,116 };
static const unsigned char char8_037[] = { 6,0,68,32,16,8,68 };
static const unsigned char char8_038[] = { 6,0,32,84,74,52,80 };
static const unsigned char char8_039[] = { 4,0,0,4,2 };
static const unsigned char char8_040[] = { 4,0,0,60,66 };
static const unsigned char char8_041[] = { 4,0,0,66,60 };
static const unsigned char char8_042[] = { 6,0,16,84,56,84,16 };
static const unsigned char char8_043[] = { 6,0,16,16,124,16,16 };
static const unsigned char char8_044[] = { 4,0,0,128,96 };
static const unsigned char char8_045[] = { 6,0,16,16,16,16,16 };
static const unsigned char char8_046[] = { 4,0,0,192,192 };
static const unsigned char char8_047[] = { 6,0,64,32,16,8,4 };
static const unsigned char char8_048[] = { 6,0,60,98,90,70,60 };
static const unsigned char char8_049[] = { 6,0,68,66,126,64,64 };
static const unsigned char char8_050[] = { 6,0,100,82,82,82,76 };
static const unsigned char char8_051[] = { 6,0,36,66,66,74,52 };
static const unsigned char char8_052[] = { 6,0,48,40,36,126,32 };
static const unsigned char char8_053[] = { 6,0,46,74,74,74,50 };
static const unsigned char char8_054[] = { 6,0,60,74,74,74,48 };
static const unsigned char char8_055[] = { 6,0,2,98,18,10,6 };
static const unsigned char char8_056[] = { 6,0,52,74,74,74,52 };
static const unsigned char char8_057[] = { 6,0,12,82,82,82,60 };
static const unsigned char char8_058[] = { 3,0,0,72 };
static const unsigned char char8_059[] = { 4,0,0,128,100 };
static const unsigned char char8_060[] = { 5,0,0,16,40,68 };
static const unsigned char char8_061[] = { 6,0,40,40,40,40,40 };
static const unsigned char char8_062[] = { 5,0,0,68,40,16 };
static const unsigned char char8_063[] = { 6,0,4,2,82,10,4 };
static const unsigned char char8_064[] = { 6,0,60,66,90,86,12 };
static const unsigned char char8_065[] = { 6,0,124,18,18,18,124 };
static const unsigned char char8_066[] = { 6,0,126,74,74,74,52 };
static const unsigned char char8_067[] = { 6,0,60,66,66,66,36 };
static const unsigned char char8_068[] = { 6,0,126,66,66,36,24 };
static const unsigned char char8_069[] = { 6,0,126,74,74,74,66 };
static const unsigned char char8_070[] = { 6,0,126,10,10,10,2 };
static const unsigned char char8_071[] = { 6,0,60,66,82,82,52 };
static const unsigned char char8_072[] = { 6,0,126,8,8,8,126 };
static const unsigned char char8_073[] = { 6,0,66,66,126,66,66 };
static const unsigned char char8_074[] = { 6,0,48,64,64,64,62 };
static const unsigned char char8_075[] = { 6,0,126,8,8,20,98 };
static const unsigned char char8_076[] = { 6,0,126,64,64,64,96 };
static const unsigned char char8_077[] = { 6,0,126,4,8,4,126 };
static const unsigned char char8_078[] = { 6,0,126,4,24,32,126 };
static const unsigned char char8_079[] = { 6,0,60,66,66,66,60 };
static const unsigned char char8_080[] = { 6,0,126,18,18,18,12 };
static const unsigned char char8_081[] = { 6,0,60,66,82,34,92 };
static const unsigned char char8_082[] = { 6,0,126,18,18,50,76 };
static const unsigned char char8_083[] = { 6,0,36,74,74,74,48 };
static const unsigned char char8_084[] = { 6,0,2,2,126,2,2 };
static const unsigned char char8_085[] = { 6,0,62,64,64,64,62 };
static const unsigned char char8_086[] = { 6,0,30,32,64,32,30 };
static const unsigned char char8_087[] = { 6,0,62,64,32,64,62 };
static const unsigned char char8_088[] = { 6,0,66,36,24,36,66 };
static const unsigned char char8_089[] = { 6,0,6,8,112,8,6 };
static const unsigned char char8_090[] = { 6,0,66,98,82,74,70 };
static const unsigned char char8_091[] = { 5,0,0,126,66,66 };
static const unsigned char char8_092[] = { 6,0,4,8,16,32,64 };
static const unsigned char char8_093[] = { 5,0,0,66,66,126 };
static const unsigned char char8_094[] = { 6,0,8,4,126,4,8 };
static const unsigned char char8_095[] = { 7,0,128,128,128,128,128,128 };
static const unsigned char char8_096[] = { 6,0,72,124,74,66,68 };
static const unsigned char char8_097[] = { 6,0,32,84,84,84,120 };
static const unsigned char char8_098[] = { 6,0,126,72,72,72,48 };
static const unsigned char char8_099[] = { 5,0,56,68,68,68 };
static const unsigned char char8_100[] = { 6,0,48,72,72,72,126 };
static const unsigned char char8_101[] = { 6,0,56,84,84,84,72 };
static const unsigned char char8_102[] = { 5,0,0,124,10,2 };
static const unsigned char char8_103[] = { 6,0,24,164,164,164,124 };
static const unsigned char char8_104[] = { 6,0,126,8,8,8,112 };
static const unsigned char char8_105[] = { 5,0,0,72,122,64 };
static const unsigned char char8_106[] = { 6,0,0,64,128,128,122 };
static const unsigned char char8_107[] = { 6,0,0,126,24,36,64 };
static const unsigned char char8_108[] = { 5,0,0,62,64,64 };
static const unsigned char char8_109[] = { 6,0,124,4,120,4,120 };
static const unsigned char char8_110[] = { 6,0,124,4,4,4,120 };
static const unsigned char char8_111[] = { 6,0,56,68,68,68,56 };
static const unsigned char char8_112[] = { 6,0,252,36,36,36,24 };
static const unsigned char char8_113[] = { 7,0,24,36,36,36,252,128 };
static const unsigned char char8_114[] = { 6,0,0,120,4,4,4 };
static const unsigned char char8_115[] = { 6,0,72,84,84,84,32 };
static const unsigned char char8_116[] = { 6,0,0,4,62,68,64 };
static const unsigned char char8_117[] = { 6,0,60,64,64,64,60 };
static const unsigned char char8_118[] = { 6,0,12,48,64,48,12 };
static const unsigned char char8_119[] = { 6,0,60,64,56,64,60 };
static const unsigned char char8_120[] = { 6,0,68,40,16,40,68 };
static const unsigned char char8_121[] = { 6,0,28,160,160,160,124 };
static const unsigned char char8_122[] = { 6,0,68,100,84,76,68 };
static const unsigned char char8_123[] = { 6,0,8,8,118,66,66 };
static const unsigned char char8_124[] = { 4,0,0,0,126 };
static const unsigned char char8_125[] = { 6,0,66,66,118,8,8 };
static const unsigned char char8_126[] = { 6,0,0,4,2,4,2 };
static const unsigned char char8_127[] = { 7,0,126,129,189,165,129,126 };
static const unsigned char char8_128[] = { 7,0,1,1,1,1,1,1 };
static const unsigned char char8_129[] = { 7,0,0,0,0,0,0,255 };
static const unsigned char char8_130[] = { 7,0,128,128,128,128,128,128 };
static const unsigned char char8_131[] = { 2,0,255 };
static const unsigned char char8_132[] = { 7,0,224,24,4,2,2,1 };
static const unsigned char char8_133[] = { 7,0,1,2,2,4,24,224 };
static const unsigned char char8_134[] = { 7,0,128,64,64,32,24,7 };
static const unsigned char char8_135[] = { 7,0,7,24,32,64,64,128 };
static const unsigned char char8_136[] = { 7,0,8,8,8,8,8,8 };
static const unsigned char char8_137[] = { 7,0,5,5,5,5,5,5 };
static const unsigned char char8_138[] = { 7,0,224,24,4,66,162,65 };
static const unsigned char char8_139[] = { 7,0,65,162,66,4,24,224 };
static const unsigned char char8_140[] = { 7,0,130,69,66,32,24,7 };
static const unsigned char char8_141[] = { 7,0,7,24,32,66,69,130 };
static const unsigned char char8_160[] = { 6,0,126,75,74,75,66 };
static const unsigned char char8_176[] = { 6,0,56,85,84,85,72 };
static const unsigned char char8_192[] = { 6,0,124,18,18,18,124 };
static const unsigned char char8_193[] = { 6,0,126,74,74,74,50 };
static const unsigned char char8_194[] = { 6,0,126,74,74,74,52 };
static const unsigned char char8_195[] = { 6,0,126,2,2,2,6 };
static const unsigned char char8_196[] = { 6,0,192,124,66,126,192 };
static const unsigned char char8_197[] = { 6,0,126,74,74,74,66 };
static const unsigned char char8_198[] = { 6,0,102,24,126,24,102 };
static const unsigned char char8_199[] = { 6,0,36,66,74,74,52 };
static const unsigned char char8_200[] = { 6,0,126,32,24,4,126 };
static const unsigned char char8_201[] = { 6,0,126,32,25,4,126 };
static const unsigned char char8_202[] = { 6,0,126,8,8,20,98 };
static const unsigned char char8_203[] = { 6,0,64,60,2,2,126 };
static const unsigned char char8_204[] = { 6,0,126,4,8,4,126 };
static const unsigned char char8_205[] = { 6,0,126,8,8,8,126 };
static const unsigned char char8_206[] = { 6,0,60,66,66,66,60 };
static const unsigned char char8_207[] = { 6,0,126,2,2,2,126 };
static const unsigned char char8_208[] = { 6,0,126,18,18,18,12 };
static const unsigned char char8_209[] = { 6,0,60,66,66,66,36 };
static const unsigned char char8_210[] = { 6,0,2,2,126,2,2 };
static const unsigned char char8_211[] = { 6,0,14,80,80,80,62 };
static const unsigned char char8_212[] = { 6,0,28,34,126,34,28 };
static const unsigned char char8_213[] = { 6,0,66,36,24,36,66 };
static const unsigned char char8_214[] = { 7,0,126,64,64,64,126,192 };
static const unsigned char char8_215[] = { 6,0,14,16,16,16,126 };
static const unsigned char char8_216[] = { 6,0,126,64,124,64,126 };
static const unsigned char char8_217[] = { 7,0,126,64,124,64,126,192 };
static const unsigned char char8_218[] = { 6,0,2,126,72,72,48 };
static const unsigned char char8_219[] = { 6,0,126,72,48,0,126 };
static const unsigned char char8_220[] = { 6,0,0,126,72,72,48 };
static const unsigned char char8_221[] = { 6,0,66,74,74,74,60 };
static const unsigned char char8_222[] = { 6,0,126,16,60,66,60 };
static const unsigned char char8_223[] = { 6,0,76,50,18,18,126 };
static const unsigned char char8_224[] = { 6,0,32,84,84,84,120 };
static const unsigned char char8_225[] = { 6,0,124,84,84,84,32 };
static const unsigned char char8_226[] = { 6,0,124,84,84,88,32 };
static const unsigned char char8_227[] = { 6,0,124,4,4,4,4 };
static const unsigned char char8_228[] = { 6,0,192,112,76,124,192 };
static const unsigned char char8_229[] = { 6,0,56,84,84,84,72 };
static const unsigned char char8_230[] = { 6,0,108,16,124,16,108 };
static const unsigned char char8_231[] = { 6,0,40,68,84,84,40 };
static const unsigned char char8_232[] = { 6,0,124,32,16,8,124 };
static const unsigned char char8_233[] = { 6,0,124,32,18,8,124 };
static const unsigned char char8_234[] = { 6,0,124,16,16,40,68 };
static const unsigned char char8_235[] = { 6,0,64,56,4,4,124 };
static const unsigned char char8_236[] = { 6,0,124,8,16,8,124 };
static const unsigned char char8_237[] = { 6,0,124,16,16,16,124 };
static const unsigned char char8_238[] = { 6,0,56,68,68,68,56 };
static const unsigned char char8_239[] = { 6,0,124,4,4,4,124 };
static const unsigned char char8_240[] = { 6,0,124,36,36,36,24 };
static const unsigned char char8_241[] = { 6,0,56,68,68,68,40 };
static const unsigned char char8_242[] = { 6,0,4,4,124,4,4 };
static const unsigned char char8_243[] = { 6,0,12,80,80,80,60 };
static const unsigned char char8_244[] = { 6,0,24,36,124,36,24 };
static const unsigned char char8_245[] = { 6,0,68,40,16,40,68 };
static const unsigned char char8_246[] = { 7,0,124,64,64,64,124,192 };
static const unsigned char char8_247[] = { 6,0,12,16,16,16,124 };
static const unsigned char char8_248[] = { 6,0,124,64,120,64,124 };
static const unsigned char char8_249[] = { 7,0,124,64,120,64,124,192 };
static const unsigned char char8_250[] = { 6,0,4,124,80,80,32 };
static const unsigned char char8_251[] = { 6,0,124,80,32,0,124 };
static const unsigned char char8_252[] = { 6,0,0,124,80,80,32 };
static const unsigned char char8_253[] = { 6,0,68,84,84,84,56 };
static const unsigned char char8_254[] = { 6,0,124,16,56,68,56 };
static const unsigned char char8_255[] = { 6,0,72,52,20,20,124 };

unsigned char const* const FONT_ASCII_8_X[] =
{ HEIGHT_8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
GAP8,
UZK_GAP8,
UZK_GAP8,
char8_035,
char8_036,
char8_037,
char8_038,
char8_039,
char8_040,
char8_041,
UZK_GAP8,
char8_043,
UZK_GAP8,
char8_045,
char8_046,
char8_047,
char8_048,
char8_049,
char8_050,
char8_051,
char8_052,
char8_053,
char8_054,
char8_055,
char8_056,
char8_057,
char8_058,
UZK_GAP8,
char8_060,
UZK_GAP8,
char8_062,
char8_063,
char8_064,
char8_065,
char8_066,
char8_067,
char8_068,
char8_069,
char8_070,
char8_071,
char8_072,
char8_073,
char8_074,
char8_075,
char8_076,
char8_077,
char8_078,
char8_079,
char8_080,
char8_081,
char8_082,
char8_083,
char8_084,
char8_085,
char8_086,
char8_087,
char8_088,
char8_089,
char8_090,
char8_091,
UZK_GAP8,
char8_093,
char8_094,
char8_095,
UZK_GAP8,
char8_097,
char8_098,
char8_099,
char8_100,
char8_101,
char8_102,
char8_103,
char8_104,
char8_105,
char8_106,
char8_107,
char8_108,
char8_109,
char8_110,
char8_111,
char8_112,
char8_113,
char8_114,
char8_115,
char8_116,
char8_117,
char8_118,
char8_119,
char8_120,
char8_121,
char8_122,
char8_123,
UZK_GAP8,
char8_125,
char8_126,
UZK_GAP8,
char8_128,
char8_129,
UZK_GAP8,
char8_131,
UZK_GAP8,
char8_133,
char8_134,
char8_135,
char8_136,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
UZK_GAP8,
char8_065,
char8_193,
char8_066,
char8_195,
char8_196,
char8_069,
char8_198,
char8_199,
char8_200,
char8_201,
char8_075,
char8_203,
char8_077,
char8_072,
char8_079,
char8_207,
char8_080,
char8_067,
char8_084,
char8_211,
char8_212,
char8_088,
char8_214,
char8_215,
char8_216,
char8_217,
char8_218,
char8_219,
char8_220,
char8_221,
char8_222,
char8_223,
char8_097,
char8_225,
char8_226,
char8_227,
char8_228,
char8_101,
char8_230,
char8_231,
char8_232,
char8_233,
char8_107,
char8_235,
char8_236,
char8_237,
char8_111,
char8_239,
char8_112,
char8_099,
char8_242,
char8_121,
char8_244,
char8_120,
char8_246,
char8_247,
char8_248,
char8_249,
char8_250,
char8_251,
char8_252,
char8_253,
char8_254,
char8_255,
};
