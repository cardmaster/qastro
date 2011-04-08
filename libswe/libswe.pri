INCLUDEPATH += $${PWD}/include

HEADERS *= $${PWD}/include/swedate.h \
           $${PWD}/include/swedll.h \
           $${PWD}/include/swehouse.h \
           $${PWD}/include/swejpl.h \
           $${PWD}/include/swenut2000a.h \
           $${PWD}/include/sweodef.h \
           $${PWD}/include/swepcalc.h \
           $${PWD}/include/sweph.h \
           $${PWD}/include/swephexp.h \
           $${PWD}/include/swephlib.h \
           $${PWD}/src/swemptab.c

SOURCES *= $${PWD}/src/swecl.c \
           $${PWD}/src/swedate.c \
           $${PWD}/src/swehel.c \
           $${PWD}/src/swehouse.c \
           $${PWD}/src/swejpl.c \
           $${PWD}/src/swemmoon.c \
           $${PWD}/src/swemplan.c \
           $${PWD}/src/swemptab.c \
           $${PWD}/src/swepcalc.c \
           $${PWD}/src/swepdate.c \
           $${PWD}/src/sweph.c \
           $${PWD}/src/swephlib.c 
