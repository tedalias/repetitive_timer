#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  mUi(new Ui::MainWindow)
{
  mUi->setupUi(this);

  mUi->mTimeSpinBox->setRange(1, 1000);
  mUi->mTimeSpinBox->setValue(1);
  updateTimerMinutes();

  createTrayIcon();
  mTrayIcon->show();

  connect(mUi->buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::okClickedSlot);
  connect(mUi->buttonBox, &QDialogButtonBox::rejected, this, &MainWindow::close);

  connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimeout);
}

MainWindow::~MainWindow()
{
  delete mUi;
  delete mTrayIcon;
}

void MainWindow::quit()
{
  mQuitRequested = true;
  close();
}

void MainWindow::okClickedSlot()
{
  updateTimerMinutes();
  close();
}

void MainWindow::startTimer()
{
  mTimer.start();
}

void MainWindow::stopTimer()
{
  mTimer.stop();
}

void MainWindow::updateTimerMinutes()
{
  if(mUi->mTimeSpinBox->value() != mTimerMinutes)
  {
    mTimerMinutes = mUi->mTimeSpinBox->value();
    mTimer.setInterval(mTimerMinutes * 1000); // TODO set back to minutes
    if(mTimer.isActive())
    {
      startTimer();
    }
  }
}

void MainWindow::onTimeout()
{
  std::cout << "Timeout" << std::endl;
}

void MainWindow::createTrayIcon()
{
  mTrayIcon = new QSystemTrayIcon(this);
  mTrayIcon->setIcon(QIcon(":/icons/timer_icon.png"));
  mTrayIcon->setVisible(true);

  QMenu* trayMenu = new QMenu(this);;
  trayMenu->addAction("&Settings", this, SLOT(show()));
  trayMenu->addSeparator();
  trayMenu->addAction("&Start", this, SLOT(startTimer()));
  trayMenu->addAction("&Stop", this, SLOT(stopTimer()));
  trayMenu->addSeparator();
  trayMenu->addAction("&Exit", this, SLOT(quit()));
  mTrayIcon->setContextMenu(trayMenu);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if(!mQuitRequested)
  {
    hide();
    event->ignore();
  }
  else
  {
    QMainWindow::closeEvent(event);
  }
}
