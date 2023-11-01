#define DEBUG_TYPE "CCov"

#include <iostream>
#include <vector>

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

namespace {
  class CCov: public FunctionPass {
	public:
	
    	static char ID; // Pass identification, replacement for typeid

		// Fill out.

		CCov() : FunctionPass(ID) {}

		Type *intTy, *ptrTy, *voidTy, *boolTy ; // These variables are to store the type instances for primitive types.
		
		FunctionCallee p_init ; // points to the function instance of _init_.
		FunctionCallee p_probe ; // points to the function instance of _probe_.
		FunctionCallee hcy_test;

		StructType * myStructType;
		ArrayType * myArrayType;
		// auto * myArray;

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
			if (M.getFunction(StringRef("_probe_")) != NULL) {
				errs() << "Error: function _probe_() already exists.\n" ;
				exit(1) ;
			}

			errs() << "Running intwrite pass\n";

			/* store the type instances for primitive types */
			boolTy = Type::getInt1Ty(M.getContext()) ;
			intTy = Type::getInt32Ty(M.getContext()) ;
			ptrTy = Type::getInt8PtrTy(M.getContext()) ;
			voidTy = Type::getVoidTy(M.getContext()) ;

			/* add a new declaration of function _init_ which has no argument */
			FunctionType * fty = FunctionType::get(voidTy, false) ;
			p_init = M.getOrInsertFunction("_init_", fty) ;

			/* add a new declaration of function _probe_ which accept three
			 * arguments (i.e., int, char *, and int) */
			Type * args_types[3] ;
			args_types[0] = intTy ; //Type::getInt32Ty(*ctx) ;
			args_types[1] = ptrTy ; //Type::getInt8PtrTy(*ctx) ;	
			args_types[2] = intTy ; //Type::getInt32Ty(*ctx) ;	
			p_probe = M.getOrInsertFunction("_probe_", 
					FunctionType::get(voidTy, ArrayRef<Type *>(args_types), false)) ;
			
			/* define my own Struct Type 
			* and initiate array of Struct Type to hold the coverage information */
			myStructType = StructType::create(M.getContext(), "struct.myStructType");
			Type * structElements[4];
			structElements[0] = intTy;
			structElements[1] = intTy;
			structElements[2] = intTy;
			structElements[3] = intTy;
			myStructType->setBody(structElements);

			myArrayType = ArrayType::get(myStructType, 10);

			auto myArray = new GlobalVariable(
				M, myArrayType, false,
				GlobalValue::CommonLinkage,
				0, "myArray"
			);
			myArray->setAlignment(llvm::MaybeAlign(16));
			ConstantAggregateZero * const_array = ConstantAggregateZero::get(myArrayType);
			myArray->setInitializer(const_array);

			// test hcy here
			Type * args_types_hcy[1];
			args_types_hcy[0] = intTy;
			hcy_test = M.getOrInsertFunction("_hcy_",
				FunctionType::get(voidTy, ArrayRef<Type *>(args_types_hcy), false));
			Value * idx = ConstantInt::get(intTy, 0, false);
			Value * indices[] = {idx, idx, idx};


			// auto smile = GetElementPtrInst::Create(
			// 	myArrayType, myArray, indices, Twine("")
			// );
			// smile->dump();




			// /* add a global definition of a structure */
			// auto type = intTy;
			// auto x = ConstantInt::get(intTy, 1, false);
			// auto gv = new GlobalVariable(
			// 	M, type, false,
			// 	GlobalValue::CommonLinkage,
			// 	x, "tmp_test"
			// );
			// gv->setAlignment(llvm::MaybeAlign(4));
			// gv->dump();

			// Value * args[1];
			// // args[0] = gv->getOperand(0);
			// args[0] = gv;

			// Type * types[4];
			// types[0] = intTy;
			// types[1] = intTy;
			// types[2] = intTy;
			// types[3] = intTy;

			// Value * inps[4];
			// inps[0] = ConstantInt::get(intTy, 0, false);
			// inps[1] = ConstantInt::get(intTy, 0, false);
			// inps[2] = ConstantInt::get(intTy, 0, false);
			// inps[3] = ConstantInt::get(intTy, 0, false);
			// StructType * st = StructType::create(M.getContext(), "S");
			// st->setBody(types);
			// Constant * insType = M.getOrInsertGlobal("makeS", st);




			// auto nw_gv = new GlobalVariable(
			// 	M, st, false,
			// 	GlobalValue::CommonLinkage,
			// 	inps, "mest"
			// )

			/* add a function call to _init_ at the beginning of 
			 * the main function*/
			Function * mainFunc = M.getFunction(StringRef("main"));
			IRB = new IRBuilder<>(M.getContext());
			if (mainFunc != NULL) {
				IRB->SetInsertPoint(mainFunc->getEntryBlock().getFirstNonPHIOrDbgOrLifetime());
				IRB->CreateCall(p_init, {}) ;
				Value * elementPtr = IRB->CreateGEP(
					myArrayType, myArray, indices, Twine("")
				);
				IRB->CreateStore(
					ConstantInt::get(Type::getInt32Ty(M.getContext()), 8),
					elementPtr
				);
				LoadInst * load = IRB->CreateLoad(intTy, elementPtr);
				IRB->CreateCall(hcy_test, load, Twine(""));
				// IRB->CreateStore(
				// 	idx, 
				// 	GetElementPtrInst::Create(
				// 		myArrayType, myArray, indices, Twine("")
				// 	)
				// );
				// LoadInst * load = IRB->CreateLoad(intTy, gv);
				// args[0] = load;
				// IRB->CreateCall(hcy_test, args, Twine("")) ;
			}



			// Function * mainTest = M.getFunction(StringRef("main"));
			// IRB = new IRBuilder<>(M.getContext());
			// if (mainFunc != NULL) {
			// 	IRB->SetInsertPoint(mainFunc->getEntryBlock().getFirstNonPHIOrDbgOrLifetime());
			// }


			return true ;
		} // doInitialization.

		virtual bool doFinalization(Module &M) {
			/* This function is executed once per target module after
			 * all executions of runOnFunction() under the module. */

			// Fill out.
			M.dump();

			return false ;
		} //doFinalization.

		virtual bool runOnFunction(Function &F) {
			/* This function is invoked once for every function in the target 
			* module by LLVM */

			// Fill out.
			FunctionType * ft = F.getFunctionType();
			ft->dump();


			/* Invoke runOnBasicBlock() for each basic block under F. */
			// for (Function::iterator itr = F.begin() ; itr != F.end() ; itr++) {
			// 	runOnBasicBlock(*itr) ;
			// }

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

			return true ;
		} // runOnBasicBlock.
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