;Include Modern UI

  !include "MUI2.nsh"
  !include "x64.nsh"

  Unicode true

;General
  !define VERSION "0.5.0"
  !define PRODUCT_NAME "shelllet ${VERSION}"
  !define APPNAME "shelllet"
  !define MUI_FOLDER "shelllet.com"
  !define COMPANYNAME "shelllet.com"
  !define HELPURL "http://shelllet.com"
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  !define MUI_FINISHPAGE_RUN "$INSTDIR\${APPNAME}.exe"
  !define MUI_FINISHPAGE_RUN_CHECKED
  !define MUI_FINISHPAGE_RUN_TEXT "运行${PRODUCT_NAME}"
  !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchLink"


  Name "${PRODUCT_NAME}"
  # Icon "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
  # UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\win-uninstall.ico"

  OutFile "${APPNAME}-${VERSION}-setup.x64.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES64\${MUI_FOLDER}"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Variables

  Var StartMenuFolder

;--------------------------------
;Interface Configuration
  !define MUI_ICON "..\favicon.ico"
  !define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall-nsis.ico"
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\nsis3-branding.bmp"
  !define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-branding.bmp"
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\nsis3-branding.bmp"
  !define MUI_ABORTWARNING

;Pages

  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${MUI_FOLDER}"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${MUI_FOLDER}"

  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_COMPONENTS
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM

  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH
;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "SimpChinese"

;--------------------------------
;Installer Sections

Section "安装文件" MAIN_FILES
    SetOutPath "$INSTDIR"
    ; Qt
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Core.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Gui.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Widgets.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Svg.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Qml.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\Qt5Network.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\libEGL.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\libGLESV2.dll
    File C:\Qt\5.13.0\msvc2017_64\bin\opengl32sw.dll

 	; vc runtime
	File "C:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\VC\Redist\MSVC\14.23.27820\vcredist_x64.exe"
	
    ; opencv
    File $%VCPKG_ROOT%\installed\x64-windows\bin\opencv_imgcodecs.dll
    File $%VCPKG_ROOT%\installed\x64-windows\bin\opencv_imgproc.dll
    File $%VCPKG_ROOT%\installed\x64-windows\bin\opencv_core.dll

    ; v8
    File C:\v8\v8\out.gn\x64.release\v8.dll
    File C:\v8\v8\out.gn\x64.release\v8_libbase.dll
    File C:\v8\v8\out.gn\x64.release\v8_libplatform.dll

	; tesseract
	File $%VCPKG_ROOT%\installed\x64-windows\bin\zlib1.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\webp.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\tiff.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\lzma.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\libpng16.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\leptonica-1.78.0.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\jpeg62.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\boost_date_time-vc142-mt-x64-1_70.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\boost_random-vc142-mt-x64-1_70.dll
	File $%VCPKG_ROOT%\installed\x64-windows\bin\boost_thread-vc142-mt-x64-1_70.dll
	
    File ..\bin\let.dll
    File ..\bin\shelllet.exe
    File ..\bin\let.exe
	; assets
	SetOutPath "$INSTDIR"
	File /r ..\assets
	File /r ..\..\let\assets
	
    SetOutPath "$INSTDIR\styles"
    File C:\Qt\5.13.0\msvc2017_64\plugins\styles\qwindowsvistastyle.dll
	
	SetOutPath "$INSTDIR\bearer"
    File C:\Qt\5.13.0\msvc2017_64\plugins\bearer\qgenericbearer.dll
	
	SetOutPath "$INSTDIR\iconengines"
    File C:\Qt\5.13.0\msvc2017_64\plugins\iconengines\qsvgicon.dll
	
    SetOutPath "$INSTDIR\platforms"
    File C:\Qt\5.13.0\msvc2017_64\plugins\platforms\qwindows.dll

    SetOutPath "$INSTDIR\translations"
    File C:\Qt\5.13.0\msvc2017_64\translations\qt_zh_TW.qm
    File C:\Qt\5.13.0\msvc2017_64\translations\qt_en.qm


    SetOutPath "$INSTDIR\imageformats"
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qwebp.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qwbmp.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qtiff.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qtga.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qsvg.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qjpeg.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qico.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qicns.dll
    File C:\Qt\5.13.0\msvc2017_64\plugins\imageformats\qgif.dll
	
    ;create desktop shortcut
    CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\${APPNAME}.exe" ""
   
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;create start-menu items
    CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
    CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\${APPNAME}.exe" "" "$INSTDIR\${APPNAME}.exe" 0

    !insertmacro MUI_STARTMENU_WRITE_END

    ;Store installation folder
    WriteRegStr HKCU "Software\${PRODUCT_NAME}" "" $INSTDIR
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayName" "${PRODUCT_NAME}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\Uninstall.exe$\" /S"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayIcon" "$\"$INSTDIR\${APPNAME}.exe$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "Publisher" "$\"${COMPANYNAME}$\""
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "HelpLink" "$\"${HELPURL}$\""
    
    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

	; Check VC Runtime
	ReadRegDWORD $0 HKLM SOFTWARE\WOW6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x64 Installed
	${If} $0 <> 1
		ExecWait '"$INSTDIR\vcredist_x64.exe" /q' 
	${EndIf}
	
SectionEnd


;Language strings
;LangString DESC_SecFiles ${LANG_ENGLISH} "basic component"
LangString DESC_MAIN_SECFILES ${LANG_SIMPCHINESE} "Main"

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${MAIN_FILES} $(DESC_MAIN_SECFILES)
!insertmacro MUI_FUNCTION_DESCRIPTION_END



;Uninstaller Section
Section Un.Main UnMain

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder

  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

  DeleteRegKey /ifempty HKCU "Software\${PRODUCT_NAME}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}"
SectionEnd

Function LaunchLink
  ExecShell "" "$INSTDIR\${APPNAME}.exe"
FunctionEnd

ShowInstDetails show

ShowUnInstDetails show


Function .onInit
  # set section 'test' as selected and read-only
  IntOp $0 ${SF_SELECTED} | ${SF_RO}
  SectionSetFlags ${MAIN_FILES} $0
FunctionEnd

Function un.onInit
  # set section 'test' as selected and read-only
  IntOp $0 ${SF_SELECTED} | ${SF_RO}
  SectionSetFlags ${UnMain} $0
FunctionEnd