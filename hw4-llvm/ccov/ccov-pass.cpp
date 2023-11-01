#define DEBUG_TYPE "CCov"

#include <iostream>
#include <fstream>

#include "llvm/IR/DebugInfo.h"
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"

#include "llvm/ADT/Statistic.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"

#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

/* CCov.cpp
 *
 * Currently, it is a 'blank' FunctionPass that gives no effect on the target 
 * program. You can implement your own FunctionPass by writing down your own 
 * code where the comment "Fill out" is.  
 * */

using namespace llvm;
using namespace std;

#define MAX 1000000

namespace {
  class CCov: public FunctionPass {
	public:
	
    	static char ID; // Pass identification, replacement for typeid

		// Fill out.

		CCov() : FunctionPass(ID) {}

		Type *intTy, *ptrTy, *voidTy, *boolTy ; // These variables are to store the type instances for primitive types.
		
		FunctionCallee p_init; // points to the function instance of _init_.
		FunctionCallee p_final; // points to the function instance of _init_.
		FunctionCallee p_probe; // points to the function instance of _probe_.

		int branchCount = -1;
		int branchCondCount[MAX] = {0};
		ofstream of;

		IRBuilder<> * IRB;

		virtual bool doInitialization(Module &M) {
			/* doInitialization() is executed once per target module,
			 * and executed before any invocation of runOnFunction().
			 * This function is for initialization and the module level 
			 * instrumentation (e.g., add functions). */

			// Fill out.
			/* check if there is a function in a target program that conflicts
			 * with the probe functions */			
			if (M.getFunction(StringRef("_init_")) != NULL) {
				errs() << "Error: function _init_() already exists.\n" ;
				exit(1) ;
			}
			if (M.getFunction(StringRef("_final_")) != NULL) {
				errs() << "Error: function _final_() already exists.\n" ;
				exit(1) ;
			}
			if (M.getFunction(StringRef("_probe_")) != NULL) {
				errs() << "Error: function _probe_() already exists.\n" ;
				exit(1) ;
			}

			errs() << "Running intwrite pass\n";

			/* store the type instances for primitive types */
			boolTy = Type::getInt1Ty(M.getContext());
			ptrTy = Type::getInt8PtrTy(M.getContext());
			intTy = Type::getInt32Ty(M.getContext());
			voidTy = Type::getVoidTy(M.getContext());

			/* add a new declaration of function _init_ which has no argument */
			FunctionType * fty = FunctionType::get(voidTy, false);
			p_init = M.getOrInsertFunction("_init_", fty);

			/* add a new declaration of function _init_ which has no argument */
			p_final = M.getOrInsertFunction("_final_", fty);

			/* add a new declaration of function _writeInit_
			 * which accepts 4 arguments (i.e., int, int, int, int)
			 * to write inital coverage data for each found branch as 0
			 */
			Type * args_types[5];
			args_types[0] = intTy;
			args_types[1] = intTy;
			args_types[2] = intTy;
			args_types[3] = intTy;
			args_types[4] = intTy;
			p_probe= M.getOrInsertFunction("_probe_", 
					FunctionType::get(voidTy, ArrayRef<Type *>(args_types), false)) ;
			
			of.open("initCoverage.dat", ios::trunc&ios::in);
			
			/* add a function call to _init_ at the beginning of 
			 * the main function*/
			Function * mainFunc = M.getFunction(StringRef("main"));
			IRB = new IRBuilder<>(M.getContext());
			if (mainFunc != NULL) {
				IRB->SetInsertPoint(mainFunc->getEntryBlock().getFirstNonPHIOrDbgOrLifetime());
				IRB->CreateCall(p_init, {});

				// IRB->SetInsertPoint(mainFunc->back().getTerminator());
				// IRB->CreateCall(p_final, {});
			}

			return true;
		} // doInitialization.

		virtual bool doFinalization(Module &M) {
			/* This function is executed once per target module after
			 * all executions of runOnFunction() under the module. */

			// Fill out.
			// M.dump();
			of.close();

			return false;
		} //doFinalization.

		virtual bool runOnFunction(Function &F) {
			/* This function is invoked once for every function in the target 
			* module by LLVM */

			// Fill out.

			/* Invoke runOnBasicBlock() for each basic block under F. */
			for (Function::iterator itr = F.begin(); itr != F.end(); itr++) {
				runOnBasicBlock(*itr);
			}

			return true;
		} //runOnFunction.

