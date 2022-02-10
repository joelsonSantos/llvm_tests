//===----------------------------------------------------------------------===//
//
// Philipp Schubert
//
//    Copyright (c) 2021
//    GaZAR UG (haftungsbeschränkt)
//    Bielefeld, Germany
//    philipp@gazar.eu
//
//===----------------------------------------------------------------------===//

#include <memory>
# include <time.h>
# include <iostream>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

int main(int Argc, char **Argv) {
  clock_t begin = clock();
  if (Argc != 2) {
    llvm::outs() << "usage: <prog> <IR file>\n";
    return 1;
  }
  // Parse an LLVM IR file
  llvm::SMDiagnostic Diag;
  llvm::LLVMContext Ctx;
  std::unique_ptr<llvm::Module> M =
      llvm::parseIRFile(Argv[1], Diag, Ctx); // NOLINT
  // Check if the module is valid
  bool BrokenDbgInfo = false;
  if (llvm::verifyModule(*M, &llvm::errs(), &BrokenDbgInfo)) {
    llvm::errs() << "error: invalid module\n";
    return 1;
  }
  if (BrokenDbgInfo) {
    llvm::errs() << "caution: debug info is broken\n";
  }
  // Iterate the IR and analyze the functions, basic blocks or individual
  // instructions.
  for (const auto &F : *M) {
    llvm::outs() << "found function " << F.getName() << '\n';
    for (const auto &basic_block : F) {
      llvm::outs() << "BasicBlock: " << basic_block.getName() << '\n';
      int count = 0;
      for (const auto &BB : basic_block) {  
          if (const auto *Alloca = llvm::dyn_cast<llvm::AllocaInst>(&BB)) {
          llvm::outs() << "found alloca inst: " << *Alloca << '\n';
          count++;
          }

          if (const auto *Store = llvm::dyn_cast<llvm::StoreInst>(&BB)) {
          llvm::outs() << "found store inst: " << *Store << '\n';
          }

	  if (const auto *Load = llvm::dyn_cast<llvm::LoadInst>(&BB)) {
          llvm::outs() << "found load inst: " << *Load << '\n';
          }

          if (const auto *ICMP = llvm::dyn_cast<llvm::ICmpInst>(&BB)) {
          llvm::outs() << "found icmp inst: " << *ICMP << '\n';
          }
	  
          if (const auto *BR = llvm::dyn_cast<llvm::CallBrInst>(&BB)) {
          llvm::outs() << "found icmp inst: " << *BR << '\n';
          }
       
          if (const auto *CallSite = llvm::dyn_cast<llvm::CallBase>(&BB)) {
          if (const auto *Callee = CallSite->getCalledFunction()) {
            llvm::outs() << "found callee: " << Callee->getName() << '\n';
          } else {
            llvm::outs() << "found indirect callsite: " << *CallSite << '\n';
          }
          }
      }	
     }
     std::cout << count;
     }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time Spent: %f", time_spent);
  return 0;
}
