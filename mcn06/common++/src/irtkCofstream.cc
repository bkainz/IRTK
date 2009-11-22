/*=========================================================================

  Library   : Image Registration Toolkit (IRTK)
  Module    : $Id$
  Copyright : Imperial College, Department of Computing
              Visual Information Processing (VIP), 2008 onwards
  Date      : $Date$
  Version   : $Revision$
  Changes   : $Author$

=========================================================================*/

#include <irtkCommon.h>

irtkCofstream::irtkCofstream()
{
#ifndef WORDS_BIGENDIAN
  _swapped = True;
#else
  _swapped = False;
#endif

#ifdef HAS_ZLIB
  _compressedFile = NULL;
#endif
  _uncompressedFile = NULL;
}

irtkCofstream::~irtkCofstream()
{
  this->Close();
}

void irtkCofstream::Write(char *data, int offset, int length)
{
  if (_compressed == False) {
    if (offset != -1) fseek(_uncompressedFile, offset, SEEK_SET);
    fwrite(data, length, 1, _uncompressedFile);
  } else {
#ifdef HAS_ZLIB
    if (offset != -1) {
      if (gztell(_compressedFile) > offset) {
        cerr << "Warning, writing compressed files only supports forward seek" << gztell(_compressedFile) << " " << offset << endl;
        exit(1);
      }
      gzseek(_compressedFile, offset, SEEK_SET);
    }
    gzwrite(_compressedFile, data, length);
#endif
  }
}

void irtkCofstream::WriteAsChar(char data, int offset)
{
  this->Write((char *)&data, offset, sizeof(char));
}

void irtkCofstream::WriteAsChar(char *data, int length, int offset)
{
  this->Write((char *)data, offset, length*sizeof(char));
}

void irtkCofstream::WriteAsUChar(unsigned char data, int offset)
{
  this->Write((char *)&data, offset, sizeof(unsigned char));
}

void irtkCofstream::WriteAsUChar(unsigned char *data, int length, int offset)
{
  this->Write((char *)data, offset, length*sizeof(unsigned char));
}

void irtkCofstream::WriteAsShort(short data, int offset)
{
  // Swap data
  if (_swapped == True) swap16((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(short));
}

void irtkCofstream::WriteAsShort(short *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap16((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(short));

  // Swap data (BACK)
  if (_swapped == True) swap16((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsUShort(unsigned short data, int offset)
{
  // Swap data
  if (_swapped == True) swap16((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(unsigned short));
}

void irtkCofstream::WriteAsUShort(unsigned short *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap16((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(unsigned short));

  // Swap data (BACK)
  if (_swapped == True) swap16((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsInt(int data, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(int));
}

void irtkCofstream::WriteAsInt(int *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(int));

  // Swap data (BACK)
  if (_swapped == True) swap32((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsUInt(unsigned int data, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(unsigned int));
}

void irtkCofstream::WriteAsUInt(unsigned int *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(unsigned int));

  // Swap data (BACK)
  if (_swapped == True) swap32((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsFloat(float data, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(float));
}

void irtkCofstream::WriteAsFloat(float *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap32((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(float));

  // Swap data (BACK)
  if (_swapped == True) swap32((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsDouble(double *data, int length, int offset)
{
  // Swap data
  if (_swapped == True) swap64((char *)data, (char *)data, length);

  this->Write((char *)data, offset, length*sizeof(double));

  // Swap data (BACK)
  if (_swapped == True) swap64((char *)data, (char *)data, length);
}

void irtkCofstream::WriteAsDouble(double data, int offset)
{
  // Swap data
  if (_swapped == True) swap64((char *)&data, (char *)&data, 1);

  this->Write((char *)&data, offset, sizeof(double));
}

void irtkCofstream::WriteAsString(char *data, int offset)
{
  if (_compressed == False) {
    if (offset!= -1) fseek(_uncompressedFile, offset, SEEK_SET);
    fputs(data, _uncompressedFile);
  } else {
#ifdef HAS_ZLIB
    if (offset != -1) gzseek(_compressedFile, offset, SEEK_SET);
    gzputs(_compressedFile, data);
#endif
  }
}
