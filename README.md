# UefiGopRotate
A EDK2 Package that supplies a UEFI driver that will bind on top of Graphics Output Devices and rotate any Blt operations by 0, 90, 180 or 270 degrees.

# Adding the GopRotate Dxe driver
Add the package to your EDK2 tree (to the GopRotate directory).  In your project's DSC, add the line
"GopRotatePkg/GopRotate/GopRotate.inf" under the components sectino.  In your projects FDF, add the line "INF GopRotatePkg/GopRotate/GopRotate.inf" 

# Adding the GopRotateShellCommandLib
In the project's DSC file, find the reference to the Shell.inf, and add to the &lt;LibraryClasses&gt; section the GopRotateShellCommandLib.inf. 

```
  ShellPkg/Application/Shell/Shell.inf {
    <LibraryClasses>
      NULL|ShellPkg/Library/UefiShellLevel2CommandsLib/UefiShellLevel2CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel1CommandsLib/UefiShellLevel1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel3CommandsLib/UefiShellLevel3CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDriver1CommandsLib/UefiShellDriver1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellInstall1CommandsLib/UefiShellInstall1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDebug1CommandsLib/UefiShellDebug1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellNetwork1CommandsLib/UefiShellNetwork1CommandsLib.inf
      NULL|ShellPkg/Library/UefiDpLib/UefiDpLib.inf
      NULL|GopRotatePkg/Library/GopRotateShellCommandLib/GopRotateShellCommandLib.inf
  }
  ```
  
  # Notes
  This was developed using EDK2 tree svn revision 18624, 10-16-2015 through the NT32 project. 
