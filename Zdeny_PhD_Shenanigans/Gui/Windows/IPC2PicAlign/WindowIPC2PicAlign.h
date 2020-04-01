#pragma once
#include "ui_WindowIPC2PicAlign.h"
#include "Core/globals.h"

class WindowIPC2PicAlign : public QMainWindow
{
	Q_OBJECT

public:
	WindowIPC2PicAlign(QWidget* parent, Globals* globals);

private:
	Ui::WindowIPC2PicAlign ui;
	Globals* globals;

private slots:
	void align();
	void alignXY();
	void flowMap();
	void features();
	void linearFlow();
	void constantFlow();
};