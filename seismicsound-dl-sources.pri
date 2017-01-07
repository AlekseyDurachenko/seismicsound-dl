INCLUDEPATH    +=                                                   \
    $$PWD/src                                                       \

HEADERS        +=                                                   \
    $$PWD/src/appargumentconsts.h                                   \
    $$PWD/src/appargument.h                                         \
    $$PWD/src/apparguments.h                                        \
    $$PWD/src/consts.h                                              \
    $$PWD/src/dataselect.h                                          \
    $$PWD/src/dataselectquery.h                                     \
    $$PWD/src/debug.h                                               \
    $$PWD/src/downloaddatabyevent.h                                 \
    $$PWD/src/downloaddatabytime.h                                  \
    $$PWD/src/event.h                                               \
    $$PWD/src/eventlistdownload.h                                   \
    $$PWD/src/eventlistprint.h                                      \
    $$PWD/src/eventquery.h                                          \
    $$PWD/src/fdsnwslist.h                                          \
    $$PWD/src/filenameconflictaction.h                              \
    $$PWD/src/info.h                                                \
    $$PWD/src/miniseedutils.h                                       \
    $$PWD/src/resources.h                                           \
    $$PWD/src/soundtags.h                                           \
    $$PWD/src/stationlistdownload.h                                 \
    $$PWD/src/stationlistprint.h                                    \
    $$PWD/src/stationquery.h                                        \
    $$PWD/src/trace.h                                               \
    $$PWD/src/urldownloader.h                                       \
    $$PWD/src/usage.h                                               \
    $$PWD/src/version.h                                             \
    $$PWD/src/xmlutils.h                                            \

SOURCES        +=                                                   \
    $$PWD/src/appargument.cpp                                       \
    $$PWD/src/apparguments.cpp                                      \
    $$PWD/src/dataselect.cpp                                        \
    $$PWD/src/dataselectquery.cpp                                   \
    $$PWD/src/debug.cpp                                             \
    $$PWD/src/downloaddatabyevent.cpp                               \
    $$PWD/src/downloaddatabytime.cpp                                \
    $$PWD/src/event.cpp                                             \
    $$PWD/src/eventlistdownload.cpp                                 \
    $$PWD/src/eventlistprint.cpp                                    \
    $$PWD/src/eventquery.cpp                                        \
    $$PWD/src/fdsnwslist.cpp                                        \
    $$PWD/src/info.cpp                                              \
    $$PWD/src/miniseedutils.cpp                                     \
    $$PWD/src/resources.cpp                                         \
    $$PWD/src/soundtags.cpp                                         \
    $$PWD/src/stationlistdownload.cpp                               \
    $$PWD/src/stationlistprint.cpp                                  \
    $$PWD/src/stationquery.cpp                                      \
    $$PWD/src/trace.cpp                                             \
    $$PWD/src/urldownloader.cpp                                     \
    $$PWD/src/usage.cpp                                             \
    $$PWD/src/version.cpp                                           \
    $$PWD/src/xmlutils.cpp                                          \

FORMS          +=                                                   \

TRANSLATIONS   +=                                                   \
    $$PWD/translations/ru.ts                                        \

RESOURCES      +=                                                   \
    $$PWD/qrc/usage.qrc                                             \

OTHER_FILES    +=                                                   \
    $$PWD/ABOUT                                                     \
    $$PWD/AUTHORS                                                   \
    $$PWD/CHANGELOG                                                 \
    $$PWD/LIBRARIES                                                 \
    $$PWD/LICENSE                                                   \
    $$PWD/LICENSE.GPL-3+                                            \
    $$PWD/README.md                                                 \

!contains(QT, testlib) {
    HEADERS   +=                                                    \

    SOURCES   +=                                                    \
        $$PWD/src/main.cpp                                          \

}

win32 {
    RC_FILE     += res/windows/rc.rc
}
