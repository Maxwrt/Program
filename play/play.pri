QT += core
CONFIG += c++11
CONFIG += plugin
CONFIG += debug_and_release


CONFIG(debug, debug|release){
      contains(TEMPLATE, app){
            win32 {
                DESTDIR = $$PWD/./bin/debug/
          }
       }
      contains(TEMPLATE, lib){
        DESTDIR = $$PWD/bin/debug/
       }
}else{
      contains(TEMPLATE, app){
        DESTDIR = $$PWD/./bin/release/
       }
      contains(TEMPLATE, lib){
        DESTDIR = $$PWD/./bin/release/
       }
}

