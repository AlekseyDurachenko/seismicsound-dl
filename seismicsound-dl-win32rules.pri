# release rules
build_pass:CONFIG(release, debug|release):win32 {
    # for bild with mxe only
    LIBS += -lsndfile -lFLAC -lvorbisenc -lvorbis -logg -lm
    CONFIG -=
    PKGCONFIG +=
}


# debug rules
build_pass:CONFIG(debug, debug|release):win32 {
    # for bild with mxe only
    LIBS += -lsndfile -lFLAC -lvorbisenc -lvorbis -logg -lm
    CONFIG +=
    PKGCONFIG +=
}
