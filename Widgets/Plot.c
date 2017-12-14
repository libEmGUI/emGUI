/**
 * @file   Plot.c
 * @author Roman Savrulin (romeo.deepmind@gmail.com)
 * @date   20.11.2012
 * @brief  Интерфейс виджета, выводящего график ЭКГ
 *
 */

#include "Widgets/Plot.h"
#include <limits.h>
#include <stdint.h>
#include <malloc.h>
#include "Draw/Draw.h"

#define MIN_GRID_PERIOD_PX 16

 /** @weakgroup prop-widget-plot
  *  @{
  */

   /**
   * @brief структура свойств виджета
   */
typedef struct xPlotProps_struct {
	uint16_t    usLastDrawedPosX;    ///< последняя отрисованная позиция по горизонтали
	uint16_t    usLastDrawedPosY0;  ///< нижняя точка последнего отрисованного горизонтального отсчета бар-диаграммы по вертикали
	uint16_t    usLastDrawedPosY1;  ///< верхняя точка последнего отрисованного горизонтального отсчета бар-диаграммы по вертикали
	uint16_t    usLastDrawedSample;
	bool        bLastFilled;
	int16_t     sDataDCOffset;
	bool        bWriteEnabled;
	uint16_t    usColor;            ///< цвет графика
	xPlotData_t      *pxL;                ///< Дескриптор отведения
	float       xScale;             ///< размер клетки по Y в единицах измерения
	uint8_t     usXMarkerCount;
	uint8_t     usYMarkerCount;
	int16_t     drawOffset;
} xPlotProps;


/**
 * @brief this private functions get dimentions considering border width (0 or 1 px)
 *
 * @param pxW - виджет
 *
 * @return середина виджета
 */
inline static uint16_t prvWidgetMiddleLine(xPlot *pxW) {
	return usWidgetGetY0(pxW, true) + usWidgetGetH(pxW) / 2;
}

static bool prvDrawGrid(xPlot * pxW, uint16_t psXCursor, bool bPartialDraw);

/**
* @brief получает значение данных в интересующей точке
*
* @param psSample - укаталель, по которому поместится полученное значение
* @param uiOffset - интересующая точка в наборе данных
* @param bActualData - в случае true usOffset ограничен текущей позицией записи данных в цикле, иначе - всем набором данных
*
* @returns true если данные для интересующей точки получены
* @returns false если данные для интересующей точки НЕ получены
*/
static bool prvGetValue(xPlotData_t *pxL, int16_t * psSample, uint32_t uiOffset, bool bActualData) {
	if (bActualData) {
		if (uiOffset >= pxL->ulWritePos)
			return false;
	} else if (uiOffset >= pxL->ulElemCount)
		return false;

	*psSample = pxL->psData[uiOffset];
	return true;
}

//int math is broken yet
#define USE_FLOAT 

/**
 * @brief производит отрисовку
 * @param pxW - виджет
 */
