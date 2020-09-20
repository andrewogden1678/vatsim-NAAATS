#include "pch.h"
#include "Styles.h"
#include "AcTargets.h"
#include <map>

using namespace Colours;

void CAcTargets::DrawAirplane(Graphics* g, CDC* dc, CRadarScreen* screen, CRadarTarget* target, int hdg) {
	// Get the aircraft's position and heading
	POINT acPoint = screen->ConvertCoordFromPositionToPixel(target->GetPosition().GetPosition());

	// Save context for later
	int sDC = dc->SaveDC();

	// Define a brush and a container for the target
	SolidBrush brush(Colours::TargetOrange);
	GraphicsContainer gContainer;	

	// Begin drawing
	gContainer = g->BeginContainer();
	
	// Draw the altitude
	FontSelector::SelectMonoFont(12, dc);
	dc->SetTextColor(TargetOrange.ToCOLORREF());
	dc->SetTextAlign(TA_CENTER);
	string line;
	if (screen->GetPlugIn()->FlightPlanSelect(target->GetCallsign()).GetClearedAltitude() != 0) {
		line = to_string(screen->GetPlugIn()->FlightPlanSelect(target->GetCallsign()).GetClearedAltitude() / 1000);
	}
	else {
		line = to_string(screen->GetPlugIn()->FlightPlanSelect(target->GetCallsign()).GetFinalAltitude() / 1000);
	}
	
	dc->TextOutA(acPoint.x, acPoint.y - 25, line.c_str());

	// Rotate the graphics object and set the middle to the aircraft position
	g->RotateTransform(hdg);
	g->TranslateTransform(acPoint.x, acPoint.y, MatrixOrderAppend);

	// This is the icon
	Point points[19] = {
		Point(0,-8),
		Point(-1,-7),
		Point(-1,-2),
		Point(-8,3),
		Point(-8,4),
		Point(-1,2),
		Point(-1,7),
		Point(-4,9),
		Point(-4,10),
		Point(0,9),
		Point(4,10),
		Point(4,9),
		Point(1,7),
		Point(1,2),
		Point(8,4),
		Point(8,3),
		Point(1,-2),
		Point(1,-7),
		Point(0,-8)
	};

	// Fill the polygon and finish
	g->FillPolygon(&brush, points, 19);
	g->EndContainer(gContainer);

	// Restore context
	dc->RestoreDC(sDC);

	// Deallocate
	DeleteObject(&brush);
	DeleteObject(&points);
	DeleteObject(&gContainer);
	DeleteObject(&acPoint);
}

POINT CAcTargets::DrawTag(CDC* dc, CRadarScreen* screen, CRadarTarget* target, pair<bool, POINT>* tagPosition) {
	// Get the aircraft's position and flight plan
	POINT acPoint = screen->ConvertCoordFromPositionToPixel(target->GetPosition().GetPosition());
	CFlightPlan acFP = screen->GetPlugIn()->FlightPlanSelect(target->GetCallsign());

	// Save context for later
	int sDC = dc->SaveDC();

	// Tag rectangle
	CRect tagRect;
	int tagOffsetX = tagPosition->second.x;
	int tagOffsetY = tagPosition->second.y;
	if (tagOffsetX == 0 && tagOffsetY == 0) { // default point, we need to set it
		if (tagPosition->first == true) {
			// Detailed
			tagRect = CRect(acPoint.x  - 50, acPoint.y - 86, acPoint.x + 30, acPoint.y - 30);
		}
		else {
			// Not detailed
			tagRect = CRect(acPoint.x - 50, acPoint.y - 65, acPoint.x + 30, acPoint.y - 35);
		}
	}
	else {
		if (tagPosition->first == true) {
			// Detailed
			tagRect = CRect(acPoint.x + tagOffsetX, acPoint.y + tagOffsetY, (acPoint.x + tagOffsetX) + 80, (acPoint.y + tagOffsetY) + 56);
		}
		else {
			// Not Detailed
			tagRect = CRect(acPoint.x + tagOffsetX, acPoint.y + tagOffsetY, (acPoint.x + tagOffsetX) + 80, (acPoint.y + tagOffsetY) + 30);
		}
	}
	
	dc->Draw3dRect(tagRect, TextWhite.ToCOLORREF(), TextWhite.ToCOLORREF());
	// Pick atc font for callsign
	// TODO: colour change based on status
	FontSelector::SelectATCFont(16, dc);
	dc->SetTextColor(TargetOrange.ToCOLORREF());
	dc->SetTextAlign(TA_LEFT);
	string text;

	// Offsets
	int offsetX = 0;
	int offsetY = 0;

	// Callsign
	text = acFP.GetCallsign();
	dc->TextOutA(tagRect.left, tagRect.top, text.c_str());
	offsetY += 15;

	// Flight level
	FontSelector::SelectMonoFont(12, dc);
	text = to_string(target->GetPosition().GetFlightLevel() / 100);
	dc->TextOutA(tagRect.left, tagRect.top + offsetY, text.c_str());
	offsetX += 50;

	// Mach
	text = "M" + to_string(acFP.GetFlightPlanData().PerformanceGetMach(target->GetPosition().GetPressureAltitude(), target->GetVerticalSpeed()));
	dc->TextOutA(tagRect.left + offsetX, tagRect.top + offsetY, text.c_str());
	offsetX = 0;
	offsetY += 25;

	if (tagPosition->first == true) {
		// Aircraft type
		text = acFP.GetFlightPlanData().GetAircraftFPType();
		dc->TextOutA(tagRect.left + offsetX, tagRect.top + offsetY, text.c_str());
		offsetX += 50;

		// Destination
		text = acFP.GetFlightPlanData().GetDestination();
		dc->TextOutA(tagRect.left + offsetX, tagRect.top + offsetY, text.c_str());
	}
	
	// Tag line
	if (tagRect.right < acPoint.x) {
		dc->MoveTo({ tagRect.right, tagRect.top + 2 });
		dc->LineTo({ tagRect.right - (tagRect.right - acPoint.x), tagRect.top + 2 });
	}
	else {
		dc->MoveTo({ tagRect.left, tagRect.top + 2 });
		dc->LineTo({ tagRect.left - (tagRect.right - acPoint.x), tagRect.top + 2 });
	}

	// Create screen object
	screen->AddScreenObject(SCREEN_TAG, acFP.GetCallsign(), tagRect, true, acFP.GetPilotName());

	// Restore context
	dc->RestoreDC(sDC);

	return { tagRect.left, tagRect.top };
}

POINT CAcTargets::MoveTag(POINT oldPosition) {
	return { 0, 0 };
}