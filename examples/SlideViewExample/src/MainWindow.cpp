/**
MIT License

Copyright (c) 2020 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MainWindow.h"
#include "SSlideView.h"
#include <QBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QLabel>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *toolBar = new QToolBar(this);
	auto *labTitle(new QLabel(this));
	auto *slideView(new SSlideView(this));
	auto *actBack = new QAction(tr("<"), this);
	auto *actNext = new QAction(tr(">"), this);

	connect(actNext, &QAction::triggered, slideView, &SSlideView::gotoNextPage);
	connect(actBack, &QAction::triggered, slideView, &SSlideView::gotoPreviousPage);

	connect(slideView, &SSlideView::currentIndexChanged,
			[this, slideView, labTitle, actBack, actNext](){
		enableButtons(slideView, actBack, actNext);
		labTitle->setText(slideView->currentPage()->windowTitle());
	});

	connect(slideView, &SSlideView::pageCountChanged,
			[this, slideView, actBack, actNext](){
		enableButtons(slideView, actBack, actNext);
	});

	slideView->appendPage(createLabel(tr("First Page")));
	slideView->appendPage(createLabel(tr("Second Page")));

	toolBar->addAction(actBack);
	toolBar->addWidget(createStretch());
	toolBar->addWidget(labTitle);
	toolBar->addWidget(createStretch());
	toolBar->addAction(actNext);
	toolBar->setMovable(false);

	setWindowTitle(tr("SlideView Example"));
	addToolBar(toolBar);
	setCentralWidget(slideView);
	resize(320, 480);
}

QWidget *MainWindow::createLabel(const QString &title)
{
	auto *label = new QLabel(title + "\n\n"
							 + "Lorem ipsum dolor sit amet, consetetur sadipscing"
							   " elitr, sed diam nonumy eirmod tempor invidunt ut"
							   " labore et dolore magna aliquyam erat, sed diam"
							   " voluptua. At vero eos et accusam et justo duo"
							   " dolores et ea rebum. Stet clita kasd gubergren,"
							   " no sea takimata sanctus est Lorem ipsum dolor"
							   " sit amet. Lorem ipsum dolor sit amet, consetetur"
							   " sadipscing elitr, sed diam nonumy eirmod tempor"
							   " invidunt ut labore et dolore magna aliquyam erat,"
							   " sed diam voluptua. At vero eos et accusam et"
							   " justo duo dolores et ea rebum. Stet clita kasd"
							   " gubergren, no sea takimata sanctus est Lorem"
							   " ipsum dolor sit amet.", this);

	label->setWordWrap(true);
	label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	label->setWindowTitle(title);
	label->setMargin(20);

	return label;
}

QWidget *MainWindow::createStretch()
{
	auto *stretch = new QWidget(this);

	stretch->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

	return stretch;
}

void MainWindow::enableButtons(SSlideView *slideView, QAction *actPrevious,
							   QAction *actNext)
{
	int currentIndex = slideView->currentIndex();

	actPrevious->setEnabled(currentIndex > 0);
	actNext->setEnabled(currentIndex < slideView->pageCount() - 1);
}
