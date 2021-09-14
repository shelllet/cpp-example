;Include Modern UI

  !include "MUI2.nsh"
  !include "x64.nsh"

  Unicode true

;General
  !define VERSION "0.2.0"
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

  OutFile "..\wiki\content\history\_index.files\${APPNAME}-${VERSION}-setup.x64.exe"

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

    SetOutPath "$INSTDIR\assets"
    FILE ..\x64\Release\assets\*.*
    
    SetOutPath "$INSTDIR\libs"
    FILE ..\x64\Release\libs\*.*

    SetOutPath "$INSTDIR\setting"
    FILE ..\x64\Release\setting\*.*
 
    SetOutPath "$INSTDIR\languages"
    FILE ..\x64\Release\languages\*.*

    SetOutPath "$INSTDIR"
    File /r ..\x64\Release\*.dll
    File ..\x64\Release\*.exe
    File ..\x64\Release\*.bin
    File ..\x64\Release\icudtl.dat

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

SectionEnd


  ;Language strings
  ;LangString DESC_SecFiles ${LANG_ENGLISH} "basic component"
  LangString DESC_MAIN_SECFILES ${LANG_SIMPCHINESE} "主程序"

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${MAIN_FILES} $(DESC_MAIN_SECFILES)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END



;Uninstaller Section
Section Un.主程序

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

Section Un.脚本

  SetShellVarContext current

  RMDir /r "$PROGRAMFILES64\scripts"

SectionEnd

Function LaunchLink
  ExecShell "" "$INSTDIR\${APPNAME}.exe"
FunctionEnd

ShowInstDetails show

ShowUnInstDetails show