		bool runOnBasicBlock (BasicBlock &B) {
			/* This function is invoked by runOnFunction() for each basic block
			 * in the function. Note that this is not invoked by LLVM and different
			 * from runOnBasicBlock() of BasicBlockPass.*/

			// Fill out.
			StringRef funcname = "unknown";
			DISubprogram * disubp = B.getParent()->getSubprogram();
			if (disubp) {
				funcname = disubp->getName();
			}

			for (BasicBlock::iterator i = B.begin() ; i != B.end() ; i++) {
				/* for each instruction of the basic block in order */

				if (i->getOpcode() == Instruction::Br) {
					BranchInst * br = dyn_cast<BranchInst>(i);

					const DebugLoc &debugloc = br->getDebugLoc();
					int loc = -1;
					if (debugloc) {
						loc = debugloc.getLine();
					}

					if (br->isConditional()) {
						BasicBlock * tDest = br->getSuccessor(0);
						BasicBlock * fDest = br->getSuccessor(1);

						int doWhileFlag = 0;
						for (BasicBlock * pred : predecessors(tDest)) {
							Instruction * termInst = pred->getTerminator();
							if (termInst->getOpcode() == Instruction::Br) {
								BranchInst * termBr = dyn_cast<BranchInst>(termInst);
								if (termBr->isUnconditional()) {
									doWhileFlag = -1;
								}
							}
						}

						// writing initial data to initCoverage.dat
						branchCount++;
						branchCondCount[loc]++;
						writeInitData(branchCount, loc, branchCondCount[loc]-1, doWhileFlag, 0);


						Value * args[5];
						args[0] = ConstantInt::get(intTy, branchCount, false);
						args[1] = ConstantInt::get(intTy, loc, false);
						args[2] = ConstantInt::get(intTy, branchCondCount[loc]-1, false);
						args[3] = ConstantInt::get(intTy, 1, false);
						args[4] = ConstantInt::get(intTy, 0, false);
						IRB->SetInsertPoint(&(tDest->back()));
						IRB->CreateCall(p_probe, args, Twine(""));


						args[3] = ConstantInt::get(intTy, 0, false);
						args[4] = ConstantInt::get(intTy, 1, false);
						IRB->SetInsertPoint(&(fDest->back()));
						IRB->CreateCall(p_probe, args, Twine(""));
					}
				} else if (i->getOpcode() == Instruction::Switch) {
					SwitchInst * sw = dyn_cast<SwitchInst>(i);

					const DebugLoc &debugloc = sw->getDebugLoc();
					int loc = -1;
					if (debugloc) {
						loc = debugloc.getLine();
					}

					int numSucc = sw->getNumSuccessors();

					int j=0;
					// for cases
					for (j=1; j<numSucc; j++) {
						branchCount++;
						branchCondCount[loc]++;
						writeInitData(branchCount, loc, branchCondCount[loc]-1, 0, 0);

						BasicBlock * succDest = sw->getSuccessor(j);

						Value * args[5];
						args[0] = ConstantInt::get(intTy, branchCount, false);
						args[1] = ConstantInt::get(intTy, loc, false);
						args[2] = ConstantInt::get(intTy, branchCondCount[loc]-1, false);
						args[3] = ConstantInt::get(intTy, 1, false);
						args[4] = ConstantInt::get(intTy, 0, false);
						IRB->SetInsertPoint(&(succDest->back()));
						IRB->CreateCall(p_probe, args, Twine(""));
					}

					// for default
					branchCount++;
					branchCondCount[loc]++;
					writeInitData(branchCount, loc, branchCondCount[loc]-1, 0, 0);

					BasicBlock * succDest = sw->getSuccessor(0);

					Value * args[5];
					args[0] = ConstantInt::get(intTy, branchCount, false);
					args[1] = ConstantInt::get(intTy, loc, false);
					args[2] = ConstantInt::get(intTy, branchCondCount[loc]-1, false);
					args[3] = ConstantInt::get(intTy, 1, false);
					args[4] = ConstantInt::get(intTy, 0, false);
					IRB->SetInsertPoint(&(succDest->front()));
					IRB->CreateCall(p_probe, args, Twine(""));
				}
			}

			return true;
		} // runOnBasicBlock.
	
	private:
	    void writeInitData(int idx, int lineNum, int idxNum, int tCnt, int fCnt) {
			// writer branch information
			of << to_string(idx) + "," + to_string(lineNum) + "," + to_string(idxNum) + ",";
			of << to_string(tCnt) + "," + to_string(fCnt) + "\n";
		}
  };
}

/* The code in the remaining part is to register this Pass to
 * LLVM Pass Manager such that LLVM/Clang can use it. */
char CCov::ID = 0;

static RegisterPass<CCov> X("CCov", "CCov Pass", false , false);

static void registerPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {

  PM.add(new CCov());
}

static RegisterStandardPasses
    RegisterPassOpt(PassManagerBuilder::EP_ModuleOptimizerEarly, registerPass);

static RegisterStandardPasses
    RegisterPassO0(PassManagerBuilder::EP_EnabledOnOptLevel0, registerPass);