/* ScummVM - Scumm Interpreter
 * Copyright (C) 2005-2006 Neil Millstone
 * Copyright (C) 2006 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
 
#ifndef _RAMSAVE_H_
#define _RAMSAVE_H_

#include "system.h"
#include "savefile.h"

// SaveFileManager class

#define DS_MAX_SAVE_SIZE 150000

class DSSaveFile : public Common::SaveFile {
	int address;
	int ptr;
	bool ownsData;
	bool saveCompressed;

	struct SCUMMSave {
		u32 magic;
		bool isValid;
		bool pad;
		char name[16];
		u32 size;
		u32 compressedSize;
		u16 pad2;
		u32 reserved;
	} __attribute__ ((packed));
	
	SCUMMSave save;
	u8* saveData;
	SCUMMSave* origHeader;
	bool isOpenFlag;
	bool isTempFile;
	
public:
	DSSaveFile();
	DSSaveFile(SCUMMSave* s, bool saveCompressed, u8* data);
	~DSSaveFile();
	
	void reset();
	
	bool isOpen() const { return isOpenFlag; }
	virtual bool eos() const;
	virtual void skip(uint32 size);
	
	virtual uint32 pos() const;
	virtual uint32 size() const;
	virtual void seek(int32 pos, int whence);

	uint32 read(void *buf, uint32 size);
	uint32 write(const void *buf, uint32 size);
	
	void setName(char *name);
	char* getName() { return save.name; }
	
	bool isValid() { return save.isValid; }
	bool isTemp() { return isTempFile; }
	bool matches(char* prefix, int num);
	bool matches(char* filename);
	
	void clearData();
	void compress();
	
	int getRamUsage() { return sizeof(save) + save.compressedSize; }
	char* getRamImage() { return (char *) &save; }
	
	int getSize() { return save.size; }
	
	DSSaveFile* clone();
	
	bool loadFromSaveRAM(vu8* address);
	int saveToSaveRAM(vu8* address);
	
	
	void deleteFile();
	
	void operator delete(void *p) {
//		consolePrintf("Finished! size=%d\n", ((DSSaveFile *) (p))->save->size);
	}



};



class DSSaveFileManager : public Common::SaveFileManager {
	
	DSSaveFile gbaSave[8];
	static DSSaveFileManager* instancePtr;
	int sramBytesFree;
	
public:
	DSSaveFileManager();
	~DSSaveFileManager();
	
	static DSSaveFileManager* instance() { return instancePtr; }

	Common::SaveFile *openSavefile(const char *filename, bool saveOrLoad);
	
	virtual Common::OutSaveFile* openForSaving(const char* filename) { return openSavefile(filename, true); }
	virtual Common::InSaveFile* openForLoading(const char* filename) { return openSavefile(filename, false); }
	
	
	void listSavefiles(const char *prefix, bool *marks, int num);
	
	void flushToSaveRAM();
	
	void addBytesFree(int size) { sramBytesFree += size; }
	int getBytesFree() { return sramBytesFree; }

	void deleteFile(char* name);
	void listFiles();
	void formatSram();
	
	void loadAllFromSRAM();

protected:
	Common::SaveFile *makeSaveFile(const char *filename, bool saveOrLoad);
};

#endif
