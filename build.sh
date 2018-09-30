# install clang, llvm
sudo apt install clang-3.9 libclang-3.9-dev  llvm-3.9 llvm-3.9-dev

# build
clang++-3.9 autoc2.cpp $(llvm-config-3.9 --cxxflags) $(llvm-config-3.9 --ldflags --libs ) -lclangFrontend -lclangFrontendTool  -lclangParse -lclangSema -lclangEdit -lclangRewrite -lclangRewriteFrontend -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangSerialization -lclangFormat -lclangDriver -lclangTooling -lclangToolingCore -lclangAST -lclangLex -lclangAnalysis -lclangBasic