static bool prvPlot(xPlot *pxW) {
	int16_t bHaveSample,
		sSample;

	if (!pxW)
		return false;

	xPlotProps* xP = (xPlotProps*)pxW->pvProp;

	if (!xP)
		return false; 

	uint16_t usX,
		usH = usWidgetGetH(pxW);

	xPlotData_t *xL = xP->pxL;

	int16_t sY0,
		sY1,
		sGraphMiddleLine = prvWidgetMiddleLine(pxW),
		sMin,
		sMax,
		sDataDCOffset = xP->sDataDCOffset;
	
	int16_t drawOffset = xP->drawOffset;
	uint32_t uiSampleCount = (pxW->bValid)?xP->pxL->ulWritePos:xP->pxL->ulElemCount;

	bool bRedrawed = false;

	uint16_t usSample = 0;

	uint16_t i, usW = usWidgetGetW(pxW);

#ifdef USE_FLOAT //if FPU is available
	float coe = usH /( xP->usYMarkerCount * xP->xScale); //при мин. масштабе во всей высоте 2мв
#else
	long coe = (usH << 16) / (PLOT_1MV * xP->xScale); //при мин. масштабе во всей высоте 2мв
#endif

	uint16_t usCorrection = 0;
	if (usW < xL->ulElemCount)
		usCorrection = xL->ulElemCount%usW;

	//коррекция для полной отрисовки данных. (например, если usAvgCount должно быть дробным)
	if (usCorrection) {
		usCorrection = xL->ulElemCount / usCorrection;
	}

	//Auto-reset
	if (xL->ulWritePos < xP->usLastDrawedSample)
		xP->usLastDrawedPosX = 0;

	//Функция проводит отрисовку данных графика
	//отрезок данных должен уместиться в pxW->usW точках на экране
	//Поэтому мы должны усреднять полученные данные.
	//График в каждой точке рисуется вертикальными линиями от минимума до максимума,
	//найденного в усредненом отрезке.
	for (i = (xP->usLastDrawedPosX == 0) ? 0 : xP->usLastDrawedPosX + 1; i < usW; i++) {
		uint16_t usAvgCount = xL->ulElemCount / usW;
		usSample = usAvgCount*i;

		if (usCorrection) {
			usSample += usSample / usCorrection;
		}

		//Проверка на возможность отрисовки всех семплов одной верт. линии.
		if (uiSampleCount - usSample < usAvgCount)
			break;

		bHaveSample = prvGetValue(xP->pxL,  &sSample, usSample, ((pxW->bValid) ? true : false));
		sMin = sMax = sSample;

		//We cannot use FPU on STM32F103, so we need to use some kind of optimizations
		while (bHaveSample && usAvgCount) {

			if (sSample < sMin)
				sMin = sSample;

			if (sSample > sMax)
				sMax = sSample;

			bHaveSample = prvGetValue(xP->pxL, &sSample, usSample++, ((pxW->bValid) ? true : false));
			//Если есть коррекция, то каждые usCorrection раз прочитаем
			//дополнительный семпл.
			if (usCorrection) {
				if (usSample % usCorrection == 0)
					usAvgCount++;
			}
			usAvgCount--;
		}

		if (!bHaveSample) //TODO: should we check usAvgCount???
			break; // data is not ready yet.

		  //Draw line from min to max position, found in averaging samples
		usX = i + usWidgetGetX0(pxW, true);

#ifdef USE_FLOAT //if FPU is available
		sY1 = sGraphMiddleLine - (sMin + sDataDCOffset) * coe - drawOffset;
		sY0 = sGraphMiddleLine - (sMax + sDataDCOffset) * coe - drawOffset;
#else
		sY1 = sGraphMiddleLine + (((sDataDCOffset - sMin) * coe) >> 16);
		sY0 = sGraphMiddleLine - (((sMax - sDataDCOffset) * coe) >> 16);
#endif

		// Ограничение при выходе за границы виджета
		if (sY0 <= usWidgetGetY0(pxW, true))
			sY0 = usWidgetGetY0(pxW, true);
		else
			if (sY0 >= usWidgetGetY1(pxW, true))
				sY0 = usWidgetGetY1(pxW, true);

		if (sY1 <= usWidgetGetY0(pxW, true))
			sY1 = usWidgetGetY0(pxW, true);
		else
			if (sY1 >= usWidgetGetY1(pxW, true))
				sY1 = usWidgetGetY1(pxW, true);

		if (sY0 > sY1) {
			uint16_t tmp;
			tmp = sY1;
			sY1 = sY0;
			sY0 = tmp;
		}

		if (pxW->bValid)
			prvDrawGrid(pxW, i, true); //Do not draw cursor on invalidates

		  //заполнение пробелов в графике
		if (sY0 > xP->usLastDrawedPosY1) {
			sY0 = xP->usLastDrawedPosY1;
		}
		if (sY1 < xP->usLastDrawedPosY0) {
			sY1 = xP->usLastDrawedPosY0;
		}

		pxDrawHDL()->vVLine(usX, sY0, sY1, xP->usColor);
		xP->usLastDrawedPosY0 = sY0;
		xP->usLastDrawedPosY1 = sY1;
		bRedrawed = true;
		xP->usLastDrawedPosX = i;
		xP->usLastDrawedSample = usSample;
	}

	return bRedrawed;
}

