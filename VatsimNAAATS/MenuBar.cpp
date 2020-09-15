#pragma once
#include "pch.h"
#include "Constants.h"
#include "MenuBar.h"
#include "Styles.h"

using namespace Colours;

map<int, string> MenuBar::BuildButtonData(int section) {
	map<int, string> data;

	// First rectangle
	if (section == 0) {
		data[MENBTN_SETUP] = "Setup";
		data[MENBTN_NOTEPAD] = "NotePad";
		data[MENBTN_ADSC] = "Contracts";
		data[MENBTN_FREQUENCY] = "Frequency";
		data[MENBTN_MISC] = "Misc";
		data[MENBTN_MESSAGE] = "Message";
		data[MENBTN_TAGS] = "Tags";
		data[MENBTN_FLIGHTPLAN] = "Flight Plan";
		data[MENBTN_DESTAPT] = "Dest Airport";
		return data;
	}
}

void MenuBar::DrawMenuBar(CDC* dc, CRadarScreen* screen, POINT topLeft) {

	// Brush to draw the bar
	CBrush brush(ScreenBlue.ToCOLORREF());

	// Make the data
	map<int, string> btnData;

	// Get screen width
	LONG screenWidth = screen->GetRadarArea().left + screen->GetRadarArea().right;

	// Create the base rectangle and the 3d bevel
	CRect baseMenuRectColour(topLeft.x, topLeft.y, topLeft.x + screenWidth, MENBAR_HEIGHT);
	dc->FillRect(baseMenuRectColour, &brush);
	CRect baseMenuRect(topLeft.x, topLeft.y, topLeft.x + screenWidth, MENBAR_HEIGHT);
	dc->Draw3dRect(baseMenuRect, ScreenBlue.ToCOLORREF(), BevelLight.ToCOLORREF());
	
	// Offset for menu rectangles
	int menuOffsetX = topLeft.x;

	// Create the first section
	CRect rect1(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT1_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect1, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect1, -1, -1);
	dc->Draw3dRect(rect1, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	// Create buttons
	btnData = BuildButtonData(0);
	int offsetX = 100;
	int offsetY = 30;
	int idx = 0;
	for (auto kv : btnData) {
		int btnWidth = 0;
		switch (kv.first) {
			case MENBTN_SETUP:
			case MENBTN_TAGS:
				btnWidth = 40 + (BTN_PAD_SIDE * 2);
				break;
			case MENBTN_NOTEPAD:
			case MENBTN_FLIGHTPLAN:
				btnWidth = 80 + (BTN_PAD_SIDE * 2);
				break;
			case MENBTN_ADSC:
			case MENBTN_DESTAPT:
				btnWidth = 90 + (BTN_PAD_SIDE * 2);
				break;
			case MENBTN_FREQUENCY:
				btnWidth = 110 + (BTN_PAD_SIDE * 2);
				break;
			case MENBTN_MISC:
				btnWidth = 55 + (BTN_PAD_SIDE * 2);
				break;
			case MENBTN_MESSAGE:
				btnWidth = 90 + (BTN_PAD_SIDE * 2);
				break;
		}

		if (idx == 4)
		{
			offsetX = 10;
			offsetY += MENBAR_BTN_HEIGHT + 1;
			DrawMenuBarButton(dc, { offsetX, offsetY }, kv.second, btnWidth, MENBAR_BTN_HEIGHT, { 0, 0 }, false);
			offsetX += btnWidth + 1;
		}
		else {
			DrawMenuBarButton(dc, { offsetX, offsetY }, kv.second, btnWidth, MENBAR_BTN_HEIGHT, { 0, 0 }, false);
			offsetX += btnWidth + 1;
		}

		idx++;
	}
	// Offset for the next rectangle
	menuOffsetX = RECT1_WIDTH + 1;

	// Create rectangle
	CRect rect2(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT2_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect2, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect2, -1, -1);
	dc->Draw3dRect(rect2, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT2_WIDTH + 1;

	// Create rectangle
	CRect rect3(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT3_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect3, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect3, -1, -1);
	dc->Draw3dRect(rect3, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT3_WIDTH + 1;

	// Create rectangle
	CRect rect4(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT4_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect4, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect4, -1, -1);
	dc->Draw3dRect(rect4, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT4_WIDTH + 1;

	// Create rectangle
	CRect rect5(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT5_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect5, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect5, -1, -1);
	dc->Draw3dRect(rect5, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT5_WIDTH + 1;

	// Create rectangle
	CRect rect6(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT6_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect6, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect6, -1, -1);
	dc->Draw3dRect(rect6, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT6_WIDTH + 1;

	// Create rectangle
	CRect rect7(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT7_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect7, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect7, -1, -1);
	dc->Draw3dRect(rect7, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT7_WIDTH + 1;

	// Create rectangle
	CRect rect8(menuOffsetX, topLeft.y + 1, menuOffsetX + RECT8_WIDTH, MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect8, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect8, -1, -1);
	dc->Draw3dRect(rect8, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	menuOffsetX += RECT8_WIDTH + 1;

	// Create end rectangle by calculating width left on screen
	CRect rect9(menuOffsetX, topLeft.y + 1, menuOffsetX + (screenWidth - menuOffsetX), MENBAR_HEIGHT - 2);
	dc->Draw3dRect(rect9, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(rect9, -1, -1);
	dc->Draw3dRect(rect9, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
}

CRect MenuBar::DrawMenuBarButton(CDC* dc, POINT topLeft, string text, int width, int height, POINT mousePointer, bool isPressed) 
{
	// Brushes
	CBrush btnNormal(ScreenBlue.ToCOLORREF());
	CBrush btnPressed(ButtonPressed.ToCOLORREF());

	// Create rectangle
	CRect button(topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height);

	// Check if pressed
	if (isPressed) {
		dc->FillSolidRect(button, ButtonPressed.ToCOLORREF());
	}
	else {
		dc->FillSolidRect(button, ScreenBlue.ToCOLORREF());
	}

	// Button bevel
	dc->Draw3dRect(button, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());
	InflateRect(button, -1, -1);
	dc->Draw3dRect(button, BevelLight.ToCOLORREF(), BevelDark.ToCOLORREF());

	// Draw text
	dc->SelectObject(CFont::FromHandle(FontSelector::NormalFont(MEN_FONT_SIZE)));
	dc->SetTextColor(TextWhite.ToCOLORREF());
	dc->TextOutA(topLeft.x + BTN_PAD_SIDE, topLeft.y + BTN_PAD_TOP, text.c_str());

	// Return the rectangle
	return button;
}