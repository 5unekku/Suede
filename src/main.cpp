#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

int main(int argc, char** argv) {
  llvm::LLVMContext ctx;
  llvm::Module mod("suede-test", ctx);
  std::cout << "Suede compiler skeleton is alive!\n";
  return 0;
}