#include "MyPlayer.h"
#include "ui_MyPlayer.h"
#include <QUrl>
#include <QDir>
#include <QStandardPaths>

MyPlayer::MyPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyPlayer)
{
    ui->setupUi(this);
    setFixedSize(700, 300);
    mPlayer = new QMediaPlayer();

    ui->horizontalSlider->setRange(0, 0);

    int defVolume = 50;
    mPlayer->setVolume(defVolume);

    connect(ui->horizontalSlider, &QSlider::sliderMoved, [&](int n)
    {
        mPlayer->setPosition(n);
    });

    connect(mPlayer, &QMediaPlayer::positionChanged, [&](int n)
    {
        ui->horizontalSlider->setValue(n);
    });
    connect(mPlayer, &QMediaPlayer::durationChanged, [&](int n)
    {
        ui->horizontalSlider->setRange(0, n);
    });

    connect(mPlayer, &QMediaPlayer::mediaChanged, [&]()
    {
        QString fileName = mPlayer->currentMedia().canonicalUrl().toLocalFile();
        QString trackName = QFileInfo(fileName).fileName();
    });

}

MyPlayer::~MyPlayer()
{
    delete ui;
    delete mPlayer;
}

void MyPlayer::on_button_back_clicked()
{
    trackNumber--;
    QString path, trackName;
    getPathTrack(path, trackName);
    mPlayer->setMedia(QUrl::fromLocalFile(path));
    ui->label_nameMusic->setText(trackName);
    mPlayer->play();
}

void MyPlayer::on_button_start_clicked()
{
    switch (mPlayer->state())
    {
    case QMediaPlayer::PlayingState :
        mPlayer->pause();
        ui->button_start->setIcon(QIcon(":/resources/play.png"));
        break;

    case QMediaPlayer::PausedState :
        mPlayer->play();
        ui->button_start->setIcon(QIcon(":/resources/stop.png"));
        break;

    case QMediaPlayer::StoppedState :
        QString path, trackName;
        getPathTrack(path, trackName);
        mPlayer->setMedia(QUrl::fromLocalFile(path));
        ui->label_nameMusic->setText(trackName);

        mPlayer->play();
        ui->button_start->setIcon(QIcon(":/resources/stop.png"));
        break;
    }
}

void MyPlayer::on_button_next_clicked()
{
    trackNumber++;
    QString path, trackName;
    getPathTrack(path, trackName);
    mPlayer->setMedia(QUrl::fromLocalFile(path));
    ui->label_nameMusic->setText(trackName);
    mPlayer->play();
}

QString MyPlayer::getDataDir(QString catalog)
{
    QString result;

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    dir.cdUp();
    result.append(dir.absolutePath());
    result.append(QDir::separator());
    result.append(catalog);

    return result;
}

bool MyPlayer::getPathTrack(QString &path, QString &trackName)
{
    QStringList folders;
    if (!getListMusics(folders))
    {
        return false;
    }
    if (isRandom)
    {
        auto rundomNumber = getRandomNumber(folders.size());
        trackName = folders.at(rundomNumber);
    }
    else
    {
        if (static_cast<quint16>(folders.size()) <= trackNumber)
        {
            trackNumber = 0;
        }
        trackName = folders.at(trackNumber);
    }
    path = getDataDir(catalogMusic + trackName);
    return true;
}

bool MyPlayer::getListMusics(QStringList &folders)
{
    QDir dir(getDataDir("music"));
    folders = dir.entryList(QStringList() << "*.mp3", QDir::Files);

    return !folders.isEmpty();
}

quint16 MyPlayer::getRandomNumber(quint16 lastNumber)
{
    std::srand(std::time(nullptr));

    return std::rand() % lastNumber;
}

void MyPlayer::on_dial_valueChanged(int value)
{
    mPlayer->setVolume(value);
}

void MyPlayer::on_button_random_clicked()
{
    isRandom = !isRandom;
}
