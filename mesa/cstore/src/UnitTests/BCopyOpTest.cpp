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
/**
 * BCopyOpTest:
 * SELECT l_shipdate, COUNT(*)
 * FROM lineitem
 * WHERE l_shipdate > D
 * GROUP BY l_shipdate
 *
 * Projections: (l_shipdate | l_shipdate)
 *
 * Strategy:
 * 1 - Compute bitmap corresponding to l_shipdate over L
 * 2 - Materialize over L and do one-pass aggregation
 * Author Miguel Ferreira (migfer@mit.edu)
 */
#include "BCopyOpTest.h"



BCopyOpTest::BCopyOpTest() {
}

BCopyOpTest::~BCopyOpTest() {
}

/* args isn't used here */
bool BCopyOpTest::run(Globals* g, const vector<string>& args) {
  if (g->build_tables) 
    system ("rm Query1DAT*");
  system ("rm BCopyOpTest.out");
  Log::writeToLog("BCopyOpTest", 10, "Query 1 starting...");
  bool success=true;
  
  if (g->build_tables) {
    Log::writeToLog("BCopyOpTest", 10, "Loading Column1...");
    string path=LINEITEM_TABLE_PATH;  // 
    //string path=RLE_EXTRACT_LOAD_AND_ACCESS_DATA_PATH;
    ColumnExtracter* ce = new ColumnExtracter(path, 1, g->force_rebuild);
    RLEEncoder* encoder=new RLEEncoder((Operator*) ce, 0, 8*PAGE_SIZE, (byte) INT_VALUE_TYPE, (short) 16, (unsigned int) 27, (unsigned int) 16);
    RLEDecoder* decoder=new RLEDecoder(true);
    PagePlacer* pagePlacer=new PagePlacer(encoder, decoder, 2, false);
    pagePlacer->placeColumn("Query1DATA", false, true);
    delete pagePlacer;
    delete ce;
    delete encoder;
    delete decoder;
  }
  Log::writeToLog("BCopyOpTest", 10, "Opening Column1...");
  StopWatch stopWatch;
  stopWatch.start();
  ROSAM* am1 = new ROSAM( "Query1DATA" , 2);
  Predicate* pred=new Predicate(Predicate::OP_GREATER_THAN);

  RLEDataSource* ds1=new RLEDataSource(am1,true);
  ds1->setPredicate(pred);
  ds1->changeRHSBinding(9000);
  // ds1->printColumn();
  
  BCopyOperator* bco = new BCopyOperator((Operator*) ds1, 0, 2);

  //Count* agg = new Count((Operator*) bco, 0, (Operator*) bco, 0);
  Sum* agg = new Sum((Operator*) bco, 0, (Operator*) bco, 1);

  Operator* srcs[1]={agg};
  int numCols[1]={2};
 
  
  BlockPrinter* bPrint=new BlockPrinter(srcs, numCols, 1, "BCopyOpTest.out");
  bPrint->printColumns();
  
  cout << "Query BCop took: " << stopWatch.stop() << " ms" <<  endl;
	
  //delete ds1;
  //delete am1;
  //if (BUILD_TABLES) 
  //  system ("rm BCopyOpTestDAT*");
  return success;	
}