void vPlotSetColor(xPlot *pxW, uint16_t usColor, bool bInvalidate) {
	xPlotProps* xP;
	if (!(xP = (xPlotProps*)pxWidgetGetProps(pxW, WidgetPlot)))
		return;

	xP->usColor = usColor;

	if (bInvalidate)
		vWidgetInvalidate(pxW);
}


void vPlotReset(xPlot *pxW, bool bInvalidate) {
	if (!pxW)
		return;

	xPlotProps* xP = (xPlotProps*)pxW->pvProp;

	xP->usLastDrawedPosX = 0;
	if (bInvalidate)
		vWidgetInvalidate(pxW);
}

/**
 * @brief отрисовка сетки виджета
 * @param pxW - виджет
 * @param sXCursor - позиция курсора
 * @bPartialDraw - флаг полной или частичной отрисовки сетки
 * @return true - отрисовка проведена
 */
static bool prvDrawGrid(xPlot * pxW, uint16_t usXCursor, bool bPartialDraw) {
	if (!pxW)
		return false;

	xPlotProps* xP = (xPlotProps*)pxW->pvProp;

	uint16_t usXMarkerCount = xP->usXMarkerCount;
	uint16_t usYMarkerCount = xP->usYMarkerCount;

	//TODO: Make these variables double to improve precision
	uint16_t usXGridSize = usWidgetGetW(pxW) / usXMarkerCount;
	uint16_t usYGridSize = usWidgetGetH(pxW) / usYMarkerCount;
	uint16_t usX,
		usY,
		usXText = usWidgetGetX0(pxW, true) + 1,
		usYText = usWidgetGetY0(pxW, true) + 8, //font height here
		usX0 = usWidgetGetX0(pxW, true),
		usX1 = usWidgetGetX1(pxW, true);

	if (bPartialDraw) { //we need to draw 1 px blank cursor(with grid if needed)
		usXCursor = usXCursor + usX0;
		usX0 = usXCursor;
		usX1 = usXCursor;
		//if we use border, we need to add 1 to usY0, and sub 1 from usY1
		if (usXCursor < usWidgetGetX1(pxW, true) - 1)
			pxDrawHDL()->vVLine(usXCursor + 1, usWidgetGetY0(pxW, true), usWidgetGetY1(pxW, true), COLOR_PLOT_SCALE_MARKER);//cursor(goes 1px forward)
		pxDrawHDL()->vVLine(usXCursor, usWidgetGetY0(pxW, true), usWidgetGetY1(pxW, true), pxW->usBgColor);//splitter/eraser
	}

	//Vertical Grid
	for (usX = usWidgetGetX0(pxW, true); usX < usWidgetGetX1(pxW, true); usX += usXGridSize) {
		if (!bPartialDraw)
			pxDrawHDL()->vVLine(usX, usWidgetGetY0(pxW, true), usWidgetGetY1(pxW, true), COLOR_PLOT_GRIDS);
		else
			if (usXCursor == usX) {
				pxDrawHDL()->vVLine(usX, usWidgetGetY0(pxW, true), usWidgetGetY1(pxW, true), COLOR_PLOT_GRIDS);
			}
	}

	//Horisontal Grid in two steps
	//If we are drawing cursor, then it is just points on cursor line (see limits above)
	for (usY = prvWidgetMiddleLine(pxW); usY > usWidgetGetY0(pxW, true); usY = (usY > usYGridSize) ? usY - usYGridSize : 0) {
		pxDrawHDL()->vHLine(usX0, usY, usX1, COLOR_PLOT_GRIDS);
	}

	for (usY = prvWidgetMiddleLine(pxW); usY < usWidgetGetY1(pxW, true); usY += usYGridSize) {
		//if (abs((int16_t)(usY - prvWidgetMiddleLine(pxW))) < usYGridSize) continue;
		pxDrawHDL()->vHLine(usX0, usY, usX1, COLOR_PLOT_GRIDS);
	}

	uint16_t usYMiddle = prvWidgetMiddleLine(pxW),
		usMvWidth = usXGridSize / 3,
		usTextW = usFontGetStrW(xP->pxL->sName, EM_GUI_SMALL_FONT);

	if (!bPartialDraw || (bPartialDraw && (usXCursor >= usXText) && (usXCursor <= usXText + usTextW))) {
		//Название отведения
		pxDrawHDL()->vPutString(
			usXText,
			usYText,
			xP->pxL->sName,
			EM_GUI_SMALL_FONT,
			COLOR_MESSAGE_TEXT,
			COLOR_PLOT_BACKGROUND,
			true
		);
	}

	return true;
}

