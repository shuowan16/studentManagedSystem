#ifndef VOICE_OPERATION_H
#define VOICE_OPERATION_H

#include <QObject>
#include <QtTextToSpeech>
#include <QThread>

class voice_operation:public QObject
{
    Q_OBJECT

public slots:
    void WordsToSay();   //播报语音

};

#endif // VOICE_OPERATION_H
