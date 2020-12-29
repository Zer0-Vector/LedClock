@SETLOCAL
@PUSHD %~dp0

@SET LIB_NAME=HexClock
@SET DEST=%OneDrive%\Documents\Arduino\libraries\%LIB_NAME%\
@MKDIR %DEST%

COPY ClockDisplay\*.* %DEST%

@POPD
@ENDLOCAL