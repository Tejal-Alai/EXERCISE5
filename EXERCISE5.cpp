// EXERCISE5.cpp : Defines the initialization routines for the DLL.
//
#include "pch.h"
#include "framework.h"
#include "EXERCISE5.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Windows.h>
#include<arxHeaders.h>
#include <dbents.h>

void CEXERCISE5App::makeLayer()
{
	// Open the Layer table for read
	AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbLayerTable* pLayerTable;
	pDb->getLayerTable(pLayerTable, AcDb::kForRead);
	// Check to see if the layer exists
	if (pLayerTable->has(_T("OBJ")) == false)
	{
		// Open the Layer table for write
		pLayerTable->upgradeOpen();
		// Create the new layer and assign it the name 'OBJ'
		AcDbLayerTableRecord* pLayerTableRecord =
			new AcDbLayerTableRecord();
		pLayerTableRecord->setName(_T("OBJ"));
		// Set the color of the layer to cyan
		AcCmColor color;
		color.setColorIndex(4);
		pLayerTableRecord->setColor(color);
		// Add the new layer to the Layer table
		pLayerTable->add(pLayerTableRecord);
		// Close the Layer table and record
		pLayerTable->close();
		pLayerTableRecord->close();
	}
}
extern "C"
int acrxEntryPoint(AcRx::AppMsgCode Msg, void* pkt)
{
	switch (Msg) {
	case AcRx::kInitAppMsg:
		acrxUnlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		acutPrintf(L"\n Command Loaded");
		// below line for registering new command
		acedRegCmds->addCommand(L"AUCommands", _T("MAKELAYER"), _T("MAKELAYER"), ACRX_CMD_MODAL, &CEXERCISE5App::makeLayer);
		break;
	case AcRx::kUnloadAppMsg:
		acutPrintf(_T("\n Command Unloaded"));
		break;
	}
	return AcRx::kRetOK;
}

BEGIN_MESSAGE_MAP(CEXERCISE5App, CWinApp)
END_MESSAGE_MAP()

CEXERCISE5App::CEXERCISE5App()
{
}

CEXERCISE5App theApp;

BOOL CEXERCISE5App::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}