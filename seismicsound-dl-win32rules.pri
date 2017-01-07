# release rules
build_pass:CONFIG(release, debug|release):win32 {
    LIBS += -lsndfile
    CONFIG -=
    PKGCONFIG +=
}


# debug rules
build_pass:CONFIG(debug, debug|release):win32 {
    LIBS += -lsndfile
    CONFIG +=
    PKGCONFIG +=
}
