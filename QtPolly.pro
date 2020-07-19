TEMPLATE = subdirs

SUBDIRS += \
    TestApplication \
    QtAws

TestApplication.depends = QtAws
