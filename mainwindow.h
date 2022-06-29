#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QTimer>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void quit();
  void okClickedSlot();
  void startTimer();
  void stopTimer();
  void onTimeout();
  void updateRemainingTimeCounter();

private:
  Ui::MainWindow *mUi;
  QSystemTrayIcon *mTrayIcon;
  QSystemTrayIcon *mMessageIcon;

  QTimer mTimer;
  QTimer mPollRemainingTimeTimer;
  int mTimerMinutes;
  bool mQuitRequested = false;

  void createTrayIcon();
  void updateTimerMinutes();

  void closeEvent(QCloseEvent* event) override;
};

#endif // MAINWINDOW_H
