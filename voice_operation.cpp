#include "voice_operation.h"
#include <QTextToSpeech>


void voice_operation::WordsToSay()
{


    QTextToSpeech *tts_speak = new QTextToSpeech;
    tts_speak->setLocale(QLocale::Chinese);
    tts_speak->setVolume(20);

    if(tts_speak->state() == QTextToSpeech::Ready)
    {
        tts_speak->say("学生成绩管理系统是整个学校工作系统的重要组成部分，"
                       "其内容对于学校管理者和学生至关重要，"
                       "所以学生成绩管理系统应该为用户提供所需要的信息以及方便的管理平台。"
                       "现代成绩查询系统理论已经不拘泥于传统的理论基础，"
                       "不强调对教学活动的严密控制，放弃了繁琐的设计模式，"
                       "开始注重教学设计的关系性和灵活性，并且提供人性化的服务，"
                       "这些优点能够极大的提高学生成绩查询的效率，"
                       "从而更加有利于学生的管理和提高学生的主动性");
    }
}
