unix {
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

    contains(DEFINES, APP_PORTABLE) {
        INSTALLS += target docs translations

        target.path = /
        docs.path   = /
        translations.path = /translations
    }

    !contains(DEFINES, APP_PORTABLE) {
        INSTALLS += target docs translations

        target.path         = /usr/bin/
        docs.path           = /usr/share/$${TARGET}/
        translations.path   = /usr/share/$${TARGET}/translations/

        # you should to determine the location of resources
        DEFINES += "APP_RESOURCES_PREFIX='/usr/share/$${TARGET}'"
    }
}
