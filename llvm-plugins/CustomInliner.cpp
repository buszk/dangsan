/*
 * CustomInliner.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: haller
 */

#include <llvm/Transforms/IPO/Inliner.h>
#include <llvm/Analysis/InlineCost.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#include <metadata.h>

using namespace llvm;

struct CustomInliner : public LegacyInlinerBase{
    static char ID;

    CustomInliner() : LegacyInlinerBase(ID) {}

    InlineCost getInlineCost(CallSite CS) {
        Function *Callee = CS.getCalledFunction();
    std::string name = Callee->getName();
	const char *func_name = name.c_str();
        if (Callee && ISMETADATAFUNC(func_name) && strncmp(func_name, "dang_", 5)) {
            return InlineCost::getAlways("dangsan_always");
	}

        return InlineCost::getNever("dangsan_never");
    }


};

char CustomInliner::ID = 0;
static RegisterPass<CustomInliner> X("custominline", "Custom Inliner Pass", true, false);


static void registerInliner(const PassManagerBuilder &,
        legacy::PassManagerBase &PM) {
    PM.add(new CustomInliner());
}
static RegisterStandardPasses RegisterInliner(PassManagerBuilder::EP_OptimizerLast, registerInliner);
static RegisterStandardPasses RegisterInliner0(PassManagerBuilder::EP_EnabledOnOptLevel0, registerInliner);