/**
 * @brief обработчик отрисовки виджета
 * @param pxW - виджет
 * @return true - отрисовка проведена
 * @return false - отрисовки не было
 */
static bool prvPlotDraw(xPlot *pxW) {
	if (!pxW)
		return false;

	xPlotProps* xP = (xPlotProps*)pxW->pvProp;

	if (pxW->eType != WidgetPlot)
		return false;

	if (!pxW->bVisible)
		return false;

	//Auto reset + invalidate
	if (xP->bLastFilled && !xP->pxL->bDataFilled) {
		pxW->bValid = false;
	}

	if (xP->bWriteEnabled != xP->pxL->bWriteEnabled) {
		pxW->bValid = false;
		xP->bWriteEnabled = xP->pxL->bWriteEnabled;
	}

	int16_t sDataDCOffset = xP->pxL->sDataDCOffset;
	if (xP->sDataDCOffset != sDataDCOffset) {
		pxW->bValid = false;
		xP->sDataDCOffset = sDataDCOffset;
	}

	xP->bLastFilled = xP->pxL->bDataFilled;

	if (pxW->bValid) {
		//Do graph plotting here, when grid is already valid.
		return prvPlot(pxW);
	}

	//Invalidation of the widget redraws grid only.

	//if widget is invalid, then make it replot data
	xP->usLastDrawedPosX = 0;
	xP->usLastDrawedPosY0 = prvWidgetMiddleLine(pxW);
	xP->usLastDrawedPosY1 = prvWidgetMiddleLine(pxW);

	bWidgetDraw(pxW);
	prvDrawGrid(pxW, 0, false);

	//for fast redrawing without cursor
	pxW->bValid = false;
	prvPlot(pxW);
	pxW->bValid = true;
	return true;
}

xPlot * pxPlotCreate(uint16_t usX0, uint16_t usY0, uint16_t usX1, uint16_t usY1, xWidget *pxWidParent, xPlotData_t * pxL) {
	xPlot *pxW;
	pxW = pxWidgetCreate(usX0, usY0, usX1, usY1, pxWidParent, true);
	
	xPlotProps* xP;

	if (pxW && pxL) {
		pxW->eType = WidgetPlot;
		vWidgetSetClickable(pxW, true);
		vWidgetSetBgColor(pxW, COLOR_PLOT_BACKGROUND, false);

		xP = (xPlotProps*)malloc(sizeof(xPlotProps));

		

		xP->usLastDrawedPosX = 0;
		xP->usLastDrawedSample = 0;
		xP->sDataDCOffset = 0;
		xP->xScale = 100;				// value in mA
		xP->bLastFilled = false;
		xP->bWriteEnabled = false;
		xP->usYMarkerCount = 6;
		xP->usXMarkerCount = 6;
		xP->drawOffset = 0;
		xP->pxL = pxL;

		xP->usLastDrawedPosY0 = prvWidgetMiddleLine(pxW);
		xP->usLastDrawedPosY1 = prvWidgetMiddleLine(pxW);

		pxW->pxDrawHandler = prvPlotDraw;
		xP->usColor = COLOR_PLOT_SCALE_MARKER;
		pxW->pvProp = xP;
		return pxW;
	}
	

	free(pxW);
	return NULL;
}

void vPlotSetScale(xPlot * pxW, float xScale) {
	if (!pxW)
		return;

	xPlotProps* xP = (xPlotProps*)pxW->pvProp;

	if (xP->xScale == xScale)
		return;

	xP->xScale = xScale;

	vWidgetInvalidate(pxW);
}


/**
 *  @}
 */
