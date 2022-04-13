/* GopRotateShellCommandLib.c
Copyright (c) 2015, Aaron Pop
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <Library/HiiLib.h>
#include <Library/ShellCommandLib.h>
#include <GopRotateShellCommandLib.h>

/// Human readable name of this library
static CHAR16 gGopRotateShellCommandFileName[] = L"GopRotateShellCommandLib";

/// HiiHandle assocaited with the string database for this library
EFI_HANDLE gGopRotateShellCommandHiiHandle = NULL;

/// EFI_GUID associated with this package
static EFI_GUID gGopRotateShellCommandGuid = { 0xc5cadaf0, 0x7730, 0x466c, { 0x91, 0xbe, 0x80, 0xff, 0x4d, 0x7d, 0x5d, 0x2b } };

/**
 *  Function that reutrns the library name assocaited with this command
 *  
 *  @retval CHAR16* Pointer to a unicode string that is the human readable name of this command library
 **/
CONST CHAR16* EFIAPI GopRotateShellCommandGetFileName(VOID)
{
    return (gGopRotateShellCommandFileName);
}

/**
 *  Libary constructor for this shell command library. Used to add to the shell the rotate command to support the GOP.
 *
 *      @param  ImageHandle     Pointer to the Image handle of this driver
 *      @param  SystemTable     Pointer to the EFI_SYSTEM_TABLE
 *
 *      @retval EFI_SUCCESS     Command always returns success
 **/
EFI_STATUS EFIAPI GopRotateShellCommandLibConstructor(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    gGopRotateShellCommandHiiHandle = HiiAddPackages (&gGopRotateShellCommandGuid, ImageHandle, GopRotateShellCommandLibStrings, NULL);
    if(gGopRotateShellCommandHiiHandle != NULL)
    {
        ShellCommandRegisterCommandName(L"rotate", ShellCommandRotate, GopRotateShellCommandGetFileName, 0, L"", FALSE, gGopRotateShellCommandHiiHandle, STRING_TOKEN(STR_GET_ROTATE_HELP));
    }
    return EFI_SUCCESS;
}

/**
 *  Libary destructor for this shell command library. Used free any allocated memory when unloading the shell
 *
 *      @param  ImageHandle     Pointer to the Image handle of this driver
 *      @param  SystemTable     Pointer to the EFI_SYSTEM_TABLE
 *
 *      @retval EFI_SUCCESS     Command always returns success
 **/
EFI_STATUS EFIAPI GopRotateShellCommandLibDestructor (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    if (gGopRotateShellCommandHiiHandle != NULL)
    {
        HiiRemovePackages(gGopRotateShellCommandHiiHandle);
    }
    return (EFI_SUCCESS);
}
