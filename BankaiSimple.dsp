# Microsoft Developer Studio Project File - Name="BankaiSimple" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BankaiSimple - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BankaiSimple.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BankaiSimple.mak" CFG="BankaiSimple - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BankaiSimple - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BankaiSimple - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BankaiSimple - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BankaiSimple - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SDL_image.lib SDL_mixer.lib SDL.lib OpenGL32.lib glu32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"lib"

!ENDIF 

# Begin Target

# Name "BankaiSimple - Win32 Release"
# Name "BankaiSimple - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\audio.cpp
# End Source File
# Begin Source File

SOURCE=.\src\audiosystem.cpp
# End Source File
# Begin Source File

SOURCE=.\src\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\src\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\entity.cpp
# End Source File
# Begin Source File

SOURCE=.\src\font.cpp
# End Source File
# Begin Source File

SOURCE=.\src\HiResTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\InputSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Joystick.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\src\md2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Mouse.cpp
# End Source File
# Begin Source File

SOURCE=.\src\object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\oglwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\src\simpengine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\terrain.cpp
# End Source File
# Begin Source File

SOURCE=.\src\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\tree.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\winmain.cpp
# End Source File
# Begin Source File

SOURCE=.\src\world.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\audio.h
# End Source File
# Begin Source File

SOURCE=.\src\audiosystem.h
# End Source File
# Begin Source File

SOURCE=.\src\camera.h
# End Source File
# Begin Source File

SOURCE=.\src\engine.h
# End Source File
# Begin Source File

SOURCE=.\src\entity.h
# End Source File
# Begin Source File

SOURCE=.\src\font.h
# End Source File
# Begin Source File

SOURCE=.\src\HiResTimer.h
# End Source File
# Begin Source File

SOURCE=.\src\InputSystem.h
# End Source File
# Begin Source File

SOURCE=.\src\Joystick.h
# End Source File
# Begin Source File

SOURCE=.\src\Keyboard.h
# End Source File
# Begin Source File

SOURCE=.\src\md2.h
# End Source File
# Begin Source File

SOURCE=.\src\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\src\object.h
# End Source File
# Begin Source File

SOURCE=.\src\oglwindow.h
# End Source File
# Begin Source File

SOURCE=.\src\simpengine.h
# End Source File
# Begin Source File

SOURCE=.\src\terrain.h
# End Source File
# Begin Source File

SOURCE=.\src\texture.h
# End Source File
# Begin Source File

SOURCE=.\src\tree.h
# End Source File
# Begin Source File

SOURCE=.\src\vector.h
# End Source File
# Begin Source File

SOURCE=.\src\world.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
