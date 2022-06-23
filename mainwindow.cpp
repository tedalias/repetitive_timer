#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  mUi(new Ui::MainWindow)
{
  mUi->setupUi(this);

  mUi->mTimeSpinBox->setRange(1, 1000);
  mUi->mTimeSpinBox->setValue(30);
  updateTimerMinutes();

  createTrayIcon();

  connect(mUi->buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::okClickedSlot);
  connect(mUi->buttonBox, &QDialogButtonBox::rejected, this, &MainWindow::close);

  connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimeout);

  stopTimer();

  mTrayIcon->show();
  mMessageIcon->show();
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
  mUi->mStatusLabel->setText("Running");
}

void MainWindow::stopTimer()
{
  mTimer.stop();
  mUi->mStatusLabel->setText("Idle");
}

void MainWindow::updateTimerMinutes()
{
  if(mUi->mTimeSpinBox->value() != mTimerMinutes)
  {
    mTimerMinutes = mUi->mTimeSpinBox->value();
    mTimer.setInterval(mTimerMinutes * 60 * 1000);
    if(mTimer.isActive())
    {
      startTimer();
    }
  }
}

void MainWindow::onTimeout()
{
  mMessageIcon->showMessage("Timeout!", QString("%1 minutes have passed. Time to take a break.").arg(mTimerMinutes));
}

void MainWindow::createTrayIcon()
{
  mTrayIcon = new QSystemTrayIcon(this);
  mTrayIcon->setIcon(QIcon(":/icons/timer_icon.png"));

  mMessageIcon = new QSystemTrayIcon(this);
  mMessageIcon->setIcon(QIcon(":/icons/timer_icon.png"));

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
