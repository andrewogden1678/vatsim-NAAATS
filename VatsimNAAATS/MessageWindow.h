#pragma once
#include "pch.h"
#include "EuroScopePlugIn.h"
#include <string>
#include <map>
#include <gdiplus.h>
#include "BaseWindow.h"

using namespace std;
using namespace Gdiplus;
using namespace EuroScopePlugIn;

class CMessageWindow : public CBaseWindow
{
	public:
		// Inherited methods
		CMessageWindow(POINT topLeft);
		virtual void RenderWindow(CDC* dc, Graphics* g, CRadarScreen* screen);
		virtual void MakeWindowItems();
		virtual void ButtonDown(int id);
		virtual void ButtonUp(int id);
		virtual void ButtonPress(int id);
		virtual void ButtonUnpress(int id);
		virtual void SetButtonState(int id, CInputState state);

		// Button definitions
		static const int BTN_CLOSE;
};

