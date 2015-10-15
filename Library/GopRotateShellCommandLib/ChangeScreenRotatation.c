/* ChangeScreenRotation.c
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
#include <ShellBase.h>
#include <Library/ShellLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/HandleParsingLib.h>
#include <Library/BaseLib.h>
#include <Protocol/GopRotate.h>

/// The Handle that the Hii String database is assocaited with
extern EFI_HANDLE gGopRotateShellCommandHiiHandle;

STATIC CONST SHELL_PARAM_ITEM ParamList[] = {
  {NULL, TypeMax}
  };


/**
 *      Function executed when the rotate command is entered
 *
 *      @param  ImageHandle     Pointer to the Image handle of this driver
 *      @param  SystemTable     Pointer to the EFI_SYSTEM_TABLE
 *
 *      @retval EFI_SUCCESS     Command always returns success
 **/
SHELL_STATUS EFIAPI ShellCommandRotate(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    LIST_ENTRY *Package;
    CHAR16 *ProblemParam;
    CONST CHAR16 *Temp;
    UINT64 Rotate = (UINTN)-1;
    UINT64 HandleNumber = (UINT64)(-1);
    GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL *GopRotate = NULL;
    EFI_HANDLE Handle = NULL;

    Status = ShellCommandLineParse(ParamList, &Package, &ProblemParam, TRUE);
    if(EFI_ERROR(Status))
    {
        Print(L"Problem Param! %s\n", ProblemParam);
        gBS->FreePool(ProblemParam);
        return SHELL_INVALID_PARAMETER;
    }

    if(ShellCommandLineGetCount(Package) == 1)
    {
        ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN(STR_GEN_TOO_FEW), gGopRotateShellCommandHiiHandle, L"rotate");  
        return SHELL_INVALID_PARAMETER;
    }

    if(ShellCommandLineGetCount(Package) > 3) 
    {
        ShellPrintHiiEx(-1, -1, NULL, STRING_TOKEN(STR_GEN_TOO_MANY), gGopRotateShellCommandHiiHandle, L"rotate");  
        return SHELL_INVALID_PARAMETER;
    }

    Temp = ShellCommandLineGetRawValue(Package, 1);
    if(Temp != NULL) 
    {
        Status = ShellConvertStringToUint64(Temp, &HandleNumber, TRUE, TRUE);
    }

    Temp = ShellCommandLineGetRawValue(Package, 2);
    if(Temp != NULL) 
    {
        Status = ShellConvertStringToUint64(Temp, &Rotate, TRUE, TRUE);
    }

    Handle = ConvertHandleIndexToHandle((UINTN)HandleNumber);

    Status = gBS->HandleProtocol(Handle, &gGraphicsOutputProtocolRotateProtocolGuid, &GopRotate);
    if(EFI_ERROR(Status))
    {
        Print(L"No Gop Rotate Protocol found on device\n");
    }
    else
    {
        switch(Rotate)
        {
            case 0:
                GopRotate->SetRotation(GopRotate, Rotate0);
                break;
            
            case 0x90:
                GopRotate->SetRotation(GopRotate, Rotate90);
                break;

            case 0x180:
                GopRotate->SetRotation(GopRotate, Rotate180);
                break;

            case 0x270:
                GopRotate->SetRotation(GopRotate, Rotate270);
                break;

            default:
                Print(L"Invalid paramter \"%s\" for rotate angle\n", Temp);
                Print(L"Expected: 0, 90, 180 or 270\n");
                break;
        }
    }
    return EFI_SUCCESS;
}