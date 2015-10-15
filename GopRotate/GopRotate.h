/* GopRotate.h
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

#define GRAPHICS_OUTPUT_ROTATE_DEV_SIGNATURE  SIGNATURE_32('g', 'o', 'r', 'p')  
typedef struct 
{
    UINTN                                       Signature;  ///< Signature of the Private structure
    EFI_HANDLE                                  Handle;     ///< Handle of the device being managed
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT            Blt;        ///< Pointer to the original Blt function
    EFI_GRAPHICS_OUTPUT_PROTOCOL                *Gop;       ///< Pointer to the Graphics Output Protocol
    GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL    GopRotate;  ///< Pointer to the Gop Rotate Protocol
    ROTATE_SCREEN                               Rotation;   ///< Internal tracking of the current screen rotation
} GRAPHICS_OUTPUT_ROTATE_PRIVATE;

#define GRAPHICS_OUTPUT_ROTATE_PRIVATE_FROM_GOP_ROTATE(a)\
  CR(a, GRAPHICS_OUTPUT_ROTATE_PRIVATE, GopRotate, GRAPHICS_OUTPUT_ROTATE_DEV_SIGNATURE)


EFI_STATUS EFIAPI GopRotateGetRotation(GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL *This, ROTATE_SCREEN *Rotation);
EFI_STATUS EFIAPI GopRotateSetRotation(GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL *This, ROTATE_SCREEN Rotation);


EFI_STATUS EFIAPI BltRotate 
(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL        *This,
    IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer,     OPTIONAL
    IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION   BltOperation,
    IN  UINTN                               SourceX,
    IN  UINTN                               SourceY,
    IN  UINTN                               DestinationX,
    IN  UINTN                               DestinationY,
    IN  UINTN                               Width,
    IN  UINTN                               Height,
    IN  UINTN                               Delta           OPTIONAL
);

typedef struct 
{
    LIST_ENTRY Link;  
    GRAPHICS_OUTPUT_ROTATE_PRIVATE *Private;
} GOP_DEVICE_LIST;


GRAPHICS_OUTPUT_ROTATE_PRIVATE *GetPrivateFromGopRotate(GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL *GopRotate);