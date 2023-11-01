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

#define MAX 100000

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
		FunctionCallee hcy_test;

		StructType * myStructType;
		ArrayType * myArrayType;
		// GlobalVariable * branchCount;

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
			
			of.open("test/initCoverage.dat", ios::trunc&ios::in);
			

			/* define my own Struct Type */
			// myStructType = StructType::create(M.getContext(), "struct.myStructType");
			// Type * structElements[4];
			// structElements[0] = intTy;
			// structElements[1] = intTy;
			// structElements[2] = intTy;
			// structElements[3] = intTy;
			// myStructType->setBody(structElements);

			/* initate an array of myStructType as global variable:
			* holds the coverage information for each branch */
			// myArrayType = ArrayType::get(myStructType, MAX);

			// auto myArray = new GlobalVariable(
			// 	M, myArrayType, false,
			// 	GlobalValue::CommonLinkage,
			// 	0, "myArray"
			// );
			// myArray->setAlignment(llvm::MaybeAlign(16));
			// ConstantAggregateZero * const_array = ConstantAggregateZero::get(myArrayType);
			// myArray->setInitializer(const_array);

			/* initate an integer indicating total number of branch */
			// branchCount = new GlobalVariable(
			// 	M, intTy, false,
			// 	GlobalValue::CommonLinkage,
			// 	ConstantInt::get(intTy, 0, false), "branchCount"
			// );
			// branchCount->setAlignment(llvm::MaybeAlign(4));

			// test hcy here
			// Type * args_types_hcy[1];
			// args_types_hcy[0] = myStructType;
			// hcy_test = M.getOrInsertFunction("_hcy_",
			// 	FunctionType::get(voidTy, ArrayRef<Type *>(args_types_hcy), false));
			// Value * idx = ConstantInt::get(intTy, 0, false);
			// Value * indices[] = {idx, idx, idx};

			/* add a function call to _init_ at the beginning of 
			 * the main function*/
			Function * mainFunc = M.getFunction(StringRef("main"));
			IRB = new IRBuilder<>(M.getContext());
			if (mainFunc != NULL) {
				IRB->SetInsertPoint(mainFunc->getEntryBlock().getFirstNonPHIOrDbgOrLifetime());
				IRB->CreateCall(p_init, {});

				IRB->SetInsertPoint(mainFunc->back().getTerminator());
				IRB->CreateCall(p_final, {});

				// Value * elementPtr = IRB->CreateGEP(
				// 	myArrayType, myArray, indices, Twine("")
				// );
				// IRB->CreateStore(
				// 	ConstantInt::get(Type::getInt32Ty(M.getContext()), 87),
				// 	elementPtr
				// );
				// LoadInst * load = IRB->CreateLoad(intTy, elementPtr);
				// IRB->CreateCall(hcy_test, myArray, Twine(""));
			}

			return true;
		} // doInitialization.

		virtual bool doFinalization(Module &M) {
			/* This function is executed once per target module after
			 * all executions of runOnFunction() under the module. */

			// Fill out.
			M.dump();
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
				cout << "=============\n";
			}
			cout << "*****************\n";

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
					cout << i->getOpcodeName() << " - ";

					BranchInst * br = dyn_cast<BranchInst>(i);
					// br->dump();

					const DebugLoc &debugloc = br->getDebugLoc();
					int loc = -1;
					if (debugloc) {
						loc = debugloc.getLine();
					}

					cout << loc << endl;

					if (br->isConditional()) {
						// writing initial data to initCoverage.dat
						br->dump();
						branchCount++;
						branchCondCount[loc]++;
						writeInitData(branchCount, loc, branchCondCount[loc]-1, 0, 0);

						Value * condition = br->getCondition();
						condition->dump();

						BasicBlock * tDest = br->getSuccessor(0);
						BasicBlock * fDest = br->getSuccessor(1);

						Value * args[5];
						args[0] = ConstantInt::get(intTy, branchCount, false);
						args[1] = ConstantInt::get(intTy, loc, false);
						args[2] = ConstantInt::get(intTy, branchCondCount[loc]-1, false);
						args[3] = ConstantInt::get(intTy, 1, false);
						args[4] = ConstantInt::get(intTy, 0, false);
						IRB->SetInsertPoint(&(tDest->front()));
						IRB->CreateCall(p_probe, args, Twine(""));


						args[3] = ConstantInt::get(intTy, 0, false);
						args[4] = ConstantInt::get(intTy, 1, false);
						IRB->SetInsertPoint(&(fDest->front()));
						IRB->CreateCall(p_probe, args, Twine(""));
					}
				}

				// if (i->getOpcode() == Instruction::Store) {
				// 	if (i->getOperand(0)->getType() == intTy) {
				// 		StoreInst * st = dyn_cast<StoreInst>(i) ;

				// 		/* add a function call to _probe_ right before
				// 			* a store instruction on an integer variable. */

				// 		const DebugLoc &debugloc = st->getDebugLoc();

				// 		int loc = -1;
				// 		if (debugloc) {
				// 			loc = debugloc.getLine();
				// 		}

				// 		// Value * var = st->getPointerOperand() ; // the target variable 
				// 		Value * val = st->getOperand(0) ; // the value to be assigned.

				// 		IRB->SetInsertPoint(&(*i));

				// 		Value * args[3] ;
				// 		args[0] = ConstantInt::get(intTy, loc, false) ; // location of store instruction.
				// 		args[1] = IRB->CreateGlobalStringPtr(funcname, "") ; // create a new string constant of the variable name, and get the pointer to it.
				// 		args[2] = val ; // the value to be assigned to the variable.
				// 		IRB->CreateCall(p_probe, args, Twine("")) ;
				// 		continue ;
				// 	}
				// }	
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