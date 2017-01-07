win32 {
    docs.files =                                                    \
        $$PWD/ABOUT                                                 \
        $$PWD/AUTHORS                                               \
        $$PWD/CHANGELOG                                             \
        $$PWD/LIBRARIES                                             \
        $$PWD/LICENSE                                               \
        $$PWD/LICENSE.GPL-3+                                        \
        $$PWD/translations/docs/*                                   \

    translations.files =                                            \
        $$PWD/translations/*.qm                                     \

    INSTALLS += target docs translations

    target.path = /
    docs.path   = /
    translations.path = /translations
}
