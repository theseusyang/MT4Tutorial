/* Copyright (c) 2005, Regents of Massachusetts Institute of Technology, 
 * Brandeis University, Brown University, and University of Massachusetts 
 * Boston. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *   - Neither the name of Massachusetts Institute of Technology, 
 *     Brandeis University, Brown University, or University of 
 *     Massachusetts Boston nor the names of its contributors may be used 
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef DICT2INT_H
#define DICT2INT_H

#include "../common/Constants.h"
#include "../common/Interfaces.h"
#include "../Wrappers/Decoder/DictMultiDecoder.h"
#include "../Wrappers/IntDataSource.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

class Block;

// Abstract class for implementaion of an Operator
class Dict2Int : public Operator {
 public:
  	Dict2Int(Operator *inOp_, int inColIndex_,AM* tableAM);
  	// destructor
  	~Dict2Int();

  	// Gets the next value block from the operator 
  	Block* getNextValBlock(int colIndex_);	
  
	// Gets the next position block (bitstring of positions) from the operator
	PosBlock* getNextPosBlock(int colIndex_);
	
	inline virtual int getLastPosition() { throw UnimplementedException("Not done for Dict2Int"); };

	void generateDictTable(AM* tableAM);
  
 private:
 	//Block* rb;
	BasicBlock* bb1;
	BasicBlock* bb2;
	//Block* mb3;
	//int* pageToDecode;
	unsigned int* dict;
	int currpos;
	Operator *m_input;
	int m_ColIndex;   
	//Operator *m_input2;
	//int m_ColIndex2;
	//int fieldSize;
	IntValPos* ivp;
  
};

#endif // DICT2INT
