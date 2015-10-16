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
#ifndef __GRAPHICS_OUTPUT_ROTATE_H__
#define __GRAPHICS_OUTPUT_ROTATE_H__

#define GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL_GUID \
    { 0xda62085c, 0x96e4, 0x4345, { 0xa3, 0xb0, 0x98, 0x89, 0xda, 0xf3, 0x16, 0xb7 } }

typedef enum 
{
    Rotate0 = 0,
    Rotate90 = 1,
    Rotate180 = 2,
    Rotate270 = 3
} ROTATE_SCREEN;

typedef struct _GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *GRAPHICS_OUTPUT_PROTOCOL_ROTATE_GET_ROTATION)(
  IN  GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL  *This,
  IN  ROTATE_SCREEN                             *Rotation
  );

typedef
EFI_STATUS
(EFIAPI *GRAPHICS_OUTPUT_PROTOCOL_ROTATE_SET_ROTATION)(
  IN  GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL  *This,
  IN  ROTATE_SCREEN                             Rotation
  );

struct _GRAPHICS_OUTPUT_PROTOCOL_ROTATE_PROTOCOL
{
    GRAPHICS_OUTPUT_PROTOCOL_ROTATE_GET_ROTATION GetRotation;
    GRAPHICS_OUTPUT_PROTOCOL_ROTATE_SET_ROTATION SetRotation;
};


extern EFI_GUID gGraphicsOutputProtocolRotateProtocolGuid;
#endif

