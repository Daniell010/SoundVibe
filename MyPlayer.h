#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QMediaPlayer>
#include <QWidget>

namespace Ui {
class MyPlayer;
}

class MyPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MyPlayer(QWidget *parent = nullptr);
    ~MyPlayer();

private slots:
    void on_button_back_clicked();
    void on_button_start_clicked();
    void on_button_next_clicked();

    void on_dial_valueChanged(int value);

    void on_button_random_clicked();

private:
    Ui::MyPlayer *ui;
    QMediaPlayer *mPlayer = nullptr;
    QString catalogMusic = "music/";
    quint32 trackNumber = 0;
    bool isRandom = false;

    QString getDataDir(QString catalog);
    bool getListMusics(QStringList &folders);
    quint16 getRandomNumber(quint16 lastNumber);
    bool getPathTrack(QString &path, QString &trackName);
};

#endif // MYPLAYER_H
